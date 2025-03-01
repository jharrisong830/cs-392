#include "insertion.h"
#include "utils.h"


int main(int argc, char** argv) {
	
	/* You can assume command-line arguments are always correct:
		e.g., ./a.out filename.txt %d
		The file doesn't necessarily exist, though.
		The format is always one of these two: %d, or %f.
	
		With testing file provided, your command should be:
		./a.out testint %d
	
	*/
	// if(argc!=3) {
	// 	printf("you failed: argc = %d\n", argc);
	// 	exit(EXIT_FAILURE);
	// }
	size_t len = 0;
	int* arr = read_array(argv[1], argv[2], &len);
	iSort(arr, len, sizeof(int), &cmpr_float);
	iPrint(arr, len, sizeof(int), &print_float);
	
	free(arr);
	
	
	exit(EXIT_SUCCESS);
}


