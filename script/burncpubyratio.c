#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    float totalTime = 100000;  //100ms
    float busyTime;  //us
    float idleTime;     //us
    float runTime = 0;    //us
    float cpuUtilization = 0;
    struct timeval start, end;

    printf("Input the CPU utilization:(From 0 to 100)\n");
    scanf("%f", &cpuUtilization);
    if(cpuUtilization > 100 || cpuUtilization < 0)
    {
        printf("Wrong input");
        return;
    }


    busyTime = totalTime * (cpuUtilization/100);
    idleTime = totalTime - busyTime;

    while(1)
    {
        gettimeofday(&start,NULL);

        runTime = 0;
        while(runTime <= busyTime)
        {
            gettimeofday(&end,NULL);
            runTime = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
        }

        usleep(idleTime);
    }

    return 0;
}



