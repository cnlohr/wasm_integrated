#include <emscripten.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <setjmp.h>

//int __stack_pointer = 0;

int add2( int a, int b )
{
	return a+b;
}

//Function in Javascript Land
extern void writestr( const char * o );
extern void beginPath();
extern void tackSegment( int x1, int y1, int x2, int y2 );
extern void stroke();
extern int dummyJSFunction( int i );

extern double OGGetAbsoluteTime();
extern void waitRecallMain();

int i = 0;

//jmp_buf env;
//int jmp = 0;
//void JumpInBuf()
//{
//	longjmp( env, 1 );
//}
//#define CNFGSwapBuffers() {  jmp = 1; if( setjmp( env ) == 0 ) { waitRecallMain(); ripcordOutOfMain(); } }

extern void jssleep(int ms, void * DATA_ADDR, void * stack_start, void * stack_end );

extern void debug(int id);

int sleeping = 0;
char ct[100];

struct asyncifystack 
{
	uint32_t * stacklocation;
	uint32_t * stackend;
};

extern uint32_t * _STACKTOP;
void * stack_start;

uint32_t getsp();

/*
void asyncify_start_unwind( void * v );
void asyncify_stop_rewind();
void asyncify_stop_unwind();
void asyncify_start_rewind( void * v );

void dosleep( int time )
{
	int dummy;
	if( sleeping == 0 )
	{
		sleeping = 1;
		sleepstack.stackend = &dummy;
//		asyncify_start_unwind( &sleepstack );
	}
	else
	{
		asyncify_stop_rewind();
		sleeping = 0;
	}
}
*/

			struct asyncifystack DATA_ADDR;

void mymain()
{
	debug(0);
	//while(1)
	{
		beginPath();
		int r1 = 100;
		int r2 = 120;
		int cx = 320;
		int cy = 240;
		float a1 = i / 1000.;
		float a2 = i / 1000.;
		tackSegment( cx+cosf(a1)*r1, cy+sinf(a1)*r1, cx+cosf(a2)*r2, cy+sinf(a2)*r2 );
		stroke();
		i++;
		//jssleep(10);
		sprintf( ct, "PART 1 %f\n", OGGetAbsoluteTime() );
		writestr( ct );
	debug(1);
		jssleep(1000,&DATA_ADDR, _STACKTOP, &DATA_ADDR);
	debug(2);

	//	sprintf( ct, "PART 2 %f\n", OGGetAbsoluteTime() );
	//	writestr( ct );
	}
}


void Wmain( int argc, char ** argv )
{
	int ss;
	stack_start = &ss;
/*
	sleepstack.stacklocation = _STACKTOP;
	mymain();
//	asyncify_stop_unwind();
	sprintf( ct, "SOMETHING ELSE %f\n", OGGetAbsoluteTime() );
	writestr( ct );
//	asyncify_start_rewind( &sleepstack );
	mymain();
	*/
	mymain();
}


int testcallback( int z )
{
	char ct[100];
	sprintf( ct, "testcallback(%d) this string is in C. %f\n", z, OGGetAbsoluteTime() );
	writestr( ct );
#if 0

	double start = OGGetAbsoluteTime();
	int i;
	beginPath();
	for( i = 0; i < 628300; i++ )
	{
		int r1 = 100;
		int r2 = 120;
		int cx = 320;
		int cy = 240;
		float a1 = i / 100000.;
		float a2 = i / 100000.;
		tackSegment( cx+cosf(a1)*r1, cy+sinf(a1)*r1, cx+cosf(a2)*r2, cy+sinf(a2)*r2 );
	}
	stroke();
	double end = OGGetAbsoluteTime();
	sprintf( ct, "Elapsed (mode 0): %f\n", end-start );
	writestr( ct );
#endif

#if 0
	//Why is firefox 5ns and Chrome 14ns?

	start = OGGetAbsoluteTime();
	beginPath();
	for( i = 0; i < 100000000; i++ )
	{
		volatile int ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);

		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
		ret = dummyJSFunction(i);
	}
	stroke();
	end = OGGetAbsoluteTime();
	sprintf( ct, "Elapsed (mode 1): %f\n", end-start );
	writestr( ct );
#endif

	return z+10000;
}
