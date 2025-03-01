/*
John Graham
I pledge my honor that I have abided by the Stevens Honor System

utils.c
*/

#include "utils.h"

#include <stdlib.h>
#include <string.h>

/*
	You are free to use any data type you like in this file.
    However, other than the five functions declared in "utils.h",
    DO NOT create any other functions.
	
*/

/**Compares two integers. a > b if 1 returned, a = b if 0 returned, a < b if -1 returned.*/
int cmpr_int(void* pa, void* pb) { //adding var names??
	int a=*((int*)pa);
	int b=*((int*)pb);
	if(a>b) {
		return 1;
	}
	else if(a<b) {
		return -1;
	}
	else {
		return 0;
	}
}

/**Compares two floats. a > b if positive result returned, a = b if 0 returned, a < b if negative result returned.*/
int cmpr_float(void* pa,void* pb) {
	float a=*((float*)pa);
	float b=*((float*)pb);
	if(a>b) {
		return 1;
	}
	else if(a<b) {
		return -1;
	}
	else {
		return 0;
	}
}

/**Prints a single integer.*/
void print_int(void* p) {
	int result=*((int*)p);
	printf("%d\n", result);
}

/**Prints a single float.*/
void print_float(void* p) {
	float result=*((float*)p);
	printf("%f\n", result);
}

/**Reads each line from the specified filename*/
void* read_array(char* filename, char* format, size_t* len) {
	FILE* fp; //all args for fopen and getline
	char* line=NULL;
	ssize_t nread=0;
	size_t i=0;

	if((fp=fopen(filename, "r")) == NULL) { //if file does not exist (fopen returns null)...
		fprintf(stderr, "File failed to open.\n");
		exit(1);
	}

	while((nread=getline(&line, len, fp)) != -1) { //predetermining the size of the array (making the actual read part easier)
		i++;
	}
	free(line);
	fclose(fp);

	size_t len_for_real=i; //length (for real)
	line=NULL; //reset paramenters...
	(*len)=0;
	i=0;
	fp=fopen(filename, "r"); //reopen file

	if(strcmp("%d", format)==0) { //if decimals...
		int* arr=(int*)malloc((len_for_real)*sizeof(int)); //allocate an int array of size len
		while((nread=getline(&line, len, fp)) != -1) { //for each line...
			arr[i]=atoi(line); //convert line to int, store at position i in arr
			i++;
		}
		free(line); //free!
		fclose(fp); //close!
		(*len)=len_for_real; //set the actual length
		return arr; //return the base pointer of the array 
	}
	else { //if floats...
		float* arr=(float*)malloc((len_for_real)*sizeof(float)); //allocate a float array of size len
		while((nread=getline(&line, len, fp)) != -1) { //for each line...
			arr[i]=atof(line); //convert line to int, store at position i in arr
			i++;
		}
		free(line); //free!
		fclose(fp); //close!
		(*len)=len_for_real; //set the actual length
		return arr; //return the base pointer of the array
	}
}