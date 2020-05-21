#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<utime.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int i,fd;
	struct stat statbuf;
	struct utimbuf times;
	if(argc!=2)
	{
		printf("Usage:ex3-3 filename\n");
		return 1;
	}
	if((fd=open(argv[1],O_RDWR))<0)
	{
		printf("%s open failed.\n",argv[1]);
		return 3;
	}
	if(stat(argv[1],&statbuf)<0)
		return 2;

	if(ftruncate(fd,0)<0)
	{
		printf("%s truncate failed.\n",argv[1]);
		return 4;
	}
	printf("%s is truncated now.\n",argv[1]);
	times.actime=statbuf.st_atime;
	times.modtime=statbuf.st_mtime;
	if(utime(argv[1],&times)==0)
		printf("utime() call successful\n");
	else
		printf("Error:utime() call failed.\n");
	return 0;
}
