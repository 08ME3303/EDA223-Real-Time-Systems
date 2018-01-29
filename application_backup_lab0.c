#include "TinyTimber.h"
#include "sciTinyTimber.h"
#include "canTinyTimber.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    Object super;
    int count;
    char c;
} App;

App app = { initObject(), 0, 'X' };

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

/*
void reader(App *self, int c) {
	static char buf[100];
	static int i = 0;		// note: technically need to check i < 20
	static int acc = 0;
	
	SCI_WRITE(&sci0, "Rcv: \'");
    SCI_WRITECHAR(&sci0, c);
    SCI_WRITE(&sci0, "\'\n");
	
	if (c != 'e' && c != 'F') {
		buf[i++] = c;
	} else if (c == 'e') {
		buf[i++] = '\0';
		i = 0;
		
		acc += atoi(buf);

		sprintf(buf, "The entered number is %d\nThe running sum is %d\n",atoi(buf), acc );
		SCI_WRITE(&sci0, buf);
	} else if (c == 'F') {
		i = 0;
		acc = 0;
		
		sprintf(buf,"The running sum is 0\n");
		SCI_WRITE(&sci0, buf);
	}
}
*/

// Problem 3
const int music[32] = {0,2,4,0,0,2,4,0,4,5,7,4,5,7,7,9,7,5,4,0,7,9,7,5,4,0,0,-5,0,0,-5,0};
#define MIN_INDEX (-10)
#define MAX_INDEX 14
const int periods[MAX_INDEX - MIN_INDEX + 1] = {2024,1911,1803,1702,1607,1516,1413,1351,1275,
	1203,1136,1072,1012,955,901,851,803,758,715,675,637,601,568,536,506};

void print_music(int key) {
	// assert -5 <= key <= 5
	for (int i=0; i<32; i++) {
		char buf[20];
		sprintf(buf, "%d ",periods[music[i] + key - MIN_INDEX]);
		SCI_WRITE(&sci0, buf);
	}
	SCI_WRITECHAR(&sci0, '\n');
}

void reader(App *self, int c) {
	static char buf[10];
	static int i = 0;
	
	if (c != 'e' && c != 'F') {
		buf[i++] = c;
		SCI_WRITECHAR(&sci0, c);
	} else if (c == 'e') {
		buf[i++] = '\0';
		i = 0;
		SCI_WRITECHAR(&sci0, '\n');		

		int key = atoi(buf);
		if (key >= -5 && key <= 5)
			print_music(key);
		else {
			SCI_WRITE(&sci0, "invalid key ");
			sprintf(buf,"%d",key);
			SCI_WRITE(&sci0, buf);
			SCI_WRITE(&sci0, ", expected value -5 <= key <= 5\n");
		}
	}
}



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
}

int main() {
    INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
	INSTALL(&can0, can_interrupt, CAN_IRQ0);
    TINYTIMBER(&app, startApp, 0);
    return 0;
}
