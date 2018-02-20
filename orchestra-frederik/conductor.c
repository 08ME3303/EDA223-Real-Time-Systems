/* -----  CANductor  ----- */
#include "conductor.h"
#include "application.h"

#include <stdio.h>

struct Conductor {
  Object super;
  Msg call;
  Time syncperiod;
};

Conductor conductor;

void conductor_init() {
  conductor = (Conductor) { initObject(), NULL, MSEC(((unsigned int) 60000 / 120) * 4) };
}

static void conductor_sync(Conductor* self, int unused);

void conductor_conduct(Conductor* self, int unused) {
  // make sure everybody starts with the same tempo
  conductor_set_bpm(self, 120);
  conductor_set_key(self,0);
  can_send_str(&can, "play");

  ABORT(self->call);
  // sync at every beat (quarter note)
  self->call = SEND(self->syncperiod, USEC(100), self, conductor_sync, 0);
}

void conductor_canon(Conductor* self, int step) {
  // make sure everybody starts with the same tempo
  conductor_set_bpm(self, 120);
  conductor_set_key(self,0);
  
  char buf[8];
  sprintf(buf, "cnn %d", step);
  can_send_str(&can, buf);

  ABORT(self->call);
  // sync at every beat (quarter note)
  self->call = SEND(self->syncperiod, USEC(100), self, conductor_sync, 0);
}

// halt and reset the orchestra.
void conductor_stop(Conductor* self, int unused) {
  ABORT(self->call);
  self->call = NULL;  // fix the ABORT bug
  can_send_str(&can, "stop");
}

void conductor_set_bpm(Conductor* self, int bpm) {
  self->syncperiod = MSEC(((unsigned int) 60000 / bpm) * 4);
  char buf[8];
  sprintf(buf, "bpm %d", bpm);
  can_send_str(&can, buf);
}

void conductor_set_key(Conductor* self, int key) {
  char buf[8];
  sprintf(buf, "key %d", key);
  can_send_str(&can, buf);
}

static void conductor_sync(Conductor* self, int unused) {
  can_send_str(&can, "sync");
  self->call = SEND(self->syncperiod, USEC(100), self, conductor_sync, 0);
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

