#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

#define BUFFERSIZE = 2048;

int main( int argc, char* argv[] )
{
	if( argc != 4 || argc != 5 )
	{
		printf("Error: Usage: ./sub char1 char2 source.txt [output.txt]\n");
		exit( 1 );
	}
	
	char buf[BUFFERSIZE];
	
	if( ( int fd = open( char* argv[4], O_RDONLY ) ) == -1 )
	{
		printf("%s\n", strerror(errno) );
		exit( 1 );
	}
	
	return 0;
}
		
