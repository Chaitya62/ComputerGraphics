#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define HEIGHT 480
#define WIDTH 640
#define X(x) x+WIDTH/2
#define Y(y) HEIGHT/2 - y
#define object struct Object

using namespace std;

struct Object{

	double M[100][100];
	int len;
};

class Transform{
	private:
		object p;
	public:
		Transform(object a){
			p = a;
		}

		object multiply(object a, object b){
			object x;
			for(int i = 0;i<a.len;i++){
				for(int j = 0;j<b.len;j++){
					//cout<<a.M[i][0]<<" * "<<b.M[0][j]<<endl;
					//cout<<a.M[i][1]<<" * "<<b.M[1][j]<<endl;
					x.M[i][j] = a.M[i][0]*b.M[0][j] + a.M[i][1]*b.M[1][j];
				}
			}

			x.len = a.len;
			return x;
		}

		object add(object a, object b){
			object x;

			for(int i = 0;i<a.len;i++){
				for(int j = 0;j<2;j++){
				 x.M[i][j] = a.M[i][j] + b.M[i][j];
				}
			}

			x.len = a.len;
			return x;
		}

		void draw(object a){
			for(int i = 0;i<a.len;i++){
				line(X(a.M[i][0]), Y(a.M[i][1]), X(a.M[(i+1)%a.len][0]), Y(a.M[(i+1)%a.len][1]));
			}
			return;
		}

		object rotate(double deg){
			double rad = deg * (3.14)/180;

			double cosx = cos(rad);
			double sinx = sin(rad);

				
			object rot;
			rot.M[0][0] = cosx;
			rot.M[0][1] = sinx;
			rot.M[1][0] = -1*sinx;
			rot.M[1][1] = cosx;
			rot.len = 2;

			
			object f = multiply(p, rot);

			return f;
		
		}

		object translate(double tx, double ty){
			object trans;
			
			for(int i = 0;i<p.len;i++){
				trans.M[i][0] = tx;
				trans.M[i][1] = ty;
			}

			object f = add(p, trans);

			return f;
		}

		object shear(double shx, double shy){
			object sh;

			sh.M[0][0] = 1;
			sh.M[1][0] = shx;
			sh.M[0][1] = shy;
			sh.M[1][1] = 1;
			sh.len = 2;

			object f = multiply(p, sh);
			
			return f;

		}


		object reflect(char ch){

			object refl;

			switch(ch){
			
				case 'x':
					refl.M[0][0] = 1;
					refl.M[1][0] = 0;
					refl.M[0][1] = 0;
					refl.M[1][1] = -1;
					refl.len = 2;
					break;
					
				case 'y':
					refl.M[0][0] = -1;
					refl.M[1][0] = 0;
					refl.M[0][1] = 0;
					refl.M[1][1] = 1;
					refl.len = 2;
					break;

				case 'e':
					refl.M[0][0] = 0;
					refl.M[1][0] = 1;
					refl.M[0][1] = 1;
					refl.M[1][1] = 0;
					refl.len = 2;

					break;
					

				case 'o':
					refl.M[0][0] = -1; 
					refl.M[1][0] = 0;
					refl.M[0][1] = 0;
					refl.M[1][1] = -1;
					refl.len = 2;
					break;
			
			}

			object f = multiply(p, refl);


			return f;
		
		
		}



};


void drawAxis(){
	
	line(X((-1*WIDTH/2)), Y(0), X(WIDTH/2), Y(0));
	line(X(0), Y(HEIGHT/2), X(0), Y(-1*HEIGHT/2));
	return;

}


void draw(object old, object ne){

	int gd = DETECT, gm;
	Transform a(old);
	
	char c;
	initgraph(&gd, &gm, NULL);
	
	drawAxis();

	a.draw(old);
	a.draw(ne);

	scanf("%c", &c);
	closegraph();

}


int main(){

	object x;
	int len;
	printf("Enter the number of points in the polygon : ");
	scanf("%d", &len);
	for(int i = 0;i<len;i++){
		printf("\nEnter the %d point: ", i+1);
		scanf("%lf %lf", &(x.M[i][0]), &(x.M[i][1]));
	}
	x.len = len;

	
	Transform a(x);

	bool loop = true;
	while(loop){
		int ch;
		char rf;
		object n;
		printf("\n1. Rotate\n 2. Translate\n 3.Shear\n 4.Reflect\n 5. Exit\n");
		scanf("%d", &ch);
		switch(ch){
			case 1:
				double deg;
				printf("Enter the degree of rotation : ");
				scanf("%lf", &deg);
				n = a.rotate(deg);
				//cout<<n.M[0][1]<<","<<n.M[0][1]<<endl;
				break;


			case 2:
				double tx,ty;
				printf("\nEnter translation x and translation y : ");
				scanf("%lf %lf", &tx, &ty);
				n = a.translate(tx, ty);

				break;


			case 3:
				double shx,shy;
				printf("\nEnter shear x and shear y : ");
				scanf("%lf %lf", &shx, &shy);
				n = a.shear(shx, shy);
				break;
		
			case 4:
				
				printf("\n x: reflect about x\n y: reflect about y\n e: reflect about x=y\n o: reflect about origin\n");
				cin>>rf;
				//printf("%c", rf);
				n = a.reflect(rf);
				break;
			
			case 5:
				loop = false;
				break;
		}

		if(loop) draw(x, n);

	
	}

	return 0;

}
