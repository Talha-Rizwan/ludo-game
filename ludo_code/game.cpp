#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> 
#include<cstdlib>
#include<ctime>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

pthread_t tid[4];//thread ids for 4 players
pthread_t tkill[4];//threads for token killing
pthread_t master_t;//thread for winning and loosing
pthread_t main_thread;//thread to create board and tokens
pthread_t rol;

sem_t sem1;				//semaphore for the player turns 
sem_t sem2;				//semaphore for the dice rolling

//initializing semaphore in main()




int random_variable=rand()%4;		// a random variable for the randomly assigning of turns via semaphore

//flags for indicating the player turn if done in a round
bool yellowTurn=1;					
bool redTurn=1;
bool greenTurn=1;
bool blueTurn=1;


void player1();
void player2();
void player3();
void player4();


int mouse_x;			//storing coordinates of mouse for token moving
int mouse_y;


//init arrays to maintain the initial values of all the tokens
int init_y[4][2]={		//for yellow

	{270,200},
	{400,200},
	{270,100},
	{400,100}
};

int init_g[4][2]={		//for green
	{270,650},
	{400,650},
	{270,550},
	{400,550}
};

int init_r[4][2]={		//for red
	{720,650},
	{850,650},
	{720,550},
	{850,550}
};

int init_b[4][2]={		//for blue
	{720,200},
	{850,200},
	{720,100},
	{850,100},
};




int yellowTokens[4][2]={//Initial Positions of yellow in home
	{270,200},
	{400,200},
	{270,100},
	{400,100}
};

bool outHouseYellow[4]={0,0,0,0};
int greenTokens[4][2]={		//Initial Positions of green in home
	{270,650},
	{400,650},
	{270,550},
	{400,550}
};
bool outHouseGreen[4]={0,0,0,0};

int redTokens[4][2]={		//Initial Positions of red in home
	{720,650},
	{850,650},
	{720,550},
	{850,550}
};
bool outHouseRed[4]={0,0,0,0};

int blueTokens[4][2]={		//Initial Positions of blue in home
	{720,200},
	{850,200},
	{720,100},
	{850,100},
};

bool outHouseBlue[4]={0,0,0,0};	

bool rolledDice = false;		//flag to indicate if dice is rolled
bool madeTurn =false;
bool win = false;				//to ckeck if the game is ended



