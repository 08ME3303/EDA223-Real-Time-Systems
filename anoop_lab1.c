#include "TinyTimber.h"
#include "sciTinyTimber.h"
#include "canTinyTimber.h"

#include <stdio.h>
#include <stdlib.h>


char* const SOUND_PORT = (char *) 0x4000741C;

typedef struct
{
	Object super;
	int pulse;
	int volume;
	//int mute;
	int freq;
} SoundGen;

SoundGen soundgen = {initObject(), 1, 5, 500};


//Method for generating tone
void generator(SoundGen *self, int unused)
{
	AFTER(USEC(self->freq), self, generator, NULL);
	*SOUND_PORT = self->pulse * self->volume;
	self->pulse = !self->pulse;
	
}

//Method for mute function
void mutefunc(SoundGen *self, int arg)
{
	self->volume = 0;
}

//Method for unmute function
void unmutefunc(SoundGen *self, int arg)
{
	self->volume = 10;
}

//Method for increasing volume
void volup(SoundGen *self, int arg)
{
	if (self->volume < 20)
	{
		self->volume = self->volume + 1;
	}
	else
	{
		self->volume = 20;
	}
}

void voldown(SoundGen *self, int arg)
{
	if (self->volume <= 0)
	{
		self->volume = 0;
	}
	else 
	{
		self->volume = self->volume - 1;
	}
}

typedef struct {
    Object super;
    int running;
    //char c;
} App;

App app = { initObject(), 0 };

void reader(App*, int);
void receiver(App*, int);

Serial sci0 = initSerial(SCI_PORT0, &app, reader);

Can can0 = initCan(CAN_PORT0, &app, receiver);

void receiver(App *self, int unused) {
    CANMsg msg;
    CAN_RECEIVE(&can0, &msg);
    SCI_WRITE(&sci0, "Can msg received: ");
    SCI_WRITE(&sci0, msg.buff);
}

void run(App *self, int c)
{
	if (self->running)
	{
		SCI_WRITE(&sci0, "Already running \n");
	}
	else
	{
		SCI_WRITE(&sci0, "Starting tone generator \n");
		ASYNC(&soundgen, generator, NULL);
		self->running = 1;
	}
}

void reader(App *self, int c) {
	//static char buf[100];
	//static int i = 0;
	
	SCI_WRITE(&sci0, "Rcv: \'"); // echo the keyboard input
    SCI_WRITECHAR(&sci0, c);
    SCI_WRITE(&sci0, "\'\n");
	
	//ASYNC(&app, run, NULL);
	
	if (c == 'm' || c == 'M')
	{
		SYNC(&soundgen, mutefunc, 0);
	}
	else if (c == 'j')
	{
		SYNC(&soundgen, volup, 0);
	}
	else if(c == 'k')
	{
		SYNC(&soundgen, voldown, 0);
	}
	else if (c == 'u')
	{
		SYNC(&soundgen, unmutefunc, 0);
	}
	else if(c == 'i')
	{
		ASYNC(&app, run, NULL);
	}
	else
	{
		SCI_WRITE(&sci0, "Ignoring key input \n");
	}
}

void begin(App *self, int unused)
{
	CAN_INIT(&can0);
	SCI_INIT(&sci0);
	SCI_WRITE(&sci0, "Initializing tone generator \n");
}

/*
void startApp(App *self, int arg) {
    CANMsg msg;

    CAN_INIT(&can0);
    SCI_INIT(&sci0);
    SCI_WRITE(&sci0, "Hello, hello...\n");

    msg.msgId = 1;
    msg.nodeId = 1;
    msg.length = 6;
    msg.buff[0] = 'H';
    msg.buff[1] = 'e';
    msg.buff[2] = 'l';
    msg.buff[3] = 'l';
    msg.buff[4] = 'o';
    msg.buff[5] = 0;
    CAN_SEND(&can0, &msg);
}*/

int main() {
    INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
	INSTALL(&can0, can_interrupt, CAN_IRQ0);
    TINYTIMBER(&app, begin, 0);
    return 0;
}
