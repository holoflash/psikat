#ifndef OBJC_STUFF
#define OBJC_STUFF

#include <objc/message.h>
#include <objc/runtime.h>

// https://github.com/ColleagueRiley/Cocoa-in-Pure-C
#define objc_msgSend_id        ((id (*)(id, SEL))objc_msgSend)
#define objc_msgSend_uint      ((NSUInteger (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void      ((void (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void_id   ((void (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_void_int  ((void (*)(id, SEL, NSInteger))objc_msgSend)
#define objc_msgSend_void_bool ((void (*)(id, SEL, BOOL))objc_msgSend)

typedef CGRect  NSRect;
typedef CGPoint NSPoint;
typedef CGSize  NSSize;

typedef void NSEvent;
typedef void NSString;
typedef void NSWindow;
typedef void NSApplication;

typedef unsigned long NSUInteger;
typedef long          NSInteger;

#define NS_ENUM(type, name)                                                                                          \
    type name;                                                                                                       \
    enum

typedef NS_ENUM(NSUInteger, NSWindowStyleMask) {
    NSWindowStyleMaskBorderless             = 0,
    NSWindowStyleMaskTitled                 = 1 << 0,
    NSWindowStyleMaskClosable               = 1 << 1,
    NSWindowStyleMaskMiniaturizable         = 1 << 2,
    NSWindowStyleMaskResizable              = 1 << 3,
    NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
};

typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    NSBackingStoreRetained    = 0,
    NSBackingStoreNonretained = 1,
    NSBackingStoreBuffered    = 2
};

typedef NS_ENUM(NSUInteger, NSEventType) {
    NSEventTypeLeftMouseDown      = 1,
    NSEventTypeLeftMouseUp        = 2,
    NSEventTypeRightMouseDown     = 3,
    NSEventTypeRightMouseUp       = 4,
    NSEventTypeMouseMoved         = 5,
    NSEventTypeLeftMouseDragged   = 6,
    NSEventTypeRightMouseDragged  = 7,
    NSEventTypeMouseEntered       = 8,
    NSEventTypeMouseExited        = 9,
    NSEventTypeKeyDown            = 10,
    NSEventTypeKeyUp              = 11,
    NSEventTypeFlagsChanged       = 12,
    NSEventTypeAppKitDefined      = 13,
    NSEventTypeSystemDefined      = 14,
    NSEventTypeApplicationDefined = 15,
    NSEventTypePeriodic           = 16,
    NSEventTypeCursorUpdate       = 17,
    NSEventTypeScrollWheel        = 22,
    NSEventTypeTabletPoint        = 23,
    NSEventTypeTabletProximity    = 24,
    NSEventTypeOtherMouseDown     = 25,
    NSEventTypeOtherMouseUp       = 26,
    NSEventTypeOtherMouseDragged  = 27,
};

typedef NS_ENUM(unsigned long long, NSEventMask) {
    NSEventMaskLeftMouseDown      = 1ULL << NSEventTypeLeftMouseDown,
    NSEventMaskLeftMouseUp        = 1ULL << NSEventTypeLeftMouseUp,
    NSEventMaskRightMouseDown     = 1ULL << NSEventTypeRightMouseDown,
    NSEventMaskRightMouseUp       = 1ULL << NSEventTypeRightMouseUp,
    NSEventMaskMouseMoved         = 1ULL << NSEventTypeMouseMoved,
    NSEventMaskLeftMouseDragged   = 1ULL << NSEventTypeLeftMouseDragged,
    NSEventMaskRightMouseDragged  = 1ULL << NSEventTypeRightMouseDragged,
    NSEventMaskMouseEntered       = 1ULL << NSEventTypeMouseEntered,
    NSEventMaskMouseExited        = 1ULL << NSEventTypeMouseExited,
    NSEventMaskKeyDown            = 1ULL << NSEventTypeKeyDown,
    NSEventMaskKeyUp              = 1ULL << NSEventTypeKeyUp,
    NSEventMaskFlagsChanged       = 1ULL << NSEventTypeFlagsChanged,
    NSEventMaskAppKitDefined      = 1ULL << NSEventTypeAppKitDefined,
    NSEventMaskSystemDefined      = 1ULL << NSEventTypeSystemDefined,
    NSEventMaskApplicationDefined = 1ULL << NSEventTypeApplicationDefined,
    NSEventMaskPeriodic           = 1ULL << NSEventTypePeriodic,
    NSEventMaskCursorUpdate       = 1ULL << NSEventTypeCursorUpdate,
    NSEventMaskScrollWheel        = 1ULL << NSEventTypeScrollWheel,
    NSEventMaskTabletPoint        = 1ULL << NSEventTypeTabletPoint,
    NSEventMaskTabletProximity    = 1ULL << NSEventTypeTabletProximity,
    NSEventMaskOtherMouseDown     = 1ULL << NSEventTypeOtherMouseDown,
    NSEventMaskOtherMouseUp       = 1ULL << NSEventTypeOtherMouseUp,
    NSEventMaskOtherMouseDragged  = 1ULL << NSEventTypeOtherMouseDragged,
};

typedef NS_ENUM(NSUInteger, NSEventModifierFlags) {
    NSEventModifierFlagCapsLock   = 1 << 16,
    NSEventModifierFlagShift      = 1 << 17,
    NSEventModifierFlagControl    = 1 << 18,
    NSEventModifierFlagOption     = 1 << 19,
    NSEventModifierFlagCommand    = 1 << 20,
    NSEventModifierFlagNumericPad = 1 << 21,
    NSEventModifierFlagHelp       = 1 << 22,
    NSEventModifierFlagFunction   = 1 << 23,
};

typedef enum NSApplicationActivationPolicy {
    NSApplicationActivationPolicyRegular,
    NSApplicationActivationPolicyAccessory,
    NSApplicationActivationPolicyProhibited
} NSApplicationActivationPolicy;

#define NSAlloc(nsclass)   objc_msgSend_id((id)nsclass, sel_registerName("alloc"))
#define NSRelease(nsclass) objc_msgSend_id((id)nsclass, sel_registerName("release"))

#endif
