/******************************************************************************
 * Your implementation of the MapReduce framework API.
 *
 * Other than this comment, you are free to modify this file as much as you
 * want, as long as you implement the API specified in the header file.
 *
 * Note: where the specification talks about the "caller", this is the program
 * which is not your code.  If the caller is required to do something, that
 * means your code may assume it has been done.
 ******************************************************************************/
#include <stdio.h>
#include "mapreduce.h"
#include <time.h>
#include <fcntl.h>

void map_helper(void*);
void reduce_helper(void*);
struct timeval start, end;

/*Helper Function to set mapper arguments*/
struct set_mapper_args{			
	struct map_reduce *mr;
	int infd,id,nmaps;
};

/*Helper Function to set reducer arguments*/
struct set_reducer_args{
	struct map_reduce *mr;
	int outfd,nmaps;
};

/*Helper function that allows to allocate arguments, pass them in pthread_create functions*/
void map_helper(void* map)
{
	struct set_mapper_args * args = (struct set_mapper_args*) map;
	int mr = 1;
	int comp = (args->mr)->mapfn(args->mr, args->infd, args->id, args->nmaps);
	int map_id = args->id;
	while(mr){				
	if(comp == 0){
		args->mr->c_jobs[map_id] += 1;		/*Valid map*/
		mr= 1;}	
	else{
		args->mr->c_jobs[map_id]  -= 1;		/*ran into error*/
		mr = 1;}
	}

}

/*Helper function to allow allocation of arguments to reducer, also allows to pass in structure in pthread_create*/
void reduce_helper(void* red)
{
	struct set_reducer_args * args = (struct reduce_args*) red;
	int rr =1;
	while(rr){
	int r_ofd = args->outfd;
	int r_nmaps = args->nmaps;
	int comp = (args->mr) -> reducefn(args->mr,r_ofd,r_nmaps);
	int num_map = args->mr->nmaps;
	if(comp == 0){
		args->mr->c_jobs[num_map] += 1;		/*Valid reduce*/
		rr = 0;}
	if(comp < 0){
		args->mr->c_jobs[num_map] -= 1;		/*ran into error*/
		rr =0;}
	else{
		printf("error1");
	    }
}
}

struct map_reduce *mr_create(map_fn map, reduce_fn reduce, int threads, int buffer_size) {
	{
	struct map_reduce * mr = malloc(sizeof(struct map_reduce));
	if (mr >= 1){ 							/*Check if mr was malloc'd*/

		int *args_arr = (int *) malloc(sizeof((threads)));	/*Allocate space and initialise all to 0 for mapper argument threads*/
		memset(args_arr,0,(threads+1)*sizeof(int));
	
		int *num_threads = (int *) malloc(sizeof(threads)); 	/*Allocate space for number of mappers, threads*/
		*num_threads = threads;
	
		int * initial = malloc(threads*sizeof(int)); 	/*Allocate and initialise to 0 the buffer count for each*/
		memset(initial,0,threads*sizeof(int));
	
		mr -> mapfn = map; 
		mr -> reducefn = reduce; 
		mr -> map_args = malloc(*num_threads * sizeof(struct set_mapper_args)); /**/
		mr -> red_args = malloc(sizeof(struct set_reducer_args));/**/
		mr -> nmaps = num_threads;/*first of the circular buffer*/
		mr -> buff_tail = malloc(buffer_size*threads); /*last of the circular buffer*/
		mr -> buffer_size = buffer_size;/*Specifies the shared buffer size*/
		mr -> buff_head = malloc(buffer_size*threads); /**/
		mr -> buff_count = initial;/*allocates buffers segment count, initialises to 0*/
		mr -> buff_arr = malloc(sizeof(pthread_t)*threads); /*creates an array to go through all mapper buffers*/
		mr -> thread_lock = malloc(sizeof(pthread_mutex_t)*threads); /*Allocates space for locks for each thread*/
		mr -> c_jobs = args_arr;	/*tracks map/reduce jobs allows us to figure out whos busy or done*/
	
		printf("%ld\n", ((end.tv_sec *100000 + end.tv_usec) - (start.tv_sec *100000 + start.tv_usec))); /*Get Time print statement for performance evaluation*/
	
		return mr;
	}
	
	else{
		printf("some error in mallocing mr");		/*mr not malloc'd hence call error*/
		mr_destroy(mr);					/*free everything allocated to heap*/
		return;
	}
}

}

/*Free's All allocated memory in mr_create function*/
void mr_destroy(struct map_reduce *mr) {

	free(mr->buff_head);				
	free(mr->buff_tail);				
	free(mr->c_jobs);
	free(mr->buffer_size);
	free(mr->nmaps);
	free(mr->buff_count);
	free(mr->buff_arr);
	free(mr->thread_lock);
	free(mr->map_args);
	free(mr->red_args);
	free(mr);
}

