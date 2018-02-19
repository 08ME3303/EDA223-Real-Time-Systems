/* -----  Tone Generator  ----- */
#ifndef TONEGEN_H
#define TONEGEN_H

// There is exactly one tone generator!
typedef struct Tonegen Tonegen;
extern Tonegen tonegen;

void tonegen_init();
void tonegen_set_volume(Tonegen*, int vol);
void tonegen_set_period(Tonegen*, int per); // per in usec!

// (DEBUG) Control directly via keyboard (char) commands
void tonegen_control(Tonegen*, int c);
#endif
