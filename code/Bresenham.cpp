#include<iostream>
#include<graphics.h>
#include<cmath>
#define point struct Point
using namespace std;

struct Point {

	double x;
	double y;

};


void LineBresenham(point p1, point p2, int color){

	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	double pi = 2*dy - dx;
	long x, y;
	x = (long) p1.x;
	y = (long) p1.y;
	
	for(int i = 0;i < dx; i++){
		if(pi <= 0){
			x += 1;
			pi = pi + 2*dy;
		}
		if(pi> 0){
			x += 1;
			y += 1;
			pi = pi + 2*dy - dx;
		}

		putpixel(x, y, color);

	}
	return;
}



int main(){
	point p1,p2;
	int gdriver = DETECT, gmode;
	cout<<"Enter the first point : "<<endl;
	cin>>p1.x>>p1.y;
	cout<<"Enter the second point : "<<endl;
	cin>>p2.x>>p2.y;
	initgraph(&gdriver, &gmode, NULL);	
		
	LineBresenham(p1, p2, RED);


	getchar();
	closegraph();
	

	return 0;
}

