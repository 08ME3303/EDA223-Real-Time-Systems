/* -----  Performer  ----- */
#ifndef PERFORMER_H
#define PERFORMER_H
#include "instrument.h"

typedef struct Performer Performer;
extern Performer performer;
void performer_init();

void performer_play(Performer*, int delay); // play with delay (in eighths)
void performer_stop(Performer*, int unused);
void performer_sync(Performer*, int unused);
void performer_set_key(Performer*, int key);
void performer_set_bpm(Performer*, int bpm);
void performer_set_volume(Performer*, int volume);

// Debug control
void performer_control(Performer*, int c);
#endif
