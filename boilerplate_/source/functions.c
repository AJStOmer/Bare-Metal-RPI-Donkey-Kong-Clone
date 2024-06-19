#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "functions.h"
#include "spider.h"
#include "square.h"
#include "ball.h"
#include "dk.h"
#include "heart.h"
#include "squareBig.h"
#include "wall.h"
#include "trophy.h"
#include "star.h"
#include "gameOver.h"
#include "skeleton.h"
#include "coin.h"
#include "DkLogo.h"
#include "dkWin.h"

//struct made for value pack
struct pack{
	int PosX;
	int PosY;
};

//struct made for walls
struct staticObj{
	int PosX;
	int PosY;
};

//struct made for all enemies
struct enemies{
	int PosX;
	int PosY;
	int wall;
};

struct enemies spider1;
struct enemies spider2;

struct enemies skeleton1;

struct enemies spike1;
struct enemies spike2;
struct enemies spike3;
struct enemies spike4;
struct enemies spike5;
struct enemies spike6;
struct enemies spike7;
struct enemies spike8;
struct enemies spike9;
struct enemies spike10;

struct pack pack1;

struct staticObj wall1;
struct staticObj wall2;
struct staticObj wall3;
struct staticObj wall4;
struct staticObj wall5;
struct staticObj wall6;

struct staticObj coin1;
struct staticObj coin2;
struct staticObj coin3;
struct staticObj coin4;
struct staticObj coin5;
struct staticObj coin6;

//char arrays for printing strings
char strRestart[7] = "RESTART";
char strQuit[4] = "QUIT";
char strNames[33] = "by CAIO ARAUJO and AARON ST. OMER";
char strPress[11] = "PRESS START";
char strStart[10] = "START GAME";
char strQuitGame[9] = "QUIT GAME";
char strWon[7] = "YOU WON";
char strScore[6] = "SCORE:"; 
char strEmpty[11] = "           ";
char strTimeRem[15] = "TIME REMAINING:";


//method for writing to latch
void writeLATCH(int bit){

	if (bit == 1){
		gpio[7] = 1 << 9;
	} else {
		gpio[10] = 1 << 9;		
	}
}

//method for writing to clock
void writeCLOCK(int bit){

	if (bit == 1){
                gpio[7] = 1 << 11;
        } else {
                gpio[10] = 1 << 11;
        }
}

//method to wait in micro seconds
void wait(int time){

	unsigned *clo = (unsigned*)CLO_REG;
	unsigned c = *clo + time; 

	while (c > *clo);
}

//method to initialize the clock latch and data lines
void initGPIO(){

	INP_GPIO( CLK );
	OUT_GPIO( CLK );
	
	INP_GPIO( LAT );
	OUT_GPIO( LAT );

	INP_GPIO( DAT );
}

// reads the data line and returns value 
int readDATA(){
	int v;

	v = ((gpio[13] >> 10) & 1);	
	return v;
}	

//method to print any buttons that were pressed
int returnButtons(){

	for (int i=0; i<=11; i++){

		if (buttons[i] == 0){

			if (i == 3){
				return 5; //START PRESSED

			} else if (i == 4){
				return 1;	//up
					
			} else if (i == 5){
				return 2;	//down
			
			} else if (i == 6){
				return 3;	//left

			} else if (i == 7){
				return 4;	//right
				
			} else if (i == 8){
				return 6;	// A

			} else if(i == 9) {
				return 0;	//nothing
			}
		}	
	}
	return 0;
}


// change so its just returning 1 number - the button that is being pressed 
int ReadSnes(){
	
	while (1){
	
		for (int i=0; i<=15; i++){//resets buttons array back to all unpressed
			buttons[i] = 1;
			buttonChecker[i] = 1;
		}
		
		writeCLOCK(1);//pulse clock
		writeLATCH(1);//pulse latch
	
		wait(12);//wait 12 micro seconds
		writeLATCH(0);//unpulse latch

		check = 0;

		for(int j = 0; j<16; j++){
				
			wait(6);//wait 6 micro seconds

			writeCLOCK(0);//write 0 to clock to unpulse

			wait(6);//wait 6 micro seconds

			int b = readDATA();// reads data line and returns if button is pressed 

			buttons[j] = b;//reads input from data line into button array
			
			writeCLOCK(1);//pulse clock
		}

		for(int i=0; i< 16; i++){//checks to see if there has been a new button change
			if(buttons[i] == buttonChecker[i]){
				check++;
			}
		}

		return(returnButtons());		
	}
}



//function for moving a Spider enemy
int moveSpiderH(int spiderPosX, int spiderPosY, int wall){
	if(wall == 0){
		if(spiderPosX+32 > 1020){
			wall = 1;
			return(wall);
		} else {
			drawImage(square.pixel_data,square.width, square.height, spiderPosX-1, spiderPosY);
			drawImage(spider.pixel_data, spider.width, spider.height, spiderPosX+1, spiderPosY);
			return(wall);
		}

	} else if(wall == 1){
		if(spiderPosX < 260){
			wall = 0;
			return(wall);
		} else {
			drawImage(square.pixel_data,square.width, square.height, spiderPosX+3, spiderPosY);			
			drawImage(spider.pixel_data, spider.width, spider.height, spiderPosX-1, spiderPosY);
			return(wall);
		}
	}
}