int blue[58][2]={		//coordinates for path for the blue token
{865,325},//star	{865,325},{615,125},{515,75},{315,325},{265,425},{515,625},{615,675},{815,425},
{815,325},
{765,325},
{715,325},
{665,325},
{615,275},
{615,225},
{615,175},
{615,125},//star
{615,75},
{615,25},
{565,25},
{515,25},
{515,75},//star
{515,125},
{515,175},
{515,225},
{515,275},
{465,325},
{415,325},
{365,325},
{315,325},//star
{265,325},
{215,325},
{215,375},
{215,425},
{265,425},//star
{315,425},
{365,425},
{415,425},
{465,425},
{515,475},
{515,525},
{515,575},
{515,625},//star
{515,675},
{515,725},
{565,725},
{615,725},
{615,675},//star
{615,625},
{615,575},
{615,525},
{615,475},
{665,425},
{715,425},
{765,425},
{815,425},//star
{865,425},
{915,425},
{915,375},
{865,375},
{815,375},
{765,375},
{715,375},
{665,375},
{615,375}
};
int green[58][2]={{265,425},	//coordinates for path for the green token
{315,425},
{365,425},
{415,425},
{465,425},
{515,475},
{515,525},
{515,575},
{515,625},
{515,675},
{515,725},
{565,725},
{615,725},
{615,675},
{615,625},
{615,575},
{615,525},
{615,475},
{665,425},
{715,425},
{765,425},
{815,425},
{865,425},
{915,425},
{915,375},
{915,325},
{865,325},
{815,325},
{765,325},
{715,325},
{665,325},
{615,275},
{615,225},
{615,175},
{615,125},
{615,75},
{615,25},
{565,25},
{515,25},
{515,75},
{515,125},
{515,175},
{515,225},
{515,275},
{465,325},
{415,325},
{365,325},
{315,325},
{265,325},
{215,325},
{215,375},
{265,375},
{315,375},
{365,375},
{415,375},
{465,375},
{515,375},
};
int red[58][2]={		//coordinates for path for the red token
{615,675},
{615,625},
{615,575},
{615,525},
{615,475},
{665,425},
{715,425},
{765,425},	
{815,425},
{865,425},
{915,425},
{915,375},
{915,325},
{865,325},
{815,325},
{765,325},
{715,325},
{665,325},
{615,275},
{615,225},
{615,175},
{615,125},
{615,75},
{615,25},
{565,25},
{515,25},
{515,75},
{515,125},
{515,175},
{515,225},
{515,275},
{465,325},
{415,325},
{365,325},
{315,325},
{265,325},
{215,325},
{215,375},
{215,425},
{265,425},
{315,425},
{365,425},
{415,425},
{465,425},
{515,475},
{515,525},
{515,575},
{515,625},
{515,675},
{515,725},
{565,725},
{565,675},
{565,625},
{565,575},
{565,525},
{565,475},
{565,425},
};
int yellow[58][2]={{515,75},	//coordinates for path for the yellow token
{515,125},
{515,175},
{515,225},
{515,275},
{465,325},
{415,325},
{365,325},
{315,325},
{265,325},
{215,325},
{215,375},
{215,425},
{265,425},
{315,425},
{365,425},
{415,425},
{465,425},
{515,475},
{515,525},
{515,575},
{515,625},
{515,675},
{515,725},
{565,725},
{615,725},
{615,675},
{615,625},
{615,575},
{615,525},
{615,475},
{665,425},
{715,425},
{765,425},
{815,425},
{865,425},
{915,425},
{915,375},
{915,325},
{865,325},
{815,325},
{765,325},
{715,325},
{665,325},
{615,275},
{615,225},
{615,175},
{615,125},
{615,75},
{615,25},
{565,25},
{565,75},
{565,125},
{565,175},
{565,225},
{565,275},
{565,325},
};

//position of tokens
int yIndex[4]={0,0,0,0};	
int rIndex[4]={0,0,0,0};
int bIndex[4]={0,0,0,0};
int gIndex[4]={0,0,0,0};

int dice_number=0;	//the variable to store the random dice number of each turn



int turn=1;

bool * yturn=new bool(0);
bool * rturn=new bool(0);
bool * gturn=new bool(0);
bool * bturn=new bool(0);

bool allowTurn=false;

void switch_turn (){		//ftn to switch turns among different players
if(dice_number!=6){

if(turn<4){
	turn++;
	rolledDice=false;
	madeTurn=false;
}
else if(turn==4){

	turn=1;
	rolledDice=false;
	madeTurn=false;
}

}

}

