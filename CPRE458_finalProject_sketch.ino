
#include "queue.c"
#include <stdio.h>

/* Defines functions of robot */
#include "SimpleRSLK.h"

#define comp_time_location 0
#define period_location    1
#define next_call_location 2
#define deadline_location  3
#define ID_location        4
#define True               1
#define False              0

/**
 * Configuration options
 */
#define             8
#define EDF                1
#define RMS                0

int init_time;

char buffer[100];

int sleep(int i){
  delay(i * 1000);
  return 1;
}




int job_a(void * args[]){
    // Serial.println("function a");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_b(void * args[]){
    // Serial.println("function b");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_c(void * args[]){
    // Serial.println("function c");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_d(void * args[]){
    // Serial.println("function d");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_e(void * args[]){
    // Serial.println("function e");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_f(void * args[]){
    // Serial.println("function f");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_g(void * args[]){
    // Serial.println("function g");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}
int job_h(void * args[]){
    // Serial.println("function h");
    int i;
    for(i = 0; i < ( *(int *)args[0]); i++){
        //Serial.println("");
        sprintf(buffer, "%c", *(char *)args[1]);
        Serial.print(buffer);
        //fflush(stdout);
        sleep(1);
    }
    return 1;
}




//TODO
// The big thing to work on right now is the timing, I need the sleep function call
// on the Robot and a way to measure time on it


int tasks[numOfJobs][5] = {
  //              comp Time      period         next call       deadline           ID
  /* Task 1 */    {    1      ,   10       ,     0     ,       10       ,     1      },
  /* Task 2 */    {    2      ,   20       ,     0     ,       20       ,     2      },
  /* Task 3 */    {    3      ,   30       ,     0     ,       30       ,     3      },
  /* Task 4 */    {    4      ,   40       ,     0     ,       40       ,     4      },
  /* Task 5 */    {    5      ,   50       ,     0     ,       50       ,     5      },
  /* Task 6 */    {    6      ,   60       ,     0     ,       60       ,     6      },
  /* Task 7 */    {    7      ,   70       ,     0     ,       70       ,     7      },
  /* Task 8 */    {    8      ,   80       ,     0     ,       80       ,     8      }
  
};

int (*funcs[numOfJobs])(void **) ={

  /* Task 1 */    &job_a,
  /* Task 2 */    &job_b,
  /* Task 3 */    &job_c,
  /* Task 4 */    &job_d,
  /* Task 5 */    &job_e,
  /* Task 6 */    &job_f,
  /* Task 7 */    &job_g,
  /* Task 8 */    &job_h

};


int joba_time = 1;
char joba_id  = 'a';
int jobb_time = 2;
char jobb_id  = 'b';
int jobc_time = 3;
char jobc_id  = 'c';
int jobd_time = 4;
char jobd_id  = 'd';
int jobe_time = 5;
char jobe_id  = 'e';
int jobf_time = 6;
char jobf_id  = 'f';
int jobg_time = 7;
char jobg_id  = 'g';
int jobh_time = 8;
char jobh_id  = 'h';





void * args[numOfJobs][2] ={

  /* Task 1 */     &joba_time,  &joba_id,
  /* Task 2 */     &jobb_time,  &jobb_id,
  /* Task 3 */     &jobc_time,  &jobc_id,
  /* Task 4 */     &jobd_time,  &jobd_id,
  /* Task 5 */     &jobe_time,  &jobe_id,
  /* Task 6 */     &jobf_time,  &jobf_id,
  /* Task 7 */     &jobg_time,  &jobg_id,
  /* Task 8 */     &jobh_time,  &jobh_id

};


/**
 * Function pointer that returns positive if the 1st param is higher priority then 2nd
 */
int EDFCompsre(struct Job i, struct Job j){
  return j.deadline - i.deadline;
}

int RMSCompareint(struct Job i, struct Job j){
  return j.period - i.period;
}



int addJobs(int start_time, int stop_time){

  // sprintf(buffer, "calling add jobs with start time of %d and stop of %d\n", start_time, stop_time);
  int i;
  for (i=0; i < numOfJobs; i++){
    // sprintf(buffer, "Job %d is called next at %d\n", i, tasks[i][next_call_location]);
    if(tasks[i][next_call_location] <= stop_time && tasks[i][next_call_location] >= start_time){
      // sprintf(buffer, "added job %d\n", i);
      queue_add(tasks[i][comp_time_location],tasks[i][period_location], 
          tasks[i][deadline_location]+tasks[i][next_call_location], funcs[i], args[i]);
      
      tasks[i][next_call_location] += tasks[i][period_location];
    }
  }
  
}





int caller(){
  int i;
  // char id = 'a';
  void * array[] = {&joba_time, &joba_id};
  // array[0] = &time;
  // array[1] = &id;
  // int (*funcs[0])(void **) = &job_a;
  for(i = 0; i <numOfJobs; i++ )
    (**funcs[i])(args[i]);
  return 1;

}

 void waitBtnPressed() {
   while(digitalRead(LP_S2_PIN) == 1){
     digitalWrite(LP_RGB_LED_GREEN_PIN, HIGH);
     delay(500);
     digitalWrite(LP_RGB_LED_GREEN_PIN, LOW);
     delay(500);
   }
 }


void setup() {
  /* Set serial communication to 115200 baud rate for MSP432 */
  Serial.begin(115200);
  delay(500);

  /* Run setup code */
  setupRSLK();

  /* Initialize LED pins as outputs */
  pinMode(LED_FR_PIN, OUTPUT); 
  pinMode(LED_FL_PIN, OUTPUT); 
  pinMode(LED_BR_PIN, OUTPUT); 
  pinMode(LED_BL_PIN, OUTPUT);
  pinMode(LP_RED_LED_PIN, OUTPUT);
  pinMode(LP_RGB_LED_RED_PIN, OUTPUT);
  pinMode(LP_RGB_LED_BLUE_PIN, OUTPUT); 
  pinMode(LP_RGB_LED_GREEN_PIN, OUTPUT);

  /* Initialize LaunchPad buttons as inputs */
  pinMode(LP_S1_PIN, INPUT_PULLUP);
  pinMode(LP_S2_PIN, INPUT_PULLUP);


  Serial.println("Waiting for button push");

  waitBtnPressed();


  // caller();

  unsigned init_time = micros()/1000000;

  int i;

  for( i = 0; i <numOfJobs; ++i)
    tasks[i][next_call_location] += init_time;

  if(EDF){
     queue_init(&EDFCompsre, numOfJobs * 2 );
  } else if (RMS){
     queue_init(&RMSCompareint, numOfJobs * 2);
  }
  loop();

}



void loop() {
  // put your main code here, to run repeatedly:


  Serial.println("Waiting for button push");

  waitBtnPressed();

  Serial.println("Ok let's rock and roll");
  unsigned int new_time;
  unsigned int old_time = init_time;
  while(True){
    while(queue_has_more){

      old_time = new_time;
      new_time = micros()/1000000;
      addJobs(old_time, new_time);
      

      struct Job nextJob;

      if (queue_pop(&nextJob) == -1)
        break;

      //sprintf(buffer, "got job %d from the stack\n", nextJob.comp_cost);

      if(nextJob.comp_cost + micros()/1000000  > nextJob.deadline){
        sprintf(buffer, "Missed job %d because %u + %u is greater then %u", nextJob.period, nextJob.comp_cost, micros()/1000000, nextJob.deadline );
        Serial.print(buffer);
        Serial.println("Missed Job");
        continue;
      }
      (**nextJob.func)(nextJob.args);

      
    }

    sprintf(buffer, "\n No Jobs: New Time: %d and Old Time: %d", new_time, old_time);
    Serial.println(buffer);

    sleep(1);

    //No jobs in the Queue so spin for a period
//    wait(period);
    
  }

}
