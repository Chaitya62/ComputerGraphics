#include<iostream>
#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define G "C:\\TURBOC3\\BGI"
#define HEIGHT 480
#define WIDTH 640
#define X(x) x+(WIDTH/2)
#define Y(y) (HEIGHT/2)-y
#define T (1<<4)
#define B (1<<3)
#define L (1<<2)
#define R (1<<1)

using namespace std;

int minH,maxH,minW,maxW;



int drawline(int, int, int, int);
int drawAxis(void);

int getTBLR(int x, int y){
	int ans = 0;
	if(y > maxH) ans |= (1 << 4);
	if(y < minH) ans |= (1 << 3);
	if(x < minW) ans |= (1 << 2);
	if(x > maxW) ans |= (1 << 1);

	return ans;
}


int clipLine(int x1, int y1, int x2, int y2){
	int start = 0,end = 0;

	//TBLR
	start = getTBLR(x1, y1);
	//cout<<start<<endl;
	end = getTBLR(x2, y2);
	//double slope = (y2-y1)/(x2-x1);
	int code = start & end;
	int accept = 0;

	while(1){

		//cout<<"here"<<endl;
		//printf("here\n");
		//cout<<"start : "<<start<<" end : "<<end<<endl;
		//cout<<"x1 : "<<x1<<" y1: "<<y1<<endl;
		//cout<<"x2: "<<x2<<" y2: "<<y2<<endl;

		if(start == 0 && end == 0){
			accept = 1;
			break;
		}
		if(start & end){
			break;
		}



		int curr;
		int x,y;

		if(start != 0){
			curr = start;
		}else{
			curr = end;
		}



			if(curr&T){
				x = x1 + (x2-x1)*(maxH-y1)/(y2-y1);
				y = maxH;
			}

			else if(curr&B){
				x = x1 + (x2-x1)*(minH-y1)/(y2-y1);
				y = minH;
			}

			else if(curr&L){
				x = minW;
				//cout<<"here"<<endl;
				y = y1 + (y2-y1)*(minW-x1)/(x2-x1);
				//cout<<x<<y<<endl;

			}else if(curr & R){
				x = maxW;
				y = y1 + (y2-y1)*(maxW-x1)/(x2-x1);
			}
		if(curr == start){

			x1 = (int)x;
			y1 = (int)y;
			start = getTBLR(x1,y1);
		
		}else{

			x2 = (int)x;
			y2 = (int)y;
			end = getTBLR(x2, y2);
		}

	}

	if(accept){
		//printf("%d,%d  %d,%d\n",x1,y1,x2,y2);
		//cleardevice();
		//setcolor(RED);
		drawline(x1,y1,x2,y2);

	}else{

		printf("Line cannot be clipped !");

	}
	return 0;
}

int drawline(int x1, int y1, int x2, int y2){
	cleardevice();
	drawAxis();

	line(X(minW), Y(minH), X(maxW), Y(minH));
	line(X(minW), Y(minH), X(minW), Y(maxH));
	line(X(minW), Y(maxH), X(maxW), Y(maxH));
	line(X(maxW), Y(maxH), X(maxW), Y(minH));

	line(X(x1), Y(y1), X(x2), Y(y2));

	return 0;
}

int drawAxis(){

	line(X(-1*WIDTH/2),Y(0), X(WIDTH/2), Y(0));
	line(X(0), Y(HEIGHT/2), X(0), Y((-1*HEIGHT/2)));

	return 0;
}

int main(){
	//clrscr();
	cout<<(1<<2)<<endl;
	int gd = DETECT,gm;
	int x1,x2;
	int y1,y2;
	printf("Enter the starting point (x, y) : ");
	scanf("%d %d", &x1,&y1);
	printf("\nEnter the ending point (x, y): ");
	scanf("%d %d", &x2, &y2);

	minW = 100;
	maxW = 200;
	minH = 100;
	maxH = 200;

	//cin>>minW>>maxW>>minH>>maxH;

	//clipLine(x1, y1, x2, y2);


	//return 0;


	//clipLine(x1,y1,x2,y2);
	//return 0;
	char c;

	initgraph(&gm, &gd, NULL);

      //	drawAxis();

	drawline(x1,y1,x2,y2);

	//getch();
	scanf("%c", &c);
	
	clipLine(x1,y1,x2,y2);
	scanf("%c", &c);
	//getch();
	closegraph();
}
