#include "game.h"
#include <stdio.h>

void start()
{
	printf("------------------------------------\n");
	printf("------1-开始游戏  0-退出游戏--------\n");
	printf("------------------------------------\n");
}
void Game()
{
	while (1) {
		start();
		printf("请输入你的选择：");
		int choice;
		scanf("%d", &choice);
		if (choice == 1) {
			// 开始游戏之前先初始化数组
			init(data, ROWs, COLs, '0');
			init(show, ROWs, COLs, '*');
			// 然后布雷
			setMine(data, ROW, COL);
			// display(data, ROW, COL);
			display(show, ROW, COL);

			// 开始扫雷
			searchMine(show, ROW, COL);
		}
		else if (choice == 0) {
			return;
		}
		else {
			printf("输入非法，请重新输入！\n");
		}
	}
}

void setMine(char mat[ROWs][COLs], int row, int col)
{
	int num = Mine;

	while (num) {
		// 生成两个随机数，分别作为x、y的坐标
		// 生成的x的范围是[1,ROW],y也类似
		int x = rand() % ROW + 1;
		int y = rand() % COL + 1;
		// 判断x,y是否合理，该位置应该原本不为雷才行
		if (mat[x][y] == '0') {
			mat[x][y] = '1';
		}
		else {
			// 否则当次循环不起作用
			num++;
		}
		num--;
	}
}
void searchMine(char mat[ROWs][COLs],int row,int col)
{
	int i = 2; // 表示用户有两次机会

	// 扫雷的过程就是让玩家输入一个坐标
	while (1) {
		int x, y;
		printf("请输入坐标：");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (data[x][y] == '1') {
				// 该位置是雷
				i--;
				if (i == 0) {
					// 游戏结束
					printf("游戏结束...\n");
					return;
				}
				else {
					printf("游戏失败，还有一次机会！\n");
					continue;
				}
			}
			else if (data[x][y] == '0') {
				// 该位置不为雷，则进行递归搜索，该位置显示的是其九宫格内雷的数量
				recurveSearch(show,row,col,x,y);
				display(show,row,col);
				if (isWin(show,row,col)) {
					break;
				}
			}
		}
		else {
			printf("输入的坐标非法，请重新输入！\n");
		}
	}
	printf("恭喜你，游戏胜利！\n");
}
void recurveSearch(char mat[ROWs][COLs], int row, int col, int x, int y) 
{
	// 判断坐标是否合规，合规了才能进行递归
	if (x >= 1 && x <= row && y >= 1 && y <= col) {
		// 两个退出条件
		if (mat[x][y] == ' ') {
			return;
		}
		else if (getNumber(data, x, y) != 0) {
			// 说明周围有雷，返回数字即可
			mat[x][y] = getNumber(data, x, y) + '0';
			return;
		}

		mat[x][y] = ' ';
		// display(mat, row, col);

		// 进行递归
		recurveSearch(mat, row, col, x-1, y-1);
		recurveSearch(mat, row, col, x-1, y);
		recurveSearch(mat, row, col, x-1, y+1);
		recurveSearch(mat, row, col, x, y-1);
		recurveSearch(mat, row, col, x, y+1);
		recurveSearch(mat, row, col, x+1, y-1);
		recurveSearch(mat, row, col, x+1, y);
		recurveSearch(mat, row, col, x+1, y+1);
	}
	else {
		// printf("坐标不合规，无法递归！\n");
	}
}

int getNumber(char mat[ROWs][COLs],int x,int y)
{
	int res = mat[x - 1][y] + mat[x - 1][y - 1] + mat[x - 1][y + 1] +
		mat[x][y - 1] + mat[x][y + 1] + mat[x + 1][y - 1] + mat[x + 1][y] + mat[x + 1][y + 1];
	res = res - 8 * '0';
	return res;
}

bool isWin(char mat[ROWs][COLs], int row, int col)
{
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (data[i][j] == '1' || data[i][j] == '0' && mat[i][j] != '*') {
				// 这种情况就继续
				continue;
			}
			else {
				return false;
			}
		}
	}
	// 如果所有位置都满足要求，则扫雷成功
	return true;
}
void display(char mat[ROWs][COLs], int row, int col)
{
	// 输出第一行的编号
	printf("  ");
	for (int i = 1; i <= col; i++) {
		printf("%d ", i);
	}
	printf("\n");

	for (int i = 1; i <= row; i++) {
		printf("%d ", i);
		for (int j = 1; j <= col; j++) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
}

// 初始化数组
void init(char mat[ROWs][COLs], int row, int col, char c)
{
	// 先将数组所有元素置为0，再产生坐标去布置雷的位置
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = c;
		}
	}
}
