//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef SAMPLE_UTIL_EVENT_H
#define SAMPLE_UTIL_EVENT_H

#include "keyboard.h"
#include "mouse.h"

class Event
{
  public:
    struct MoveEvent
    {
        int X;
        int Y;
    };

    struct SizeEvent
    {
        int Width;
        int Height;
    };

    struct ScaleEvent
    {
        float X;
        float Y;
    };

    struct KeyEvent
    {
        Key Code;
        int Mods;
        bool Alt;
        bool Control;
        bool Shift;
        bool System;
    };

    struct MouseMoveEvent
    {
        int X;
        int Y;
    };

    struct MouseButtonEvent
    {
        MouseButton Button;
        int Mods;
        int X;
        int Y;
    };

    struct MouseWheelEvent
    {
        int Delta;
    };

    struct ScrollEvent
    {
        double X;
        double Y;
    };

    enum EventType
    {
        EVENT_CLOSED,                 // The window requested to be closed
        EVENT_MOVED,                  // The window has moved
        EVENT_RESIZED,                // The window was resized
        EVENT_LOST_FOCUS,             // The window lost the focus
        EVENT_GAINED_FOCUS,           // The window gained the focus
        EVENT_TEXT_ENTERED,           // A character was entered
        EVENT_KEY_PRESSED,            // A key was pressed
        EVENT_KEY_RELEASED,           // A key was released
        EVENT_KEY_REPEATED,
        EVENT_MOUSE_WHEEL_MOVED,      // The mouse wheel was scrolled
        EVENT_MOUSE_BUTTON_PRESSED,   // A mouse button was pressed
        EVENT_MOUSE_BUTTON_RELEASED,  // A mouse button was released
        EVENT_MOUSE_MOVED,            // The mouse cursor moved
        EVENT_MOUSE_ENTERED,          // The mouse cursor entered the area of the window
        EVENT_MOUSE_LEFT,             // The mouse cursor left the area of the window
        EVENT_TEST,                   // Event for testing purposes
    
        EVENT_MAXIMIZE,
        EVENT_FRAME_BUFFER_RESIZED,
        EVENT_CONTENT_SCALE,
        EVENT_ICONTIFY,
        EVENT_REFRESH,
        EVENT_SCROLL,
        EVENT_CHARACTER,
        
        // Internal key state used for sticky keys
        EVENT_STICK,
    };

    EventType Type;

    union
    {
        MoveEvent Move;                // Move event parameters
        SizeEvent Size;                // Size event parameters
        KeyEvent Key;                  // Key event parameters
        MouseMoveEvent MouseMove;      // Mouse move event parameters
        MouseButtonEvent MouseButton;  // Mouse button event parameters
        MouseWheelEvent MouseWheel;    // Mouse wheel event parameters

        ScaleEvent Scale;
        ScrollEvent Scroll;
    
        bool Maximized;
        bool Iconify;
        unsigned int CodePoint;
    };
};

#endif  // SAMPLE_UTIL_EVENT_H