//function for checking if DK has come in contact with an enemy
void GeneralHitBox(int spiderPosX, int spiderPosY){
	//top check
	if((dkPosY+32 > spiderPosY && dkPosY +32 < spiderPosY+32) && (dkPosX > spiderPosX-32 && dkPosX < spiderPosX+32) ){
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);
		dkPosX = 292;
		dkPosY = 654;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		dkLives --;
		displayHearts(dkLives);
	}
	//bottom check
	if((dkPosY-32 < spiderPosY && dkPosY-32 > spiderPosY-32) && (dkPosX > spiderPosX-32 && dkPosX < spiderPosX+32) ){
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);
		dkPosX = 292;
		dkPosY = 654;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		dkLives--;
		displayHearts(dkLives);
	}
	
	//left check
	if((dkPosX+32 > spiderPosX && dkPosX+32 < spiderPosX+32) && (dkPosY > spiderPosY-32 && dkPosY< spiderPosY+32) ){
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);	
		dkPosX = 292;
		dkPosY = 654;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		dkLives --;
		displayHearts(dkLives);		
	}
	
	//right check
	if((dkPosX-32 < spiderPosX && dkPosX-32 > spiderPosX-32) && (dkPosY > spiderPosY-32 && dkPosY < spiderPosY+32) ){
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);
		dkPosX = 292;
		dkPosY = 654;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		dkLives --;
		displayHearts(dkLives);	
	}
}


//function for if dk has come in contact with a wall
void staticHitBox(int hitboxX, int hitboxY){
	if((dkPosY+32 > hitboxY && dkPosY +32 < hitboxY+32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX+32) ){
		drawImage(wall.pixel_data,wall.width, wall.height, hitboxX, hitboxY);
		dkPosY = dkPosY-dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY); 
	}
	//bottom check
	if((dkPosY-32 < hitboxY && dkPosY-32> hitboxY-32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX +32) ){
		drawImage(wall.pixel_data,wall.width, wall.height, hitboxX, hitboxY);
		dkPosY = dkPosY+dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
	}
	//left check
	if((dkPosX+32 > hitboxX && dkPosX+32 < hitboxX+32) && (dkPosY > hitboxY-32 && dkPosY< hitboxY+32) ){
		drawImage(wall.pixel_data,wall.width, wall.height, hitboxX, hitboxY);
		dkPosX = dkPosX-dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);	
	}
	
	//right check
	if((dkPosX-32 < hitboxX && dkPosX-32 > hitboxX-32) && (dkPosY > hitboxY-32 && dkPosY < hitboxY+32) ){
		drawImage(wall.pixel_data,wall.width, wall.height, hitboxX, hitboxY);
		dkPosX = dkPosX+dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
	}
}


//function for the skeleton to stop when it reaches walls and spikes
void enemyStaticHitBox(int hitboxX, int hitboxY){
		if((skeleton1.PosY+32 > hitboxY && skeleton1.PosY+32 < hitboxY+32) && (skeleton1.PosX > hitboxX-32 && skeleton1.PosX < hitboxX+32) ){
			skeleton1.PosY = skeleton1.PosY-skeletonSpeed;
			drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY); 
		}
		if((skeleton1.PosY-32 < hitboxY && skeleton1.PosY-32> hitboxY-32) && (skeleton1.PosX > hitboxX-32 && skeleton1.PosX < hitboxX +32) ){
			skeleton1.PosY = skeleton1.PosY+skeletonSpeed;
			drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY); 
		}
		if((skeleton1.PosX+32 > hitboxX && skeleton1.PosX+32 < hitboxX+32) && (skeleton1.PosY > hitboxY-32 && skeleton1.PosY< hitboxY+32) ){
			skeleton1.PosX = skeleton1.PosX-skeletonSpeed;
			drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY); 
		}
		if((skeleton1.PosX-32 < hitboxX && skeleton1.PosX-32 > hitboxX-32) && (skeleton1.PosY > hitboxY-32 && skeleton1.PosY < hitboxY+32) ){
			skeleton1.PosX = skeleton1.PosX+skeletonSpeed;
			drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY); 
		}
}

//function to determine if dk has reached a value pack and if so generate a random pack effect (extra lives, more speed, instant level win)
void packHitBox(int hitboxX, int hitboxY){
    void printf(char *str){
              uart_puts(str);
    }	
	int packHit = 0;
	int packEffect = 0;

	if((dkPosY+32 > hitboxY && dkPosY +32 < hitboxY+32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX+32) ){
		drawImage(square.pixel_data, square.width, square.height, pack1.PosX, pack1.PosY);
		pack1.PosX = 0;
		pack1.PosY = 0;
		dkPosY = dkPosY-dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY); 
		packHit = 1;

	}
	//bottom check
	if((dkPosY-32 < hitboxY && dkPosY-32> hitboxY-32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX +32) ){
		drawImage(square.pixel_data, square.width, square.height, pack1.PosX, pack1.PosY);	
		pack1.PosX = 0;
		pack1.PosY = 0;		
		dkPosY = dkPosY+dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		packHit = 1;
	}
	//left check
	if((dkPosX+32 > hitboxX && dkPosX+32 < hitboxX+32) && (dkPosY > hitboxY-32 && dkPosY< hitboxY+32) ){
		drawImage(square.pixel_data, square.width, square.height, pack1.PosX, pack1.PosY);	
		pack1.PosX = 0;
		pack1.PosY = 0;				
		dkPosX = dkPosX-dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		packHit = 1;
	}
	
	//right check
	if((dkPosX-32 < hitboxX && dkPosX-32 > hitboxX-32) && (dkPosY > hitboxY-32 && dkPosY < hitboxY+32) ){
		drawImage(square.pixel_data, square.width, square.height, pack1.PosX, pack1.PosY);	
		pack1.PosX = 0;
		pack1.PosY = 0;			
		dkPosX = dkPosX+dkSpeed;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		packHit = 1;
	}

	if(packHit == 1){
		packEffect = (dkPosX + dkPosY)%3;
		if(packEffect == 0){
			dkSpeed += 1;
			printf("speed");
		}else if(packEffect == 1){
			dkLives ++;
			displayHearts(dkLives);
			printf("life");				
		}else if(packEffect == 2){
			drawImage(square.pixel_data, square.width, square.height, dkPosX, dkPosY);		
			dkPosX = 940;
			dkPosY = 40;
			printf("level");		

		}
		packHit = 0;
	}
}


