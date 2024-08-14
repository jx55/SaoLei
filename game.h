#pragma once
#define ROW 9
#define COL 9
#define ROWs 12
#define COLs 12

// À×µÄ¸öÊý
#define Mine 10

#include <stdbool.h>

char data[ROWs][COLs];
char show[ROWs][COLs];

void start();
void Game();

void setMine(char mat[ROWs][COLs],int row,int col);
void display(char mat[ROWs][COLs],int row,int col);

void init(char mat[ROWs][COLs], int row, int col, char c);
void recurveSearch(char mat[ROWs][COLs],int row,int col,int x,int y);
int getNumber(char mat[ROWs][COLs],int x,int y);
void searchMine(char mat[ROWs][COLs], int row, int col);
bool isWin(char mat[ROWs][COLs], int row, int col);
