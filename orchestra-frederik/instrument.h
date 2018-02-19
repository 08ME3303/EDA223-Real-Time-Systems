/* -----  Instrument  ----- */
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "TinyTimber.h"

typedef struct Instrument Instrument;
extern Instrument instrument;
void instrument_init(); // also initialises tonegen

#define MIN_PITCHINDEX (-10)
#define MAX_PITCHINDEX 14
typedef struct {
  int pitchindex; // MIN_PITCHINDEX <= pitchindex <= MAX_PITCHINDEX
  Time duration;
  int loudness;
} Note;

void instrument_play_note(Instrument*, Note*);

// (DEBUG) Control directly via keyboard (char) commands
void instrument_debug(Instrument*, int c);

#endif
