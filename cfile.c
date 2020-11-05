//Function in Javascript Land
extern void canvasClear();
extern void beginPath();
extern void tackSegment(int x1, int y1, int x2, int y2);
extern void stroke();
extern void logStr(const char*);
extern void requestAnimationFrame();
extern void setTimeout(unsigned int);

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

float sinf(float f) {
	int i = f * 100000;
	i %= 200000;
	return i > 100000 ? 2 - i/100000.f : i/100000.f;
}
float cosf(float f) {
	f += 1;
	int i = f * 100000;
	i %= 200000;
	return i > 100000 ? 2 - i/100000.f : i/100000.f;
}

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
		tackSegment(100, frame%60+200, 300, (60-(frame%60))+200);
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
	do {
		logStr("tick");
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
