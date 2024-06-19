#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
//#include "functions.h"

//defines our gpio base address
#define GPIO_BASE 0xFE200000

//defines our clock register address
#define CLO_REG 0xFE003004

int buttons[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};    //array if int to check if button was pressed
int buttonChecker[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  //array of int to prevent spam printing
int check = 0;	//int to help stop mass printing


unsigned *gpio = (unsigned*)GPIO_BASE;
//macros for gpio
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))

//defininitions for clock latch and data lines
#define CLK 11
#define LAT 9
#define DAT 10

int dkSpeed = 2;
int skeletonSpeed = 1;

int dkPosX = 260;
int dkPosY = 686;
int dkLives = 4;
int checker = 0;

int spiderPosX = 400;
int spiderPosY = 400;

int ball1PosX = 600;
int ball1PosY = 600;

int trophyX = 953;
int trophyY = 10;

int numCoins = 0;
int valuePackMade = 0;

void writeLATCH(int bit);
void writeCLOCK(int bit);
void wait(int time);
void initGPIO();
int readDATA();
int returnButtons();
int ReadSnes();
int moveSpiderH(int x, int y, int w);
void GeneralHitBox(int x, int y);
void moveDK();
void initSpider();
int level1();
int level2();
int level3();
int level4();
int gameOver();
void gameWon(int timeLeft);
void displayHeart(int numHeart);
void staticHitBox(int a, int b);
void packHitBox(int x, int y);
int menuScreen();
void initScreen();
void drawSpikesH(int x, int y);
void drawSpikesV(int x, int y);

#endif