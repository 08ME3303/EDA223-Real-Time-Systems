/* -----  CANductor  ----- */
#include "TinyTimber.h"
#include "conductor.h"
#include "application.h"
#include "canTinyTimber.h"
#include "sciTinyTimber.h"

#include <stdio.h>
#include <string.h>

// the CAN node id. completely irrelevant.
const int nodeId = 0;

struct Conductor {
  Object super;
  Msg call;
  int bpm;
  int key;
};

Conductor conductor;

void conductor_init() {
  conductor = (Conductor) { initObject(), NULL, 120, 0 };
}

extern Can can;
extern Serial sci;


static void conductor_sync(Conductor* self, int unused);
static void conductor_send(Conductor* self, char* text);

void conductor_conduct(Conductor* self, int unused) {
  // make sure everybody starts with the same tempo
  conductor_set_bpm(self, self->bpm);
  conductor_set_key(self,self->key);
  conductor_send(self, "play");

  ABORT(self->call);
  // sync at every beat (quarter note)
  self->call = SEND(MSEC(((unsigned int) 60000 / self->bpm) * 4),
                 USEC(100), self, conductor_sync, 0);
}

// halt and reset the orchestra.
void conductor_stop(Conductor* self, int unused) {
  ABORT(self->call);
  self->call = NULL;  // fix the ABORT bug
  conductor_send(self, "stop");
}

void conductor_set_bpm(Conductor* self, int bpm) {
  self->bpm = bpm;
  char buf[8];
  sprintf(buf, "bpm %d", bpm);
  conductor_send(self, buf);
}

void conductor_set_key(Conductor* self, int key) {
  self->key = key;
  char buf[8];
  sprintf(buf, "key %d", key);
  conductor_send(self, buf);
}

static void conductor_sync(Conductor* self, int unused) {
  conductor_send(self, "sync");
  self->call = SEND(MSEC(((unsigned int) 60000 / self->bpm) * 4),
                 USEC(100), self, conductor_sync, 0);
}

static void conductor_send(Conductor* self, char* text) {
    CANMsg msg;
    msg.msgId = 1;      // unused
    msg.nodeId = nodeId;
    msg.length = 8;
    strcpy((char*) msg.buff, text);

    CAN_SEND(&can, &msg); // remove this when using the physical loopback cable
    SYNC(&app, app_can, &msg); // loop-back to controller
}

void conductor_debug(Conductor* self, int c) {
  switch (c) {
    // case 'a': conductor_init(); break;

    case 'b': conductor_conduct(self,0); break;
    case 'c': conductor_stop(self,0); break;

    case 'd': conductor_set_key(self,-3); break;
    case 'e': conductor_set_key(self,0); break;
    case 'f': conductor_set_key(self,3); break;

    case 'g': conductor_set_bpm(self,60); break;
    case 'h': conductor_set_bpm(self,90); break;
    case 'i': conductor_set_bpm(self,120); break;
    case 'j': conductor_set_bpm(self,150); break;
    case 'k': conductor_set_bpm(self,240); break;
    default: SCI_WRITE(&sci, "Ignored unknown keyboad input.\n");
  }
}

