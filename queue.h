struct Job {
  char ID;
  int (*func)(void **);
  void ** args;

  //Maybe should change this to a time
  int period;

  //Exicution time
  int comp_cost;

  int deadline;
};


/**
 * set up the queue with the comparitor to order the queue
 */
int queue_init(int (*comparitor)(struct Job i, struct Job j), int buffer_size);


/**
 * add an item into the sorted queue
 */

int queue_add(int comp_time, int period, int deadline, int (*func)(void **), void ** args);


/**
 * remove the top job from the queue and store it in
 * the passed pointer
 */
int queue_pop(struct Job *to_return);


/**
 * check if there is more in the Queue
 */
int queue_has_more();