//token killing function
//check if any token is killed by any other token
void kill_token(int killer[][2],int killed1[][2],int killed1_init[][2],int killed2[][2],int killed2_init[][2],int killed3[][2],int killed3_init[][2]){
// star positions {865,325},{615,125},{515,75},{315,325},{265,425},{515,625},{615,675},{815,425},
for(int i=0;i<4;i++){

	for(int j=0;j<4;j++){

		if((killer[i][0]==killed1[j][0] && killer[i][1]==killed1[j][1]) && ((killer[i][0]!=865 && killer[i][1]!=325) || (killer[i][0]!=615 && killer[i][1]!=125) || (killer[i][0]!=515 && killer[i][1]!=75) || (killer[i][0]!=315 && killer[i][1]!=325) || (killer[i][0]!=265 && killer[i][1]!=425) || (killer[i][0]!=515 && killer[i][1]!=625) || (killer[i][0]!=615 && killer[i][1]!=675) || (killer[i][0]!=815 && killer[i][1]!=425))){
			killed1[j][0]=killed1_init[j][0];
			killed1[j][1]=killed1_init[j][1];
			    DrawString( 130, 800, "token killed ! " ,colors[MISTY_ROSE]);

		}

		if((killer[i][0]==killed2[j][0] && killer[i][1]==killed2[j][1]) && ((killer[i][0]!=865 && killer[i][1]!=325) || (killer[i][0]!=615 && killer[i][1]!=125) || (killer[i][0]!=515 && killer[i][1]!=75) || (killer[i][0]!=315 && killer[i][1]!=325) || (killer[i][0]!=265 && killer[i][1]!=425) || (killer[i][0]!=515 && killer[i][1]!=625) || (killer[i][0]!=615 && killer[i][1]!=675) || (killer[i][0]!=815 && killer[i][1]!=425))){
			killed2[j][0]=killed2_init[j][0];
			killed2[j][1]=killed2_init[j][1];
			    DrawString( 130, 800, "token killed ! " ,colors[MISTY_ROSE]);

		}

		if((killer[i][0]==killed3[j][0] && killer[i][1]==killed3[j][1]) && ((killer[i][0]!=865 && killer[i][1]!=325) || (killer[i][0]!=615 && killer[i][1]!=125) || (killer[i][0]!=515 && killer[i][1]!=75) || (killer[i][0]!=315 && killer[i][1]!=325) || (killer[i][0]!=265 && killer[i][1]!=425) || (killer[i][0]!=515 && killer[i][1]!=625) || (killer[i][0]!=615 && killer[i][1]!=675) || (killer[i][0]!=815 && killer[i][1]!=425))){
			killed3[j][0]=killed3_init[j][0];
			killed3[j][1]=killed3_init[j][1];
			    DrawString( 130, 800, "token killed ! " ,colors[MISTY_ROSE]);

		}

	}


	
}

}





