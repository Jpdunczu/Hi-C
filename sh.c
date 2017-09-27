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
#include "wait.h"

#define oops(errno){ printf("%s\n", strerror(errno)); };
#define ARGLEN 100
#define MAXARGS 20

char* makestring( char* );
char ** parse( char* );
void execute( char*[] );

int main( int argc, const char* argv[] )
{
	if(signal( SIGINT, SIG_IGN ) == SIG_ERR)
		oops(errno);
	if(signal( SIGCHLD, SIG_IGN ) == SIG_ERR)
		oops(errno);
		
	int numargs;
	char argbuf[ARGLEN];
	char* arglist[MAXARGS+1];
	
	numargs = 0;
		
	while( 1 )
	{
		printf("$");
		if( fgets(argbuf, ARGLEN, stdin ) && *argbuf != '\n' )
			execute( parse( makestring(argbuf) ) );
		
	}	
	
	exit(1);
	
	return 0;
}

char* makestring( char* buf )
{
	if(strncmp(buf,"exit",4)==0)
		exit(1);
		
	char* cp;
	
	buf[strlen(buf)-1] = '\0';
	cp = malloc(strlen(buf)+1);
	if(cp==NULL)
	{
		oops(errno);
		exit(1);
	}
	strcpy(cp,buf);
	return cp;
}

char** parse( char* str )
{		
	char** args = malloc( 256 );
	int i = 0;
	
	args[i] = strtok(str, " ");
	
	while( args[i] )
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	
	return args;
}

void execute( char* arglist[] )
{
	int pid, exitstatus;
	
	pid = fork();
	
	switch( pid )
	{
		case -1:
			oops(errno);
			exit(1);
		case 0:
			execvp( arglist[0], arglist );
			oops(errno);
			exit(1);
		default:
			wait( &exitstatus );
	}
}

