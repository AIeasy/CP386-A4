
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>


int read_File(char * f_name){
  FILE *in_put = fopen(f_name,"r");
  if(in_puit == NULL)
   {
      printf("Error! Can not open the input file\n");   
      return -1;             
   }
    int LINE_LENGTH = 128;
    char *line = (char *)malloc(sizeof(char) * LINE_LENGTH);
  
  
  
  
}

void logStart(char *tID) {
	printf("Thread has started");
}
void logFinish(char *tID) {
	printf("Thread has finished);
}
void logStart(char *tID) {
	printf("Thread is realseasing resources");
}


void *thread_run(void * thread){
  int *t_id = (int*)t;
  printf("--> Customer/Thread %d\n",t_id);
  printf("        Allocated resources:\n");
  printf("        Needed:\n");
  printf("        Available:\n");
  logStart(t_id);
  logFinish(t_id);
  logRelease(t_id);
  printf("New available:\n");
  return;
}



