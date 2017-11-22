#include<iostream>
#include <X11/Xlib.h>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<thread>
#include<graphics.h>
#define width  640
#define height 480

using namespace std;

class Game{

	private: 
		int gmode, gdriver = DETECT;
		int errorcode;
		bool game_running = 1;
		

	public: 
	
	Game(){
		//XInitThreads();
	}
		
	static int logMessage(){
			printf("Hello, World!");
			return 0;
		}

		int start(){
			
			try{ 
				initgraph(&gdriver, &gmode, NULL);
			}catch(const char* msg){
				printf("Graphics Error : %s \n",msg);
				return -1;
			}
			//thread second(logMessage);
			while(game_running){
				
				int c = getchar();
				takeInput(c);
			}
			
			closegraph();
						
		}
		
		int takeInput(int c){
			printf("%d \n", c);
			if(c == 'q' || c == 'Q' ) game_running = false; 
		}
		
		 

		int redraw(){
			cleardevice();
			
		}
		
		
		





};



int main(){
	printf("Press return or Enter to start !\n");
	getchar();
	Game game;
	game.start();
	//thread second(Game::logMessage);

	return 0;
}
