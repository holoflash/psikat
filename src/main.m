#import "Graphics.h"
#include "app.h"
#include "audio.h"
#include "constants.h"
#include "helpers.h"
#import <Cocoa/Cocoa.h>
#include <math.h>
#include <stdlib.h>

App  g_app;
bool running = true;

@interface WindowDelegate : NSObject <NSWindowDelegate> {
    NSWindow *windowRef;
}
- (void)setWindow:(NSWindow *)win;
- (void)open_document:(id)sender;
- (NSMenu *)create_menu;
@end

@implementation WindowDelegate
- (void)setWindow:(NSWindow *)win {
    windowRef = win;
}

- (BOOL)windowShouldClose:(id)sender {
    (void)sender;
    running = false;
    return YES;
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize {
    (void)sender;
    printf("window resized to %f %f\n", frameSize.width, frameSize.height);
    return frameSize;
}

- (NSMenu *)create_menu {
    NSMenu *main_menu = [[NSMenu alloc] init];

    NSMenuItem *app_menu_item = [[NSMenuItem alloc] init];
    [main_menu addItem:app_menu_item];

    NSMenu *app_menu = [[NSMenu alloc] init];
    [app_menu addItemWithTitle:@"Quit App" action:@selector(terminate:) keyEquivalent:@"q"];
    [app_menu_item setSubmenu:app_menu];

    NSMenuItem *file_menu_item = [[NSMenuItem alloc] init];
    [main_menu addItem:file_menu_item];

    NSMenu *file_menu = [[NSMenu alloc] initWithTitle:@"File"];
    // CMD+n
    [[file_menu addItemWithTitle:@"New" action:nil
                   keyEquivalent:@"n"] setKeyEquivalentModifierMask:NSEventModifierFlagOption];
    // CMD+SHIFT+O
    [[file_menu addItemWithTitle:@"Load project..." action:@selector(open_document:)
                   keyEquivalent:@"O"] setTarget:self];

    [file_menu addItem:[NSMenuItem separatorItem]];
    // CTRL+CMD+S
    [[file_menu addItemWithTitle:@"Save" action:nil keyEquivalent:@"s"]
        setKeyEquivalentModifierMask:NSEventModifierFlagControl | NSEventModifierFlagCommand];

    [file_menu_item setSubmenu:file_menu];
    return main_menu;
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

void handle_key_down(int key_code) {
    switch (key_code) {
    case KEY_ENTER:
        g_app.transport.curr_note_index = 0;
        g_app.transport.sample_count    = 0;
        g_app.transport.phase           = 0.0;

        if (g_app.transport.playback_state == STOPPED || g_app.transport.playback_state == PAUSED) {
            g_app.transport.playback_state = PLAYING;
            audio_start(&g_app.audio.output_unit);

        } else {
            g_app.transport.playback_state = STOPPED;
        }
        break;
    case KEY_SPACE:
        g_app.transport.sample_count = 0;
        if (g_app.transport.playback_state == PLAYING) {
            g_app.transport.playback_state = PAUSED;
            audio_stop(&g_app.audio.output_unit);
        } else {
            g_app.transport.playback_state = PLAYING;
            audio_start(&g_app.audio.output_unit);
        }
        break;
    }
}

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

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSApplication *NSApp = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    WindowDelegate *delegate = [[WindowDelegate alloc] init];

    [NSApp setMainMenu:[delegate create_menu]];

    Graphics *graphics = [[Graphics alloc] init];

    NSWindowStyleMask style_mask =
        NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskTitled;

    NSRect    frame  = NSMakeRect(500, 400, 600, 400);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:style_mask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];

    [delegate setWindow:window];

    [window setDelegate:delegate];
    [window makeKeyAndOrderFront:nil];
    [window setIsVisible:YES];
    [window setTitle:@"psikat"];
    [window setContentView:graphics];
    [window setFrame:[[NSScreen mainScreen] visibleFrame] display:YES];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp finishLaunching];

    [pool drain];

    while (running) {
        // May only want to call this when updates are needed?
        // [graphics setNeedsDisplay:YES];
        if (g_app.transport.playback_state == STOPPED) {
            audio_stop(&g_app.audio.output_unit);
        }
        NSAutoreleasePool *loopPool = [[NSAutoreleasePool alloc] init];

        NSEvent *event = [NSApp nextEventMatchingMask:NSUIntegerMax
                                            untilDate:nil
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];

        if (event) {
            // Will want to handle NSEventTypeKeyUp later on
            if (event.type == NSEventTypeKeyDown) {
                handle_key_down(event.keyCode);
                // NSLog(@"EVENT: [%@]) [%s] [%d]",
                //       event.charactersIgnoringModifiers,
                //       NSEventModifierFlagsToChar(event.modifierFlags),
                //       event.keyCode);
            } else {
                [NSApp sendEvent:event];
            }
        }
        [NSApp updateWindows];

        [loopPool drain];
    }

    app_destroy();
    [delegate release];
    [window release];

    return EXIT_SUCCESS;
}