/**/
int mr_start(struct map_reduce *mr, const char *inpath, const char *outpath) {
	
	gettimeofday(&start, NULL);/*Start taking the time for performance evaluation0*/
	
	mr->red_args->mr = mr;/*sets mr to reducer*/
	mr->red_args->outfd = open(outpath,O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); /*give read, write truncate permission to for reducer*/
	mr->red_args->nmaps = *mr->nmaps; /*sets nmaps for reducer*/
	for (int i = 0; i < *mr->nmaps;i++){/*go through number of maps and perform argument set and thread creation for each*/
		mr->map_args[i].mr = mr;
		 mr->map_args[i].infd = open(inpath, O_RDONLY,644);	/* open file descriptor for mapper arguments */
		if (mr->map_args[i].infd < 0){/*if error in input file descriptor*/
			return -1;}
		mr->map_args[i].id = i;/* set id argument*/
		mr->map_args[i].nmaps = *mr->nmaps;/*set nmpas argument*/
		int map_thread = pthread_create(&mr->buff_arr[i], NULL, map_helper, (void *)&mr->map_args[i]); /*Create mapthread with the allocated variales*/
		if (map_thread != NULL){
			if (map_thread == -1){ /*return error, in case of failed thread creation*/
			return -1;}
	}
	}
	int reduce_thread = pthread_create(&mr->buff_arr[*mr->nmaps], NULL, (void*)&reduce_helper, mr->red_args); /*create reducer thread with set args*/
	if (reduce_thread != NULL){
		if (reduce_thread == -1){ /*if error in reducer thread return -1*/
		return -1;}
	}
	return 0;
}


int mr_finish(struct map_reduce *mr) {
	for (int i = 0; i < *mr->nmaps ;i++)  /*check all threads*/
	{
	pthread_join(mr->buff_arr[i], NULL); /*check if everything is done if not wait*/
	}
	pthread_join(mr->buff_arr[*mr->nmaps], NULL);
	gettimeofday(&end, NULL);/*End time for performance eval*/
}

/*Concurrency implemented via mutex locks, in session thread acquires the lock and only it can open it*/
int mr_produce(struct map_reduce *mr, int id, const struct kvpair *kv) {

	pthread_mutex_lock(&(mr->thread_lock[id]));		/*Lock critical section*/
	if (kv == 0){	
		return NULL;				/*checks existence of kv pair*/
	}
	
	Buff_sec* store = malloc(sizeof(char));		/*Allocate space to a temp buffer that can store kv pair values to be passed on*/
	store->kv = malloc(2*sizeof(int));		/*malloc space for key value pair, basically twice of unsined 32 bit integer*/
	
	store->kv->key = malloc(kv->keysz); 		/*malloc space for key */
	store->kv->value = malloc(kv->valuesz);		/* malloc space for value*/

	int copy_key = memmove(store->kv->key, kv->key, kv->keysz);
	if (copy_key == NULL){			/*use mmove to copy key to temporary buffer*/
		printf("eror in memmove");	/*error catching for memmove*/
		return NULL;}
	else{
		store->kv->keysz = kv->keysz;}
	
	int copy_value = memmove(store->kv->value, kv->value, kv->valuesz);		/*--------------->"Critical Section"*/
	if (copy_value == NULL){
		printf("error in memmove");		/*use mmove to copy value to temporary buffer*/
		return NULL;}				/*error catching for memmove*/
	else{
		store->kv->valuesz = kv->valuesz;
	}

	if(mr->buff_tail[id])				/*tail of buffer to temporary store*/
		(mr->buff_tail)[id]->next = store; 
	(mr->buff_tail)[id] = store; 

	if(!mr->buff_head[id])
		mr->buff_head[id] = (mr->buff_tail)[id];	/*now move to new head*/
	mr->buff_count[id] +=1;

	pthread_mutex_unlock(&(mr->thread_lock[id]));		/*Unlock critical section*/

	return 1;

}

int mr_consume(struct map_reduce *mr, int id, struct kvpair *kv) {

	if (kv == 0){						/*check for existence of kv pair*/
	return NULL;}

	while(!(mr->buff_count[id])) 
	{		
		if (mr->c_jobs[id] !=0 && mr->buff_count[id] <= 0){	
			if(kv !=NULL){			
			return 0;
			}
	}
	}
	pthread_mutex_lock(&(mr->thread_lock[id]));		/*Lock critical section*/

	Buff_sec* head = malloc(sizeof(char)); 			/*allocate space for temporary head of buffer*/
	Buff_sec* tail = malloc(sizeof(char));			/*allocate space fro temporary tail of buffer*/
	
	if ((head==NULL) || (tail == NULL)){			
		return 0;
	}
	else{
		head = mr->buff_head[id];			/*temporary node tail = buffer head*/ 
		tail = mr->buff_tail[id];}			/*temporary node tail = buffer tail*/
 
	memmove(kv->key, head->kv->key, head->kv->keysz);
	memmove(kv->value, head->kv->value, head->kv->valuesz); /*copy */ 

	kv->keysz = head->kv->keysz;
	kv->valuesz = head->kv->valuesz;

 	if((head != NULL && tail != NULL)){ 			/*case where head is tail*/
		if (!(head != tail)){
			mr->buff_head[id]=0; 
			mr->buff_tail[id]=0;}
		else{
		mr->buff_head[id] = mr->buff_head[id]->next; /* iterate to next buffer segment*/
		}
		
	}
	mr->buff_count[id] -= 1;
	pthread_mutex_unlock(&(mr->thread_lock[id]));		/*unlock critical section*/
	return 1;

}
