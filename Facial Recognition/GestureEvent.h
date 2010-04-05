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
    static void Thread( void* pParams )
    {
        MessageBox(NULL, L"Nod Triggered", L"Nod", NULL);
    }

    virtual void gHandler() {
        uintptr_t hand = _beginthread( &NodReceiver::Thread, 0, NULL );   
        Sleep(10);
        HWND dialog = FindWindow(L"#32770", L"Nod");
        EndDialog(dialog, 0);
    }
};

[event_receiver(native)]
class ShakeReceiver : public GestureReceiver {
public:
    static void Thread( void* pParams )
    {
        MessageBox(NULL, L"Shake Triggered", L"Shake", NULL);
    }

    virtual void gHandler() {
        _beginthread( &ShakeReceiver::Thread, 0, NULL );   
    }
};

#endif