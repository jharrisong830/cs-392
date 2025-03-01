/*
John Graham
I pledge my honor that I have abided by the Stevens Honor System

insertion.c
*/

#include "insertion.h"


/*
	We emphasize this: because this is a generic implementation, in insertion.c you must not use if-else to
	discriminate different data types in your code. Your code must be able to deal with any data type possible.
	Therefore, we limit the usage of the following primitive types:
	- int or size_t: only allowed as loop iterators;
	- char or u_int8_t: can be used as you wish;
	- Types that are used in the declarations of iSort() and iPrint(): feel free to use them for their _original_
      purpose;
	- All other types are not allowed to appear in insertion.c: no exceptions, no matter if you actually used
	  them, or what purpose it is. Once it appears, you will receive 30% reduction of the homework.

	You are free to create helper functions only in insertion.c; you must declare and implement them in the
    .c file instead of the header files. Do not change any of the header files.
	
*/

/**Given any two pointers whose types share the same width, swaps the data of their bytes one-by-one*/
void swapBytes(size_t width, void* elem1, void* elem2) {
	for(size_t i=0; i<width; i++) {
		char* byte1=(char*)(elem1+i); //convert to char pointers
		char* byte2=(char*)(elem2+i);
		
		char temp=(*byte1); //swap the bytes!
		(*byte1)=(*byte2);
		(*byte2)=temp;
	}
}

/**Insertion sort algorithm*/
void iSort(void* base, size_t nel, size_t width, int (*compare)(void*,void*)) {
	for(size_t i=1; i<nel; i++) { //assumes every element before i is in the sorted part of the array
		for(int j=i-1; j>=0; j--) { //moving backwards through each element in the sorted array, insert the first unsorted element (j+1) into the correct position in the sorted array
			void* curr=base+(width*(j+1));
			void* prev=base+(width*j);
			if((*compare)(curr, prev) < 0) { //curr is less than prev
				swapBytes(width, curr, prev); //swap the two elements!
			}
		}
	}
}

/**Prints an array starting at base, with a size of nel*/
void iPrint(void* base, size_t nel, size_t width, void (*print)(void*)) {
	for(int i=0; i<nel; i++) {
		(*print)(base+(width*i));
	}
}