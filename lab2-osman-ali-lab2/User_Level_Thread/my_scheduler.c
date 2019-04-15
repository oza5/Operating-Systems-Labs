/**** You may MODIFY the designated portions of this file ****/
/**** You may also add any additional functions you need for your implementation ****/

/**** Please fill in your (and your partner's) information (Name and PSU email) below and in the variables below
 * Name: Osman Ali
 * Email: oza5@psu.edu
 * Name:Sahil Bhanderi
 * Email: skb5400@psu.edu
 ****/
#include "threads.h"

// Fill out your PSU ID (xyz1234) here
// Make sure to NOT USE your PSU number
char ID_1[] = "oza5";
char ID_2[] = "skb5400";

// If you need to have extra variables from threads.c, add them here as `extern`
extern int scheduling_type;
extern thread_queue_t* ready_list;
extern thread_queue_t* thread_list;
extern thread_t* current;
struct timespec con_beg;
struct timespec con_end;
int switch_count = 0;
// You may also add your own variables

// This function is called once by the test file, before the thread are created
// Feel free to modify this function as much as you want, to initialize variables or structs for instance
void setup(int schedule)
{
    printf("Student IDs:\nID_1: %s\nID_2: %s\n", ID_1, ID_2);
    srand(time(NULL));
    scheduling_type = schedule; // FCFS == 0, RR == 1, vLOT == 2, mLOT == 3
    ready_list = malloc(sizeof(thread_queue_t));
    ready_list->head = ready_list->tail = NULL;
    ready_list->size = 0;

    thread_list = malloc(sizeof(thread_queue_t));
    thread_list->head = ready_list->tail = NULL;
    thread_list->size = 0;

    current = NULL;

    signal(SIGVTALRM, Dispatch);
}

// This function adds the thread t to the ready queue q according the scheduler used
// Feel free to modify this function as much as you want
void InsertWrapper(thread_t* t, thread_queue_t* q)
{
    if (scheduling_type == FCFS) {
        InsertAtHead(t, q);
	return;
    }
    /**** Your Code Here ****/
    if (scheduling_type == RR){
	thread_enqueue(t,q);
	return;
    }
    if (scheduling_type == vLOT){
	thread_enqueue(t,q);
	return;}

    if (scheduling_type == mLOT){
	thread_enqueue(t,q);
	return;}
}

// This function is called whenever a context switch is starting
void BeginContextSwitch()
{
    clock_gettime(CLOCK_MONOTONIC,&con_beg); //start taking the time 
}

// This function is called whenever a context switch is done

void EndContextSwitch()
{
    clock_gettime(CLOCK_MONOTONIC,&con_end); //stop taking the time 
    switch_count = switch_count + 1;
    printf("# of switches: %d \n", switch_count);
    printf("time: %lld \n", (long long)con_end.tv_nsec - (long long)con_beg.tv_nsec); // Print length of time taken by switch
  
}

// Add extra functions you want here

// Manages the thread scheduling when called
// Returns the running thread
thread_t* scheduler()
{
    /**** You may also add variable declarations here, or in the sections below ****/
    int all_total_thread = 0;
    int weight_count = 0;
    int random1;
    int node_total = 0;
    int ticket;
    thread_node_t* node;
    thread_node_t* return_node;
    thread_node_t* node_iter;
    thread_node_t* run_next;
    node = ready_list->head;
    node_iter = ready_list->head;
    /**** End variable declarations ****/

    /**** NOTE: the last running thread will be at in the `current` variable ****/
    // Make sure we still have some work to do
    if (ready_list->size == 0)
        return NULL;
    //int number, priority = 0;
    switch (scheduling_type) {
    case RR:; // Round Robin
        /**** Implement the Round Robin scheduler here ****/
        // Your code here
	if (current == NULL){ // thread is finished running then just return head
		return thread_dequeue(ready_list); //returns head of ready list
	}else{
		return thread_dequeue(ready_list); // current head and running thread returned
	}
        /**** End Round Robin code ****/

    case vLOT:; // Vanilla Lottery
        /**** Implement the Vanilla Lottery scheduler here ****/

        // Your code here
	while(node_iter != NULL) {   //Code mostly understood from Ramzi(textbook)
	all_total_thread += node_iter->thread->weight;  //iterates over the entire list and calculates total value of all thread weights
	node_iter = node_iter->next;			//iterates to next node, keeps going until list is exhausted
	}

	ticket = random() % all_total_thread; // Generates randomized winning ticket

	while(node != NULL) {
		node_total += node->thread->weight; //iterating and adding weights of threads to find the winner
		if (node_total > ticket)	//as soon as magic ticket number is hit, we determine that to be winner and break
			break;
	    		node = node->next;
	}
	run_next = node->thread;		//returns the next to run by vLot schedueling
	return run_next;
        /**** End Vanilla Lottery code ****/

    case mLOT:; // Modified Lottery
        /**** Implement the Modified Lottery scheduler here ****/
        // Your code here
        if((current!=NULL)&&(current->status->state==RUNNING))  
        {
          if(current-> weight > weight_count)
          {
            weight_count = weight_count+1;    //get the total weight count
            return current;
          }
          else
          {
            thread_enqueue(current, ready_list);	//Add current thread to the queue and increment weight count
            weight_count=1;
          }
        }
        random1 = random()%(ready_list->size);		//Generate random number regardless of threead weight
        return_node = ready_list->head;
        while(random1 > 0)
        {
          return_node = return_node->next;		//global variable handles the amount of time a thread that is selected gets
          random1 = random1-1;				//the more the weight the more time quanta provided.
        }
        current = return_node->thread;
        RemoveFromList(GetMyId(),ready_list);

        return current;
        /**** End Modified Lottery code ****/

    case FCFS: // First Come, First Served
        /**** DO NOT MODIFY ****/
        return ready_list->head->thread;

    default:
        return NULL;
    }
}
