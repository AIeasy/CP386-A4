
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
	int safe_seq[5];
	
	//available = argv[]
	//read file and generate max.
	//safe check
	//wait for request 
	//read request, process request? 
	//RQ request,RL release,* output,Run find safe sequence.
}

int safe_check(){
	int work[4]; // work = avai
	for(int i=0;i<4;i++){
		work[i] = Available[i];
	}
	int small;
	int k=0;
	int safe[0,0,0,0,0]; //safe condition, set to false when init.
	for(i=0;i<5;i++){//check if all can be in safe condition
		if(safe[i]==0 && Allocation[i][0] <= work[0] && Allocation[i][1] <= work[1] && Allocation[i][2] <= work[2] && Allocation[i][3] <= work[3]){//try to alloc
			work[0] += Allocation[i][0];
			work[1] += Allocation[i][1];
			work[2] += Allocation[i][2];
			work[3] += Allocation[i][3];
			safe[i] = 1;//change safe to 1
			safe_seq[k++] = i;
			i=0;//check again
		}
	}
	for(i=0;i<5;i++){ //check if all in safe condition
		if(safe[i]==0){ // return false if not.
			return 0;
		}
	}
	return 1;
}
void request(int n,int req[]){
	if(compare_matrix(req,need[n])==0){//check if request greater than need.
		printf("request greater than need\n");
		return 0;
	}
	if(compare_matrix(req,Avaiable)==1){//if req less than Avai, try to allocation
		alloc(n,req);
		if(safe_check()==0){
			rollback(n,req);
			//rollback or keep going
			//let thread wait?
		else{
			printf("State is safe, and request is satisfied");
		}
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
int release(int n,int rel){//release resources 
	if(compare_matrix(rel,Allocation[n])==1){
		for(int i = 0;i<4;i++){
			Allocation[n][i] = Allocation[n][i] - rel[i];
			Available[i] += rel[i];
			//need do not change?
			printf("The resources have been released successfully\n");
		}
	}
	else{
		printf("invalid release");
	}
}
int status(){//print all matirx
	printf("Available Resources:\n");
	for(int i = 0;i<4;i++){
		printf("%d",Available[i]);
		printf(" ");
	}
	printf("\n");
	printf("Maximum Resources:\n");
	for(int k =0;k<5;k++){
		for(i=0;i<4;i++){
			printf("%d",max[k][i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("Allocated Resources:\n");
	for(int k =0;k<5;k++){
		for(i=0;i<4;i++){
			printf("%d",Allocation[k][i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("Need Resources:\n")
		for(int k =0;k<5;k++){
		for(i=0;i<4;i++){
			printf("%d",Need[k][i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
void Run(){
	printf("Safe Sequence is:");
	for(int i =0;i<5;i++){
		printf("%d",safe_seq[i]);
		printf(" ");
	}
	print("\n");
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



