/* -----  Application  ----- */
#include "application.h"
#include "sciTinyTimber.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tonegen.h"
#include "instrument.h"
#include "performer.h"
#include "conductor.h"


/* -----  Initialisation  ----- */
void app_sci_interrupt(App* self, int c);
Serial sci = initSerial(SCI_PORT0, &app, app_sci_interrupt);

void app_can_interrupt(App* self, int unused);
Can can = initCan(CAN_PORT0, &app, app_can_interrupt);

struct App {
  Object super;
  int canon; // performer canon multiplier
  int can_read_disable;
};

App app = { initObject(), 0, 0 };

void app_init(App* self, int unused) {
  SCI_INIT(&sci);
  CAN_INIT(&can);

  // init our own objects (all of them!)
  performer_init();
  conductor_init();
}

int main() {
  INSTALL(&sci, sci_interrupt, SCI_IRQ0);
  INSTALL(&can, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, app_init, 0);
  return 0;
}


/* -----  CAN  ----- */
void app_can(App* self, CANMsg* msg) {
  SCI_WRITE(&sci, "Can msg received: ");
  SCI_WRITE(&sci, msg->buff);
  SCI_WRITE(&sci, "\n");

  if (strcmp((char*) msg->buff, "stop") == 0) {
    SYNC(&performer, performer_stop, 0);
  } else if (strcmp((char*) msg->buff, "play") == 0) {
    SYNC(&performer, performer_play, 0);
  } else if (strncmp((char*) msg->buff, "cnn ", 4) == 0) {
    SYNC(&performer, performer_play, atoi((char*) msg->buff + 4));
  } else if (strcmp((char*) msg->buff, "sync") == 0) {
    SYNC(&performer, performer_sync, 0);
  } else if (strncmp((char*) msg->buff, "bpm ", 4) == 0) {
    SYNC(&performer, performer_set_bpm, atoi((char*) msg->buff + 4));
  } else if (strncmp((char*) msg->buff, "key ", 4) == 0) {
    SYNC(&performer, performer_set_key, atoi((char*) msg->buff + 4));
  } else {
    SCI_WRITE(&sci, "Ignored unknown CAN message.\n");
  }
}

void app_can_interrupt(App* self, int unused) {
  CANMsg msg;
  CAN_RECEIVE(&can, &msg);
  if (!self->can_read_disable) {
    app_can(self, &msg);
  }
}

// the CAN node id. completely irrelevant.
const int nodeId = 0;

void app_send_str(App* self, char* text) {
    CANMsg msg;
    msg.msgId = 1;      // unused
    msg.nodeId = nodeId;
    msg.length = 8;
    strcpy((char*) msg.buff, text);

    CAN_SEND(&can, &msg);
    app_can(self, &msg); // loop-back
}


/* -----  SCI  ----- */
void app_sci_interrupt(App* self, int c) {
  static int mode = 0; // leader 1, slave 0
  static int volume = 15;
  static int state = 0; // input bpm 1, input key 2
  static int acc;

  if (state == 0) {
    switch (c) {
      case '0': {
        SCI_WRITE(&sci, "Entered slave mode. Press '1' to switch to leader mode.\n");
        SCI_WRITE(&sci, "Press 'q' and 'w' to decrease and increase the volume, respectively.\n");
        mode = 0;
        self->can_read_disable = 0;
      } break;

      case '1': {
        SCI_WRITE(&sci, "Entered leader mode. Press '0' to switch to slave mode.\n");
        SCI_WRITE(&sci, "Press 'p' to conduct in chorus form, 'c' for 1-bar canon,"
                        " 'd' for 2-bar canon. Press 's' to stop the orchestra. \n");
        SCI_WRITE(&sci, "Press 'b' to input a new tempo. Press 'k' to input a new key.\n");
        SCI_WRITE(&sci, "Press 'q' and 'w' to decrease and increase the volume, respectively.\n");
        mode = 1;
        self->can_read_disable = 1;
      } break;

      case 'q': {
        volume = volume > 0 ? volume - 1 : 0;
        SYNC(&performer, performer_set_volume, volume);
      } break;

      case 'w': {
        volume = volume < 20 ? volume + 1 : 20;
        SYNC(&performer, performer_set_volume, volume);
      } break;

      case 'p': {
        if (mode == 1) {
          SCI_WRITE(&sci, "Conductor: Play!.\n");
          SYNC(&conductor, conductor_conduct, 0);
        } else {
          SCI_WRITE(&sci, "Ignored conductor command.\n");
        }
      } break;

      case 'c': {
        if (mode == 1) {
          SCI_WRITE(&sci, "Conductor: Canon 4!.\n");
          SYNC(&conductor, conductor_canon, 4);
        } else {
          SCI_WRITE(&sci, "Ignored conductor command.\n");
        }
      } break;

      case 'd': {
        if (mode == 1) {
          SCI_WRITE(&sci, "Conductor: Canon 8!.\n");
          SYNC(&conductor, conductor_canon, 8);
        } else {
          SCI_WRITE(&sci, "Ignored conductor command.\n");
        }
      } break;

      case 's': {
        SYNC(&conductor, conductor_stop, 0);
      } break;

      case 'b': {
        SCI_WRITE(&sci, "Enter new bpm: ");
        state = 1;
        acc = 0;
      } break;

      case 'k': {
        SCI_WRITE(&sci, "Enter new key: ");
        state = 2;
        acc = 0;
      } break;
    }
  } else if (state == 1) {
    if (c >= '0' && c <= '9') {
      SCI_WRITECHAR(&sci, c);
      acc = 10 * acc + (c - '0');
    } else if (c == 'e') {
      SCI_WRITE(&sci, "\nUpdating bpm.");
      SYNC(&conductor, conductor_set_bpm, acc);
      state = 0;
    }
  } else if (state == 2) {
    if (c >= '0' && c <= '9') {
      SCI_WRITECHAR(&sci, c);
      acc = 10 * acc + (c - '0');
    } else if (c == '+') {
      SCI_WRITE(&sci, "\nUpdating key.");
      SYNC(&conductor, conductor_set_key, acc);
      state = 0;
    } else if (c == '-') {
      SCI_WRITE(&sci, "\nUpdating key.");
      SYNC(&conductor, conductor_set_key, -acc);
      state = 0;
    }
  }
}

void app_debug(App* self, int c) {
  static int state = -1;
  char buf[80];

  sprintf(buf,"SCI char: %c\n",c);
  SCI_WRITE(&sci, buf);
  if (c >= '0' && c <= '5') {
    state = c - '0';
    SCI_WRITE(&sci, "Changed Mode.\n");
  } else if (state == -1) {
    SCI_WRITE(&sci, "Please select desired mode.\n");
  } else if (state == 0) {
    SYNC(&tonegen, tonegen_debug, c);
  } else if (state == 1) {
    SYNC(&instrument, instrument_debug, c);
  } else if (state == 2) {
    SYNC(&performer, performer_debug, c);
  } else if (state == 3) {
    SYNC(&conductor, conductor_debug, c);
  }
}
