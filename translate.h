//data structures
int tlb_array[16][3];
int pagetable_array[256];
int physicalmem_array[256][256];
int translate_counter;
int physicalmem_counter;

//statitics
int tlb_hit;
int pagefault;

//binary converion functions
int bin2dec(char *line,int start);
void dec2bin(int frame, char* offset);

//tlb functions
int tlb_lookup(int page);
int tlb_update(int page,int frame);

//page table functions
int pagetable_lookup(int page);

// i/o functions
int access(int frame, int offset);
int load(int page, int frame);
