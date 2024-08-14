#include "game.h"
#include <stdio.h>

void start()
{
	printf("------------------------------------\n");
	printf("------1-��ʼ��Ϸ  0-�˳���Ϸ--------\n");
	printf("------------------------------------\n");
}
void Game()
{
	while (1) {
		start();
		printf("���������ѡ��");
		int choice;
		scanf("%d", &choice);
		if (choice == 1) {
			// ��ʼ��Ϸ֮ǰ�ȳ�ʼ������
			init(data, ROWs, COLs, '0');
			init(show, ROWs, COLs, '*');
			// Ȼ����
			setMine(data, ROW, COL);
			// display(data, ROW, COL);
			display(show, ROW, COL);

			// ��ʼɨ��
			searchMine(show, ROW, COL);
		}
		else if (choice == 0) {
			return;
		}
		else {
			printf("����Ƿ������������룡\n");
		}
	}
}

void setMine(char mat[ROWs][COLs], int row, int col)
{
	int num = Mine;

	while (num) {
		// ����������������ֱ���Ϊx��y������
		// ���ɵ�x�ķ�Χ��[1,ROW],yҲ����
		int x = rand() % ROW + 1;
		int y = rand() % COL + 1;
		// �ж�x,y�Ƿ������λ��Ӧ��ԭ����Ϊ�ײ���
		if (mat[x][y] == '0') {
			mat[x][y] = '1';
		}
		else {
			// ���򵱴�ѭ����������
			num++;
		}
		num--;
	}
}
void searchMine(char mat[ROWs][COLs],int row,int col)
{
	int i = 2; // ��ʾ�û������λ���

	// ɨ�׵Ĺ��̾������������һ������
	while (1) {
		int x, y;
		printf("���������꣺");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (data[x][y] == '1') {
				// ��λ������
				i--;
				if (i == 0) {
					// ��Ϸ����
					printf("��Ϸ����...\n");
					return;
				}
				else {
					printf("��Ϸʧ�ܣ�����һ�λ��ᣡ\n");
					continue;
				}
			}
			else if (data[x][y] == '0') {
				// ��λ�ò�Ϊ�ף�����еݹ���������λ����ʾ������Ź������׵�����
				recurveSearch(show,row,col,x,y);
				display(show,row,col);
				if (isWin(show,row,col)) {
					break;
				}
			}
		}
		else {
			printf("���������Ƿ������������룡\n");
		}
	}
	printf("��ϲ�㣬��Ϸʤ����\n");
}
void recurveSearch(char mat[ROWs][COLs], int row, int col, int x, int y) 
{
	// �ж������Ƿ�Ϲ棬�Ϲ��˲��ܽ��еݹ�
	if (x >= 1 && x <= row && y >= 1 && y <= col) {
		// �����˳�����
		if (mat[x][y] == ' ') {
			return;
		}
		else if (getNumber(data, x, y) != 0) {
			// ˵����Χ���ף��������ּ���
			mat[x][y] = getNumber(data, x, y) + '0';
			return;
		}

		mat[x][y] = ' ';
		// display(mat, row, col);

		// ���еݹ�
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
		// printf("���겻�Ϲ棬�޷��ݹ飡\n");
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
				// ��������ͼ���
				continue;
			}
			else {
				return false;
			}
		}
	}
	// �������λ�ö�����Ҫ����ɨ�׳ɹ�
	return true;
}
void display(char mat[ROWs][COLs], int row, int col)
{
	// �����һ�еı��
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

// ��ʼ������
void init(char mat[ROWs][COLs], int row, int col, char c)
{
	// �Ƚ���������Ԫ����Ϊ0���ٲ�������ȥ�����׵�λ��
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = c;
		}
	}
}
