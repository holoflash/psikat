#include "audio.h"
#include "constants.h"
#include "font.h"
#include "helpers.h"
#include "key_handler.h"
#include "ui_strings.h"
#import <Cocoa/Cocoa.h>
#include <math.h>
#include <stdlib.h>

App            g_app;
static NSView *g_graphics = nil;

void request_redraw(void) {
    if (g_graphics) {
        dispatch_async(dispatch_get_main_queue(), ^{
          [g_graphics setNeedsDisplay:YES];
        });
    }
}

void render_graphics(CGContextRef ctx, CGSize bounds) {
    CGContextSetRGBFillColor(ctx, COLOR_BG);
    CGContextFillRect(ctx, CGRectMake(0, 0, bounds.width, bounds.height));

    draw_psk_string(ctx, &UI_STR_ALPHABET_UPPER, (Vec2){bounds.width, bounds.height});
    draw_psk_string(ctx, &UI_STR_ALPHABET_LOWER, (Vec2){bounds.width, bounds.height - 96});
}

@interface Window : NSWindow
@end

@implementation Window
- (void)sendEvent:(NSEvent *)event {
    if (event.type == NSEventTypeKeyDown) {
        handle_key_down(&g_app, event.keyCode);
        return;
    }
    [super sendEvent:event];
}
@end

@interface Graphics : NSView
@end

@implementation Graphics
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

    render_graphics(ctx, self.bounds.size);
}
@end

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property(strong) Window *window;
@end

@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // MENU
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSMenu     *main_menu     = [NSMenu new];
    NSMenuItem *app_menu_item = [NSMenuItem new];
    NSMenu     *app_menu      = [NSMenu new];
    [app_menu addItemWithTitle:@"Quit psikat" action:@selector(terminate:) keyEquivalent:@"q"];
    [app_menu_item setSubmenu:app_menu];
    [main_menu addItem:app_menu_item];

    NSMenuItem *file_menu_item = [NSMenuItem new];
    NSMenu     *file_menu      = [[NSMenu alloc] initWithTitle:@"File"];

    [[file_menu addItemWithTitle:@"New" action:nil
                   keyEquivalent:@"n"] setKeyEquivalentModifierMask:NSEventModifierFlagOption];
    [[file_menu addItemWithTitle:@"Load project..."
                          action:@selector(open_document:)
                   keyEquivalent:@"O"] setTarget:self];
    [file_menu addItem:[NSMenuItem separatorItem]];

    [[file_menu addItemWithTitle:@"Save" action:nil keyEquivalent:@"s"]
        setKeyEquivalentModifierMask:NSEventModifierFlagControl | NSEventModifierFlagCommand];

    [file_menu_item setSubmenu:file_menu];
    [main_menu addItem:file_menu_item];

    [NSApp setMainMenu:main_menu];

    // WINDOW
    self.window =
        [[Window alloc] initWithContentRect:NSZeroRect
                                  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                                            NSWindowStyleMaskMiniaturizable
                                    backing:NSBackingStoreBuffered
                                      defer:NO];

    Graphics *graphics = [Graphics new];
    g_graphics         = graphics;

    [self.window setContentView:graphics];
    [self.window setTitle:@"psikat"];
    [self.window setFrame:[[NSScreen mainScreen] visibleFrame] display:YES];
    [self.window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

- (void)open_document:(id)sender {
    NSOpenPanel *panel = [NSOpenPanel openPanel];

    [panel beginWithCompletionHandler:^(NSModalResponse result) {
      if (result == NSModalResponseOK) {
          NSURL *file = [[panel URLs] firstObject];
          if (file) {
              // Do things here with the file
              NSLog(@"%@", file.path);
          }
      }
    }];
}
@end

void app_init(void) {
    g_app.project = (Project){
        .pattern_len = 16,
        .bpm         = 100,
        .tuning      = 440.0,
        .duration    = 0.0,
        .pattern =
            {
                {57, 16.0, SQUARE},
                {60, 16.0, SQUARE},
                {64, 16.0, SQUARE},
                {68, 16.0, SQUARE},
                {69, 16.0, SQUARE},
                {72, 16.0, SQUARE},
                {76, 16.0, SQUARE},
                {80, 16.0, SQUARE},
                {81, 16.0, SQUARE},
                {80, 16.0, SQUARE},
                {76, 16.0, SQUARE},
                {72, 16.0, SQUARE},
                {69, 16.0, SQUARE},
                {68, 16.0, SQUARE},
                {64, 16.0, SQUARE},
                {60, 16.0, SQUARE},
            },
    };

    g_app.transport.playback_state  = STOPPED;
    g_app.transport.curr_note_index = 0;
    g_app.transport.phase           = 0.0;
    g_app.transport.sample_count    = 0.0;
    g_app.transport.master_volume   = 0.1;
    g_app.audio.sample_rate         = 48000.0;

    audio_init(&g_app.audio.output_unit, &g_app);
}

void app_destroy(void) {
    audio_stop(&g_app.audio.output_unit);
    audio_destroy(&g_app.audio.output_unit);
}

//    ▄███████▄    ▄████████  ▄█     ▄█   ▄█▄    ▄████████     ███
//   ███    ███   ███    ███ ███    ███ ▄███▀   ███    ███ ▀█████████▄
//   ███    ███   ███    █▀  ███▌   ███▐██▀     ███    ███    ▀███▀▀██
//   ███    ███   ███        ███▌  ▄█████▀      ███    ███     ███   ▀
// ▀█████████▀  ▀███████████ ███▌ ▀▀█████▄    ▀███████████     ███
//   ███                 ███ ███    ███▐██▄     ███    ███     ███
//   ███           ▄█    ███ ███    ███ ▀███▄   ███    ███     ███
//  ▄████▀       ▄████████▀  █▀     ███   ▀█▀   ███    █▀     ▄████▀
//                                  ▀
int main(void) {
    app_init();

    NSApplication *app      = [NSApplication sharedApplication];
    AppDelegate   *delegate = [AppDelegate new];
    app.delegate            = delegate;
    [app run];

    app_destroy();
    return EXIT_SUCCESS;
}
