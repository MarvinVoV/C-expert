#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *name;
	char ch;
	while((ch = getopt(argc, argv, "ae:")) != EOF){
		switch(ch){
			case 'a':
				printf("output a\n");
				break;
			case 'e':
				name = optarg;
				break;
			default:
				fprintf(stderr, "Unkown option:'%s'\n", optarg);
		}
		argc -= optind;
		argv += optind;
	}
	

	return 0;
}
