// -----  Application  -----
#ifndef APPLICATION_H
#define APPLICATION_H

#include "TinyTimber.h"
#include "canTinyTimber.h"

typedef struct App App;
extern App app;

extern const int nodeId;
void app_can(App* self, CANMsg* msg);
#endif