//function to move the skeleton and have it follow the player
void moveSkeleton(){
	int directionX = 0;
	int directionY = 0;

	if(dkPosX > skeleton1.PosX){
		directionX = skeletonSpeed;	
	} else if(dkPosX < skeleton1.PosX){
		directionX = -skeletonSpeed;
	} else {
		directionX = 0;
	}

	if(dkPosY > skeleton1.PosY){
		directionY = skeletonSpeed;	
	} else if(dkPosY < skeleton1.PosY){
		directionY = -skeletonSpeed;
	} else {
		directionY = 0;
	}
	
	drawImage(square.pixel_data, square.width, square.height, skeleton1.PosX, skeleton1.PosY);
	skeleton1.PosX+=directionX;
	skeleton1.PosY+=directionY;
	drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY);
}


//function for moving DK
void moveDK(){
	int a = ReadSnes();
	if(a == 1 && dkPosY > 4){//up
		//printf("UP\n\n");
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY-dkSpeed);
		dkPosY -= dkSpeed;
	}else if(a == 2 && dkPosY+32 < 714){//down
		//printf("DOWN\n\n");/
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);		
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY+dkSpeed);
		dkPosY += dkSpeed;
	}else if(a == 3 && dkPosX > 260){//left
		//printf("LEFT\n\n");
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);		
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX-dkSpeed, dkPosY);
		dkPosX -= dkSpeed;
	}else if(a == 4 && dkPosX+32 < 1020){//right
		//printf("RIGHT\n\n");
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);		
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX+dkSpeed, dkPosY);
		dkPosX += dkSpeed;
	} else if(a == 0){
		//printf("STAY\n\n");
	}
}


//function to display the players hearts
void displayHearts(int numHeart){
	int size = 100;

	for (int i = 0; i < numHeart+1; i ++){
		drawImage(squareBig.pixel_data,squareBig.width, squareBig.height, 96, size);
		size += 64;
	}

	size = 100;
	for(int i =0; i < numHeart; i++){
		drawImage(heart.pixel_data, heart.width, heart.height, 96, size);
		size += 64;
	}

}

//function to check if dk has picked up any coins
int pickUpCoin(int hitboxX, int hitboxY){
	if((dkPosY+32 > hitboxY && dkPosY +32 < hitboxY+32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX+32) ){
		drawImage(square.pixel_data, square.width, square.height, hitboxX, hitboxY);
		numCoins++;
		return(1);
	}
	//bottom check
	if((dkPosY-32 < hitboxY && dkPosY-32> hitboxY-32) && (dkPosX > hitboxX-32 && dkPosX < hitboxX +32) ){
		drawImage(square.pixel_data, square.width, square.height, hitboxX, hitboxY);
		numCoins++;
		return(1);
	}
	//left check
	if((dkPosX+32 > hitboxX && dkPosX+32 < hitboxX+32) && (dkPosY > hitboxY-32 && dkPosY< hitboxY+32) ){
		drawImage(square.pixel_data, square.width, square.height, hitboxX, hitboxY);
		numCoins++;
		return(1);
	}
	
	//right check
	if((dkPosX-32 < hitboxX && dkPosX-32 > hitboxX-32) && (dkPosY > hitboxY-32 && dkPosY < hitboxY+32) ){
		drawImage(square.pixel_data, square.width, square.height, hitboxX, hitboxY);
		numCoins++;
		return(1);
	}
}


//function to check if dk has reached the trophy
int trophyHit(int trophyPosX, int trophyPosY){
	//bottom check
	if((dkPosY-32 < trophyPosY && dkPosY-32> trophyPosY-44) && (dkPosX > trophyPosX && dkPosX < trophyPosX +70) ){
		return(1);
	}

	// //left check
	if((dkPosX+32 > trophyPosX && dkPosX+32 < trophyPosX+32) && (dkPosY > trophyPosY-32 && dkPosY< trophyPosY+32) ){
		return(1);
	}

	return(0);
}


//function to randomly place a value pack after 30 seconds
void makeValuePack(){
	pack1.PosX = (((dkPosY + dkPosX)*dkPosY)%988);
	if(pack1.PosX < 256){
		pack1.PosX = pack1.PosX + 256;
	}
	
	pack1.PosY = (((dkPosY + dkPosX)*dkPosX)%688);
	
	drawImage(star.pixel_data, star.width, star.height, pack1.PosX, pack1.PosY);			
}


//function to draw spikes horizontally for the last level
void drawSpikesH(int posX, int posY){

	for (int i=0; i <= 21; i++){
		drawImage(ball.pixel_data, ball.width, ball.height, posX, posY);	
		posX += 35;
	}
}

//function to draw spikes vertically for the last level
void drawSpikesV(int posX, int posY){

	for (int i=0; i <= 18; i++){
		drawImage(ball.pixel_data, ball.width, ball.height, posX, posY);	
		posY += 34;
	}
}

//function made specifically for the last stage to check the arena spike hitbox
void arenaHitBox(){
	if(dkPosY+32 > 688 || dkPosY < 32 || dkPosX < 288 || dkPosX+32 > 992){
		drawImage(square.pixel_data,square.width, square.height, dkPosX, dkPosY);
		dkPosX = 292;
		dkPosY = 654;
		drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
		dkLives --;
		displayHearts(dkLives);
	}
}



