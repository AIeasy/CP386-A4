
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
	char matrix[5][4];
	int i,j;
	if(in_puit == NULL){
		printf("Error! Can not open the input file\n");
		return -1;
	}
	for(i=0; i<5; i++) {
		for(j=0; j<4; j++) {
		    fscanf(in_put," %c, ",&matrix[i][j]);
		}
	}
	
	return matrix;
  
  
  
}

void logStart(char *tID) {
	printf("Thread has started");
}
void logFinish(char *tID) {
	printf("Thread has finished");
}
void logStart(char *tID) {
	printf("Thread is realseasing resources");
}

void *thread_run(void * thread){
  int *t_id = (int*)t;
  printf("--> Customer/Thread %d\n",t_id);
  printf("        Allocated resources:\n");//printing out all the allocated resources
  printf("        Needed:\n");//all the maxinum needed resources
  printf("        Available:\n");//available resources
  logStart(t_id);//log start
  sleep(3);
  logFinish(t_id);//log finish
  sleep(3);
  logRelease(t_id);//log release all thread used resources
  printf("New available:\n");//print out new available resources
  return;
}



