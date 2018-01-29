// PSA: This code was not tested!

// Long live global variables! (I know this is ugly, but also convenient.)
int deadline = 0;
int benchmark = 0;


/* -----  Tone Generator  ----- */
typedef struct {
  Object super;
  int period;     // in usec, 0 < period < 10ms (upper bound bounds latency)
  int volume;     // 0 <= volume <= 20
  int out_state;  // 1 for output high, 0 for low
  int mute;       // disable output
} Tonegen;

char* const DAC_OUT = (char*) 0x4000741C;

int edge(Tonegen* self, int unused) {
  if (!deadline && !benchmark) {
    AFTER(USEC(self->period), self, edge, NULL);
  } else if (deadline && !benchmark) {
    SEND(USEC(self->period), USEC(100), self, edge, NULL);
  }

  self->out_state = !self->out_state;
  *DAC_OUT = self->out_state && !self->mute ? self->volume : 0;
}

int set_volume(Tonegen* self, int arg) {
  self->volume = arg < 0 ? 0 : (arg > 20 ? 20 : arg);
}

int set_mute(Tonegen* self, int arg) {
  self->mute = arg;
}

int set_period(Tonegen* self, int arg) {
  self->period = arg < 1 ? 1 : (arg > MSEC(10) ? MSEC(10) : arg);
}


/* -----  Background task with variable load  ----- */
typedef struct {
  Object super;
  int load;
} Background;

const int background_period = USEC(1300);

int busy(Background* self, int unused) {
  if (!deadline && !benchmark) {
    AFTER(background_period, self, busy, NULL);
  } else if (deadline && !benchmark) {
    SEND(background_period, background_period, self, busy, NULL);
  }

  // Spin for a bit.
  for (int i=0; i < self->load; i++);
}

int set_load(Background* self, int arg) {
  self->load = arg;
}


/* -----  Keyboard control  ----- */
void reader(App *self, int c) {
  SCI_WRITECHAR(&sci0, c);  // echo

  // Note that the read race conditions are unproblematic!
  if (c == 'a') {
    SYNC(&tonegen, set_volume, tonegen.volume + 1);
  } else if (c == 'b') {
    SYNC(&tonegen, set_volume,
      tonegen.volume > 1 ? tonegen.volume - 1 : tonegen.volume);
  } else if (c == 'c') {
    SYNC(&tonegen, set_mute, !tonegen.mute);
  } else if (c == 'd' || c == 'e') {
    SYNC(&background, set_load, background.load + (c == 'd' ? 500 : -500));
    SCI_WRITE(&sci0, "\nNew background load: ");
    char buf[20];
    sprintf(buf, "%d\n", background.load);
    SCI_WRITE(&sci0, buf);
  } else if (c == 'f') {
    deadline = !deadline;
    if (!deadline) {
      SCI_WRITE(&sci0, "\nDeadline scheduling is now off.\n");
    } else {
      SCI_WRITE(&sci0, "\nDeadline scheduling is now on.\n");
    }
  } else if (c == 'x') {
    SYNC(&app, run, NULL);
  } else if (c == 'y') {
    SYNC(&app, benchmark, NULL);
  } else {
    SCI_WRITE(&sci0, "\nIgnored unknown key.\n");
  }
}


/* -----  Main / Initialisation  ----- */
typedef struct {
  Object super;
  int running;
} App;

App app = { initObject(), 0 };

// Initially muted, with period corresponding to 1kHz.
Tonegen tonegen = {initObject(), USEC(500), 1, 0, 1};

// Initial load 1000.
Background background = { initObject(), 1000 };

int motd(App* self, int unused) {
  SCI_WRITE(&sci0, "Hi! Press 'x' to start normal execution and 'y' to start benchmarking.\n");
}

int run(App* self, int unused) {
  if (self->running) {
    SCI_WRITE(&sci0, "\nError: Already running!\n");
  } else {
    SCI_WRITE(&sci0, "\nStarting tone generator.\n");
    SYNC(&tonegen, edge, NULL);

    SCI_WRITE(&sci0, "Starting background task.\n");
    SYNC(&background, load, NULL);

    SCI_WRITE(&sci0, "Startup complete.\n");
    self->running = 1;
  }
}

int main() {
  INSTALL(&sci, sci_interrupt, SCI_IRQ0);
  TINYTIMBER(&app, motd, NULL);
}


/* -----  Benchmarking  ----- */
// call method directly??
#define BENCH(obj, meth, arg)                     \
  {                                               \
    int max = 0;                                  \
    for (int i=0; i<500; i++) {                   \
      Time t1 = CURRENT_OFFSET();                 \
      meth(obj, arg);                            \
      Time t2 = CURRENT_OFFSET();                 \
      int d = USEC_OF(t2) - USEC_OF(t1);          \
      max = d > max ? d : max;                    \
    }                                             \
                                                  \
    Time t3 = CURRENT_OFFSET();                   \
    for (int i=0; i<500; i++) {                   \
      meth(obj, arg);                            \
    }                                             \
    Time t4 = CURRENT_OFFSET();                   \
    int avg = (USEC_OF(t2) - USEC_OF(t1)) / 500;  \
                                                  \
    char buf[40];                                 \
    sprintf(buf, "max %d, avg %d\n", max, avg);   \
    SCI_WRITE(&sci0, buf);                        \
  }

int benchmark(App* self, int unused) {
  if (self->running) {
    SCI_WRITE(&sci0, "\nError: Can't benchmark while already running!\n");
  } else {
    SCI_WRITE(&sci0, "\nStarting benchmark.\n");
    benchmark = 1;

    SCI_WRITE(&sci0, "Benchmarking tone generator: ");
    BENCH(&tonegen, edge, NULL);

    SCI_WRITE(&sci0, "Benchmarking background at load=");
    char buf[20];
    sprintf(buf, "%d", background.load);
    SCI_WRITE(&sci0, ": ");
    BENCH(&background, busy, NULL);

    background.load = 5000;   // fill in appropriate number
    SCI_WRITE(&sci0, "Benchmarking background at load=");
    char buf[20];
    sprintf(buf, "%d", background.load);
    SCI_WRITE(&sci0, ": ");
    BENCH(&background, busy, NULL);

    SCI_WRITE(&sci0, "Benchmark completed.\n");
    benchmark = 0;
  }
}

