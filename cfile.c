//Function in Javascript Land
extern void canvasClear();
extern void beginPath();
extern void tackSegment(int x1, int y1, int x2, int y2);
extern void stroke();
extern void logNum(unsigned int x);
extern void requestAnimationFrame();
extern void setTimeout(unsigned int);
extern float sinf(float x);
extern float cosf(float x);

void start_unwind(void*);
void stop_unwind();
void start_rewind(void*);
void stop_rewind();

const unsigned int callStackSize = 4096;
unsigned char callStack[callStackSize];
struct {
	void *beg;
	void *end;
} callStruct = {
	callStack,
	&callStack[callStackSize]
};
unsigned char sleepStack[callStackSize];
struct {
	void *beg;
	void *end;
} sleepStruct = {
	sleepStack,
	&sleepStack[callStackSize]
};

unsigned char sleeping0 = 0;
void submitFrame() {
	if(!sleeping0) {
		sleeping0 = 1;
		start_unwind(&callStruct);
	} else {
		stop_rewind();
		sleeping0 = 0;
	}
}
void animation() {
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
		submitFrame();
		++frame;
	} while(1);
}
void reenterAnimation() {
	start_rewind(&callStruct);
	animation();
	stop_unwind();
	requestAnimationFrame();
}
void runAnimation() {
	animation();
	stop_unwind();
	requestAnimationFrame();
}

unsigned char sleeping1 = 0;
void timerSleep() {
	if(!sleeping1) {
		sleeping1 = 1;
		start_unwind(&sleepStruct);
	} else {
		stop_rewind();
		sleeping1 = 0;
	}
}
void timerLoop() {
	unsigned int num = 0;
	do {
		logNum(++num);
		timerSleep();
	} while(1);
}
void reenterTimer() {
	start_rewind(&sleepStruct);
	timerLoop();
	stop_unwind();
	setTimeout(1000);
}
void runTimer() {
	timerLoop();
	stop_unwind();
	setTimeout(1000);
}