//level 1 main function
int level1(){
	
	initScreen();
	int startFlag = 0;
	while(startFlag != 5){
		startFlag = ReadSnes();
	}

	drawString(585,370,&strEmpty,0x0);
	drawRect(256,0,1024,718,0xF,0);

	//timer code 
	unsigned *clo = (unsigned*)CLO_REG;
	unsigned int game_start_time = *clo;
	unsigned int game_end_time = game_start_time+(300)*1000000;

	int a = 0;
	int control = 0;
	int menuFLag;
	valuePackMade = 0;

	dkPosX = 292;
	dkPosY = 654;
	dkLives = 4;
	dkSpeed = 2;

	pack1.PosX = 0;
	pack1.PosY = 0;

	//initializes the spiders positions
	spider1.PosX = 988;
	spider1.PosY = 500;
	
	spider2.PosX = 260;
	spider2.PosY = 200;

	//initializes the spike positions
	spike1.PosX = 600;
	spike1.PosY = 600;

	spike2.PosX = 850;
	spike2.PosY = 400;

	spike3.PosX = 900;
	spike3.PosY = 100;

	spike4.PosX = 600;
	spike4.PosY = 70;

	spike5.PosX = 400;
	spike5.PosY = 450;
	
	//initializes the coin positions
	coin1.PosX = 800;
	coin1.PosY = 450;
	
	coin2.PosX = 422;
	coin2.PosY = 250;

	coin3.PosX = 900;
	coin3.PosY = 675;

	coin4.PosX = 350;
	coin4.PosY = 600;

	coin5.PosX = 552;
	coin5.PosY = 100;

	coin6.PosX = 750;
	coin6.PosY = 300;

	//prints trophy
	drawImage(trophy.pixel_data, trophy.width, trophy.height, trophyX, trophyY);

	//prints spikeball
	drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);
	drawImage(ball.pixel_data, ball.width, ball.height, spike1.PosX, spike1.PosY);
	drawImage(ball.pixel_data, ball.width, ball.height, spike2.PosX, spike2.PosY);
	drawImage(ball.pixel_data, ball.width, ball.height, spike3.PosX, spike3.PosY);
	drawImage(ball.pixel_data, ball.width, ball.height, spike4.PosX, spike4.PosY);
	drawImage(ball.pixel_data, ball.width, ball.height, spike5.PosX, spike5.PosY);		

	//prints coins
	drawImage(coin.pixel_data, coin.width, coin.height, coin1.PosX, coin1.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin2.PosX, coin2.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin3.PosX, coin3.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin4.PosX, coin4.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin5.PosX, coin5.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin6.PosX, coin6.PosY);

	//prints spiders
	drawImage(spider.pixel_data, spider.width, spider.height, spider1.PosX, spider1.PosY);
	drawImage(spider.pixel_data, spider.width, spider.height, spider2.PosX, spider2.PosY);

	//displays dks intial hearts
	displayHearts(dkLives);

	//creates char array and int variables for the timer
	char time[3];
	int firstNum;
	int secondNum;
	int thirdNum;
	int part;

	while(1){
		
		//timer code
		char time[3];
		unsigned *clo = (unsigned*)CLO_REG;
		unsigned int current_time = *clo;
		unsigned int time_left = (game_end_time - current_time)/1000000;
		thirdNum = time_left%10;
		part = time_left/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;

		time[0] = (char)firstNum + 48;
		time[1] = (char)secondNum + 48;
		time[2] = (char)thirdNum + 48;

		drawString(1059, 60, strTimeRem, 0x0f);
		drawString(1110, 90, time, 0x0f);


		//check if player pressed the menu button
		control = ReadSnes();		
		if (control == 5){
			menuFLag = menuScreen();

			if (menuFLag == 0){
				return 1;	// return 1 to variable in main and restarts scene 1
			} else if (menuFLag == 1){
				return 0;	// return 0, out of scenes loop
			}
		}

		//calling movement and hitbox functions 
		moveDK();
		packHitBox(pack1.PosX, pack1.PosY);
		control = ReadSnes();
		GeneralHitBox(spider1.PosX, spider1.PosY);
		GeneralHitBox(spider2.PosX, spider2.PosY);
		GeneralHitBox(spike1.PosX, spike1.PosY);
		GeneralHitBox(spike2.PosX, spike2.PosY);
		GeneralHitBox(spike3.PosX, spike3.PosY);
		GeneralHitBox(spike4.PosX, spike4.PosY);
		GeneralHitBox(spike5.PosX, spike5.PosY);

		//checks if player has picked up any coins
		a = 0;
		a = pickUpCoin(coin1.PosX, coin1.PosY);
		if(a == 1){
			coin1.PosX = 0;
			coin1.PosY = 0;
			a = 0;
		}		
		a = pickUpCoin(coin2.PosX, coin2.PosY);
		if(a == 1){
			coin2.PosX = 0;
			coin2.PosY = 0;	
			a = 0;
		}	
		a = pickUpCoin(coin3.PosX, coin3.PosY);
		if(a==1){
			coin3.PosX = 0;
			coin3.PosY = 0;
			a = 0;
		}
		a = pickUpCoin(coin4.PosX, coin4.PosY);
		if(a== 1){
			coin4.PosX = 0;
			coin4.PosY = 0;	
			a = 0;	
		}	
		a = pickUpCoin(coin5.PosX, coin5.PosY);
		if(a == 1){
			coin5.PosX = 0;
			coin5.PosY = 0;
			a = 0;		
		}
		a = pickUpCoin(coin6.PosX, coin6.PosY);				
		if(a== 1){
			coin6.PosX = 0;
			coin6.PosY = 0;		
			a = 0;
		}	
		
		//checks if dk has no more lives, if trophy is reached, no time left, or its time to print a value pack
		if (dkLives == 0){
			return 6;		// 6 is the gameOver flag
		}
		if(trophyHit(trophyX,trophyY)){
			return 2;		// next level flag
		}
		if(time[0] == '0' && time[1] == '0' && time[2] == '0'){
			return 6;
		}
		if(time[0] == '2' && time[1] == '7' && time[2] == '0' && valuePackMade == 0){
			makeValuePack();		
			valuePackMade = 1;
		}

		//functions for moving both spiders horizontally
		a = moveSpiderH(spider1.PosX, spider1.PosY, spider1.wall);
		spider1.wall = a;
		if(spider1.wall == 0){
			spider1.PosX = spider1.PosX + 1;
		} else {
			spider1.PosX = spider1.PosX - 1;
		}

		a = moveSpiderH(spider2.PosX, spider2.PosY, spider2.wall);
		spider2.wall = a;
		if(spider2.wall == 0){
			spider2.PosX = spider2.PosX + 1; 
		} else {
			spider2.PosX = spider2.PosX - 1;
		}
	}
}


