#include "stdio.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int transltr(int);

int main(int argc, const char* argv[])
{	
	
	char str[] = "cm FILE [rwx]\n";
	
	if(argc<1||argc>3)
	{
		printf("Error: %s", str);
		exit(1);
	}
	
	struct stat info;
	int st;
	st = stat(argv[1], & info);
	if(st==-1)
	{
		printf("%s\n",strerror(errno));
		exit(1);
	}
	
	int mode;
	mode = info.st_mode;
	
	int result;
	
	if(argc==3)
	{
		if(strncmp(argv[2],"rwx",3)==0)
		{
			result = chmod(argv[1],(mode|=00700));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"rw",2)==0)
		{
			result = chmod(argv[1],(mode|=00600));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"rx",2)==0)
		{
			result = chmod(argv[1],(mode|=00500));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"wx",2)==0)
		{
			result = chmod(argv[1],(mode|=00300));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"r",1)==0)
		{
			result = chmod(argv[1],(mode|=00400));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"w",1)==0)
		{
			result = chmod(argv[1],(mode|=00200));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		else if(strncmp(argv[2],"x",1)==0)
		{
			result = chmod(argv[1],(mode|=00100));
			if(result==-1)
			{
				printf("%s\n", strerror(errno));
				exit(1);	
			}
			exit(1);
		}
		
		printf("Error: %s", str);
		exit(1);
	}

return 0;	
}
	
