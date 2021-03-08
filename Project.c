//Banker's Algorithm OS Project
//K18-0179 (Uzair Ahmed Mughal - 4B) | K18-0361 (Muzammil - 4B)
#include<stdio.h> 
#include <stdlib.h> 
#include<stdbool.h>

//Global Variables
int i,j,ind=0,num_pro,num_res;
int **alloc,**max,**need,*avail,*safe_seq;

//function declaration
void display_data(void);
void initiate(void);
void calculate_need(void);
bool check(int);
bool check_safe_seq(int);
void change_available(int);
void start(void);


//stating program
void initiate(){
	
	printf("~~~~~~~~~~~~~~~Banker's Algorithm~~~~~~~~~~~~~~~\n\n");
	printf("Enter the number of processes: ");
	scanf("%d",&num_pro);
	printf("Enter the number of resources: ");
	scanf("%d",&num_res);
	
	alloc=(int **) calloc(num_pro,sizeof(int *));
	
	for(i=0;i<num_pro;i++){
		
		alloc[i]=(int *)calloc(num_res,sizeof(int *));
	}
	
	max=(int **) calloc(num_pro,sizeof(int*));
	
	for(i=0;i<num_pro;i++){
		
		max[i]=(int *) calloc(num_res,sizeof(int*));
	}
	
	need=(int **) calloc(num_pro,sizeof(int*));
	
	for(i=0;i<num_pro;i++)	{
		
		need[i]=(int *) calloc(num_res,sizeof(int*));
	}
	
	avail=(int *) calloc(num_res,sizeof(int*));
	
	safe_seq=(int *) calloc(num_pro,sizeof(int*));
	
	display_data();
	
	printf("\n\nEnter the resouces allocated to each process:\n");
	
	for(i=0;i<num_pro;i++){
		
		for(j=0;j<num_res;j++){
			
			printf("%d-Process:",i+1);
			scanf("%d",*(alloc+i)+j);
		}
	}
	
	display_data();
	
	printf("\n\nEnter the maximum required resoucres for each process:\n");
	
	for(i=0;i<num_pro;i++){
		
		for(j=0;j<num_res;j++){
			
			printf("%d-Process:",i+1);
			scanf("%d",*(max+i)+j);
		}
	}
	
	display_data();
	
	printf("\n\nEnter the available resoucres:\n");
	
	for(i=0;i<num_res;i++){
		
		scanf("%d",(avail+i));
	}
}

//displaying all data
void display_data(){
	
	//printf("\033[2J");
	system("cls");
	printf("\t\t~~~~~~~~~~~~~~Banker's Algorithm~~~~~~~~~~~~~~~\n\n");
	printf("\t |Processes| \t |Allocation| \t |Maximum| \t |Need| \t |Available| \n\n");
	
	for(i=0;i<num_pro;i++){
		
		printf("\t      P%d \t  [",i+1);
		
		for(j=0;j<num_res;j++)
			printf(" %d",alloc[i][j]);
		
		printf(" ]\t [");	
		
		for(j=0;j<num_res;j++)
			printf(" %d",max[i][j]);
				
		printf(" ]\t [");	
		
		for(j=0;j<num_res;j++)
			printf(" %d",need[i][j]);
		
		printf(" ]\t");
		
		if(i==0){
			
			printf("  [");
			for(j=0;j<num_res;j++)
				printf(" %d",avail[j]);
			printf(" ]");
		}
		printf("\n");
	}
}

//calculating need matrix
void calculate_need(){
	
	for(i=0;i<num_pro;i++){
		
		for(j=0;j<num_res;j++){
			
			if ((max[i][j]-alloc[i][j]) < 0)	{
				printf("Maximum Value has bad input!");
				exit(0);
			}	else
				need[i][j]=max[i][j]-alloc[i][j];
		}
	}
}

//check condition
bool check(int k){
	
	for(j=0;j<num_res;j++){
		
		if(need[k][j] > avail[j])
			return false;
	}
	return true;
}


//check in safe sequence
bool check_safe_seq(int k){
	
	for(j=0;j<num_pro;j++){
					
		if(k == safe_seq[j]-1)
			return true;
	}
	return false;
}

//updating available resources
void change_available(int k){
	
	printf("\nAvailable: [ ");

	for(j=0;j<num_res;j++){
		
		avail[j]=avail[j]+alloc[k][j];
		printf("%d ", avail[j]);

	}

	printf("]\n");
}

//starting algorithm
void start(){
	
	int k,verify;
	
	while(1){
		
		for(i=0;i<num_pro;i++){
			
			verify=1;
			
			if(check_safe_seq(i))
				continue;
				
			else if(check(i)){
				
				verify=0;
				printf("P%d- ",i+1);
				printf("Need < Word!\n");
				safe_seq[ind]=i+1;
				ind++;
				change_available(i);
			}
			else{
				
				printf("P%d- ",i+1);
				printf("Need > Word!\n");
			}
			//system("pause");			
		}
		if(verify==1)
			break;
	}
	
	for(i=0;i<num_pro;i++)	{
		
		if (safe_seq[i] == 0)	{
			printf("Safe sequence not found because one or more process is not getting the required resources!\n");
			exit(0);
		}
	}

	printf("Safe Sequence is: {");
	for(i=0;i<num_pro;i++)
		printf(" %d ",safe_seq[i]);
	printf("}\n");
}

void main(){
	
	initiate();
	display_data();
	calculate_need();
	display_data();
	start();
}

// bool check_total_resc()	{

// 	int tot_avail = 0, tot_need = 0;
	
// 	for (int i = 0; i < num_pro; i++)	{

// 		for (int j = 0; j < num_res; j++)	{
// 			tot_avail += alloc[i][j];
// 			tot_need += need[i][j];
// 		}
// 	}
// }
