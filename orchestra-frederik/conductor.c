/* -----  CANductor  ----- */
#include "conductor.h"
#include "controller.h"
#include "canTinyTimber.h"
#include "sciTinyTimber.h"

typedef struct {
  Object super;
  Msg call;
  int bpm;
  int key;
} Conductor;

Conductor conductor = { initObject(), NULL, 120, 0 };

extern Can can;
extern Serial sci;

static int conduct_can_debug = 1;

void conductor_conduct(Conductor* self, int unused) {
  // make sure everybody starts with the same tempo
  conductor_set_bpm(self, self->bpm);
  conductor_set_key(self,self->key);
  conductor_send(&app, "play");

  ABORT(this->call);
  // sync at every beat (quarter note)
  this->call = SEND(MSEC((unsigned int) 60000 / self->bpm), USEC(100), self, conductor_sync, 0);
}

// halt and reset the orchestra.
void conductor_stop(Conductor* self, int unused) {
  ABORT(self->call);
  conductor_send(&app, "stop");
}

void conductor_set_bpm(Conductor* self, int bpm) {
  self->bpm = bpm;
  char buf[8];
  sprintf(buf, "bpm %d", bpm);
  conductor_send(&app, buf);
}

void conductor_set_key(Conductor* self, int key) {
  self->key = key;
  char buf[8];
  sprintf(buf, "key %d", k);
  conductor_send(&app, buf);
}


static void conductor_sync(Conductor* self, int unused) {
  conductor_send(&app, "sync");
  this->call = SEND(MSEC((unsigned int) 60000 / self->bpm), USEC(100), self, conductor_sync, 0);
}

static void conductor_send(Conductor* self, char* text) {
    CANMsg msg;
    msg.msgId = 1;      // unused
    msg.nodeId = nodeId;
    msg.length = 8;
    strcpy(msg.buf, text);
    CAN_SEND(&can, &msg);

    if (conduct_can_debug) {
      SCI_WRITE(&sci, "Can msg: ");
      SCI_WRITE(&sci, msg->buff);
      SCI_WRITE(&sci, "\n");
    } else {
      SYNC(&controller, controller_parsemsg, &msg); // loop-back to controller
    }
}

void conductor_control(Conductor*, int c) {
  switch (c) {
    case 'a': if (!conduct_can_debug) {
                SCI_WRITE(&sci, "Conductor CAN debug enabled\n");
                conduct_can_debug = 1;
              } else {
                SCI_WRITE(&sci, "Conductor CAN debug disabled\n");
                conduct_can_debug = 0;
              } break;

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