//main function for level 2
int level2(){
	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);
	
	//timer code 
	unsigned *clo = (unsigned*)CLO_REG;
	unsigned int game_start_time = *clo;
	unsigned int game_end_time = game_start_time+(300)*1000000;

	int a = 0;
	int control = 0;
	int menuFLag;
	valuePackMade = 0;

	dkPosX = 292;
	dkPosY = 654;
	drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);


	//prints trophy
	drawImage(trophy.pixel_data, trophy.width, trophy.height, trophyX, trophyY);

	//prints skeletons and walls
	skeleton1.PosX = 700;
	skeleton1.PosY = 650;
	drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY);
	
	wall1.PosX = 600;
	wall1.PosY = 600;
	drawImage(wall.pixel_data, wall.width, wall.height, wall1.PosX, wall1.PosY);

	wall2.PosX = 850;
	wall2.PosY = 400;
	drawImage(wall.pixel_data, wall.width, wall.height, wall2.PosX, wall2.PosY);

	wall3.PosX = 900;
	wall3.PosY = 100;
	drawImage(wall.pixel_data, wall.width, wall.height, wall3.PosX, wall3.PosY);

	wall4.PosX = 600;
	wall4.PosY = 70;
	drawImage(wall.pixel_data, wall.width, wall.height, wall4.PosX, wall4.PosY);

	wall5.PosX = 400;
	wall5.PosY = 450;
	drawImage(wall.pixel_data, wall.width, wall.height, wall5.PosX, wall5.PosY);	


	spike1.PosX = 300;
	spike1.PosY = 100;
	drawImage(ball.pixel_data, ball.width, ball.height, spike1.PosX, spike1.PosY);	
	
	spike2.PosX = 400;
	spike2.PosY = 200;
	drawImage(ball.pixel_data, ball.width, ball.height, spike2.PosX, spike2.PosY);	
	
	spike3.PosX = 500;
	spike3.PosY = 300;
	drawImage(ball.pixel_data, ball.width, ball.height, spike3.PosX, spike3.PosY);	
	
	spike4.PosX = 600;
	spike4.PosY = 400;
	drawImage(ball.pixel_data, ball.width, ball.height, spike4.PosX, spike4.PosY);	
	
	spike5.PosX = 700;
	spike5.PosY = 500;
	drawImage(ball.pixel_data, ball.width, ball.height, spike5.PosX, spike5.PosY);	
	
	spike6.PosX = 800;
	spike6.PosY = 600;
	drawImage(ball.pixel_data, ball.width, ball.height, spike6.PosX, spike6.PosY);	

	displayHearts(dkLives);

	char time[3];
	int firstNum;
	int secondNum;
	int thirdNum;
	int part;

	while(1){
		//timer code
		char time[3];
		unsigned *clo = (unsigned*)CLO_REG;
		unsigned int current_time = *clo;
		unsigned int time_left = (game_end_time - current_time)/1000000;
		thirdNum = time_left%10;
		part = time_left/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;

		time[0] = (char)firstNum + 48;
		time[1] = (char)secondNum + 48;
		time[2] = (char)thirdNum + 48;

		drawString(1059, 60, strTimeRem, 0x0f);
		drawString(1110, 90, time, 0x0f);

		//move skeleton and dk
		moveDK();
		packHitBox(pack1.PosX, pack1.PosY);
		moveSkeleton();
		GeneralHitBox(skeleton1.PosX, skeleton1.PosY);

		//checks if player wants to open the menu
		control = ReadSnes();		
		if (control == 5){
			menuFLag = menuScreen();

			if (menuFLag == 0){
				return 1;	// return 1 to variable in main and restarts scene 1
			} else if (menuFLag == 1){
				return 0;	// return 0, out of scenes loop
			}
		}

	
		if (dkLives <= 0){
			return 6;		// 6 is the gameOver flag
		}
		if(trophyHit(trophyX,trophyY)){
			return 3;		// next level flag
		}
		if(time[0] == '0' && time[1] == '0' && time[2] == '0'){
			return 6;
		}		
		if(time[0] == '2' && time[1] == '7' && time[2] == '0' && valuePackMade == 0){
			makeValuePack();
			valuePackMade = 1;			
		}

		//call hitbox funcions on walls and enemies
		enemyStaticHitBox(wall1.PosX, wall1.PosY);
		staticHitBox(wall1.PosX, wall1.PosY);
		
		enemyStaticHitBox(wall2.PosX, wall2.PosY);
		staticHitBox(wall2.PosX, wall2.PosY);
		
		enemyStaticHitBox(wall3.PosX, wall3.PosY);
		staticHitBox(wall3.PosX, wall3.PosY);
		
		enemyStaticHitBox(wall4.PosX, wall4.PosY);
		staticHitBox(wall4.PosX, wall4.PosY);
		
		enemyStaticHitBox(wall5.PosX, wall5.PosY);
		staticHitBox(wall5.PosX, wall5.PosY);
	
		enemyStaticHitBox(spike1.PosX, spike1.PosY);
		GeneralHitBox(spike1.PosX, spike1.PosY);
		
		enemyStaticHitBox(spike2.PosX, spike2.PosY);		
		GeneralHitBox(spike2.PosX, spike2.PosY);

		enemyStaticHitBox(spike3.PosX, spike3.PosY);		
		GeneralHitBox(spike3.PosX, spike3.PosY);

		enemyStaticHitBox(spike4.PosX, spike4.PosY);		
		GeneralHitBox(spike4.PosX, spike4.PosY);

		enemyStaticHitBox(spike5.PosX, spike5.PosY);		
		GeneralHitBox(spike5.PosX, spike5.PosY);

		enemyStaticHitBox(spike6.PosX, spike6.PosY);		
		GeneralHitBox(spike6.PosX, spike6.PosY);
	}
}


