#include<iostream>
#include<cmath>
#include<graphics.h>
#define point struct Point
using namespace std;


struct Point{
	double x;
	double y;
};

int LineDDA(point p1, point p2, int color){


	// calculate the initial parameters
	double dx = (p2.x - p1.x); 
	double dy = (p2.y - p1.y);
	long steps = (dx > dy ? (long) dx : (long) dy);
	double xi = dx / (double) steps;
	double yi = dy / (double) steps;
	double x = p1.x, y= p1.y;

	// draw the first point 
	putpixel(x, y, color);


	//draw the line
	for(long i = 0; i<steps; i++){
		x += xi;
		y += yi;
		putpixel(x, y, color);
	}
	return 0;
}


int main(){
	point p1,p2;
	cout<<"Enter the first point : ";
	cin>>p1.x>>p1.y;
	cout<<"Enter the second point : ";
	cin>>p2.x>>p2.y;
	int gdriver = DETECT, gmode;

	// initialize graphics module

	initgraph(&gdriver, &gmode, NULL);
	LineDDA(p1, p2, RED);
	getchar();
	closegraph();

}