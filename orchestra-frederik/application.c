/* -----  Main / Initialisation  ----- */
// pipe sci input to conductor or performer

#include "TinyTimber.h"
#include "sciTinyTimber.h"
#include "canTinyTimber.h"

#include <stdio.h>
#include <stdlib.h>

#include "tonegen.h"
#include "instrument.h"
#include "performer.h"
#include "controller.h"
#include "conductor.h"

// todo: add bpm, volume state...
typedef struct {
  Object super;
} App;

App app = { initObject() };

Serial sci = initSerial(SCI_PORT0, &app, app_sci);
Can can = initCan(CAN_PORT0, &app, app_can);

// Keyboard control
void app_sci(App* self, int c) {
  char buf[80];

  sprintf(buf,"SCI char: %c\n");
  SCI_WRITE(&sci, buf);

  if (c < 'n') { // todo: control conductor explicitely
    SYNC(&conductor, conductor_control, c);
  } else {       // todo: control controller explicitely
    SYNC(&controller, controller_keyboard, c);
  }
}

void app_can(App* self, int unused) {
  CANMsg msg;
  CAN_RECEIVE(&can, &msg);
  SYNC(&controller, controller_CAN, &msg);
}

// optional: make all inits runtime
int app_init(App* self, int unused) {
  SCI_INIT(&sci);
  CAN_INIT(&can);
  TONEGEN_INIT(&tonegen);
  INSTRUMENT_INIT(&instrument);
  PERFORMER_INIT(&performer);
  CONTROLLER_INIT(&controller);
  CONDUCTOR_INIT(&conductor);
}

int main() {
  INSTALL(&sci, sci_interrupt, SCI_IRQ0);
  INSTALL(&can0, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, app_init, 0);
}

