/* -----  Instrument  ----- */
#include "TinyTimber.h"
#include "tonegen.h"
#include "instrument.h"

struct Instrument {
  Object super;
  Msg call;
};

Instrument instrument;

void instrument_init() {
	tonegen_init();
	instrument = (Instrument) { initObject(), NULL };
}

const int tone_lookup[MAX_PITCHINDEX - MIN_PITCHINDEX + 1] = {2024,1911,1803,1702,1607,
  1516,1413,1351,1275,1203,1136,1072,1012,955,901,851,803,758,715,675,637,601,
  568,536,506};

static void instrument_end_note(Instrument* self, int unused);

void instrument_play_note(Instrument* self, Note* note) {
  SYNC(&tonegen, tonegen_set_period,
    tone_lookup[note->pitchindex - MIN_PITCHINDEX]);
  SYNC(&tonegen, tonegen_set_volume, note->loudness);
  ABORT(self->call);  // make sure only one note at a time.
  self->call = SEND(note->duration, USEC(100), self, instrument_end_note, 0);
}

static void instrument_end_note(Instrument* self, int unused) {
  self->call = NULL;  // fix for the ABORT bug
  SYNC(&tonegen, tonegen_set_volume, 0);
}

// (DEBUG) Control directly via keyboard (char) commands
void instrument_debug(Instrument* self, int c) {
  if (c == 'a') {
    // instrument_init();
  } else if (c >= 'b' && c <= 'b' + MAX_PITCHINDEX - MIN_PITCHINDEX) {
    Note note = {c - 'b' + MIN_PITCHINDEX, SEC(1), 15};
    instrument_play_note(self, &note);
  }
}

