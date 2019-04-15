/**** You may MODIFY the designated portions of this file ****/
/**** You may also add any additional functions you need for your implementation ****/

/**** Please fill in your (and your partner's) information (Name and PSU email) below and in the variables below
 * Name:Osman Ali
 * Email: oza5@psu.edu
 * Name: Sahil Bhanderi
 * Email: skb5400@psu.edu
 ****/

// Feel free to modify this value for test purposes
#define SLEEP_TIME 10;


void counter () {
  /**** Your Code Here ****/
  long tid;
    pid_t id;
    int temp;
    id = GetMyId();
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
    printf("total rf = %d\n",rf);
    DeleteThread(id);
   /**** End Your Code ****/
}

void sleeping () {
  /**** Your Code Here ****/
  struct timespec begin;
  struct timespec current;
  clock_gettime(CLOCK_MONOTONIC,&begin);
  long long int rf=0;
  int id=GetMyId();
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
    printf("total rf = %d\n",rf);
    DeleteThread(id);
  /**** End Your Code ****/
}



