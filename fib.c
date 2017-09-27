#include "stdio.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "termios.h"
#include "signal.h"

#define oops(errno,x){ printf("%s\n", strerror(errno)); exit(x); };

int fibo;

void controlC(int);

int main( int argc )
{
	struct termios info;
	int result;
	
	result = tcgetattr(0, &info);
	if(result == -1)
		oops(errno, 1);
			
		info.c_lflag &= ~ECHO;
			if( tcsetattr(0, TCSANOW, &info)==-1 )
				oops(errno, 1); 
		
		
	if( argc != 1 )
	{
		printf("Error: Usage: ./fib");
		exit(1);
	}
	
	int fib[1];
	fibo = 0;
	
	if(signal( SIGINT, controlC ) == SIG_ERR)
		oops(errno, 1);
	if(signal( SIGQUIT, controlC ) == SIG_ERR)
		oops(errno, 1);
		
		while( fibo >= 0 )
		{	
			if( fibo == 0 )
			{
				sleep(3);
				fibo = fib[0] = 1;
			
				sleep(3);
				fibo = fib[1] = 1;
			}
			
			sleep(3);
			fibo = fib[0] + fib[1];
			fib[0] = fib[1];
			fib[1] = fibo;
		}
					
return 0;

}

void controlC(int n)
{ 				
	printf( "Signal Received: %i, Fibonacci Number: %i\n", n, fibo ); 		
	if( n == SIGQUIT )
	{
		struct termios info2;
		int result;
	
		result = tcgetattr(0, &info2);
		if(result == -1)
			oops(errno, 1);
			
		info2.c_lflag |= ECHO;
			if( tcsetattr(0, TCSANOW, &info2)==-1 )
				oops(errno, 1);  
		exit(1);
	}
	sleep(3);
}

