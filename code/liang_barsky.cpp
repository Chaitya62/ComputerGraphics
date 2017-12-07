#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#define HEIGHT 480
#define WIDTH 640
#define X(x) x + WIDTH/2
#define Y(y) WIDTH/2 - y


using namespace std;

double minH, maxH, minW, maxW;

void drawAxis(){
	
	line(X(-WIDTH/2), Y(0), X(WIDTH/2), Y(0));
	line(X(0),Y(HEIGHT/2), X(0), Y(-HEIGHT/2) );
	return;
}

void drawWindow(){
	line(X(minW), Y(minW), X(maxW), Y(minW));
	line(X(minW), Y(minW), X(minW), Y(maxW));
	line(X(maxW), Y(maxW), X(maxW), Y(minW));
	line(X(maxW), Y(maxW), X(minW), Y(maxW));
	return;
}



int main(){
	minH = 100;
	maxH = 200;
	minW = 100;
	maxW = 200;
	double xa;

	double p[4],q[4];

	double x1,x2,y1,y2;


	printf("Enter the first point  :");
	scanf("%lf %lf", &x1, &y1);
	printf("Enter the second point : ");
	scanf("%lf %lf", &x2, &y2);


	double temp = min(x1, x2);
	double temp2 = max(x1,x2);

	x1 = temp;
	x2 = temp2;

	temp = min(y1,y2);
	temp2 = max(y1,y2);

	y1 = temp;
	y2 = temp2;

	double delx,dely;
	delx = x2-x1;
	dely = y2-y1;

	p[0] = -1*delx;
	p[1] = delx;
	p[2] = -1*dely;
	p[3] = dely;

	q[0] = x1-minW;
	q[1] = maxW-x1;
	q[2] = y1-minH;
	q[3] = maxH-y1;


	double tmin = 0 ,tmax = 1;

	bool flag = false;
	

	for(int i = 0;i<4;i++){

		if(p[i] == 0 && q[i] < 0){
			flag = true;
			xa = i;
			break;
		}

	
		if(p[i] != 0){
				double tx = q[i]/p[i];
			if(p[i]<0){
				tmin = max(tmin, tx);
			}else{
				tmax = min(tmax, tx);
			}
		}
	
	}


	bool isOutSide = false;
	double nx1,ny1,nx2,ny2;
	
	if(flag){
		if(xa == 0 || xa == 1){
			ny1 = max(minH, y1);
			ny2 = min(maxH, y2);
			nx1 = x1;
			nx2 = x2;
		
		}else{
			ny1 = y1;
			ny2 = y2;
			nx1 = max(minW, x1);
			nx2 = min(maxW, x2);
		
		}
	
	}else{

		if(tmin>tmax) isOutSide = true;
		nx1 = x1 + tmin*(delx); 
		ny1 = y1 + tmin*(dely);

		nx2 = x1 + tmax*(delx);
		ny2 = y1 + tmax*(dely);
	}


	//cout<<nx1<<","<<ny1<<" : "<<nx2<<", "<<ny2<<endl;
	int gd = DETECT, gm;
	
	char c;

	initgraph(&gd, &gm, NULL);

	drawAxis();
	drawWindow();
	line(X((int)x1),Y((int)y1),X((int)x2),Y((int)y2));

	scanf("%c", c);

	cleardevice();

	drawAxis();
	drawWindow();
	if(!isOutSide)
		line(X((int)nx1), Y((int)ny1), X((int)nx2), Y((int)ny2));
	
	scanf("%c", c);

	closegraph();

	return 0;

}
