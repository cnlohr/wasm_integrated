#include <emscripten.h>
#include <stdio.h>
#include <unistd.h>

//int __stack_pointer = 0;

int add2( int a, int b )
{
	return a+b;
}

//Function in Javascript Land
extern void writeout( int o );
extern void writeoutStr( const char * o );


int testcallback( int z )
{
	char ct[100];
	sprintf( ct, "testcallback(%d) this string is in C.\n", z );

	writeoutStr( ct );
	writeout( z+10000 );

	return z+10000;
}
