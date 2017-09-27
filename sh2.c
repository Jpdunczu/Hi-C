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
#define BUFSIZE 256

void makestring( char* );
void parse( char* );
void execute( char*[] );
void redirectin( char*[] );
void redirectout( char*[] );
void piped( char*[] );

//stdin = fd (0)
//stdout = fd (1)
//stderror = fd (2)

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
			makestring(argbuf);	
	}	
	
	exit(1);
	
	return 0;
}

void makestring( char* buf )
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
	parse( cp );
}

void parse( char* str )
{		
	char** args = malloc( 256 );
	int i = 0;
	
	args[i] = strtok(str, " ");
	
	while( args[i] )
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	if( strncmp(args[1], "<", 1 ) == 0 )
	{ redirectin( args ); return; }
	else if( strncmp(args[1], ">", 1 ) == 0 )
	{ redirectout( args ); return; }
	else if( strncmp(args[1], "|", 1 ) == 0 )
	{ piped( args ); return; }
	else
	{ execute( args ); }
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

void redirectin( char* args[] )
{
	int fd;
	char buf[BUFSIZE];
	int s = dup(0);
	
	close(0);
	fd = open( args[2], O_RDONLY );
	int bytes = read(0, buf, BUFSIZE );
	buf[bytes] = '\0';
	
	close(fd);
	
	dup2( s, 0 );
	close(s);	
}

void redirectout( char* args[] )
{
	int pid, fd, exitstatus;
	
	if( ( pid = fork() ) == -1 )
	{ oops(errno); return; }
	
	if( pid == 0 )
	{
		close(1);
		fd = creat( args[2], 0644 );
		execlp( args[0], args[0], NULL );
		perror( "execlp" );
		exit(1);
	}
	
	wait( &exitstatus );
}

void piped( char* args[] )
{
	int pip[2], newfd, pid, exitstatus;
	
	if( pipe( pip ) == -1 )
		oops(errno);
		
	if( ( pid = fork() ) == -1 )
		oops(errno);
		
	if( pid > 0 )
	{
		close( pip[1] );
		
		if( dup2( pip[0], 0 ) == -1 )
			oops(errno);
			
		close( pip[0] );
		execlp( args[2], args[2], NULL );
		oops( errno );
	}
	
	close( pip[0] );
	
	if( dup2( pip[1], 1 ) == -1 )
		oops(errno);
		
	close( pip[1] );
	execlp( args[1], args[1], NULL );
	oops( errno );
	
	wait( &exitstatus );
}
