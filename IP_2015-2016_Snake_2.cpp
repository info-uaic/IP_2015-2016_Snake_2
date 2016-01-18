/*
English (Romanian below):

Snake-like Game - 3rd Release
Programmed in December 2015 - January 2016 by Lucian-Jan Filimon for the "Alexandru Ioan Cuza" University of Iasi - Faculty of Computer Science (Project for "Introduction in programming", professors" Corina Forascu, Alexandru Citea).

1st release features:
-A start screen, from which players can choose a level of difficulty
-An end screen
-A snake which can traverse from one side of the screen to the opposite one (e.g. if the snake hits the upper border of the screen, it will continue its path exiting through the lower border)
-A score indicator which shows the current score permanently
-Food which increases the size of the snake with one unit.
-The game is shown as ASCII art on console

Improvements in the 2nd release:
-The creation of a proper scoreboard, displayed permanently in the upper right corner of the screen
-Introduction of a new type of food, which appears when the size of the snake is divided exactly by 5 and whose role is to increase the speed of the snake.
-Showing a border around the game board
-Increase of the size of the game board

Improvements in the 3rd release:
-Fixing movement errors (now the snake does not stop when the gamer attempts to reverse the direction of the snake and, more importantly, does not eat itself when the attempt is made at the border of the game board)
-Addition of sound effects

Romana

Joc tip Snake - versiunea 3
Programat in Decembrie 2015 - Ianuarie 2016 de Lucian-Jan Filimon pentru Universitatea "Alexandru Ioan Cuza" din Iasi - Facultatea de Informatica(Proiect pentru obiectul "Introducere in programare", profesori: Corina Forascu, Alexandru Citea).

Versiunea 1 contine urmatoarele insusiri:
-Un ecran de start, prin care jucatorii pot alege un nivel de dificultate
-Un ecran de finish
-Un sarpe ce poate traversa dintr-o parte in cealata a ecranului (ex: daca sarpele se loveste de partea superioara a ecranului, acesta isi va continua drumul iesind din partea inferioara)
-Un indicator de score afisat in permanenta
-"Mancarea" ce creste dimensiunea sarpelui cu o unitate.
-Un afisaj de tip ASCII art pe consola.

Imbunatatiri aduse in versiunea 2:
-Crearea unui veritabil scoreboard, afisat in permanenta in partea dreapta sus a ecranului
-Adaugarea unui nou tip de mancare, ce apare atunci cand dimensiunea sarpelui se imparte exact la 5, si a carui rol este de a creste viteza sarpelui
-Crearea unei "rame" in jurul spatiului de joc
-Marirea spatiului de joc

Imbunatatiri aduse in versiunea 3:
-Corectarea erorilor de miscare (acum sarpele nu se mai opreste atunci cand dorim sa-l intoracem, si, mai ales, nu se mananca singur atunci cand vrem sa-l intoarcem la marginea spatiului de joc)
-Adaugarea de efecte sonore
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

#define boardSizeX 25
#define boardSizeY 50

char gameBoard[boardSizeX][boardSizeY];
bool canContinue=true;
struct Snake{
    int size;
    short int direction;
    short int pdirection;
    int posX[boardSizeX*boardSizeY];
    int posY[boardSizeX*boardSizeY];
}snake;
struct Food{
    int posX;
    int posY;
}food,speedFood;
int difficultyLevel;

void moveSnake(){
    int i=snake.size;
    while(i>0){
        snake.posX[i]=snake.posX[i-1];
        snake.posY[i]=snake.posY[i-1];
    i--;
    }
}

 void clearScreen(){
    cout << flush;
    system ("CLS");
    }

void initialiseSnake(){
    snake.size=3;
    snake.direction=1;
    snake.pdirection=1;
    srand (time(NULL));
    snake.posX[0]=rand()%boardSizeX;
    snake.posY[0]=rand()%boardSizeY;
    snake.posX[1]=snake.posX[0]-1;
    snake.posY[1]=snake.posY[0];
    snake.posX[2]=snake.posX[1]-1;
    snake.posY[2]=snake.posY[1];}

void newFood(Food &food){
    food.posX=rand()%boardSizeX;
    food.posY=rand()%boardSizeY;
    }

void initaliseBoard(){
    int i,j;
        for(i=0;i<boardSizeX;i++)
        for(j=0;j<boardSizeY;j++)
        gameBoard[i][j]=' ';
    }

void checkEdges(){
    if(snake.posX[0]==-1){snake.posX[0]=boardSizeX-1;}
    if(snake.posX[0]==boardSizeX){snake.posX[0]=0;}
    if(snake.posY[0]==-1){snake.posY[0]=boardSizeY-1;}
    if(snake.posY[0]==boardSizeY){snake.posY[0]=0;}
}

void newTurn(){
    switch(snake.direction) {
  case 0:
    if (snake.posX[0]==0&&snake.pdirection!=0) {
      snake.direction=snake.pdirection;
      newTurn();
    }
    if (!(snake.posX[0]-1==snake.posX[1])) {
      moveSnake();
      snake.posX[0]--;
      snake.pdirection=snake.direction;
    } else {
      snake.direction=snake.pdirection;
      newTurn();
    }
    break;
  case 1:
    if (snake.posX[0]==(boardSizeX-1)&&snake.pdirection!=1) {
      snake.direction=snake.pdirection;
      newTurn();
    }
    if (!(snake.posX[0]+1==snake.posX[1])) {
      moveSnake();
      snake.posX[0]++;
      snake.pdirection=snake.direction;
    } else {
      snake.direction=snake.pdirection;
      newTurn();
    }
    break;
  case 2:
    if (snake.posY[0]==0&&snake.pdirection!=2) {
      snake.direction=snake.pdirection;
      newTurn();
    }
    if (!(snake.posY[0]-1==snake.posY[1])) {
      moveSnake();
      snake.posY[0]--;
      snake.pdirection=snake.direction;
    } else {
      snake.direction=snake.pdirection;
      newTurn();
    }
    break;
  case 3:
    if (snake.posY[0]==(boardSizeY-1)&&snake.pdirection!=3) {
      snake.direction=snake.pdirection;
      newTurn();
    }

    if (!(snake.posY[0]+1==snake.posY[1])) {
      moveSnake();
      snake.posY[0]++;
      snake.pdirection=snake.direction;
    } else {
      snake.direction=snake.pdirection;
      newTurn();
    }
    break;
  default:break;
  }
  checkEdges();
        if((snake.posX[0]==food.posX)&&(snake.posY[0]==food.posY)){
            snake.posX[snake.size]=snake.posX[snake.size-1];
            snake.posY[snake.size]=snake.posY[snake.size-1];
            snake.size++;
            Beep(880,200);
            newFood(food);
            if (snake.size%5==0){
                newFood(speedFood);
            }
        }
        if((snake.posX[0]==speedFood.posX)&&(snake.posY[0]==speedFood.posY)){
            Beep(800,200);
            Beep(1319,200);
            difficultyLevel/=2;
            speedFood.posX=boardSizeX+1;
            speedFood.posY=boardSizeY+1;
        }
}

bool snakeCollides(){
    if(snake.size>2){
    int i;
    for(i=1;i<snake.size;i++){
                if((snake.posX[i]==snake.posX[0])&&(snake.posY[i]==snake.posY[0])){return true;}
}
}
return false;}

void showBoard(){
    int i,j;
    initaliseBoard();
    for(i=0;i<snake.size;i++){
       gameBoard[snake.posX[i]][snake.posY[i]]='0';}
    gameBoard[food.posX][food.posY]='*';
    gameBoard[speedFood.posX][speedFood.posY]='$';
    clearScreen();
    for(i=0;i<boardSizeY+15;i++){cout<<'_';}cout<<endl<<'|';
    for(j=0;j<boardSizeY;j++){cout<<gameBoard[0][j];}cout<<'|'<<" Scor curent "<<"\n|";
    for(j=0;j<boardSizeY;j++){cout<<gameBoard[1][j];}cout<<'|'<<"       "<<snake.size-3<<"\n|";
    for(j=0;j<boardSizeY;j++){cout<<gameBoard[2][j];}cout<<'|';for(i=1;i<14;i++){cout<<'T';}cout<<endl;
    for(i=3;i<boardSizeX;i++){cout<<'|';
    for(j=0;j<boardSizeY;j++){
    cout<<gameBoard[i][j];}
    cout<<'|'<<endl;}
    for(i=0;i<boardSizeY+2;i++){cout<<'T';}cout<<endl;
    }

void startGame(){
    cout<<"  ____              _        "<<endl;
    cout<<" / ___| _ __   __ _| | _____ "<<endl;
    cout<<" `___ `| '_ ` / _` | |/ / _ `"<<endl;
    cout<<"  ___) | | | | (_| |   <  __/"<<endl;
    cout<<" |____/|_| |_|`__,_|_|`_`___|"<<endl<<endl;
    cout<<"Programat in 2015 de Lucian-Jan Filimon"<<endl<<endl;
    cout<<"Scrie un nivel de dificultate intre 1 si 3(1-greu,3-usor):";
    cin>>difficultyLevel;
    while(difficultyLevel>3||difficultyLevel<1){
        cout<<"Nivelul de dificultate trebuie sa fie intre 1 si 3!"<<endl<<"Introdu din nou:";
        cin>>difficultyLevel;
        }
}

void gameOver(){
    clearScreen();
    cout<<"     _    _         _              _       _   _ "<<endl;
    cout<<"    / `  (_)  _ __ (_) ___ _ __ __| |_   _| |_| |"<<endl;
    cout<<"   / _ ` | | | '_ `| |/ _ ` '__/ _` | | | | __| |"<<endl;
    cout<<"  / ___ `| | | |_) | |  __/ | | (_| | |_| | |_|_|"<<endl;
    cout<<" /_/   `_`_| | .__/|_|`___|_|  `__,_|`__,_|`__(_)"<<endl;
    cout<<"             |_|                                 "<<endl<<endl;
    cout<<"Ai terminat cu scorul "<<snake.size-3<<"!";
    Sleep(5000);
}

void game(){
    while(canContinue){

    if(GetAsyncKeyState( VK_UP ) & 0x8000){snake.direction=0;}
    if(GetAsyncKeyState( VK_DOWN ) & 0x8000){snake.direction=1;}
    if(GetAsyncKeyState( VK_LEFT ) & 0x8000){snake.direction=2;}
    if(GetAsyncKeyState( VK_RIGHT ) & 0x8000){snake.direction=3;}

    newTurn();

    if(snakeCollides()){
        canContinue=false;}
    else{
        showBoard();}
    Sleep(difficultyLevel*75);
    }
    gameOver();
    }

int main()
{   startGame();
    initialiseSnake();
    newFood(food);
    speedFood.posX=boardSizeX+1;
    speedFood.posY=boardSizeY+1;
    game();
    return 0;
}