//this ftn moves the selected tokens according to the dice number
void moveNext(int Tokens[][2],int cord[][2],int* Index, bool *outHouse,bool* t)
{

	
	if(outHouse[0]==0 && outHouse[1]==0 && outHouse[2]==0 && outHouse[3]==0 && dice_number!=6){//the player cannot move

		DrawString( 130, 800, "cannot move ! " ,colors[MISTY_ROSE]);
		cout<<"cannot move"<<endl;
			
		if(rolledDice)
		{
			switch_turn();
		}
		
	}

else {
	if(dice_number==6){
		
		if( (mouse_x<Tokens[0][0]+50 && mouse_x>=Tokens[0][0]-50) && (mouse_y<Tokens[0][1]+50 &&mouse_y>Tokens[0][1]-50) && outHouse[0]==0){

	 		Tokens[0][0]=cord[Index[0]][0];
		 	Tokens[0][1]=cord[Index[0]][1];
		 	Index[0]=0;
		//	 sleep(1);
		outHouse[0]=1;
		mouse_x=0;
		mouse_y=0;
			return;
		 }

		else if( (mouse_x<Tokens[1][0]+50 && mouse_x>Tokens[1][0]-50) && (mouse_y<Tokens[1][1]+50 && mouse_y>Tokens[1][1]-50) && outHouse[1]==0){

		 	Tokens[1][0]=cord[Index[1]][0];
		 	Tokens[1][1]=cord[Index[1]][1];
		 	Index[1]=0;
		//	 sleep(1);
		outHouse[1]=1;
		mouse_x=0;
		mouse_y=0;
		
		return;
		 }

		else if( (mouse_x<Tokens[2][0]+50 && mouse_x>=Tokens[2][0]-50) && (mouse_y<Tokens[2][1]+50 &&mouse_y>Tokens[2][1]-50) && outHouse[2]==0){

	 		Tokens[2][0]=cord[Index[2]][0];
		 	Tokens[2][1]=cord[Index[2]][1];
		 	Index[2]=0;
		//	 sleep(1);
		outHouse[2]=1;
		mouse_x=0;
		mouse_y=0;
		return;
		 }

		else if( (mouse_x<Tokens[3][0]+50 && mouse_x>=Tokens[3][0]-50) && (mouse_y<Tokens[3][1]+50 &&mouse_y>Tokens[3][1]-50) && outHouse[3]==0){	

		 	Tokens[3][0]=cord[Index[3]][0];	
		 	Tokens[3][1]=cord[Index[3]][1];
	 		Index[3]=0;
		//	 sleep(1);
		outHouse[3]=1;
		mouse_x=0;
		mouse_y=0;
		return;
		 }

		else if( (mouse_x<Tokens[0][0]+50 && mouse_x>=Tokens[0][0]-50) && (mouse_y<Tokens[0][1]+50 &&mouse_y>Tokens[0][1]-50) && outHouse[0]==1){
			
			if(dice_number>(57-Index[0])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			
			return;
			}
			Index[0]+=6;
			Tokens[0][0]=cord[Index[0]][0];	
		 	Tokens[0][1]=cord[Index[0]][1];
			 mouse_x=0;
			mouse_y=0;
	 		return;

		}

		else if( (mouse_x<Tokens[1][0]+50 && mouse_x>=Tokens[1][0]-50) && (mouse_y<Tokens[1][1]+50 &&mouse_y>Tokens[1][1]-50) && outHouse[1]==1){
			
			if(dice_number>(57-Index[1])){
		    cout<<"sorry you cannot move"<<endl;
			
			DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			return;
			}

			Index[1]+=6;
			Tokens[1][0]=cord[Index[1]][0];	
		 	Tokens[1][1]=cord[Index[1]][1];
			 mouse_x=0;
		mouse_y=0;
	 		return;

		}


		else if( (mouse_x<Tokens[2][0]+50 && mouse_x>=Tokens[2][0]-50) && (mouse_y<Tokens[2][1]+50 &&mouse_y>Tokens[2][1]-50) && outHouse[2]==1){
			
			if(dice_number>(57-Index[2])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			
			return;
			}
			Index[2]+=6;
			Tokens[2][0]=cord[Index[2]][0];	
		 	Tokens[2][1]=cord[Index[2]][1];
			 mouse_x=0;
		mouse_y=0;
	 		return;

		}

		else if( (mouse_x<Tokens[3][0]+50 && mouse_x>=Tokens[3][0]-50) && (mouse_y<Tokens[3][1]+50 &&mouse_y>Tokens[3][1]-50)&& outHouse[3]==1){
			
			if(dice_number>(57-Index[3])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			return;
			}
			Index[3]+=6;
			Tokens[3][0]=cord[Index[3]][0];	
		 	Tokens[3][1]=cord[Index[3]][1];
			 mouse_x=0;
		mouse_y=0;
	 		return;

		}

	
	}//from here on yIndex is used//////////////////////////////////////////////
	else if(dice_number<6){
		*t=0;

if( (mouse_x<Tokens[0][0]+50 && mouse_x>=Tokens[0][0]-50) && (mouse_y<Tokens[0][1]+50 &&mouse_y>Tokens[0][1]-50) && outHouse[0]==1){

			if(dice_number>(57-Index[0])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			
			return;
			}
			
			Index[0]+=dice_number;
			Tokens[0][0]=cord[Index[0]][0];	
		 	Tokens[0][1]=cord[Index[0]][1];
	 		mouse_x=0;
		mouse_y=0;
		switch_turn();
			return;
		}

		else if( (mouse_x<Tokens[1][0]+50 && mouse_x>=Tokens[1][0]-50) && (mouse_y<Tokens[1][1]+50 &&mouse_y>Tokens[1][1]-50) && outHouse[1]==1){
			
			if(dice_number>(57-Index[1])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			
			return;
			}
			

			Index[1]+=dice_number;
			Tokens[1][0]=cord[Index[1]][0];	
		 	Tokens[1][1]=cord[Index[1]][1];
	 		mouse_x=0;
		mouse_y=0;
		switch_turn();
			return;
		}


		else if( (mouse_x<Tokens[2][0]+50 && mouse_x>=Tokens[2][0]-50) && (mouse_y<Tokens[2][1]+50 &&mouse_y>Tokens[2][1]-50) && outHouse[2]==1){
			if(dice_number>(57-Index[2])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			
			return;
			}
			

			Index[2]+=dice_number;
			Tokens[2][0]=cord[Index[2]][0];	
		 	Tokens[2][1]=cord[Index[2]][1];
			 mouse_x=0;
		mouse_y=0;
		switch_turn();
	 		return;

		}

		else if( (mouse_x<Tokens[3][0]+50 && mouse_x>=Tokens[3][0]-50) && (mouse_y<Tokens[3][1]+50 &&mouse_y>Tokens[3][1]-50) && outHouse[3]==1){
			if(dice_number>(57-Index[3])){
		    DrawString( 130, 800, "sorry you cannot move ! " ,colors[MISTY_ROSE]);
			cout<<"sorry you cannot move"<<endl;
			return;
			}
			Index[3]+=dice_number;
			Tokens[3][0]=cord[Index[3]][0];	
		 	Tokens[3][1]=cord[Index[3]][1];
			 mouse_x=0;
		     mouse_y=0;
			 switch_turn();
	 		return;

		}

	}

}
}

