/* -----  CANductor  ----- */
typedef struct Conductor Conductor;
extern Conductor conductor;

void conductor_init();

void conductor_set_bpm(Conductor*, int bpm);
void conductor_set_key(Conductor*, int key);
void conductor_conduct(Conductor*, int unused);
void conductor_stop(Conductor*, int unused);

// Debug keyboard control
void conductor_debug(Conductor*, int c);

