#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"
#include <sys/time.h>
#include <sys/resource.h>

int x[5] = {1,2,3,4,5};
//double c = 10.0;

void allocate()
{
    int i;
    int *p;
    for(i =1 ; i<1000000 ; i++)
    {
      p = malloc(500 * sizeof(int));
      if(func(i)) { free (p);}
    }
}

void allocate1()
{
  int i;
  int *p;
  for (i=1 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    if(i & 1)
      free (p);
  }
}

void allocate2()
{
  int i;
  int *p;
  for (i=1 ; i<300000 ; i++)
  {
    p = malloc(10000 * sizeof(int));
    free (p);
  }
}


int main(int argc, char const *argv[]) {
  struct rusage usage;
  struct rusage usage2;
  struct timeval sys_start;
  struct timeval sys_end;  
  struct timeval usr_start;
  struct timeval usr_end;
  long int s_res_set_size, e_res_set_size;
  long int s_signal, e_signal;
  long int s_vol_switch,e_vol_switch;
  long int s_inv_switch,e_inv_switch;
  int i;
  int *p;
  printf("Executing the code ......\n");
  printf("\nPrinting rusage details before execution......");
  getrusage(RUSAGE_SELF, &usage2);

  sys_start=usage2.ru_stime;
  usr_start=usage2.ru_utime;
  s_res_set_size=usage2.ru_maxrss;
  s_signal=usage2.ru_nsignals;
  s_vol_switch=usage2.ru_nvcsw;
  s_inv_switch=usage2.ru_nivcsw;
   printf("\nsystem starts at: %ld.%09lds,\nuser starts at: %ld.%09lds,\nsize: %ld,\nsignals: %ld,\nvoluntary switches: %ld,\ninvoluntart switches: %ld\n"
  ,sys_start.tv_sec,sys_start.tv_usec, usr_start.tv_sec
  ,usr_start.tv_usec,s_res_set_size,s_signal,s_vol_switch,s_inv_switch);
   

  allocate();

  for (i=0 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    free (p);
  }
  printf("\n\nProgram execution successfull\n");
  getrusage(RUSAGE_SELF, &usage);
  printf("\nPrinting rusage details after execution......");
  sys_end=usage.ru_stime;
  usr_end=usage.ru_utime;
  e_res_set_size=usage.ru_maxrss;
  e_signal=usage.ru_nsignals;
  e_vol_switch=usage.ru_nvcsw;
  e_inv_switch=usage.ru_nivcsw;
  printf("\nsystem ends at: %ld.%09lds,\nuser ends at: %ld.%09lds,\nsize: %ld,\nsignals: %ld,\nvoluntary switches: %ld,\ninvoluntart switches: %ld\n"
  ,sys_end.tv_sec,sys_end.tv_usec, usr_end.tv_sec
  ,usr_end.tv_usec,e_res_set_size,e_signal,e_vol_switch,e_inv_switch);
  printf("\n***********END OF DETAILS**************\n");
  return 0;
}
