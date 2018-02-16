/* -----  Tone Generator  ----- */

// There is exactly one tone generator!
typedef struct Tonegen;
extern Tonegen tonegen;
#define TONEGEN_INIT(arg_tonegen) SYNC(arg_tonegen, tonegen_start, 0)

void tonegen_start(Tonegen*, int unused);
void tonegen_set_volume(Tonegen*, int vol);
void tonegen_set_period(Tonegen*, int per); // per in usec!

// (DEBUG) Control directly via keyboard (char) commands
void tonegen_control(Tonegen*, int c);

