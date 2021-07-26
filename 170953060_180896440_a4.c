
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
	//wait for request 
	//read request, process request? 
	//RQ request,RL release,* output,Run find safe sequence.
}

int safe_check(){
	//
	return 1;
}
int request(int n,int req[]){
	if(compare_matrix(req,need[n])==0){//check if request greater than need.
		printf("request greater than need");
		return 0;
	}
	if(compare_matrix(req,Avaiable)==1){//if req less than Avai, try to allocation
		alloc(n,req);
		if(safe_check()==0){
			rollback(n,req);
			//rollback or keep going
			//let thread wait?
		}
	}
}
void alloc(int n,int req[]){//Try to allocation sources 
	for(int i=0;i<4;i++){
		Available[i] = Available[i] - req[i];
		Allocation[n][i] = Allocation[n][i] + req[i];
		Need[n][i] = Need[n][i] - req[i];
	}
}
void rollback(int n,int req[]){//roll back to origin 
	for(int i=0;i<4;i++){
		Available[i] = Available[i] + req[i];
		Allocation[n][i] = Allocation[n][i] - req[i];
		Need[n][i] = Need[n][i] + req[i];
	}
}
int release(){
}
int output(){
}
int Run(){
}
int compare_matrix(int fir[],int sec[]){//compare two matrix, return 1 if first <= second, else return 0.
	for(int i =0;i<4;i++）{
		if(fir[i]>sec[i]){
			return 0;
		}
	}
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



