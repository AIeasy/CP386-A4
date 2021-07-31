
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
void *thread_run(void *thread);
typedef struct Customer{
    int ID;
    int Allocation[4];
    int max[4];
    int Need[4];
}Customer;
Customer *customers;
int max[5][4]={{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
int Available[4];
int main(int argc, char *argv[]){
	
        printf("Number of Customers: 5\n");
	int safe_seq[5];
	Customer* cus = (Customer*) malloc(sizeof(Customer)*5);
    	customers=cus;
	for (int c=0;c<5;c++){//init max
		cus[c].ID=c;
		for(int r=0;r<4;r++){
			cus[c].Allocation[r]=0;
			cus[c].max[r]=max[c][r];
			cus[c].Need[r]=max[c][r];
		}
		
	}
	int p =1;
	int k=0;
	while(argv[p]!=NULL){
		k = atoi(argv[p]);
		Available[p-1]=k;
		p++;
	}
	printf("Currently Available resources:")
	for(k=0;k<4;k++){
		printf("%d ",Available[k]);
	}
	
	//read file and generate max.
	//safe check
	if (safe_check(Available,safe_seq)==0){//check if in safe condition.
		printf('Error: current thread list is not safe');
		return;
	}else{
		char* command = malloc(sizeof(char*)*300);
		while(1){
			int input[4];
			int t_id;
			printf("Enter command:\n");
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
				else if (i==1){
					t_id = atoi(token);
					
				}else{
					input[i]=atoi(token);
				
				}
				token = strtok(NULL," ");
				i++;
			}
			
			if (mode ==1){
				printf("%d",t_id);
				for(k=0;k<4;k++){
					printf("%d",input[k]);
				}
				request(t_id,input,Available,safe_seq);
			} else if (mode ==2){
				release(t_id,input,Available);
			} else if (mode ==3){
				status(Available);
				
			}else if (mode == 4){
				if(safe_check(Available,safe_seq)==1){
					Run(safe_seq);
					pthread_t my_thread;
					for (int x=0;x<5;x++){
						int p=safe_seq[x];
						my_thread = pthread_create(&my_thread,NULL,thread_run,&p);
						if (my_thread !=0){
							printf("ERROR, THREAD FAIL");	
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

int safe_check(int Available[],int safe_seq[]){
	int work[4]; // work = avai
	for(int i=0;i<4;i++){
		work[i] = Available[i];
	}
	int small;
	int k=0;
	int safe[5]={0,0,0,0,0}; //safe condition, set to false when init.
	for(int n=0;n<5;n++){//check if all can be in safe condition
		if(safe[n]==0 && customers[n].Allocation[0] <= work[0] && customers[n].Allocation[1] <= work[1] && customers[n].Allocation[2] <= work[2] && customers[n].Allocation[3] <= work[3]){//try to alloc
			work[0] += customers[n].Allocation[0];
			work[1] += customers[n].Allocation[1];
			work[2] += customers[n].Allocation[2];
			work[3] += customers[n].Allocation[3];
			safe[n] = 1;//change safe to 1
			safe_seq[k++] = n;
			n=0;//check again
		}
	}
	for(int i=0;i<5;i++){ //check if all in safe condition
		if(safe[i]==0){ // return false if not.
			return 0;
		}
	}
	return 1;
}
void request(int n,int req[],int Available[],int safe_seq[]){
	if(compare_matrix(req,customers[n].Need)==0){//check if request greater than need.
		printf("request greater than need\n");
		return 0;
	}
	else if(compare_matrix(req,Available)==1){//if req less than Avai, try to allocation
		alloc(n,req,Available);
		if(safe_check(Available,safe_seq)==0){
			rollback(n,req,Available);
			printf("not safe");
			//rollback or keep going
			//let thread wait?
		}
		else{
			printf("State is safe, and request is satisfied");
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
int release(int n,int rel[],int Available[]){//release resources 
	if(compare_matrix(rel,customers[n].Allocation)==1){
		for(int i = 0;i<4;i++){
			customers[n].Allocation[i] -= rel[i];
			Available[i] += rel[i];
			//need do not change?
			printf("The resources have been released successfully\n");
		}
	}
	else{
		printf("invalid release");
	}
}
int status(int Available[]){//print all matirx
	printf("Available Resources:\n");
	for(int i = 0;i<4;i++){
		printf("%d",Available[i]);
		printf(" ");
	}
	printf("\n");
	printf("Maximum Resources:\n");
	for(int k =0;k<5;k++){
		for(int i=0;i<4;i++){
			printf("%d",customers[k].max[i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("Allocated Resources:\n");
	for(int k =0;k<5;k++){
		for(int i=0;i<4;i++){
			printf("%d",customers[k].Allocation[i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("Need Resources:\n");
	for(int k =0;k<5;k++){
		for(int i=0;i<4;i++){
			printf("%d",customers[k].Need[i]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
void Run(int safe_seq[]){
	
	printf("Safe Sequence is:");
	for(int i =0;i<5;i++){
		printf("%d",safe_seq[i]);
		printf(" ");
	}
	printf("\n");
	
}
int compare_matrix(int fir[],int sec[]){//compare two matrix, return 1 if first <= second, else return 0.
	for(int i =0;i<4;i++){
		if(fir[i]>sec[i]){
			return 0;
		}
	}
		 return 1;   
}
void logStart(char *tID) {
	printf("Thread has started");
	return;
}
void logFinish(char *tID) {
	printf("Thread has finished");
	return;
}
void logRelease(char *tID) {
	printf("Thread is realseasing resources");
	return;
}

void *thread_run(void *thread){
  int *t_id = (int*)thread;
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
  }
  return 0;
}



