#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/times.h>
#include<sys/wait.h>
int main(void)
{
	int i,status;
	pid_t pid;
	time_t currentTime;
	struct tms cpuTime;
	if((pid=fork())==-1)
	{
		printf("\nError in creating process..");
		exit(EXIT_FAILURE);
	}
	else if(pid==0)
	{
		time(&currentTime);
		printf("\nChild process started at %s",ctime(&currentTime));
		for(i=0;i<5;i++)
		{
			printf("\nCounting:%d",i);
			sleep(1);
		}
		time(&currentTime);
		printf("\nChild process ended at %s",ctime(&currentTime));
		exit(EXIT_SUCCESS);
		}
		else
		{
		time(&currentTime);
		printf("\nParent process started at %s",ctime(&currentTime));
		if(wait(&status)==-1)
		printf("\nError");
		if(WIFEXITED(status))
		printf("\nChild process ended normally");
		else
		printf("\nChild process did not ended normally");
		if (times(&cpuTime)<0)
		printf("\ntime Error");
		else
		{
			printf("\nParent process user time=%fn",((float)
				cpuTime.tms_utime));
			printf("\nParent process system time=%fn",((float)
				cpuTime.tms_stime));
			printf("\nChild process user time=%fn",((double)
				cpuTime.tms_utime));
			printf("\nChild process system time=%fn",((double)
				cpuTime.tms_stime));
		}
		time(&currentTime);
		printf("\nParent process ended at %s",ctime(&currentTime));
		exit(EXIT_SUCCESS);
	}
}