//main function for level 3
int level3(){
	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);

	//timer code 
	unsigned *clo = (unsigned*)CLO_REG;
	unsigned int game_start_time = *clo;
	unsigned int game_end_time = game_start_time+(300)*1000000;

	int a = 0;
	int control = 0;
	int menuFLag;
	valuePackMade = 0;

	//initializes the player, spider, skeleton, walls and spikes
	dkPosX = 270;
	dkPosY = 650;
	drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);

	drawImage(trophy.pixel_data, trophy.width, trophy.height, trophyX, trophyY);

	skeleton1.PosX = 700;
	skeleton1.PosY = 650;
	drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY);
	
	spider1.PosX = 260;
	spider1.PosY = 350;
	spider1.wall = 1;
	drawImage(spider.pixel_data, spider.width, spider.height, spider1.PosX, spider1.PosY);

	spike1.PosX = 270;
	spike1.PosY = 550;
	drawImage(ball.pixel_data, ball.width, ball.height, spike1.PosX, spike1.PosY);	

	spike2.PosX = 420;
	spike2.PosY = 480;
	drawImage(ball.pixel_data, ball.width, ball.height, spike2.PosX, spike2.PosY);	

	spike3.PosX = 400;
	spike3.PosY = 685;
	drawImage(ball.pixel_data, ball.width, ball.height, spike3.PosX, spike3.PosY);	

	spike4.PosX = 985;
	spike4.PosY = 120;
	drawImage(ball.pixel_data, ball.width, ball.height, spike4.PosX, spike4.PosY);	

	spike5.PosX = 850;
	spike5.PosY = 10;
	drawImage(ball.pixel_data, ball.width, ball.height, spike5.PosX, spike5.PosY);	

	spike6.PosX = 320;
	spike6.PosY = 380;
	drawImage(ball.pixel_data, ball.width, ball.height, spike6.PosX, spike6.PosY);	

	spike7.PosX = 875;
	spike7.PosY = 135;
	drawImage(ball.pixel_data, ball.width, ball.height, spike7.PosX, spike7.PosY);	

	spike8.PosX = 750;
	spike8.PosY = 100;
	drawImage(ball.pixel_data, ball.width, ball.height, spike8.PosX, spike8.PosY);	

	spike9.PosX = 920;
	spike9.PosY = 250;
	drawImage(ball.pixel_data, ball.width, ball.height, spike9.PosX, spike9.PosY);		


	wall1.PosX = 300;
	wall1.PosY = 30;
	drawImage(wall.pixel_data, wall.width, wall.height, wall1.PosX, wall1.PosY);	
	
	wall2.PosX = 400;
	wall2.PosY = 130;
	drawImage(wall.pixel_data, wall.width, wall.height, wall2.PosX, wall2.PosY);	
	
	wall3.PosX = 500;
	wall3.PosY = 230;
	drawImage(wall.pixel_data, wall.width, wall.height, wall3.PosX, wall3.PosY);	
	
	wall4.PosX = 740;
	wall4.PosY = 450;
	drawImage(wall.pixel_data, wall.width, wall.height, wall4.PosX, wall4.PosY);	
	
	wall5.PosX = 840;
	wall5.PosY = 550;
	drawImage(wall.pixel_data, wall.width, wall.height, wall5.PosX, wall5.PosY);	

	wall6.PosX = 940;
	wall6.PosY = 650;
	drawImage(wall.pixel_data, wall.width, wall.height, wall6.PosX, wall6.PosY);	
	
	displayHearts(dkLives);

	//for timer
	char time[3];
	int firstNum;
	int secondNum;
	int thirdNum;
	int part;

	while(1){
		//timer code
		char time[3];
		unsigned *clo = (unsigned*)CLO_REG;
		unsigned int current_time = *clo;
		unsigned int time_left = (game_end_time - current_time)/1000000;
		thirdNum = time_left%10;
		part = time_left/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;

		time[0] = (char)firstNum + 48;
		time[1] = (char)secondNum + 48;
		time[2] = (char)thirdNum + 48;

		drawString(1059, 60, strTimeRem, 0x0f);
		drawString(1110, 90, time, 0x0f);


		//moves the player, skeleton, and spider and checks for collisions
		moveDK();
		moveSkeleton();

		GeneralHitBox(spider1.PosX, spider1.PosY);
		GeneralHitBox(skeleton1.PosX, skeleton1.PosY);

		a = moveSpiderH(spider1.PosX, spider1.PosY, spider1.wall);
		spider1.wall = a;
		if(spider1.wall == 0){
			spider1.PosX = spider1.PosX + 1;
		} else {
			spider1.PosX = spider1.PosX - 1;
		}
	
		packHitBox(pack1.PosX, pack1.PosY);
		control = ReadSnes();	
		if (control == 5){
			menuFLag = menuScreen();

			if (menuFLag == 0){
				return 1;	// return 1 to variable in main and restarts scene 1
			} else if (menuFLag == 1){
				return 0;	// return 0, out of scenes loop
			}
		}			

		//checks is dk is out of Lives, if trophy has been reached, no more time or if its time to spawn a value pack
		if (dkLives <= 0){
			return 6;
		}
		if(trophyHit(trophyX,trophyY)){
			return 4;
		}
		if(time[0] == '0' && time[1] == '0' && time[2] == '0'){
			return 6;
		}		
		if(time[0] == '2' && time[1] == '7' && time[2] == '0' && valuePackMade == 0){
			makeValuePack();
			valuePackMade = 1;	
		}

		//calculates hitboxes for walls and spikes
		enemyStaticHitBox(wall1.PosX, wall1.PosY);
		staticHitBox(wall1.PosX, wall1.PosY);
		
		enemyStaticHitBox(wall2.PosX, wall2.PosY);
		staticHitBox(wall2.PosX, wall2.PosY);
		
		enemyStaticHitBox(wall3.PosX, wall3.PosY);
		staticHitBox(wall3.PosX, wall3.PosY);
		
		enemyStaticHitBox(wall4.PosX, wall4.PosY);
		staticHitBox(wall4.PosX, wall4.PosY);
		
		enemyStaticHitBox(wall5.PosX, wall5.PosY);
		staticHitBox(wall5.PosX, wall5.PosY);
	
		enemyStaticHitBox(wall6.PosX, wall6.PosY);
		staticHitBox(wall6.PosX, wall6.PosY);
	
		enemyStaticHitBox(spike1.PosX, spike1.PosY);
		GeneralHitBox(spike1.PosX, spike1.PosY);
		
		enemyStaticHitBox(spike2.PosX, spike2.PosY);		
		GeneralHitBox(spike2.PosX, spike2.PosY);

		enemyStaticHitBox(spike3.PosX, spike3.PosY);		
		GeneralHitBox(spike3.PosX, spike3.PosY);

		enemyStaticHitBox(spike4.PosX, spike4.PosY);		
		GeneralHitBox(spike4.PosX, spike4.PosY);

		enemyStaticHitBox(spike5.PosX, spike5.PosY);		
		GeneralHitBox(spike5.PosX, spike5.PosY);

		enemyStaticHitBox(spike6.PosX, spike6.PosY);		
		GeneralHitBox(spike6.PosX, spike6.PosY);

		enemyStaticHitBox(spike7.PosX, spike7.PosY);		
		GeneralHitBox(spike7.PosX, spike7.PosY);

		enemyStaticHitBox(spike8.PosX, spike8.PosY);		
		GeneralHitBox(spike8.PosX, spike8.PosY);

		enemyStaticHitBox(spike9.PosX, spike9.PosY);		
		GeneralHitBox(spike9.PosX, spike9.PosY);
	}
}


