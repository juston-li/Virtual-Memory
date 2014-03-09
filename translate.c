/*
 *Main address translatation function
 *Reads Address.txt file, initializes data structures
 *Then calls functions to convert to binary, lookup tlb
 *lookup page table if tlb miss, then return the memory request
 *
 *@Juston Li
*/

#include <stdio.h> 
#include <stdlib.h>
#include "translate.h"

int main( int argc, char *argv[]) {
	FILE *file;
	char *inputFilename = argv[1];

	file = fopen(inputFilename, "r");

	if (file == NULL) {
		fprintf(stderr, "Can't open file!\n");
		return 0;
	} else {
		int i,j;
		char line [34];
		translate_counter = 0;
		physicalmem_counter = 0;
		tlb_hit = 0;
		pagefault = 0;
		//initialize arrays
		for (i=0; i<=15; i++){
			for (j=0; j<2; j++ ){
				tlb_array[i][j] = -1; //page,frame,last used
			}
		}
		for (i=0; i<=255; i++){
			pagetable_array[i] = -1; //page number
		}

		while ( fgets ( line, sizeof line, file ) != NULL ) {
			printf("Logical Address: %s",line);

			int page = bin2dec(line,16);
			int offset = bin2dec(line,24);
			printf("Page: %i\n", page);
			printf("Offset: %i\n", offset);

			int frame = tlb_lookup(page);
			if (frame >= 0) {
				tlb_hit++;
			} else if (frame == -1) { //tlb miss
				pagetable_lookup(page); //pagetable updates tlb after walk
				frame = tlb_lookup(page);  //certain hit
			}
			printf("Frame: %i\n", frame);
			dec2bin(frame,line); //print physical address

			int value = access(frame,offset);
			printf("Value: %i\n\n", value);

			translate_counter++;
		}
	}
	/*debug*/
	int i;
	for (i=0; i<=15; i++){
		printf("tlb[%i] = %i, %i, %i \n", i, tlb_array[i][0], tlb_array[i][1],tlb_array[i][2]);
	}
	/*
	for (i=0; i<=255; i++){
		printf("page[%i] = %i \n", i, pagetable_array[i]);
	}
	for (i=0; i<=15; i++){
		printf("physicalmem[%i] = %i, %i, %i \n", i, physicalmem_array[i][0], physicalmem_array[i][1],physicalmem_array[i][2]);
	}
	*/
	float tlb_hitrate = tlb_hit /(float) translate_counter;
	float  pagefault_rate = pagefault / (float)translate_counter;
	printf("TLB Hitrate:%f | Pagefault Rate:%f | TLB hits:%i | Pagefaults:%i | Total Memory requests:%i\n", 
		tlb_hitrate, pagefault_rate, tlb_hit, pagefault, translate_counter);
	fclose(file);
	return 1;
}
