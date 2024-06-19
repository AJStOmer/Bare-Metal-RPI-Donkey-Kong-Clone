#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "dk.h"
#include "square.h"
#include "spider.h"
#include "ball.h"
#include "gameOver.h"
char strGoat[17] = "Akash the G.O.A.T";
char strEnd[18] = "THANKS FOR PLAYING";

//main
int main(){
	//our gameOn variable
	int gameOn = 1;

	//initialize our frame buffer and gpio lines
	fb_init();
	initGPIO();
	
	//makes the current display screen the main menu
	int flag = mainMenu();

	//if the player selects quit end on the first screen end game
	if(flag == 1){
		fillScreen(0);
		drawString(520,400,&strEnd,0xF);
		drawString(522,350,&strGoat,0xF);
		gameOn = 0;
	}

	//make flag equal to 1 for level 1
	flag = 1;
	//while loop for our game
	while(gameOn){	

		// levels loop
		while((flag != 0) && (flag != 5) && (flag != 6)){

			while(flag == 1){//flag = 1 is level 1
				flag = level1();
			}
			while(flag == 2){//flag = 2 is level 2
				flag = level2();
			}
			while(flag == 3){//flag = 3 is level 3
				flag = level3();
			}
			while(flag == 4){//flag = 4 is level 4
				flag = level4();
			}
		}

		// flag = 0 means we go to main menu
		if (flag == 0){
			
			flag = mainMenu();	// returns 1 if quit was pressed, 0 if start game

			if (flag == 1){//again if flag = 1 in main menu we quit game
				fillScreen(0);
				drawString(520,400,&strEnd,0xF);
				drawString(522,350,&strGoat,0xF);
				gameOn = 0;

			} else if (flag == 0){
				flag = 1;	// whiel flag = 1 in main menu come back to beginning of while and start scene 1 again
			}

		// this means we game over
		} else if (flag == 6){
			flag = gameOver(); // if a level returns 6 game is over
		
		// this means we won the last level now we return for the main menu
		} else if (flag == 5){//flag = 5 means game won
			flag = 0;
		}	
	}
	return 0; // should stop program 
}

