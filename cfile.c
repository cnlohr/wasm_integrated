#include <emscripten.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <setjmp.h>

//Function in Javascript Land
extern void canvasClear();
extern void beginPath();
extern void tackSegment(int x1, int y1, int x2, int y2);
extern void stroke();

void run();
void submitFrame();

const uint32_t callStackSize = 4096;
uint8_t sleeping = 0;
uint8_t callStack[callStackSize];
struct {
	void *beg;
	void *end;
	//void (*reenter)();
} callStruct = {
	callStack,
	&callStack[callStackSize]
};

void *getCallStackData() {
	return &callStruct;
}

void animation() {
	run();
	int frame = 0;
	do {
		canvasClear();
		beginPath();
		for(int i = 0; i <= 62; i++) {
			int r1 = 120;
			int r2 = 120;
			int cx = 320;
			int cy = 240;
			float a1 = i / 10. + frame / 60.;
			float a2 = i / 10. + 1;
			tackSegment(cx+cosf(a1)*r1, cy+sinf(a1)*r1, cx+cosf(a2)*r2, cy+sinf(a2)*r2);
		}
		stroke();
		//submitFrame();
		++frame;
	} while(0);
}
