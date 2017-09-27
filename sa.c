#include "stdio.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"



int main(int argc, const char* argv[])
{
	if(argc <= 2||argc > 4)
	{
		printf("Usage: sa [d|l|m|r|u] ARG1 [ARG2]\n");
		exit(1);
	}
	
	int result;
	if(argc == 3)
	{
		struct stat lnkz;
		int st;
		st = stat(argv[2],& lnkz);
		if(st==-1)
		{
			printf("%s\n",strerror(errno));
			exit(1);
		}
		
		int lnkzlft;
		lnkzlft=lnkz.st_nlink;
		
		switch(argv[1][0])
		{
			case 'd':
			while(lnkzlft>0)
			{
				result=unlink(argv[2]);
				if(result==-1)
					printf("%s\n",strerror(errno));
				lnkzlft--;
			}
			break;
			case 'u':
				result=unlink(argv[2]);
				if(result==-1)
					printf("%s\n",strerror(errno));
			break;
			default:
				printf("Usage: sa [d|l|m|r|u] ARG1 [ARG2]\n");
				exit(1);
		}
				
	}
	
	if(argc==4)
	{
		switch(argv[1][0])
		{
			case 'l':
				result=link(argv[2],argv[3]);
				if(result==-1)
					printf("%s\n",strerror(errno));
			break;
			case 'm':
				result=rename(argv[2],argv[3]);
				if(result==-1)
					printf("%s\n",strerror(errno));
			break;
			case 'r':
				result=rename(argv[2],argv[3]);
				if(result==-1)
					printf("%s\n",strerror(errno));
			break;
			default:
				printf("Usage: sa [d|l|m|r|u] ARG1 [ARG2]\n");
				exit(1);
		}
	}
	
	return 0;
}

