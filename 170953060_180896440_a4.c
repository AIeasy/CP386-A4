
//Github AIeasy peng3060,https://github.com/AIeasy/CP386-A4
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
	printf("Currently Available resources: ");
	for(k=0;k<4;k++){
		printf("%d ",Available[k]);
	}
	printf("\n");
	printf("Maximum resources from file:\n");
	for(int k =0;k<5;k++){
		for(int i = 0;i<4;i++){
			printf("%d ",customers[k].max[i]);
		}
		printf("\n");
	}
	//read file and generate max.
	//safe check
	if (safe_check(Available,safe_seq)==0){//check if in safe condition.
		printf("Error: current thread list is not safe\n");
		return;
	}else{
		char* command = malloc(sizeof(char*)*300);
		while(1){
			int input[4];
			int t_id;
			printf("Enter command:\n");
			fgets(command, 300, stdin);
			char* token = strtok(command," ");
			int i =0;
			int mode =0;
			while (token!=NULL){
				if (i==0){
					if(strcmp("RQ",token)==0){
						mode =1;
					}else if (strcmp("RL",token)==0){
						mode = 2;
					}else if (strcmp("Status\n",token)==0){
						mode=3;
					}else if (strcmp("Run\n",token)==0){
						mode= 4;
					}else if (strcmp("Exit\n",token)==0){
						mode =5;
					}else{
						printf("ERROR: PLEASE INPUT RIGHT MODE COMMAND\n");
						return;
					}
					
				}
				else if (i==1){
					t_id = atoi(token);
					
				}else{
					input[i-2]=atoi(token);
				
				}
				token = strtok(NULL," ");
				i++;
			}
			
			if (mode ==1){
				request(t_id,input,Available,safe_seq);
			} else if (mode ==2){
				release(t_id,input,Available);
			} else if (mode ==3){
				status(Available);
				
			}else if (mode == 4){
				if(safe_check(Available,safe_seq)==1){
					Run(safe_seq);
					
					for (int x=0;x<5;x++){
						pthread_t my_thread;
						pthread_attr_t new_thread;
						pthread_attr_init(&new_thread);
						int p=safe_seq[x];
					        
						
						my_thread = pthread_create(&my_thread,&new_thread,thread_run,&customers[safe_seq[x]].ID);
						sleep(1);
						if (my_thread !=0){
							printf("ERROR, THREAD FAIL\n");	
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
				exit(0);
				 
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
		if(safe[n]==0 && customers[n].Need[0] <= work[0] && customers[n].Need[1] <= work[1] && customers[n].Need[2] <= work[2] && customers[n].Need[3] <= work[3]){//try to alloc
			work[0] += customers[n].Allocation[0];
			work[1] += customers[n].Allocation[1];
			work[2] += customers[n].Allocation[2];
			work[3] += customers[n].Allocation[3];
			safe[n] = 1;//change safe to 1
			safe_seq[k++] = n;
			n=-1;//check again
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
			printf("not safe\n");
			//rollback or keep going
			//let thread wait?
		}
		else{
			printf("State is safe, and request is satisfied\n");
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
		}	
			printf("The resources have been released successfully\n");
		
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
void logStart(int *tID) {
	printf("        Thread has started\n");
	return;
}
void logFinish(int *tID) {
	printf("        Thread has finished\n");
	return;
}
void logRelease(int *tID) {
	printf("        Thread is realseasing resources\n");
	for( int x =0;x<4;x++){
		Available[x]+=customers[*tID].Allocation[x];
	}
	return;
}

void *thread_run(void *thread){
  int *t_id = (int*)thread;
  printf("--> Customer/Thread %d\n",*t_id);
  printf("        Allocated resources:");//printing out all the allocated resources
  for (int x = 0; x <4 ;x++){
	  printf(" %d",customers[*t_id].Allocation[x]);
  }
  printf("\n");
  printf("        Needed:");//all the maxinum needed resources
	for (int y= 0;y<4;y++){
		printf(" %d",customers[*t_id].Need[y]);
	}
  printf("\n");
  printf("        Available:");//available resources
  for(int z = 0;z<4;z++){
  	printf(" %d",Available[z]);
  }
  printf("\n");
  logStart(t_id);
  logFinish(t_id);
  logRelease(t_id);
  printf("        New Available:");
  for(int n=0;n<4;n++){
	  printf(" %d",Available[n]);
  }
  printf("\n");
  return 0;
}



