/* -----  Performer  ----- */
#include "performer.h"

struct Performer {
  Object super;

  Msg call;
  int state;    // 0 for first half, 1 second half of eighth note
  int position; // position in piece
  int eighths_delay; // delay until next note

  Time period;  // period corresponding to a sixteenth note
  int key;      // offset to pitch
  int volume;

  struct {      // changes to be applied at the start of the next bar
    Time period;
    int key;
  } next;
};

Performer performer;

// start with 120 Hz
void performer_init() {
	instrument_init();
	performer = (Performer) {
	              .super = initObject(),
	              .call = NULL,
	              .state = 0,
	              .position = 0,
	              .eighths_delay = 0,
	              .period = SEC(1) / (4 * 120), // 120bpm
                .key = 0,
                .volume = 15 };
  performer.next.period = performer.period;
  performer.next.key = performer.key;
}

void performer_set_key(Performer* self, int key) {
  self->next.key = key;
}

void performer_set_bpm(Performer* self, int bpm) {
  self->next.period = SEC(1) / (4 * bpm);
}

void performer_set_volume(Performer* self, int volume) {
  self->volume = volume;
}

void performer_stop(Performer* self, int unused) {
  ABORT(self->call);
  self->call = NULL; // fix the ABORT bug
  self->state = 0;
  self->position = 0;
}

void performer_eighth(Performer* self, int unused);

// play the piece, delayed by `delay' quarters
void performer_play(Performer* self, int delay) {
  performer_stop(self, 0);
  self->eighths_delay = delay * 2;
  performer_eighth(self, 0);
}

void performer_sync(Performer* self, int unused) {
  ABORT(self->call);

  switch (self->state) {
  case 1: // lagging behind, hurry up!
    performer_eighth(self, 0);
    break;
  case 0: // speeding, repeat last eighth note
    self->eighths_delay++;
    performer_eighth(self, 0);
    break;
  }
}

/* -----  The `brother john' state machine  ----- */
#define SCORE_LENGTH 32
const int score_pitches[SCORE_LENGTH] = {0,2,4,0,0,2,4,0,4,5,7,4,5,7,7,9,7,5,4,
                                         0,7,9,7,5,4,0,0,-5,0,0,-5,0};
const char score_lengths[SCORE_LENGTH] = "aaaaaaaaaabaabccccaaccccaaaabaab";
const Time gap = MSEC(100); // gap between notes

int shape_eighths(char shape) {return shape == 'c' ? 1 : (shape == 'a' ? 2 : 4);}

void performer_sixteenth(Performer* self, int unused);
void performer_eighth(Performer* self, int unused) {
  self->state = 0;

  if (self->eighths_delay == 0) {
    // calculate current position in eighths
    int i, j = 0;
    for (i=0; i<self->position; i++)
      j += shape_eighths(score_lengths[i]);

    // start of new bar, update tempo and key
    if (j % 8 == 0) {
      self->period = self->next.period;
      self->key = self->next.key;
    }

    // play next note
    int eighths = shape_eighths(score_lengths[self->position]);
    Note note = { self->key + score_pitches[self->position],
                  self->period * 2 * eighths - gap,
                  self->volume };
    SYNC(&instrument, instrument_play_note, &note);
    self->eighths_delay = eighths-1;

    // move position in piece
    self->position = (self->position + 1) % SCORE_LENGTH;
  } else {
    self->eighths_delay--;
  }

  self->call = SEND(self->period, USEC(100), self, performer_sixteenth, 0);
}


void performer_sixteenth(Performer* self, int unused) {
  self->state = 1;
  self->call = SEND(self->period, USEC(100), self, performer_eighth, 0);
}

/* -----  DEBUG  ----- */
void performer_debug(Performer* self, int c) {
  static int bpm;
  switch (c) {
    case 'a': /*performer_init();*/ bpm = 120; break;
    case 'b': performer_play(self,0); break;
    case 'c': performer_stop(self,0); break;
    case 'd': performer_sync(self,0); break;

    case 'e': performer_set_key(self,self->key - 1); break;
    case 'f': performer_set_key(self,0); break;
    case 'g': performer_set_key(self,self->key + 1); break;

    case 'h': bpm-=5; performer_set_bpm(self,bpm); break;
    case 'i': bpm = 120; performer_set_bpm(self,bpm); break;
    case 'j': bpm+=5; performer_set_bpm(self,bpm); break;
  }
}

