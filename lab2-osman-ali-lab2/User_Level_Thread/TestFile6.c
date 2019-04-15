#define _GNU_SOURCE
#include "threads.h"

long long total =0;
void counter(){
    long tid;			//Most code in this file is from Kernel_level functions.c
    pid_t id;
    int temp;
    id = GetMyId();		// System call replaced
    int total = 0;

    struct timespec begin;
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    long long int rf = 0;
    while (1)
    {
        rf++;

        clock_gettime(CLOCK_MONOTONIC, &current);
        if (((long long)current.tv_sec - (long long)begin.tv_sec) >= 10.0)
        {

            break;
        }
    }
    total += rf;
    printf("total= %d\n",rf);	//Print total rf value
    DeleteThread(id);			//System call replaced
}

void sleeping()
{
  struct timespec begin;
  struct timespec current;
  clock_gettime(CLOCK_MONOTONIC,&begin);
  long long int rf=0;
  int id=GetMyId();			//System call replaced
  int total =0;
  int temp;

    if (id % 2 == 0)
    {
        sleep(2);
    }
    else
    {
        sleep(7);
    }
    while (1)
    {
        rf++;
        clock_gettime(CLOCK_MONOTONIC, &current);
	if (rf % 100000 == 0)
        {
            int id = GetMyId();
            printf("sleeping tid: %d rf = %d\n", id, rf);
        }

        if (((long long)current.tv_sec - (long long)begin.tv_sec) >= 10)
        {
            break;
        }
    }
  
    total += rf;
    printf("total total = %d\n of tid = %d",rf,id);  //Print total rf value
    DeleteThread(id);		   //System call replaced
}


int main(int argc, char* argv[])		//Test code derived from TestFiles to test sleeping/counter
{
    if (argc != 2) {
        printf("Usage: %s [FCFS] | [RR] | [vLOT] | [mLOT]\n", argv[0]);
        return 1;
    } else if (strcmp(argv[1], "FCFS") == 0) {
        setup(FCFS); // First Come, First Served
    } else if (strcmp(argv[1], "RR") == 0) {
        setup(RR); // Round Robin
    } else if (strcmp(argv[1], "vLOT") == 0) {
        setup(vLOT); // Vanilla Lottery
    } else if (strcmp(argv[1], "mLOT") == 0) {
        setup(mLOT); // Modified Lottery
    } else {
        printf("Usage: %s [FCFS] | [RR] | [vLOT] | [mLOT]\n", argv[0]);
        return 1;
    }

    for(int i =1;i<=16;i++){                    //can change i to 8,16,32 for easy testing
    CreateThread(counter,1);} // 0
    

    //CreateThread(sleeping, 1); // 3
    //CreateThread(counter, 1); // 2
   //
    Go();
   //
   return 0;
   }
   //