//thread ftns to check for killing of tokens
void * kill_t1(void * arg){			

	kill_token(yellowTokens,blueTokens,init_b,redTokens,init_r,greenTokens,init_g );
	pthread_exit(NULL);

}

void * kill_t2(void * arg){

	kill_token(greenTokens,blueTokens,init_b,redTokens,init_r,yellowTokens,init_y );


	pthread_exit(NULL);
}

void * kill_t3(void* arg){
	kill_token(redTokens,blueTokens,init_b,yellowTokens,init_y,greenTokens,init_g );
	
	pthread_exit(NULL);

}

void* kill_t4(void * arg){

	kill_token(blueTokens,yellowTokens,init_y,redTokens,init_r,greenTokens,init_g );
	pthread_exit(NULL);
}



//ftns for players to take their turn randomly but equally 

void player1(){//yellow turn
								//applying semaphores on player turns

sem_wait(&sem1);				//yellow player occupying the shared resource i-e turn
 if(yellowTurn==0){
	sem_post(&sem1);				//releasing if not its turn
	}

	yellowTurn=0;
 DrawString( 400, 800, "Yellow Turn", colors[MISTY_ROSE]);
 cout<<"YELLOW TURN"<<endl;
			
	moveNext(yellowTokens, yellow, yIndex,outHouseYellow,yturn);
	pthread_create(&tkill[0],NULL,kill_t1,NULL );

	yellowTurn=0;

	if(yellowTurn==0 && blueTurn==0 && redTurn==0 && greenTurn==0){
		yellowTurn=1;
		redTurn=1;
		blueTurn=1;
		greenTurn=1;

	}



	sem_post(&sem1);			//yellow player releasing the turn 

	pthread_exit(NULL);	
}
void player2(){//green
 sem_wait(&sem1);			//applying semaphores on player turns
							//green player occupying the shared resource i-e turn
 if(greenTurn==0){
	sem_post(&sem1);		//releasing if not its turn
	}

	greenTurn=0;
 DrawString( 400, 800, "Green Turn", colors[MISTY_ROSE]);
cout<<"GREEN TURN"<<endl;

	moveNext(greenTokens, green, gIndex,outHouseGreen,gturn);
		pthread_create(&tkill[1],NULL,kill_t1,NULL );

	greenTurn=0;

	if(yellowTurn==0 && blueTurn==0 && redTurn==0 && greenTurn==0){
		yellowTurn=1;
		redTurn=1;
		blueTurn=1;
		greenTurn=1;

	}

	sem_post(&sem1);			//green player releasing the turn 

pthread_exit(NULL);
}


