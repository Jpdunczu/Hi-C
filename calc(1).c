#include "stdio.h"
#include "stdlib.h"

int main( int argc, const char* argv[] )
{
	char str[] = "Usage: ./calc [x/+-] [operand1] [operand2]\n";

	if( argc != 4 )
	{
		printf( "%s", str );
		return 0;
	}

float a = atof( argv[2] );
float b = atof( argv[3] );
float ans = 0.0;

char *c = (char*)malloc( 4 );

c = (char*)argv[1];

if( *c == 'x' )
{
ans = a*b;
printf( " %f\n", ans );
}
else if( *c == '/' )
{
if( b == 0 )
{
printf( "Error: cannot divide by 0\n" );
return 0;
}
ans = a/b;
printf( " %f\n", ans );
}
else if( *c == '+' )
{
ans = a+b;
printf( " %f\n", ans );
}
else if( *c == '-' )
{
ans = a-b;
printf( " %f\n", ans );
}
else
printf( " %s\n", str );

free( c );

return 0;

}

