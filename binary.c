/* Binary functions
 *
 *bin2dec returns the decimial int of an 8char binary
 * int start indicates where to start so the function 
 * can be used for both the page and offset
 *
 *dec2bin prints a decimal to its binary decimal
 *ugly mass printing of each digit
 */

#include <stdio.h> 
#include <stdlib.h>

int bin2dec(char *line,int start) {
	int logical = 0;
	int digit = 0;
	while(digit < 8) {
		char c = line[start];
		if(c == '1') {
			logical = logical * 2 + 1;
		} else if (c == '0') {
			logical *=2;
		}
		start++;
		digit++;
	}
	return logical;
}

void dec2bin(int frame, char* offset) {
	int physical[8] = {0};
	int i = 0;
    while(frame!=0){
		physical[i]= frame % 2;
		frame = frame / 2;
		i++;
    }
	printf("Physical Address: ");
	for(i =7; i >=0; i--) {
		printf("%i", physical[i]);
	}
	printf(" ");
	for(i =24; i <= 31; i++) {
		printf("%c", offset[i]);
	}
	printf("\n");
}