void player3(){//red
sem_wait(&sem1);			//applying semaphores on player turns
							//red player occupying the shared resource i-e turn
 if(redTurn==0){
	sem_post(&sem1);	
	}

	redTurn=0;				//releasing if not its turn

*rturn=1;
 DrawString( 400, 800, "Red Turn", colors[MISTY_ROSE]);
	cout<<"RED TURN"<<endl;

	moveNext(redTokens, red, rIndex,outHouseRed,rturn);
		pthread_create(&tkill[2],NULL,kill_t1,NULL );

		redTurn=0;

	if(yellowTurn==0 && blueTurn==0 && redTurn==0 && greenTurn==0){
		yellowTurn=1;
		redTurn=1;
		blueTurn=1;
		greenTurn=1;

	}

	sem_post(&sem1);			//red player releasing the turn 

pthread_exit(NULL);
}



void player4(){//blue


sem_wait(&sem1);			//applying semaphores on player turns
							//blue player occupying the shared resource i-e turn
 if(blueTurn==0){	
	sem_post(&sem1);			//releasing if not its turn
	}

	blueTurn=0;




*bturn=1;
 DrawString( 400, 800, "Blue Turn", colors[MISTY_ROSE]);
	cout<<"BLUE TURN"<<endl;
moveNext(blueTokens, blue, bIndex,outHouseBlue,bturn);
		pthread_create(&tkill[3],NULL,kill_t1,NULL );

	blueTurn=0;

	if(yellowTurn==0 && blueTurn==0 && redTurn==0 && greenTurn==0){
		yellowTurn=1;
		redTurn=1;
		blueTurn=1;
		greenTurn=1;

	}

	sem_post(&sem1);				//blue player releasing the turn 

pthread_exit(NULL);
}



void * p1(void * arg){			//thread ftn for player1 to take its turn

player1();


	pthread_join(tid[0],NULL);


	pthread_exit(NULL);
}


void * p2(void * arg){		//thread ftn for player2 to take its turn

player2();


	pthread_join(tid[1],NULL);


	pthread_exit(NULL);
}

void * p3(void * arg){		//thread ftn for player3 to take its turn

player3();


	pthread_join(tid[2],NULL);


	pthread_exit(NULL);
}

void * p4(void * arg){		//thread ftn for player4 to take its turn

player4();


	pthread_join(tid[3],NULL);


	pthread_exit(NULL);
}




