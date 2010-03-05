// $Id$
// Copyright (c) 2010 by Brian Blonski
#ifndef _GESTURE_EVENT_H
#define _GESTURE_EVENT_H

#include <stdio.h>

[event_source(native)]
class GestureEvent
{
public:
    __event void gEvent(int nValue);
};

[event_receiver(native)]
class GestureReceiver {
public:
   void gHandler() {
      printf("Event Triggered\n");
   }

   void hookEvent(GestureEvent* source) {
       __hook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
   }

   void unhookEvent(GestureEvent* source) {
       __unhook(&GestureEvent::gEvent, source, &GestureReceiver::gHandler);
   }
};

#endif