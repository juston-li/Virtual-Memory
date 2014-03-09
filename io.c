/*
 *I/O functions
 *
 *access returns the memory request from the physicalmem_array 
 *
 *load: after page fault, load is called to bring the page needed into
 *physicalmem_array from BACKING_STORE.bin
*/

#include <stdio.h> 
#include <stdlib.h>
#include "translate.h"

int access(int frame, int offset) { //guranteed to be in memory, since after tlb and  possible pagewalk
	return physicalmem_array[frame][offset];
}

int load(int page, int frame) {
	FILE *file;
	char *inputFilename = "BACKING_STORE.bin";
	int *buffer;
	int i;

	file = fopen(inputFilename, "r");
	for(i=0; i<=255; i++) {
		int offset = page * 256 + i;
		buffer = (int*) malloc(8);
		fseek(file, offset, SEEK_SET);
		fread(buffer, 1, 1, file);
		physicalmem_array[frame][i] = buffer[0];
	}
	fclose(file);
	return 1;
}
