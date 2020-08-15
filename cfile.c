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

//This "console logger" function isn't working.
EM_JS(void, console_logger, (const char* str), {
 	 console.log(UTF8ToString(str));
} );


int testcallback( int z )
{
	char ct[100];
	//sprintf( ct, "Calling back: %d\n", z );
	//Not sure why - can't do this.
	//console_logger(ct);
	writeout( z+10000 );

	//EM_ASM({ alert("Alert box"); } );

	return z+10000;
}
