#include<iostream>
#include<graphics.h>
#define HEIGHT 480
#define WIDTH 640
#define X(x) x+(WIDTH/2)
#define Y(y) (HEIGHT/2) - y

using namespace std;


void putpixelo(int x, int y, int color){

	setlinestyle(SOLID_LINE, 1, 3);
	line(X(-100), Y(100), X(100), Y(100));
	putpixel(X(x), Y(y),color);
	return;
}


int drawEllipse(int rx, int ry){

	int x = 0, y = ry;
	double p1 = ry*ry - rx*rx*ry + rx*rx/4;

	putpixelo(x, y, RED);
	while(2*rx*rx*y >= 2*ry*ry*x){
		
		if(p1 < 0){
			x+=1;
			y = y;
			p1 = p1 + 2*ry*ry*x + ry*ry;
			
		}else{
			x+=1;
			y-=1;

			p1 = p1+2*ry*ry*x + ry*ry - 2*rx*rx*y;
		
		}

		putpixelo(x, y, RED);
		putpixelo(-x,y,YELLOW);
		putpixelo(-x,-y, GREEN);
		putpixelo(x, -y, BLUE);
	}

	double p2 = ry*ry*(x+0.5)*(x+0.5) + rx*rx*(y-1)*(y-1) - rx*rx*ry*ry;

	while(x != rx && y != 0){
		
		if(p2 > 0){
			
		      y-=1;
		      x = x;
		      p2 = p2 - 2*rx*rx*y + rx*rx;

		}else{
		
			y-=1;
			x+=1;

			p2 = p2 - 2*rx*rx*y + 2*ry*ry*(x) + rx*rx;
		}

				
		putpixelo(x, y, WHITE);
		putpixelo(-x,y,YELLOW);
		putpixelo(-x,-y, GREEN);
		putpixelo(x, -y, BLUE);
		
	}
	
		x = rx; 
		y = 0;
		
		putpixel(x, y, RED);
		putpixel(-x,y,YELLOW);
		putpixel(-x,-y, GREEN);
		putpixel(x, -y, BLUE);

	return 0;

}


int main(){
	
	int gd = DETECT,gm;

	initgraph(&gd, &gm, NULL);

	line(X(-(WIDTH/2)), Y(0), X(WIDTH/2), Y(0));
	line(X(0), Y(HEIGHT/2), X(0), Y(-HEIGHT/2));
	drawEllipse(200, 100);
	drawEllipse(201, 101);
	drawEllipse(199, 99);
	drawEllipse(202, 102);
	drawEllipse(203, 103);
	drawEllipse(204, 104);
	drawEllipse(205, 105);
	getchar();

	closegraph();



	return 0;
}
