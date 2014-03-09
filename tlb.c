/*
 * TLB Functions
 * 
 *tlb_lookup checks if the page requests is in the tlb
 * returns the frame number if it is, return -1 if miss
 *
 *tlb_update updates a new page into tlb
 *allocates first empty space possible
 *if tlb is full, each entry holds a counter of the last memory access
 * it was used. Replace the entry with the lowered counter.
 */
#include <stdio.h> 
#include <stdlib.h>
#include "translate.h"

int tlb_lookup(int page) {
	int i;
	for(i=0; i<=15; i++) {
		if(tlb_array[i][0] == page) {
			tlb_array[i][2] = translate_counter; 
			return tlb_array[i][1];
		}	
	}
	return -1;
}

int tlb_update(int page,int frame) {
	int i;
	for(i=0; i<=15; i++) { //check for empty 
		if(tlb_array[i][0] == -1) { 
			tlb_array[i][0] = page;
			tlb_array[i][1] = frame;
			tlb_array[i][2] = translate_counter;
			return 1;
		}
	}
	//not empty, must choose one to kick out
	int min = tlb_array[0][2];
	int min_holder = 0;
	printf("MIN HOLDER: %i", min_holder);
	for(i=1; i<=15; i++) {  //check for smallest tlb_counter
		if(tlb_array[i][2] < min) {
			min = tlb_array[i][2];
			min_holder = i;
		}
	}
	tlb_array[min_holder][0] = page;
	tlb_array[min_holder][1] = frame;
	tlb_array[min_holder][2] = translate_counter;
	return 2;
} 

