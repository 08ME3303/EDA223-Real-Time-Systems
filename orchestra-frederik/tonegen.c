/* -----  Tone Generator  ----- */
#include "TinyTimber.h"
#include "tonegen.h"

struct Tonegen {
  Object super;
  Msg call;
  Time period;    // 50us <= period <= 5ms (10kHz >= f >= 100Hz)
  int volume;     // 0 <= volume <= 20
};

// There single global tone generator!
Tonegen tonegen = { initObject()  // Object
                  , NULL          // Msg
                  ,  USEC(1000)   // Time, corresponding to 500 Hz
                  ,  0            // Volume, muted
                  };

// Setters
void tonegen_set_volume(Tonegen* self, int vol) {
  self->volume = vol < 0 ? 0 : (vol > 20 ? 20 : vol);
}

void tonegen_set_period(Tonegen* self, int per) {
  self->period = USEC( per < 50 ? 50 : (per > 5000 ? 5000 : per) );
}


// The tone generator state machine
char* const DAC_OUT = (char*) 0x4000741C;

static void tonegen_edge(Tonegen* self, int state) {
  *DAC_OUT = state ? self->volume : 0;
  ABORT(self->call);
  self->call = SEND(self->period, USEC(100), self, tonegen_edge, !state);
}

void tonegen_init() {
  SYNC(&tonegen, tonegen_edge, 0);
}


// (DEBUG) Control directly via keyboard (char) commands
void tonegen_control(Tonegen* self, int c) {
  switch (c) {
    case 'a': tonegen_init(); break;
    case 'b': tonegen_set_volume(self, self->volume + 1); break;
    case 'c': tonegen_set_volume(self, self->volume - 1); break;
    case 'd': tonegen_set_period(self, USEC_OF(self->period) << 1); break;
    case 'e': tonegen_set_period(self, USEC_OF(self->period) >> 1); break;
  }
}

