#include "app.h"
#include "audio.h"
#include "constants.h"
#include "helpers.h"
#include "menu.h"
#include "wav.h"
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
- (void)start_playback:(id)sender;
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

- (void)open_document:(id)sender {
    NSOpenPanel *panel = [NSOpenPanel openPanel];

    [panel beginWithCompletionHandler:^(NSModalResponse result) {
      if (result == NSModalResponseOK) {
          NSURL *file = [[panel URLs] firstObject];
          if (file) {
              // Do things here with the file
          }
      }
    }];
}
- (void)start_playback:(id)sender {
    audio_start(&g_app.audio.output_unit);
}
@end

char *ns_strcat(char *s, const char *append) {
    char *save = s;
    for (; *s; ++s)
        ;
    while ((*s++ = *append++))
        ;
    return save;
}

const char *NSEventModifierFlagsToChar(NSEventModifierFlags modifierFlags) {
    static char result[100];
    result[0] = '\0';
    if ((modifierFlags & NSEventModifierFlagCapsLock) == NSEventModifierFlagCapsLock)
        ns_strcat(result, "CAPSLOCK, ");
    if ((modifierFlags & NSEventModifierFlagShift) == NSEventModifierFlagShift)
        ns_strcat(result, "SHIFT, ");
    if ((modifierFlags & NSEventModifierFlagControl) == NSEventModifierFlagControl)
        ns_strcat(result, "CONTROL, ");
    if ((modifierFlags & NSEventModifierFlagOption) == NSEventModifierFlagOption)
        ns_strcat(result, "OPTION, ");
    if ((modifierFlags & NSEventModifierFlagCommand) == NSEventModifierFlagCommand)
        ns_strcat(result, "COMMAND, ");
    return result;
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

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSApplication *NSApp = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    WindowDelegate *delegate = [[WindowDelegate alloc] init];

    /* MENU*/
    // -----------------------------------------------------------------
    NSMenu     *main_menu     = [[NSMenu alloc] init];
    NSMenuItem *app_menu_item = [[NSMenuItem alloc] init];
    [main_menu addItem:app_menu_item];

    NSMenu *app_menu = [[NSMenu alloc] init];
    [app_menu addItemWithTitle:@"Quit App" action:@selector(terminate:) keyEquivalent:@"q"];
    [app_menu_item setSubmenu:app_menu];

    NSMenuItem *file_menu_item = [[NSMenuItem alloc] init];
    [main_menu addItem:file_menu_item];

    // keyEquivalent
    // Allows to easily assign keyboard shortcuts while adding them to the menu bar
    // -----------------------------------------------------------------
    // keyEquivalent:@"a" = CMD+a,  keyEquivalent:@"A" = CMD+SHIFT+A
    // -----------------------------------------------------------------
    // setKeyEquivalentModifierMask:
    //      NSEventModifierFlagCommand | NSEventModifierFlagOption | NSEventModifierFlagControl
    NSMenu *file_menu = [[NSMenu alloc] initWithTitle:@"File"];
    // CMD+n
    [[file_menu addItemWithTitle:@"New" action:nil
                   keyEquivalent:@"n"] setKeyEquivalentModifierMask:NSEventModifierFlagOption];
    // CMD+SHIFT+O
    [[file_menu addItemWithTitle:@"Load project..." action:@selector(open_document:)
                   keyEquivalent:@"O"] setTarget:delegate];
    [file_menu addItem:[NSMenuItem separatorItem]];
    // CTRL+CMD+S
    [[file_menu addItemWithTitle:@"Save" action:nil keyEquivalent:@"s"]
        setKeyEquivalentModifierMask:NSEventModifierFlagControl | NSEventModifierFlagCommand];

    NSMenuItem *startItem = [file_menu addItemWithTitle:@"Start"
                                                 action:@selector(start_playback:)
                                          keyEquivalent:@"S"];

    [file_menu_item setSubmenu:file_menu];
    [NSApp setMainMenu:main_menu];
    // -----------------------------------------------------------------

    NSWindowStyleMask styleMask = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
                                  NSWindowStyleMaskTitled | NSWindowStyleMaskResizable;

    NSRect    frame  = NSMakeRect(500, 400, 600, 400);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:styleMask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];

    [delegate setWindow:window];
    [window setDelegate:delegate];

    [window makeKeyAndOrderFront:nil];
    [window setIsVisible:YES];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp finishLaunching];

    [pool drain];

    while (running) {
        NSAutoreleasePool *loopPool = [[NSAutoreleasePool alloc] init];

        NSEvent *event = [NSApp nextEventMatchingMask:NSUIntegerMax
                                            untilDate:nil
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];

        if (event) {
            if (event.type == NSEventTypeKeyDown) {
                NSLog(@"EVENT: [%@]) [%s] [%d]",
                      event.charactersIgnoringModifiers,
                      NSEventModifierFlagsToChar(event.modifierFlags),
                      event.keyCode);
            }
            [NSApp sendEvent:event];
        }
        [NSApp updateWindows];

        [loopPool drain];
    }

    audio_stop(&g_app.audio.output_unit);
    audio_destroy(&g_app.audio.output_unit);

    [delegate release];
    [window release];

    return EXIT_SUCCESS;
}
