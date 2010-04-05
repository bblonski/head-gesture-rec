// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _GESTURE_EVENT_H
#define _GESTURE_EVENT_H

#include <stdio.h>
#include <windows.h>

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
      //LPCWSTR note = "Nod Triggered";
      MessageBox(NULL, L"Nod Triggered", L"Nod", NULL);
   }

   void hookEvent(GestureEvent* source) {
       __hook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
   }

   void unhookEvent(GestureEvent* source) {
       __unhook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
   }
};

#endif