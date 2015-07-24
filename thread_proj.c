/*
	Myles McLevedge
	CSC 412
	Project 2 - Multithreaded Application
	March 27, 2015
	
	The objective of this assigment is to create a program that
	uses pthreads to perform three different computations on a set
	of integers supplied through the command line.
*/

#include <stdio.h>
#include <pthread.h>

pthread_t avg_thread, max_thread, min_thread;		//the actual threads
int values[100];					//arbitrary-sized buffer for input values

void *avg(void *num) {
	int c, i, sum, average;

	c = (long)num;					//convert number of args back to long
	i = 0;
	sum = 0;
		
	while(i < c) {
		sum += values[i];
		i++;
	}	
	
	average = sum / c;	

	printf("Average is: %d\n", average);
	pthread_exit(NULL);
}

void *max(void *num) {
	int c, i, maximum;
	
	c = (long)num;
	i= 1;
	maximum = values[0];

	while(i < c) {						//linear search
		if(values[i] > maximum) maximum = values[i]; 
		i++;
	}	

	printf("Maximum is: %d\n", maximum);
	pthread_exit(NULL);
}

void *min(void *num) {
	int c, i, minimum;
	
	c = (long)num;
	i= 1;
	minimum = values[0];

	while(i < c) {						//linear search
		if(values[i] < minimum) minimum = values[i];
		i++;
	}	

	printf("Minimum is: %d\n", minimum);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

	if(argc < 2) {						//to ensure input is given and
		printf("Need input\n");				//exit program otherwise
		return(0);
	}

	else if(argc > 101) {
		printf("Need less than 100 input\n");	//arbitrary limit
		return(0);
	}
	
	else {
		int a = 1;				//start counting from argv[1]

		while(a < argc){
			int arg;

			if (sscanf (argv[a], "%i", &arg)!=1) {				//assign input to arg and  
				printf ("Error: %s is not an integer\n", argv[a]);	//make sure it's an int
				return(0); 						//exit program otherwise
			}
			
			else values[a-1] = arg;		//if valid int, add input to buffer
			a++;		
		}
	}
	
	int  avg_status, min_status, max_status;	//to hold threads' status
	long arg_num = (long)(argc - 1);		
	
	avg_status = pthread_create(&avg_thread, NULL, avg, (void *)arg_num);	//create the thread and pass it
	if(avg_status) printf("Create thread error\n");				//the number of args

	min_status = pthread_create(&min_thread, NULL, min, (void *)arg_num);
	if(min_status) printf("Create thread error\n");

	max_status = pthread_create(&max_thread, NULL, max, (void *)arg_num);
	if(max_status) printf("Create thread error\n");

	pthread_exit(NULL);				//exit program
}
