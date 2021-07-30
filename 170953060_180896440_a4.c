
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
typedef struct Customer{
    int ID;
    int Allocation[4];
    int max[4];
    int Need[4];
}Customer;

int n = 5,m = 4;//n number of processes, m number of resources types.
//int max[n][m];
int Allocation[n][m];
int Available[m];
int Need[n][m]; //need = max - alloca
int safe_seq[5];
int max={{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
int main(int argc, char *argv[]){
	Customer* cus = (Customer*) malloc(sizeof(Customer)*5);
    	customers=cus;
	for (int c=0;c<5;c++){
		cus[c].ID=c;
		for(int r=0;r<4;r++){
			cus[c].max[r]=max[c][r];	
		}
		
	}
	for( int i=1;i<m;i++){
		Available[i-1]=atoi(argv[i]);
		}
	//read file and generate max.
	//safe check
	if (safe_check()==0){
		printf('Error: current thread list is not safe');
		return;
	}else{
		char command[256];
		while(1){
			int input[4];
			int t_id;
			printf('Enter command:\n');
			scanf("%s",command);
			char* token = strtok(command," ");
			int i =0;
			int mode =0;
			while (token!=NULL){
				if (i==0){
					if(strcmp("RQ",token)==0){
						mode =1;
					}else if (strcmp("RL",token)==0){
						mode = 2;
					}else if (strcmp("STATUS",token)==0){
						mode=3;
					}else if (strcmp("RUN",token)==0){
						mode= 4;
					}else if (strcmp("EXIT",token)==0){
						mode =5;
					}else{
						printf("ERROR: PLEASE INPUT RIGHT MODE COMMAND");
						return;
					}
					
				}
				if (i==1){
					tid = atoi(token);
					token = strtok(NULL," ")
				}else{
					
				input[i]=atoi(token);
				token = strtok(NULL," ");
				}
				i++;
			}
			if (mode ==1){
				request(tid,input);
			} else if (mode ==2){
				release(tid,input);
			} else if (mode ==3){
				status();
				
			}else if (mode == 4){
				if(safe_check()==1){
					Run();
					pthread_t my_thread;
					for (int x=0;x<5;x++){
						int pthread = *(p);
						pthread = pthread_create(&my_thread,NULL,thread_run(),&p[x]);
						if (pthread !=0){
							print("ERROR, THREAD FAIL");	
						}
					}
					pthread_exit(NULL);
				}
		
					
				else{
					printf("Current thread list is not safe, can not perform run threads\n");
					return;
				}
				
			
			}else if (mode == 5){
				printf("Exiting Program....\n");
				return;
			}
				
				
			
			
			
			
			
			
			
			
		}
			
			
			
	}
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
void request(int n,int req[],int Available){
	if(compare_matrix(req,customers[n].need)==0){//check if request greater than need.
		printf("request greater than need\n");
		return 0;
	}
	if(compare_matrix(req,Avaiable)==1){//if req less than Avai, try to allocation
		alloc(n,req,Availble);
		if(safe_check()==0){
			rollback(n,req,Availble);
			//rollback or keep going
			//let thread wait?
		else{
			printf("State is safe, and request is satisfied");
		}
		}
	}
}
void alloc(int n,int req[],int Available[]){//Try to allocation sources 
	for(int i=0;i<4;i++){
		Available[i] = Available[i] - req[i];
		customers[n].Allocation[i] += req[i];
		customers[n].Need[i] -= req[i];
	}
}
void rollback(int n,int req[],int Available[]){//roll back to origin 
	for(int i=0;i<4;i++){
		Available[i] = Available[i] + req[i];
		customers[n].Allocation[i] -= req[i];
		customers[n].Need[i] += req[i];
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
  for (int x =0;x<5;x++){
	  for(int a =0;a<4;a++){
		  printf("%d",customers[x].Allocation[a]);	  
 	   }
  }
  printf("        Needed:\n");//all the maxinum needed resources
	  for (int y = 0;y<5;y++){
	  for(int n=0;n<4;n++){
		  printf("%s",customers[y].Need[n]);
	  }
	  printf("\n");
  }
  printf("        Available:\n");//available resources
  for(int z = 0;z<4;z++){
  printf("%d",Available[z]);
  logStart(t_id);//log start
  sleep(3);
  logFinish(t_id);//log finish
  sleep(3);
  logRelease(t_id);//log release all thread used resources
  printf("New available:\n");//print out new available resources
  return;
}



