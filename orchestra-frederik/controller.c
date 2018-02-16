/* -----  Controller  ----- */
#include "controller.h"
#include "sciTinyTimber.h"

#include <stdlib.h>

struct Controller {
  Object super;
};

Controller controller = { initObject() };

extern Sci sci;

void controller_CAN(Controller* self, CANMsg* msg) {
  SCI_WRITE(&sci, "Can msg received: ");
  SCI_WRITE(&sci, msg->buff);
  SCI_WRITE(&sci, "\n");

  if (strcmp(msg->buff, "stop") == 0) {
    SYNC(&performer, performer_stop, 0);
  } else if (strcmp(msg->buff, "play") == 0) {
    SYNC(&performer, performer_play, nodeId * 8 * 2);
  } else if (strcmp(msg->buff, "sync") == 0) {
    SYNC(&performer, performer_sync, 0);
  } else if (strncmp(msg->buff, "bpm ", 4) == 0) {
    SYNC(&performer, performer_set_bpm, atoi(msg->buff + 4););
  } else if (strncmp(msg->buff, "key ", 4) == 0) {
    SYNC(&performer, performer_set_key, atoi(msg->buff + 4););
  } else {
    SCI_WRITE(&sci, "Ignored unknown CAN message.\n");
  }
}

void controller_keyboard(Controller* self, int c) {
  if (c >= 'a' && c <= 'a' + 20) {
    SYNC(&performer, performer_set_volume, c - 'a');

    char buf[80];
    sprintf(buf,"Set volume to %d\n", c - 'a');
    SCI_WRITE(&sci, buf);
  } else {
    SCI_WRITE(&sci, "Ignored unknown keyboad input.\n");
  }
}

