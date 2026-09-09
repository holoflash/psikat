#include "app.h"
#include "audio.h"
#include "constants.h"
#include "helpers.h"
#include "objc_stuff.h"
#include "wav.h"
#include <ApplicationServices/ApplicationServices.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreVideo/CVDisplayLink.h>
#include <math.h>
#include <objc/message.h>
#include <objc/runtime.h>
#include <stdlib.h>

// https://github.com/ColleagueRiley/Cocoa-in-Pure-C
bool         running = true;
unsigned int onClose(void *self) {
    NSWindow *win = NULL;
    object_getInstanceVariable(self, "NSWindow", (void *)&win);
    if (win == NULL)
        return true;

    running = false;

    return true;
}

NSSize windowResize(void *self, SEL sel, NSSize frameSize) {
    NSWindow *win = NULL;
    object_getInstanceVariable(self, "NSWindow", (void *)&win);
    if (win == NULL)
        return frameSize;

    printf("window resized to %f %f\n", frameSize.width, frameSize.height);
    return frameSize;
}

const char *NSEventTypeToChar(NSEventType eventType) {
    switch (eventType) {
    case NSEventTypeLeftMouseDown:
        return "LeftMouseDown";
    case NSEventTypeLeftMouseUp:
        return "LeftMouseUp";
    case NSEventTypeRightMouseDown:
        return "RightMouseDown";
    case NSEventTypeRightMouseUp:
        return "RightMouseUp";
    case NSEventTypeMouseMoved:
        return "MouseMoved";
    case NSEventTypeLeftMouseDragged:
        return "LeftMouseDragged";
    case NSEventTypeRightMouseDragged:
        return "RightMouseDragged";
    case NSEventTypeMouseEntered:
        return "MouseEntered";
    case NSEventTypeMouseExited:
        return "MouseExited";
    case NSEventTypeKeyDown:
        return "KeyDown";
    case NSEventTypeKeyUp:
        return "KeyUp";
    case NSEventTypeFlagsChanged:
        return "FlagsChanged";
    case NSEventTypeAppKitDefined:
        return "AppKitDefined";
    case NSEventTypeSystemDefined:
        return "SystemDefined";
    case NSEventTypeApplicationDefined:
        return "ApplicationDefined";
    case NSEventTypePeriodic:
        return "Periodic";
    case NSEventTypeCursorUpdate:
        return "CursorUpdate";
    case NSEventTypeScrollWheel:
        return "ScrollWheel";
    case NSEventTypeTabletPoint:
        return "TabletPoint";
    case NSEventTypeTabletProximity:
        return "TabletProximity";
    case NSEventTypeOtherMouseDown:
        return "OtherMouseDown";
    case NSEventTypeOtherMouseUp:
        return "OtherMouseUp";
    case NSEventTypeOtherMouseDragged:
        return "OtherMouseDragged";
    default:
        return "N/A";
    }
}

