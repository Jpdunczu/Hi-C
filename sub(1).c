#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

#define BUFFERSIZE 2048

int main( int argc, char* argv[] )
{
	if(argc<4||argc>5)
	{
		printf("Error: Usage: ./sub char1 char2 source.txt [output.txt]\n");
		exit( 1 );
	}
	
	char change1, change2;
	change1 = argv[1][0];
	change2 = argv[2][0];
	
	char buf[BUFFERSIZE];
	int fd;
	fd = open(argv[3], O_RDONLY);
	
	if(fd == -1)
	{
		printf("%s\n", strerror(errno));
		exit( 1 );
	}
	
	int n_char;
	n_char = read(fd, buf, BUFFERSIZE);
	if(n_char == -1)
	{
		printf("%s\n", strerror(errno));
		exit( 1 );
	}
	
	int count = 0;
	
	while(count != n_char)
	{
		if(buf[count] == change1)
			buf[count] = change2;
		if(argc==4)
			printf("%c", buf[count]);
		count++;
	}

	if(argc==5)
	{
		int fd2;
		fd2 = creat(argv[4], 00700);
		if(fd2==-1)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}

		int result2;
		result2=write(fd2, buf, n_char);
		if(result2==-1)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}	
	
	int result;
	result = close(fd);
	if(result == -1)
	{
		printf("%s\n", strerror(errno));
		exit( 1 );
	}
	
	return 0;
}
		
