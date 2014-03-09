/*
 *Pagetable functions
 *
 *Checks the page table if the given page is valid
 *If it is update the cache and finish, TLB will be immediatly looked up for 
 * a certain hit
 *
 *If the page is not valid, load the page into the physicalmem_array
 *update the pagetable with the corresponding frame the page was placed in
 * update the TLB
 */
#include <stdio.h> 
#include <stdlib.h>
#include "translate.h"

int pagetable_lookup(int page) {
	if(pagetable_array[page] >= 0) {
		tlb_update(page, pagetable_array[page]); //store in cache
		return 1;
	} else { //page fault
		pagefault++;
		load(page, physicalmem_counter);
		pagetable_array[page] = physicalmem_counter; //store in page table
		tlb_update(page, physicalmem_counter); //store in cache
		physicalmem_counter++;
	}		
	return -1;
}
