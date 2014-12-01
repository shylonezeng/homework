#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>

int timespec2str(char *buf, uint len, struct timespec *ts) ;
time_t axtime;
char *filename;
void wakeup(int sig)
{
	char timestr[50];
// 	if(!timespec2str(timestr,30,axtime))	
	printf("time of last access to file %s: %s",filename,ctime(&axtime));
}

int main(int argc,char** argv)
{

	struct stat statbuf;

	if(argc!=2)
	{
		printf("usage: command filename\n");
		exit(0);

	}
	filename=argv[1];
	axtime=(time_t)0;
	while(1)
	{	
		if(stat(argv[1],&statbuf)==-1)
		{
			printf("file %s not exits\n",argv[1]);
			exit(0);
		}

		if(axtime!= statbuf.st_atime)
		{
			printf("file %s accessed\n",argv[1]);
			axtime=statbuf.st_atime;
		}
		signal(SIGALRM,wakeup);
		alarm(60);
		pause();
	}
	return 0;
}

// int timespec2str(char *buf, uint len, struct timespec *ts) {
// 	int ret;
// 	struct tm t;
// // 
// 	tzset();
// 	if (localtime_r(&(ts->tv_sec), &t) == NULL)
// 		return 1;
// 
// 	ret = strftime(buf, len, "%F %T", &t);
// 	if (ret == 0)
// 		return 2;
// 	len -= ret - 1;
// 
// 	ret = snprintf(&buf[strlen(buf)], len, ".%09ld", ts->tv_nsec);
// 	if (ret >= len)
// 		return 3;
// 
// 	return 0;
// }
