#include<iostream>
#include<graphics.h>
#include<cmath>
#include<cstdio>
#define HEIGHT 480
#define WIDTH 640
using namespace std;


long nCr(long n, long r){
	if(r == 0) return 1;
	if(n == r) return 1;
	if(r > n) return 0;
	return nCr(n-1, r-1) + nCr(n-1, r);
}


class Point{
	private:
		bool centerAsOrigin;
	public:
		double X;
		double Y;
		Point(double x, double y, bool CAO){
			X = x;
			Y = y;
			centerAsOrigin = CAO;
		}
		Point(){
			centerAsOrigin = false;
			X = 0;
			Y = 0;
		}
		Point operator+(Point a){
			Point temp;
			temp.X = this->X + a.X;
			temp.Y = this->Y + a.Y;
			return temp;
		}
		
		Point operator*(double a){
			Point temp;
		
			temp.X = this->X * a;
			temp.Y = this->Y * a;
			return temp;
		}
};


void DrawCurve(Point *p, long N, int color){
	
	// draw the lines joining control points
		//	printf("%lf %lf\n",put.X, put.Y);
	for(long i = 0;i<N-1;i++) line(p[i].X, p[i].Y, p[i+1].X, p[i+1].Y);

	//double p = 0;
	for(double t = 0;t<=1;t+=0.0001){
		//printf("%lf \n", t);
		Point put;
		put.X = 0;
		put.Y = 0;
		for(long i = 0;i<N;i++){
			Point x(0, 0, false);
			x = (p[i]*pow(t, i));
			//cout<<pow(t, i)<<" "<<pow(1-t, N-i-1)<<" "<<nCr(N-1,i)<<endl;;
		//	printf("%lf %lf\n",put.X, put.Y);
			x = (x*pow(1-t, N-1-i));
			x = x*nCr(N-1, i);

			put = put + x;
			//printf("%lf %lf\n",put.X, put.Y);
		}
		//printf("%lf %lf \n", put.X, put.Y);
		putpixel(put.X, put.Y, color);

	}

}


int main(){
	long N;
	cout<<"Enter the number of points : ";
	cin>>N;
	Point *p;
	int gdriver= DETECT, gmode;
	p = new Point[N];
	for(int i = 0;i<N;i++){
		cout<<"Enter "<<i<<" point : ";
		cin>>p[i].X>>p[i].Y;
	}
	initgraph(&gdriver, &gmode, NULL);

	DrawCurve(p, N, RED);
	getchar();
	closegraph();
	return 0;
}

