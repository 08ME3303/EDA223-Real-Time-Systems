/* -----  Controller  ----- */
#include "canTinyTimber.h"

struct Controller;
typedef struct Controller Controller;

#define CONTROLLER_INIT(arg_controller) ;

const int nodeId = 0; // fill in proper ID

void controller_CAN(Controller*, CANMsg*);

// only volume control via keyboard!
void controller_keyboard(Controller*, int c);

