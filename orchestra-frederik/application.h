// -----  Application  -----
#ifndef APPLICATION_H
#define APPLICATION_H

#include "TinyTimber.h"
#include "sciTinyTimber.h"
#include "canTinyTimber.h"

extern Serial sci;
extern Can can;

typedef struct App App;
extern App app;

void can_send_str(Can*, char*);
#endif