//main function for level 4
int level4(){

 	//timer code 
	unsigned *clo = (unsigned*)CLO_REG;
	unsigned int game_start_time = *clo;
	unsigned int game_end_time = game_start_time+(300)*1000000;	
	
	int a = 0;
	int control = 0;
	int menuFLag;
	valuePackMade = 0;

	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);

	displayHearts(dkLives);

	dkPosX = 292;
	dkPosY = 654;
	drawImage(dk.pixel_data, dk.width, dk.height, dkPosX, dkPosY);

	drawImage(trophy.pixel_data, trophy.width, trophy.height, trophyX-32, trophyY+32);

	skeleton1.PosX = 700;
	skeleton1.PosY = 650;
	drawImage(skeleton.pixel_data, skeleton.width, skeleton.height, skeleton1.PosX, skeleton1.PosY);

	drawSpikesH(257, 1);
	drawSpikesH(257, 686);

	drawSpikesV(257, 33);
	drawSpikesV(992, 33);

	//sets coin positions
	coin1.PosX = 290;
	coin1.PosY = 38;
	
	coin2.PosX = 327;
	coin2.PosY = 38;

	coin3.PosX = 290;
	coin3.PosY = 78;

	coin4.PosX = 960;
	coin4.PosY = 656;

	coin5.PosX = 924;
	coin5.PosY = 656;

	coin6.PosX = 960;
	coin6.PosY = 620;

	//draws coins
	drawImage(coin.pixel_data, coin.width, coin.height, coin1.PosX, coin1.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin2.PosX, coin2.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin3.PosX, coin3.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin4.PosX, coin4.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin5.PosX, coin5.PosY);
	drawImage(coin.pixel_data, coin.width, coin.height, coin6.PosX, coin6.PosY);

	//intializes array and variables for the timer
	char time[3];
	int firstNum;
	int secondNum;
	int thirdNum;
	int part;

	while(1){
	//timer code
		char time[3];
		unsigned *clo = (unsigned*)CLO_REG;
		unsigned int current_time = *clo;
		unsigned int time_left = (game_end_time - current_time)/1000000;
		thirdNum = time_left%10;
		part = time_left/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;

		time[0] = (char)firstNum + 48;
		time[1] = (char)secondNum + 48;
		time[2] = (char)thirdNum + 48;

		drawString(1059, 60, strTimeRem, 0x0f);
		drawString(1110, 90, time, 0x0f);
		
		//movement and hitbox functions are called
		moveDK();
		moveSkeleton();
		GeneralHitBox(skeleton1.PosX, skeleton1.PosY);
		packHitBox(pack1.PosX, pack1.PosY);
		arenaHitBox();

		//check if the player has opened the menu
		control = ReadSnes();	
		if (control == 5){
			menuFLag = menuScreen();

			if (menuFLag == 0){
				return 1;	// return 1 to variable in main and restarts scene 1
			} else if (menuFLag == 1){
				return 0;	// return 0, out of scenes loop
			}
		}			

		//check to see if player has picked up coins
		a = 0;
		a = pickUpCoin(coin1.PosX, coin1.PosY);
		if(a == 1){
			coin1.PosX = 0;
			coin1.PosY = 0;
			a = 0;
		}		
		a = pickUpCoin(coin2.PosX, coin2.PosY);
		if(a == 1){
			coin2.PosX = 0;
			coin2.PosY = 0;	
			a = 0;
		}	
		a = pickUpCoin(coin3.PosX, coin3.PosY);
		if(a==1){
			coin3.PosX = 0;
			coin3.PosY = 0;
			a = 0;
		}
		a = pickUpCoin(coin4.PosX, coin4.PosY);
		if(a== 1){
			coin4.PosX = 0;
			coin4.PosY = 0;	
			a = 0;	
		}	
		a = pickUpCoin(coin5.PosX, coin5.PosY);
		if(a == 1){
			coin5.PosX = 0;
			coin5.PosY = 0;
			a = 0;		
		}
		a = pickUpCoin(coin6.PosX, coin6.PosY);				
		if(a== 1){
			coin6.PosX = 0;
			coin6.PosY = 0;		
			a = 0;
		}	
		
		//check if game is over, game is won, 30 seconds have passed or no time left
		if (dkLives <= 0){
			return 6;		// 6 is the gameOver flag
		}
		if(trophyHit(trophyX-32,trophyY+32)){
			gameWon(time_left);
			return 5;		// 5 is the win game flag
		}
		if(time[0] == '0' && time[1] == '0' && time[2] == '0'){
			return 6;
		}		
		if(time[0] == '2' && time[1] == '7' && time[2] == '0' && valuePackMade == 0){
			makeValuePack();
			valuePackMade = 1;		
		}
	}
}



