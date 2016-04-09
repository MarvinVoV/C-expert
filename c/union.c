#include <stdio.h>
#include <stdlib.h>

typedef union{
	short count;
	float weight;
	float volume;
} quantity;

typedef struct {
	const char *name;
	const char *country;
	quantity amount;
} fruit_order;

int main(void){
	quantity q = {4}; // this means the quantity is a count of 4

	printf("quantity count is %d\n", q.count);

	quantity z = {.weight=2.0};
	printf("quantity weight is %f\n", z.weight);

	fruit_order apples = {"apple", "england", .amount.weight=4.2};
	printf("This order contains %2.2f lbs of %s\n", apples.amount.weight, apples.name);
	return 0;
}
