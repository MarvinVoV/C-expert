#include <stdio.h>
#include <stdlib.h>

struct point{
	int x;
	int y;
};

int main(){
	struct point *p;
	p=(struct point *)malloc(sizeof(struct point));
	p->x=50;
	p->y=100;
	printf("x=%d y=%d\n",p->x,p->y);

	free(p);
	return 0;
}
