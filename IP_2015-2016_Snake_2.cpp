/*
English (Romanian below):

Snake-like Game - 1st Release
Programmed in December 2015 - January 2016 by Lucian-Jan Filimon for the "Alexandru Ioan Cuza" University of Iasi - Faculty of Computer Science (Project for "Introduction in programming", professors" Corina Forascu, Alexandru Citea).

1st release features:
-A start screen, from which players can choose a level of difficulty
-An end screen
-A snake which can traverse from one side of the screen to the opposite one (e.g. if the snake hits the upper border of the screen, it will continue its path exiting through the lower border)
-A score indicator which shows the current score permanently
-Food which increases the size of the snake with one unit.
-The game is shown as ASCII art on console

Romana

Joc tip Snake - versiunea 1
Programat in Decembrie 2015 de Lucian-Jan Filimon pentru Universitatea "Alexandru Ioan Cuza" din Iasi - Facultatea de Informatica(Proiect pentru obiectul "Introducere in programare", profesori: Corina Forascu, Alexandru Citea).

Versiunea 1 contine urmatoarele insusiri:
-Un ecran de start, prin care jucatorii pot alege un nivel de dificultate
-Un ecran de finish
-Un sarpe ce poate traversa dintr-o parte in cealata a ecranului (ex: daca sarpele se loveste de partea superioara a ecranului, acesta isi va continua drumul iesind din partea inferioara)
-Un indicator de score afisat in permanenta
-"Mancarea" ce creste dimensiunea sarpelui cu o unitate.
-Un afisaj de tip ASCII art pe consola.
*/

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

#define boardSizeX 10
#define boardSizeY 20

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
}food;
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

void newFood(){
    food.posX=rand()%boardSizeX;
    food.posY=rand()%boardSizeY;
    }

void initaliseBoard(){
    int i,j;
        for(i=0;i<boardSizeX;i++)
        for(j=0;j<boardSizeY;j++)
        gameBoard[i][j]=' ';
    }

void newTurn(){
    switch(snake.direction){
    case 0:
        if(!(snake.posX[0]-1==snake.posX[1])){
            moveSnake();snake.posX[0]--;
            snake.pdirection=snake.direction;
        }else{snake.direction=snake.pdirection;}break;
    case 1:
        if(!(snake.posX[0]+1==snake.posX[1])){
            moveSnake();snake.posX[0]++;
            snake.pdirection=snake.direction;
        }else{snake.direction=snake.pdirection;}break;
    case 2:
        if(!(snake.posY[0]-1==snake.posY[1])){
            moveSnake();snake.posY[0]--;
            snake.pdirection=snake.direction;
        }else{snake.direction=snake.pdirection;}break;
    case 3:
        if(!(snake.posY[0]+1==snake.posY[1])){
            moveSnake();snake.posY[0]++;
            snake.pdirection=snake.direction;
        }else{snake.direction=snake.pdirection;}break;
    default:break;
    }
        if((snake.posX[0]==food.posX)&&(snake.posY[0]==food.posY)){
            snake.posX[snake.size]=snake.posX[snake.size-1];
            snake.posY[snake.size]=snake.posY[snake.size-1];
            snake.size++;
            newFood();
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

void checkEdges(){
    if(snake.posX[0]==-1){snake.posX[0]=boardSizeX-1;}
    if(snake.posX[0]==boardSizeX){snake.posX[0]=0;}
    if(snake.posY[0]==-1){snake.posY[0]=boardSizeY-1;}
    if(snake.posY[0]==boardSizeY){snake.posY[0]=0;}
}

void showBoard(){
    int i,j;
    initaliseBoard();
    checkEdges();
    for(i=0;i<snake.size;i++){
       gameBoard[snake.posX[i]][snake.posY[i]]='0';}
    gameBoard[food.posX][food.posY]='*';
    clearScreen();
    for(i=0;i<boardSizeX;i++){
    for(j=0;j<boardSizeY;j++)
    cout<<gameBoard[i][j];
    cout<<endl;}
    cout<<"Scor curent: "<<snake.size-3;
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
    newFood();
    game();
    return 0;
}
