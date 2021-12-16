#include "queue.h"
//#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 200

struct Job heap[MAX_SIZE];
int last_job;

/**
 * Function pointer that returns positive if the 1st param is higher priority then 2nd
 */
int (*compare)(struct Job i,  struct Job j );

int nullOut(int i){
  memset(&heap[i], 0, sizeof(struct Job));
}




int parent(int i){
  return i/2;
}

int right_child(int i){
   if(i*2 > MAX_SIZE)
    return -1;
  return i*2+2;
}


int left_child(int i){
  if(i*2+1 > MAX_SIZE)
    return -1;
  return i*2+1;
}

int swap(int i, int j){
  struct Job temp;
  memcpy(&temp, &heap[i], sizeof(struct Job));
  memcpy(&heap[i], &heap[j], sizeof(struct Job));
  memcpy(&heap[j], &temp, sizeof(struct Job));
  return 1;
  
}

/**
 * set up the queue with the comparitor to order the queue
 */
int queue_init(int (*comparitor)(struct Job i, struct Job j), int buffer_size){

  // heap = (struct Job *) malloc(sizeof(struct Job) * buffer_size);

  
  compare = comparitor;

  last_job = 0;

  return 1;
  
}




/**
 * add an item into the sorted queue
 */
int queue_add(int comp_time, int period, int deadline, int (*func)(void **), void ** args){
  if (last_job >= MAX_SIZE)
    return -1;
  
  heap[last_job].ID = *(char *)args[1];
  heap[last_job].func = func;
  heap[last_job].comp_cost = comp_time;
  heap[last_job].period = period;
  heap[last_job].deadline = deadline;
  heap[last_job].args = args;

  int location = last_job;

  last_job++;


  //This should perculate the job up
  while(location != 0 && (*compare)(heap[location], heap[parent(location)]) > 0){
    swap(location, parent(location));
    location = parent(location);
  }

  return 1;
  
}


/**
 * remove the top job from the queue and store it in
 * the passed pointer
 */
int queue_pop(struct Job *to_return){
  if(!queue_has_more())
    return -1;


  memcpy(to_return, &heap[0], sizeof(struct Job));
  nullOut(0);
  swap(0, --last_job);

  
  int left;
  int right;
  int left_less_then_right;

  int location = 0;
  int old;
  char flag;
  do{
    if(location > last_job)
      break;
      
     flag = 0;
     left = (*compare)(heap[location], heap[left_child(location)]);
     right = (*compare)(heap[location], heap[right_child(location)]);

     left_less_then_right = (*compare)(heap[left_child(location)], heap[right_child(location)]);
     


    old = location;
    if(left < 0 && left_child(location) < last_job  && left_less_then_right > 0){
      swap(location, left_child(location));
      location = left_child(location);
      flag = 1;
    } else if (right < 0 && right_child(location) < last_job){
      swap(location, right_child(location));
      location = right_child(location);
      flag = 1;
    }

    
    
  
  } while((right < 0 || left < 0) && (flag));


  return 1;

  
}


/**
 * check if there is more in the Queue
 */
int queue_has_more(){
  return last_job;
}



// int main(){
//   return 1;
// }
