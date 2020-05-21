#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define LNAME 9
#define PERMS 0666
#define DATAFILE "datafile"
#define USERS 10
typedef struct user{
	int uid;
	char login[LNAME+1];
}RECORD;
char *user_name[]={"u1","u2","u3","u4","u5","u6","u7","u8","u9","admin"};
int main()
{
	int i,fd;
	RECORD rec;
	if((fd=open(DATAFILE,O_WRONLY|O_TRUNC|O_CREAT,PERMS))==-1)
	{
		perror("open");
		return 1;
	}
	for(i=USERS-1;i>=0;i++)
	{
		rec.uid=i;
		strcpy(rec.login,user_name[i]);
		lseek(fd,(long)i*sizeof(RECORD),SEEK_SET);
		write(fd,(char*)&rec,sizeof(RECORD));
	}
	lseek(fd,0L,SEEK_END);
	close(fd);
	return 0;
}

