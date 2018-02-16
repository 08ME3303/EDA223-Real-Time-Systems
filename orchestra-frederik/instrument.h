#ifndef INSTRUMENT_H
#define INSTRUMENT_H

/* -----  Instrument  ----- */
#include "TinyTimber.h"
#include "tonegen.h"

typedef struct Instrument Instrument;
extern Instrument instrument;

// Initialising the instrument means initialising the tone generator.
#define INSTRUMENT_INIT(arg_instrument) ;

#define MIN_PITCHINDEX (-10)
#define MAX_PITCHINDEX 14
typedef struct {
  int pitchindex; // MIN_PITCHINDEX <= pitchindex <= MAX_PITCHINDEX
  Time duration;
  int loudness;
} Note;

void instrument_play_note(Instrument*, Note*);

// (DEBUG) Control directly via keyboard (char) commands
void instrument_control(Instrument*, int c);

#endif
