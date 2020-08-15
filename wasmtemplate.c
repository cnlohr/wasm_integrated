#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char ** argv )
{
	if( argc != 3 )
	{
		fprintf( stderr, "Usage: detemplate template.ht datafile.b64\n" );
		return -5;
	}
	FILE * ht = fopen( argv[1], "rb" );
	FILE * df = fopen( argv[2], "rb" );
	if( !ht )
	{
		fprintf( stderr, "Error: cannot open template file \"%s\"\n", argv[1] );
		exit( -5 );
	}
	if( !df )
	{
		fprintf( stderr, "Error: cannot open data file \"%s\"\n", argv[2] );
		exit( -6 );
	}

	int maxlinelen = 80;
	char * line = malloc(maxlinelen);
	int lineptr = 0;
	int c;
	while( ( c = fgetc(ht) ) != EOF )
	{
		if( c == '\n' )
		{
			if( strcmp( line, "%WASMBLOB%" ) == 0 )
			{
				while( ( c = fgetc(df) )!= EOF )
				{
					if( c == '\n' )
						printf( "\\\n\t\t" );
					else
						putchar( c );
				}
			}
			else
			{
				puts( line );
			}
			lineptr = 0;
			line[lineptr] = 0;
		}
		else
		{
			line[lineptr++] = c;
			if( lineptr >= maxlinelen )
			{
				maxlinelen *= 2;
				line = realloc( line, maxlinelen );
			}
			line[lineptr] = 0;
		}
	}
}
