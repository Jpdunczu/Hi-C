#include "stdio.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "termios.h"

#define oops(errno,x){ printf("%s\n", strerror(errno)); };

int main(int argc, const char* argv[])
{
	struct termios info;
	int result;
	
	result = tcgetattr(0, &info);
	if(result == -1)
		oops(errno, 1);

	if(argc==1&&(strncmp(argv[0],"./ss",4)==0))
	{
		if(info.c_iflag & IUCLC)
			printf("iuclc, ");
			
		if(info.c_lflag & ECHO)
			printf("echo, ");
			
		printf("erase = %c\n", info.c_cc[VERASE]);
		
		exit(1);
	}
	
	if(argc>3)
	{
		printf("Usage: ./ss [SETTING]\n");
		exit(1);
	}
	
	if(strncmp(argv[1],"+iuclc",6)==0)
	{
		info.c_iflag |= IUCLC;
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1);
		exit(1);
	}
	
	if(strncmp(argv[1],"-iuclc",6)==0)
	{
		info.c_iflag &= ~IUCLC;
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1);
		exit(1);
	}
	
	if(strncmp(argv[1],"+echo",5)==0)
	{
		info.c_lflag |= ECHO;
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1);
		exit(1);
	}
	
	if(strncmp(argv[1],"-echo",5)==0)
	{
		info.c_lflag &= ~ECHO;
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1);
		exit(1);
	}
	
	if(strncmp(argv[1],"erase",5)==0)
	{
		info.c_cc[VERASE] = argv[2][0];
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1);
		exit(1);
	}
		
	return 0;	
}
