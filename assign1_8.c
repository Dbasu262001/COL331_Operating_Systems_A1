#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]= c - '0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
  
  	//----FILL THE CODE HERE for unicast sum
	int pid;
	int start_ind;
	int end_ind;
	int my_pid = getpid();
	for(int i=0;i<8;i++){
		pid = fork();
		if(pid!=0){
			continue;
		}else{
			start_ind = i*(size/8);
			if(i!=7){
			
			end_ind = (i+1)*(size/8);
			
			}else{
			//start_ind = 
			end_ind = size;
			}
			
			break;
		}
	
	}
	//int mypid =getpid();
	if(type ==0){
		if(pid==0){
			int p_sum = 0;
			for(int i=start_ind;i<end_ind;i++)
			{
				p_sum += arr[i];
				printf(1,"index is %d value is %d :",i,arr[i]);
			}
			int *msg_child = (int *)malloc(8);
			msg_child = &p_sum;
			send(getpid(),my_pid,(void*)msg_child);
			exit();
		
		}
		else{
			for(int i=0;i<8;i++){
				int stat =-1;
				char *msg = (char *)malloc(8);
				while(stat==-1){
					 stat = recv(msg);
				 }
				int* t = (int*) msg;
				tot_sum = tot_sum + *t;
				
				
			}
			for(int i=0;i<8;i++){
				wait();
			}
		}
	
	
	
	

	}

  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	//Multicast Distributed algorithm
	if(type ==1){
	
	
	
	
	
	
	
	
	}
	
	
	exit();
}
