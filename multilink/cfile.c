#include <emscripten.h>

int addwat( int a, int b );
int add2( int a, int b )
{
	return a+b;
}
int add2cwat( int a, int b )
{
	return 999;
//	return addwat( a, b );
}