//function for printing the main menu
int mainMenu(){

	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);

	drawString(500,350,&strNames,0xF);
	//drawString(585,300,&strLogo,0xF);
	drawString(590,460,&strStart,0x4);
	drawString(595,540,&strQuitGame,0xF);
	drawImage(logo.pixel_data, logo.width, logo.height, 540, 200);

	int a = 1;
	int lastA = 1;
	// waits until A is pressed 
	while (a != 6){ 
		a = ReadSnes();

		if (a == 1 && lastA != 1){
			drawString(590,460,&strStart,0x4);
			drawString(595,540,&strQuitGame,0xF);
			lastA = 1;
		}
		if (a == 2 && lastA != 2){
			drawString(590,460,&strStart,0xF);
			drawString(595,540,&strQuitGame,0x4);
			lastA = 2;
		}
	}

	if (lastA == 1){
		return 0;	// returns 0 if Start Game was pressed

	} else if (lastA == 2){
		return 1;	// returns 1 if quit game was pressed
	}
}


//function for the menu screen
int menuScreen(){

	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);
	drawString(600,300,&strRestart,0x4);
	drawString(610,400,&strQuit,0xF);

	int a = 1;
	int lastA = 1;

	// waits until start or A is pressed 
	while (a != 6 && a != 5){ 
		a = ReadSnes();

		if (a == 1 && lastA != 1){
			drawString(600,300,&strRestart,0x4);
			drawString(610,400,&strQuit,0xF);
			lastA = 1;
		}
		if (a == 2 && lastA != 2){
			drawString(600,300,&strRestart,0xF);
			drawString(610,400,&strQuit,0x4);
			lastA = 2;
		}
	}

	if (a == 5){
		//back to game;

	} else {
		if (lastA == 1){
			return 0;

		} else if (lastA == 2){
			return 1;
		}
	}
}

//function for initializing the screen
void initScreen(){

	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);
	drawString(585,370,&strPress,0xF);
}


//function to draw game over
int gameOver(){
	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);

	drawImage(gameOverIm.pixel_data, gameOverIm.width, gameOverIm.height, 525, 300);

	int a = 0;
	while (a == 0){
		a = ReadSnes(0);
	}
	return 0;	// press anything and come back to main	
}

//function to draw gamewon
void gameWon(int timeLeft){
	fillScreen(0);
	drawRect(256,0,1024,718,0xF,0);

	drawString(593,350,&strWon,0xF);
	displayScore(timeLeft);
	drawImage(dkWin.pixel_data, dkWin.width, dkWin.height, 550, 110);

	int a = 0;

	// press anything and come back to main
	while (a == 0){
		a = ReadSnes();
	}
}

//function to calculate and display score 
void displayScore(int timeLeft){
	int fifthNum, fourthNum, thirdNum, secondNum, firstNum, part;
	char threeDigit[3];
	char fourDigit[4];
	char fiveDigit[5];
	int score = timeLeft*dkLives*(numCoins+1);	
	drawString(600, 400, &strScore, 0xF);

	if(score < 999){
		thirdNum = score%10;
		part = score/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;	
		threeDigit[0] = (char)firstNum + 48;
		threeDigit[1] = (char)secondNum + 48;
		threeDigit[2] = (char)thirdNum + 48;
		drawString(610, 430, threeDigit, 0xF);	

	} else if(score < 9999){
		fourthNum = score%10;
		part = score/10;
		thirdNum = part%10;
		part = part/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10; 
		fourDigit[0] = (char)firstNum + 48;
		fourDigit[1] = (char)secondNum + 48;
		fourDigit[2] = (char)thirdNum + 48;
		fourDigit[3] = (char)fourthNum + 48;	
		drawString(610, 430, fourDigit, 0xF);	

	} else {
		fifthNum = score%10;
		part = score/10;
		fourthNum = part%10;
		part = part/10;
		thirdNum = part%10;
		part = part/10;
		secondNum = part%10;
		part = part/10;
		firstNum = part%10;
		fiveDigit[0] = (char)firstNum + 48;
		fiveDigit[1] = (char)secondNum + 48;
		fiveDigit[2] = (char)thirdNum + 48;
		fiveDigit[3] = (char)fourthNum + 48;
		fiveDigit[4] = (char)fifthNum + 48;		
		drawString(610, 430, fiveDigit, 0xF);						
	} 
}