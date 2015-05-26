#include<stdio.h>
#include<stdlib.h>
struct point{
	int x;
	int y;
};
struct rect{
	struct point pt1;
	struct point pt2;
};

struct point makepoint(int x,int y){
	struct point p;
	p.x=x;
	p.y=y;
	return p;
}

struct point addpoint(struct point p1,struct point p2){
	p1.x+=p2.x;
	p1.y+=p2.y;
	return p1;
}
int main(){
	struct point p=(struct point)addpoint(makepoint(10,10),makepoint(100,100));
	printf("x=%d,y=%d\n",p.x,p.y);
    exit(0);
}
