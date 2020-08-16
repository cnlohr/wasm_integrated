#include <emscripten.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int add2( int a, int b )
{
	return a+b;
}

//Function in Javascript Land
extern void writeout( int o );
extern void writeoutStr( const char * o );
extern void beginPath();
extern void stroke();
extern void tackSegment( int x1, int y1, int x2, int y2 );
extern void canvasClear();

int testcallback( int z )
{
	char ct[100];
	sprintf( ct, "testcallback(%d) this string is in C.\n", z );

	writeoutStr( ct );
	writeout( z+10000 );

	return z+10000;
}

int frame;

void animationFrame()
{
	int i;
	frame++;
	canvasClear();
	beginPath();

	for( i = 0; i <= 62; i++ )
	{
		int r1 = 120;
		int r2 = 120;
		int cx = 320;
		int cy = 240;
		float a1 = i / 10.    + frame/60.;
		float a2 = i / 10. + 1;
		tackSegment( cx+cosf(a1)*r1, cy+sinf(a1)*r1, cx+cosf(a2)*r2, cy+sinf(a2)*r2 );
	}
	stroke();
}


