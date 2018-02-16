/* -----  Performer  ----- */
#include "performer.h"

typedef struct {
  Object super;
  Msg call;
  int state;    // 1 beat, 0 gap
  Time period;  // period corresponding to half an eighth note
  int position; // position in piece
  int volume;
  int key;      // offset to pitch
  int eights_delay; // delay until next note
} Performer;

// start with 120 Hz
Performer performer = { initObject(), NULL, 0,
                        MSEC(60000 / (4 * 120)), 3, 0, 0 };

void performer_set_key(Performer* self, int key) {
  self->key = key;
}

void performer_set_bpm(Performer* self, int bpm) {
  self->period = MSEC(60000 / (4 * bpm));
}

void performer_set_volume(Performer* self, int volume) {
  self->volume = volume;
}

void performer_stop(Performer* self, int unused) {
  ABORT(self->call);
  self->state = 0;
  self->position = 0;
}

// play the piece, delayed by `delay' eighths
void performer_play(Performer* self, int delay) {
  reset(performer_stop, 0);
  self->eighths_delay = delay;
  eighth_beat(self, 0);
}

void performer_sync(Performer* self, int unused) {
  ABORT(self->call);

  switch (self->state) {
  case 1: // lagging behind, hurry up!
    performer_eighth(self, 0);
    break;
  case 0: // speeding, repeat last eighth note
    self->delay++;
    performer_eighth(self, 0);
    break;
  }
}

void performer_control(Tonegen* self, int c) {
  switch (c) {
    case 'a': PERFORMER_INIT(self); break;
    case 'b': performer_play(self,0); break;
    case 'c': performer_stop(self,0); break;
    case 'd': performer_sync(self,0); break;

    case 'e': performer_set_key(self,-3); break;
    case 'f': performer_set_key(self,0); break;
    case 'g': performer_set_key(self,3); break;

    case 'h': performer_set_bpm(self,60); break;
    case 'i': performer_set_bpm(self,90); break;
    case 'j': performer_set_bpm(self,120); break;
    case 'k': performer_set_bpm(self,150); break;
    case 'l': performer_set_bpm(self,240); break;
  }
}

/* -----  The `brother john' state machine  ----- */
#define SCORE_LENGTH 32
const int score_pitches[SCORE_LENGTH] = {0,2,4,0,0,2,4,0,4,5,7,4,5,7,7,9,7,5,4,
                                         0,7,9,7,5,4,0,0,-5,0,0,-5,0};
const char score_lengths[SCORE_LENGTH] = "aaaaaaaaaabaabccccaaccccaaaabaab";
const Time gap = MSEC(100); // gap between notes

void performer_eighth(Performer* self, int unused) {
  this->state = 0;

  if (self->eighths_delay == 0) {
    char shape = score_lengths[self->position];
    int eighths = shape == 'c' ? 1 : (shape == 'a' ? 2 : 4);
    Note note = { self->key + score_pitches[self->position];
                  period * 2 * eighths - gap,
                  self->volume };
    SYNC(&instrument, play_note, &note);
    eighths_delay = eights-1;
  } else {
    self->eighths_delay--;
  }

  this->call = SEND(self->period, USEC(100), self, performer_sixteenth, 0);
}


void performer_sixteenth(Performer* self, int unused) {
  this->state = 1;
  this->call = SEND(self->period, USEC(100), self, performer_eighth, 0);
}

