/* -----  Main / Initialisation  ----- */
#include "application.h"
#include "sciTinyTimber.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tonegen.h"
#include "instrument.h"
#include "performer.h"
#include "conductor.h"

// performer offset in bars
int canon = 0;

// todo: add bpm, volume state...
struct App {
  Object super;
};

App app = { initObject() };

void app_sci_interrupt(App* self, int c);
Serial sci = initSerial(SCI_PORT0, &app, app_sci_interrupt);


void app_can_interrupt(App* self, int unused);
Can can = initCan(CAN_PORT0, &app, app_can_interrupt);

void app_sci_interrupt(App* self, int c) {
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

void app_can_interrupt(App* self, int unused) {
  CANMsg msg;
  CAN_RECEIVE(&can, &msg);
  app_can(self, &msg);
}

void app_can(App* self, CANMsg* msg) {
  SCI_WRITE(&sci, "Can msg received: ");
  SCI_WRITE(&sci, msg->buff);
  SCI_WRITE(&sci, "\n");

  if (strcmp((char*) msg->buff, "stop") == 0) {
    SYNC(&performer, performer_stop, 0);
  } else if (strcmp((char*) msg->buff, "play") == 0) {
    SYNC(&performer, performer_play, canon * 8);
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

/* SCI still controls volume and key of performer, rest is done by conductor
void controller_keyboard(App* self, int c) {
  if (c >= 'a' && c <= 'a' + 20) {
    SYNC(&performer, performer_set_volume, c - 'a');

    char buf[80];
    sprintf(buf,"Set volume to %d\n", c - 'a');
    SCI_WRITE(&sci, buf);
  } else {
    SCI_WRITE(&sci, "Ignored unknown keyboad input.\n");
  }
}
*/

void app_init(App* self, int unused) {
  SCI_INIT(&sci);
  CAN_INIT(&can);

  // init our own objects (all of them!)
  performer_init();
  conductor_init();

  SCI_WRITE(&sci, "Select: 0 -> Tonegen, 1 -> Instrument, 2 -> Performer, 3 -> Conductor.\n");
}

int main() {
  INSTALL(&sci, sci_interrupt, SCI_IRQ0);
  INSTALL(&can, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, app_init, 0);
}

