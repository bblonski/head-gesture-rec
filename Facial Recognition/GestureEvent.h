// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _GESTURE_EVENT_H
#define _GESTURE_EVENT_H

#include <stdio.h>
#include <windows.h>
#include <process.h>


[event_source(native)]
class GestureEvent
{
public:
    __event void gEvent(void);
};

[event_receiver(native)]
class GestureReceiver {
public:
    virtual void gHandler() {
        printf("Event Triggered\n");
    }

    void hookEvent(GestureEvent* source) {
        __hook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
    }

    void unhookEvent(GestureEvent* source) {
        __unhook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
    }
};

[event_receiver(native)]
class NodReceiver : public GestureReceiver {
public:
    virtual void gHandler() {
        HWND dialog = FindWindow(L"#32770", L"Nod");
        EndDialog(dialog, 0);
    }
};

[event_receiver(native)]
class ShakeReceiver : public GestureReceiver {
public:
    virtual void gHandler() {
        HWND dialog = FindWindow(L"#32770", L"Shake");
        EndDialog(dialog, 0); 
    }
};

#endif