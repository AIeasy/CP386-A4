
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

int main(int argc, char *argv[]){
	int n = 5,m = 4;//n number of processes, m number of resources types.
        int max[n][m];
        int Allocation[n][m];
        int Available[m];
        int Need[n][m]; //need = max - alloca
	
	//available = argv[]
	//read file and generate max.
	//safe check
	//wait for request -> request
}

int safe_check(){
	//
	return 1;
}



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



