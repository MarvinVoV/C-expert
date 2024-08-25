#include <stdio.h>


enum colors {
	RED, GREEN, PUCE
};

typedef enum{
	COUNT, POUNDS, PINTS
} unit_of_measures;


int main(void){
	unit_of_measures unit = COUNT;
	switch(unit){
		case PINTS:
			printf("pints");
			break;
		case POUNDS:
			printf("pounds");
			break;
		case COUNT:
			printf("count");
			break;
		default:
			printf("nothing");
	}	
	printf("\n");
	return 0;
}