void drawDice(int number)			//ftn to draw dice on board
{

	DrawRoundRect(533,350,60,60,colors[WHITE]);
	if(number==1)
	{
	DrawCircle(563,380,5,colors[RED]);
	}
	if(number==2)
	{
		DrawCircle(555,380,5,colors[RED]);
		DrawCircle(571,380,5,colors[RED]);
	}
	if(number==3)
	{
		DrawCircle(551,380,5,colors[RED]);
		DrawCircle(563,380,5,colors[RED]);
		DrawCircle(575,380,5,colors[RED]);
	}
	if(number==4)
	{
		DrawCircle(546,395,5,colors[RED]);
		DrawCircle(580,395,5,colors[RED]);
		DrawCircle(546,365,5,colors[RED]);
		DrawCircle(580,365,5,colors[RED]);
	}
	if(number==5)
	{
		DrawCircle(546,395,5,colors[RED]);
		DrawCircle(580,395,5,colors[RED]);
		DrawCircle(563,380,5,colors[RED]);
		DrawCircle(546,365,5,colors[RED]);
		DrawCircle(580,365,5,colors[RED]);
	}
	if(number==6)
	{
		DrawCircle(548,395,5,colors[RED]);
		DrawCircle(563,395,5,colors[RED]);
		DrawCircle(578,395,5,colors[RED]);
		DrawCircle(548,365,5,colors[RED]);
		DrawCircle(563,365,5,colors[RED]);
		DrawCircle(578,365,5,colors[RED]);
	}
}
void tokens()			//ftn to draw tokens on board
{

for(int i=0; i<4; i++)
{	
	DrawCircle(blueTokens[i][0],blueTokens[i][1],20,colors[DEEP_SKY_BLUE]);
	DrawCircle(redTokens[i][0],redTokens[i][1],20,colors[FIREBRICK]);
	DrawCircle(greenTokens[i][0],greenTokens[i][1],20,colors[FOREST_GREEN]);
	DrawCircle(yellowTokens[i][0],yellowTokens[i][1],20,colors[GOLD]);
}	
	
}

 void board(){		//ftn to draw board
 
 	//making the board display	
	
		
	//home triangles
	DrawTriangle( 565, 375, 490, 300 , 640 , 300, colors[DARK_GOLDEN_ROD] ); 
	DrawTriangle( 565, 375, 490, 450 , 490 , 300, colors[GREEN] );
	DrawTriangle( 565, 375, 490, 450 , 640 , 450, colors[RED] );
	DrawTriangle( 565, 375, 640, 450 , 640 , 300, colors[MIDNIGHT_BLUE] );

	
	//making the middle boxes
	for(int i=0;i<=250;i+=50)
	DrawSquare( 490 , i ,50,colors[WHITE]);	     // Boxes around Yellow side.
	DrawSquare( 490 , 50 ,50,colors[DARK_GOLDEN_ROD]); 

	for(int i=440;i>=190;i-=50)
	DrawSquare( i , 300 ,50,colors[WHITE]);
	DrawSquare( 290 , 300 ,50,colors[DARK_GOLDEN_ROD]);


	DrawSquare( 190 , 350 ,50,colors[WHITE]);
	
	
	//making ending homes
	
	
	for(int i=840;i>=640;i-=50)
	DrawSquare( i , 350 ,50,colors[MIDNIGHT_BLUE]); // BLUE
	
	for(int i=240;i<=440;i+=50)
	DrawSquare( i , 350 ,50,colors[GREEN]); // Green	
	
	for(int i=650;i>=450;i-=50)	
	DrawSquare( 540 , i ,50,colors[RED]); //  Red
	
	for(int i=50;i<=250;i+=50)
	DrawSquare( 540 , i ,50,colors[DARK_GOLDEN_ROD]); // Yellow
	
	
// creating white spacesS

	for(int i=190;i<=440;i+=50)
	DrawSquare( i , 400 ,50,colors[WHITE]);
	DrawSquare( 240 , 400 ,50,colors[GREEN]);   // Boxes around Green Side


	for(int i=450;i<=700;i+=50)
	DrawSquare( 490 , i ,50,colors[WHITE]);
	DrawSquare( 490 , 600 ,50,colors[GREEN]);

	DrawSquare( 540 , 700 ,50,colors[WHITE]);
	



	for(int i=640;i<=890;i+=50)	
	DrawSquare( i , 300 ,50,colors[WHITE]); // Boxes around Blue side
	DrawSquare( 840 , 300 ,50,colors[MIDNIGHT_BLUE]);



	for(int i=0;i<=250;i+=50)
	DrawSquare( 590 , i ,50,colors[WHITE]); 
	DrawSquare( 590 , 100 ,50,colors[MIDNIGHT_BLUE]);

	DrawSquare( 890 , 350 ,50,colors[WHITE]);
	
	
	
	for(int i=450;i<=700;i+=50)
	DrawSquare( 590 , i ,50,colors[WHITE]); // Boxes around the Red side
	DrawSquare( 590 , 650 ,50,colors[RED]);
	
	
	for(int i=640;i<=890;i+=50)
	DrawSquare( i , 400 ,50,colors[WHITE]);
	DrawSquare( 790 , 400 ,50,colors[RED]);
	
	
	DrawSquare( 540 , 0 ,50,colors[WHITE]);
	
	
	
	//Display Score
	

//	DrawRoundRect( 50.0, 50.0, 75.0, 75.0,colors[DIM_GRAY], 25.0);
	

	
	//creating the homes

	DrawSquare( 190 , 00 ,300,colors[DARK_GOLDEN_ROD]);
	DrawSquare( 230 , 40 ,225,colors[MISTY_ROSE]);

	DrawSquare( 190 , 450 ,300,colors[GREEN]);
	DrawSquare( 230 , 490 ,225,colors[MISTY_ROSE]);

	DrawSquare( 640 , 00 ,300,colors[MIDNIGHT_BLUE]);
	DrawSquare( 680 , 40 ,225,colors[MISTY_ROSE]);
		
	DrawSquare( 640 , 450 ,300,colors[RED]);
	DrawSquare( 680 , 490 ,225,colors[MISTY_ROSE]);
}

 
 
 int random_dice() 
  {
 int  dice=(rand()%6)+1;
   return dice;
  }
 
 

