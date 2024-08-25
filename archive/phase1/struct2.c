#include <stdio.h>
#include <stdlib.h>

static struct point{
	int x;
	int y;
};
static struct rect{
	struct point p1;
	struct point p2;
};


int main(){
	struct point p,*pp;
	pp=&p;
	p.x=100;
	p.y=200;
	pp->x=50; // equals to (*pp).x=50
	printf("sizeof p %ld\n",sizeof(pp));
	printf("x=%d y=%d\n",pp->x,pp->y);
	printf("x=%d y=%d\n",(*pp).x,(*pp).y);

	return 0;
}
