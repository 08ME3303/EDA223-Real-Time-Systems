/* -----  Performer  ----- */
#include "instrument.h"

typedef struct Performer Performer;
extern Performer performer;

#define PERFORMER_INIT(arg_performer) INSTRUMENT_INIT(&instrument);

void performer_stop(Performer* self, int bpm);

// play with delay (in eighths)

void performer_play(Performer*, int delay);
void performer_stop(Performer*, int unused);
void performer_sync(Performer*, int unused);
void performer_set_key(Performer*, int key);
void performer_set_bpm(Performer*, int bpm);
void performer_set_volume(Performer*, int volume);

// Debug control
void performer_control(Performer*, int c);