void* r_dice(void* arg){

dice_number= random_dice();


}





void * win_ckecker(void * arg){
int aa=0;
for(int i=0;i<4;i++){
	if(yIndex[i]>=57)
	aa++;
	
	}
	if(aa==4)
	win=true;

	aa=0;
	
for(int i=0;i<4;i++){
	if(rIndex[i]>=57)
	aa++;
	
	}
	if(aa==4)
	win=true;

	aa=0;

for(int i=0;i<4;i++){
	if(gIndex[i]>=57)
	aa++;
	
	}
	if(aa==4)
	win=true;

	aa=0;
for(int i=0;i<4;i++){
	if(bIndex[i]>=57)
	aa++;
	
	}

	if(aa==4)
	win=true;

	pthread_exit(NULL);

}





 void * bd(void * arg){

 	board();
	tokens();
	drawDice(dice_number);
 	pthread_exit(NULL);
 }




 
 
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{


	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	
    static int st=0;

	if(st<5){
		DrawString( 130, 500, "WELCOME TO LUDO !!! " ,colors[MISTY_ROSE]);
		DrawString( 150, 400, "THE GAME OF MIND AND LUCK !!! " ,colors[MISTY_ROSE]);
		DrawString( 580, 250, "				GOOD LUCK :) " ,colors[MISTY_ROSE]);

		sleep(1);
		st++;
	}
	else {
		if(win==false){

pthread_create(&main_thread,NULL,bd,NULL);
pthread_join(main_thread,NULL);

	 board();
	
	 drawDice(dice_number);
	 tokens();
		if(turn==1){
//			player1();//with yellow color
	pthread_create(&tid[0],NULL,p1,NULL);
	pthread_join(tid[0],NULL);
		}
		else if(turn==2){
//			player2();
	pthread_create(&tid[1],NULL,p2,NULL);
	pthread_join(tid[1],NULL);

		}
		else if(turn==3){
//			player3();
	pthread_create(&tid[2],NULL,p3,NULL);
	pthread_join(tid[2],NULL);

		}
		else if(turn==4){
//			player4();
	pthread_create(&tid[3],NULL,p4,NULL);
	pthread_join(tid[3],NULL);
		}	
	
	pthread_create(&master_t,NULL,win_ckecker,NULL);









	}
else if(win==true){

		DrawRoundRect(0,0,1080,1080,colors[BLACK]);
		DrawString( 130, 500, "YOU WON !!!			GAME ENDED " ,colors[MISTY_ROSE]);
		DrawString( 150, 400, " PRESS ESC TO EXIT!!! " ,colors[MISTY_ROSE]);
		sleep(1);

	}
	}
	
	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();


//	pthread_exit(NULL);

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 32/* space bsr key ASCII*/) {

		sem_wait(&sem2);			//semaphore applied on dice to restrict the players to only use one at a time

		cout<<"mouse rolled"<<endl;
		pthread_create(&rol,NULL,r_dice,NULL);
		rolledDice=true;


		sem_post(&sem2);		//releasing the shared resource
	
	}
	
	if (key == 'b' || key == 'B') //Key for placing the bomb
			{

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
//	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	y=-(y-840);
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	y=-(y-840);
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		//cout << GLUT_DOWN << " " << GLUT_UP << endl;
		if(state==0)
		{
		     mouse_x=x;
		     mouse_y=y;	
		cout<<"X= "<<x<<" and y= "<<y<<endl;
		}



	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
//			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	sem_init(&sem1,0,1);//initializing semaphore
	sem_init(&sem2,0,1);//initializing semaphore


	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