char *ns_strcat(register char *s, register const char *append) {
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
        ns_strcat(result, "CapsLock, ");
    if ((modifierFlags & NSEventModifierFlagShift) == NSEventModifierFlagShift)
        ns_strcat(result, "NShift, ");
    if ((modifierFlags & NSEventModifierFlagControl) == NSEventModifierFlagControl)
        ns_strcat(result, "Control, ");
    if ((modifierFlags & NSEventModifierFlagOption) == NSEventModifierFlagOption)
        ns_strcat(result, "Option, ");
    if ((modifierFlags & NSEventModifierFlagCommand) == NSEventModifierFlagCommand)
        ns_strcat(result, "Command, ");
    if ((modifierFlags & NSEventModifierFlagNumericPad) == NSEventModifierFlagNumericPad)
        ns_strcat(result, "NumericPad, ");
    if ((modifierFlags & NSEventModifierFlagHelp) == NSEventModifierFlagHelp)
        ns_strcat(result, "Help, ");
    if ((modifierFlags & NSEventModifierFlagFunction) == NSEventModifierFlagFunction)
        ns_strcat(result, "Function, ");

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
    class_addMethod(objc_getClass("NSObject"), sel_registerName("windowShouldClose:"), (IMP)onClose, 0);

    NSApplication *NSApp = objc_msgSend_id((id)objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
    objc_msgSend_void_int(NSApp, sel_registerName("setActivationPolicy:"), NSApplicationActivationPolicyRegular);

    NSBackingStoreType macArgs = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
                                 NSBackingStoreBuffered | NSWindowStyleMaskTitled | NSWindowStyleMaskResizable;

    SEL func = sel_registerName("initWithContentRect:styleMask:backing:defer:");

    NSWindow *window = ((id (*)(id, SEL, NSRect, NSWindowStyleMask, NSBackingStoreType, bool))objc_msgSend)(
        NSAlloc(objc_getClass("NSWindow")),
        func,
        (NSRect){
            {200, 200},
            {200, 200}
    },
        macArgs,
        macArgs,
        false);

    Class delegateClass = objc_allocateClassPair(objc_getClass("NSObject"), "WindowDelegate", 0);

    class_addIvar(delegateClass, "NSWindow", sizeof(NSWindow *), rint(log2(sizeof(NSWindow *))), "L");

    class_addMethod(
        delegateClass, sel_registerName("windowWillResize:toSize:"), (IMP)windowResize, "{NSSize=ff}@:{NSSize=ff}");

    id delegate = objc_msgSend_id(NSAlloc(delegateClass), sel_registerName("init"));

    object_setInstanceVariable(delegate, "NSWindow", window);

    objc_msgSend_void_id(window, sel_registerName("setDelegate:"), delegate);

    objc_msgSend_void_bool(NSApp, sel_registerName("activateIgnoringOtherApps:"), true);
    ((id (*)(id, SEL, SEL))objc_msgSend)(window, sel_registerName("makeKeyAndOrderFront:"), NULL);
    objc_msgSend_void_bool(window, sel_registerName("setIsVisible:"), true);

    objc_msgSend_void(NSApp, sel_registerName("finishLaunching"));

    // TODO: here while debugging
    // wav_hello_world();
    // return 0;
    //___________________________
    static App app;
    app.project = (Project){
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

    app.transport.playback_state  = STOPPED;
    app.transport.curr_note_index = 0;
    app.transport.phase           = 0.0;
    app.transport.sample_count    = 0.0;
    app.transport.master_volume   = 0.1;

    app.audio.sample_rate = 48000.0;

    audio_init(&app.audio.output_unit, &app);
    audio_start(&app.audio.output_unit);

    while (running) {
        id pool = objc_msgSend_id(NSAlloc(objc_getClass("NSAutoreleasePool")), sel_registerName("init"));

        NSEvent *e = (NSEvent *)((id (*)(id, SEL, NSEventMask, void *, NSString *, bool))objc_msgSend)(
            NSApp,
            sel_registerName("nextEventMatchingMask:untilDate:inMode:dequeue:"),
            ULONG_MAX,
            NULL,
            ((id (*)(id, SEL, const char *))objc_msgSend)(
                (id)objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), "kCFRunLoopDefaultMode"),
            true);

        unsigned int type = objc_msgSend_uint(e, sel_registerName("type"));

        NSPoint p = ((NSPoint (*)(id, SEL))objc_msgSend)(e, sel_registerName("locationInWindow"));

        if (type != 0)
            printf("Event [type=%s location={%f, %f} modifierFlags={%s}]\n",
                   NSEventTypeToChar(type),
                   p.x,
                   p.y,
                   NSEventModifierFlagsToChar(objc_msgSend_uint(e, sel_registerName("modifierFlags"))));

        objc_msgSend_void_id(NSApp, sel_registerName("sendEvent:"), e);
        ((void (*)(id, SEL))objc_msgSend)(NSApp, sel_registerName("updateWindows"));

        NSRelease(pool);
    }
    if (!running) {
        audio_stop(&app.audio.output_unit);
        audio_destroy(&app.audio.output_unit);
        return EXIT_SUCCESS;
    }
}
