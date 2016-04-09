#include <stdio.h>
#include <stdlib.h>

struct fish{
	const char *name;
	const char *species;
	int teeth;
	int age;
};

// now phone will become an alias for 'struct cell_phone'
typedef struct cell_phone{
	int cell_no;
	const char *wallpaper;
	float minutes_of_charge;
} phone;

typedef struct {
	const char *name;
	int age;
}person;

void print_fish(struct fish f){
	printf("name is %s\n", f.name);
	printf("species is %s\n", f.species);
	printf("teeth is %d\n", f.teeth);
	printf("age is %d\n", f.age);

}

void print_fish2(struct fish *f){
	// the parentheses are really important. The code will break without the them
	printf("name is %s\n", (*f).name);
	printf("species is %s\n", f->species);
	printf("teeth is %d\n", f->teeth);
}

int main(void){
	// struct fish is the data type, 'snappy' is the variable
	struct fish snappy = {"Snappy", "Piranaha", 69, 4};	
	// this will create a brand new copy of struct 
	struct fish test = snappy;
	test.age = 30;
	printf("Storage size of struct fish %ld\n", sizeof(struct fish));
	printf("%ld\n", sizeof(snappy.age));
	print_fish(snappy);
	print_fish(test);
	print_fish2(&snappy);
	phone my_phone = {2, "wallpaper", 20.3};
	printf("charge is %f\n", my_phone.minutes_of_charge);
	person p = {"tom", 32};
	printf("%s\n", p.name);
	return 0;
}
