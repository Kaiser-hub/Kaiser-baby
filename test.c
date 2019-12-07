#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>


#define MAX_ROW 20
#define MAX_COL 20

char chessBoard[MAX_ROW][MAX_COL] = { 0 };//棋盘字符二维数组
int row = 0, col = 0;//玩家输入的坐标
int crow = 0, ccol = 0;//电脑输入的坐标
int x = 0, y = 0;//检查有连续棋子的情况出现后，坐标的位置

//游戏开始界面打印以及玩家选择是否开始游戏
int BeginGame() {
	printf("==============================\n");
	printf("欢迎来到五子棋游戏！\n");
	printf("1.开始游戏\n");
	printf("0.退出游戏\n");
	printf("==============================\n");
	return 0;
}

//初始化棋盘
void Init() {
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			chessBoard[i][j] = ' ';
		}
	}
}

//打印棋盘
void Print() {
	printf("    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19\n");
	for (int i = 0; i < MAX_ROW; i++) {
		printf("  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
		printf("%2d| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n",i,
			chessBoard[i][0], chessBoard[i][1], chessBoard[i][2], chessBoard[i][3], 
			chessBoard[i][4], chessBoard[i][5], chessBoard[i][6], chessBoard[i][7], 
			chessBoard[i][8], chessBoard[i][9], chessBoard[i][10], chessBoard[i][11], 
			chessBoard[i][12], chessBoard[i][13], chessBoard[i][14], chessBoard[i][15],
			chessBoard[i][16], chessBoard[i][17], chessBoard[i][18], chessBoard[i][19]);
	}
	printf("  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
}

//玩家落子
void PlayerMove() {
	printf("该你落子了\n");
	printf("请输入你要落子位置的坐标\n");
	while (1) {
		scanf("%d %d", &row, &col);
		if (row < 0 || row >(MAX_ROW - 1) || col < 0 || col >(MAX_COL - 1)) {
			printf("输入坐标有误，请重新输入\n");
			continue;
		}
		else if (chessBoard[row][col] != ' ') {
			printf("此位置已经有棋子了，请选择其他位置落子\n");
			continue;
		}
		else {
			chessBoard[row][col] = 'X';
			break;
		}
	}
}

//玩家1落子
void Player_1Move() {
	printf("该玩家1落子了\n");
	printf("请输入你要落子位置的坐标\n");
	int row = 0, col = 0;
	while (1) {
		scanf("%d%d", &row, &col);
		if (row < 0 || row > (MAX_ROW - 1) || col < 0 || col > (MAX_COL - 1)) {
			printf("输入坐标有误，请重新输入\n");
			continue;
		}
		else if (chessBoard[row][col] != ' ') {
			printf("此位置已经有棋子了，请选择其他位置落子\n");
			continue;
		}
		else {
			chessBoard[row][col] = 'X';
			break;
		}
	}
}

//玩家2落子
void Player_2Move() {
	printf("该玩家2落子了\n");
	printf("请输入你要落子位置的坐标\n");
	int row = 0, col = 0;
	while (1) {
		scanf("%d%d", &row, &col);
		if (row < 0 || row >(MAX_ROW - 1) || col < 0 || col >(MAX_COL - 1)) {
			printf("输入坐标有误，请重新输入\n");
			continue;
		}
		else if (chessBoard[row][col] != ' ') {
			printf("此位置已经有棋子了，请选择其他位置落子\n");
			continue;
		}
		else {
			chessBoard[row][col] = 'O';
			break;
		}
	}
}

//检查某个位置是否有五连子的机会
int Check_5qi(int row, int col) {
	int min = -1, max = 0;
	for (int i = row - 4; i < row + 4; i++) {//检查竖向
		if (i > MAX_ROW-1) {
			break;
		}
		if (min == -1 && i >= 0) {
			min = i;
		}
		max = i;
	}
	if (max - min >= 5) {
		return 1;
	}
	for (int i = col - 4; i < col + 4; i++) {//检查横向
		if (i > MAX_COL-1) {
			break;
		}
		if (min == -1 && i >= 0) {
			min = i;
		}
		max = i;
	}
	if (max - min >= 5) {
		return 1;
	}
}

//判断是否存有N个连续棋子的情况，并且返回它的方向（1横向或2竖向或3、4对角线）
int CheckContinuity_N(int N, int row, int col, char ch) {
	int count = 0;
	for (int i = col - 4; i <= col + 4; i++) {//横向判断
		if (i < 0) {
			continue;
		}
		if (i > 19) {
			break;
		}
		if (chessBoard[row][i] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			x = row;
			y = i;
			return 1;
		}
	}
	count = 0;
	for (int i = row - 4; i <= row + 4; i++) {//竖向判断
		if (i < 0) {
			continue;
		}
		if (i > 19) {
			break;
		}
		if (chessBoard[i][col] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			y = col;
			x = i;
			return 2;
		}
	}
	count = 0;
	for (int i = row - 4, j = col - 4; i <= row + 4 && j <= col + 4; i++, j++) {//左上到右下对角线判断
		if (i < 0 || j < 0) {
			continue;
		}
		if (i > 19 || j > 19) {
			break;
		}
		if (chessBoard[i][j] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			x = i;
			y = j;
			return 3;
		}
	}
	count = 0;
	for (int i = row - 4, j = col + 4; i <= row + 4 && j >= col - 4; i++, j--) {//右上到左下对角线判断
		if (i < 0 || j > 19) {
			continue;
		}
		if (i > 19 || j < 0) {
			break;
		}
		if (chessBoard[i][j] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			x = i;
			y = j;
			return 4;
		}
	}
	return 0;
}

//判断（row，col）周围有多少二连子
int CheckContinuity_2(int N, int row, int col, char ch) {
	int count = 0, ret = 0;
	for (int i = col - 2; i <= col + 2; i++) {//横向判断
		if (i < 0 || i == col) {
			continue;
		}
		if (i > 19) {
			break;
		}
		if (chessBoard[row][i] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			ret = ret + 1;
			break;
		}
	}
	count = 0;
	for (int i = row - 2; i <= row + 2; i++) {//竖向判断
		if (i < 0 || i == row) {
			continue;
		}
		if (i > 19) {
			break;
		}
		if (chessBoard[i][col] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			ret = ret + 1;
			break;
		}
	}
	count = 0;
	for (int i = row - 2, j = col - 2; i <= row + 2 && j <= col + 2; i++, j++) {//左上到右下对角线判断
		if (i < 0 || j < 0 || (i == row && j == col)) {
			continue;
		}
		if (i > 19 || j > 19) {
			break;
		}
		if (chessBoard[i][j] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			ret = ret + 1;
			break;
		}
	}
	count = 0;
	for (int i = row - 2, j = col + 2; i <= row + 2 && j >= col - 2; i++, j--) {//右上到左下对角线判断
		if (i < 0 || j > 19 || (i == row && j == col)) {
			continue;
		}
		if (i > 19 || j < 0) {
			break;
		}
		if (chessBoard[i][j] != ch) {
			count = 0;
			continue;
		}
		count++;
		if (count == N) {
			ret = ret + 1;
			break;
		}
	}
	return ret;
}

//在已连成的N个子的前后落子
int ComputerAI_1(int N, int a) {
	if (a == 1) {//横向连成N个子
		if (y - 5 >= 0 && chessBoard[x][y - N] == ' ') {
			chessBoard[x][y - N] = 'O';
			crow = x;
			ccol = y - N;
			return 1;
		}
		if (y + 5 - N < MAX_COL&&chessBoard[x][y + 1] == ' ') {
			chessBoard[x][y + 1] = 'O';
			crow = x;
			ccol = y + 1;
			return 1;
		}
	}
	else if (a == 2) {//竖向连成N个子
		if (x - 5 >= 0 && chessBoard[x - N][y] == ' ') {
			chessBoard[x - N][y] = 'O';
			crow = x - N;
			ccol = y;
			return 1;
		}
		if (x + 5 - N < MAX_ROW&&chessBoard[x + 1][y] == ' ') {
			chessBoard[x + 1][y] = 'O';
			crow = x + 1;
			ccol = y;
			return 1;
		}
	}
	else if (a == 3) {//左上到右下对角线连成N个子
		if (x - 5 >= 0 && y - 5 >= 0 && chessBoard[x - N][y - N] == ' ') {
			chessBoard[x - N][y - N] = 'O';
			crow = x - N;
			ccol = y - N;
			return 1;
		}
		if (x + 5 - N < MAX_ROW && y + 5 - N < MAX_COL && chessBoard[x + 1][y + 1] == ' ') {
			chessBoard[x + 1][y + 1] = 'O';
			crow = x + 1;
			ccol = y + 1;
			return 1;
		}
	}
	else if (a == 4) {//右上到左下对角线连成N个子
		if (x - 5 >= 0 && y + 5 - N < MAX_COL && chessBoard[x - N][y + N] == ' '){
			chessBoard[x - N][y + N] = 'O';
			crow = x - N;
			ccol = y + N;
			return 1;
		}
		if (y - 5 >= 0 && x + 5 - N < MAX_ROW&&chessBoard[x + 1][y - 1] == ' ') {
			chessBoard[x + 1][y - 1] = 'O';
			crow = x + 1;
			ccol = y - 1; 
			return 1;
		}
	}
	return 0;
}

//检查是否有XX X或X XX或XXX X或X XXX情况
int ComputerAI_2(int a, int b, char ch) {
	if (a == 1) {//横向检查
		if (y + b < MAX_COL && chessBoard[x][y + 1] == ' ' && chessBoard[x][y + b] == ch) {
			chessBoard[x][y + 1] = 'O';
			crow = x;
			ccol = y + 1;
			return 1;
		}
		if (y - b - 1 >= 0 && chessBoard[x][y - b] == ' ' && chessBoard[x][y - b - 1] == ch) {
			chessBoard[x][y - b] = 'O';
			crow = x;
			ccol = y - b;
			return 1;
		}
	}
	else if (a == 2) {//竖向检查
		if (x + b < MAX_ROW && chessBoard[x + 1][y] == ' ' && chessBoard[x + b][y] == ch) {
			chessBoard[x + 1][y] = 'O';
			crow = x + 1;
			ccol = y;
			return 1;
		}
		if (x - b - 1 >= 0 && chessBoard[x - b][y] == ' ' && chessBoard[x - b - 1][y] == ch) {
			chessBoard[x - b][y] = 'O';
			crow = x - b;
			ccol = y;
			return 1;
		}
	}
	else if (a == 3) {//左上到右下对角线检查
		if (x + b < MAX_ROW && y + b < MAX_COL && chessBoard[x + 1][y + 1] == ' ' && chessBoard[x + b][y + b] == ch) {
			chessBoard[x + 1][y + 1] = 'O';
			crow = x + 1;
			ccol = y + 1;
			return 1;
		}
		if (x - b - 1 >= 0 && y - b - 1 >= 0 && chessBoard[x - b][y - b] == ' ' && chessBoard[x - b - 1][y - b - 1] == ch) {
			chessBoard[x - b][y - b] = 'O';
			crow = x - b;
			ccol = y - b;
			return 1;
		}
	}
	else if (a == 4) {//右上到左下对角线检查
		if (x + b < MAX_ROW && y - b - 1 >= 0 && chessBoard[x + 1][y - 1] == ' ' && chessBoard[x + b][y - b] == ch) {
			chessBoard[x + 1][y - 1] = 'O';
			crow = x + 1;
			ccol = y - 1;
			return 1;
		}
		if (y + b < MAX_COL && x - b - 1 >= 0 && chessBoard[x - b][y + b] == ' ' && chessBoard[x - b - 1][y + b - 1] == ch) {
			chessBoard[x - b][y - b] = 'O';
			crow = x - b;
			ccol = y + b;
			return 1;
		}
	}
	return 0;
}

//检查是否有 XXX 或 XX 的情况
int ComputerAI_3(int a, int b) {
	if (a == 1) {//横向检查
		if (y + 1 < MAX_COL && y - b >= 0 && chessBoard[x][y + 1] == ' ' && chessBoard[x][y - b] == ' ') {
			if (y + 5 - b < MAX_COL) {
				chessBoard[x][y + 1] = 'O';
				crow = x;
				ccol = y + 1;
				return 1;
			}
			else if (y - b >= 0) {
				chessBoard[x][y - b] = 'O';
				crow = x;
				ccol = y - b;
				return 1;
			}
		}
	}
	else if (a == 2) {//竖向检查
		if (x + 1 < MAX_ROW && x - b >= 0 && chessBoard[x + 1][y] == ' ' && chessBoard[x - b][y] == ' ') {
			if (x + 5 - b < MAX_ROW) {
				chessBoard[x + 1][y] = 'O';
				crow = x + 1;
				ccol = y;
				return 1;
			}
			else if (x - b >= 0) {
				chessBoard[x - b][y] = 'O';
				crow = x - b;
				ccol = y;
				return 1;
			}
		}
	}
	else if (a == 3) {//左上到右下对角线检查
		if (x + 1 < MAX_ROW && y + 1 < MAX_COL && x - b >= 0 && y - b >= 0 && chessBoard[x + 1][y + 1] == ' ' && chessBoard[x - b][y - b] == ' ') {
			if (x + 5 - b < MAX_ROW && y + 5 - b < MAX_COL) {
				chessBoard[x + 1][y + 1] = 'O';
				crow = x + 1;
				ccol = y + 1;
				return 1;
			}
			else if (x - b >= 0 && y - b >= 0) {
				chessBoard[x - b][y - b] = 'O';
				crow = x - b;
				ccol = y - b;
				return 1;
			}
			else if (Check_5qi(x, y) == 1) {
				if (x + 1 < MAX_ROW && y + 1 < MAX_COL) {
					chessBoard[x + 1][y + 1] = 'O';
					crow = x + 1;
					ccol = y + 1;
					return 1;
				}
				else if (x - b >= 0 && y - b >= 0) {
					chessBoard[x - b][y - b] = 'O';
					crow = x - b;
					ccol = y - b;
					return 1;
				}
			}
		}
	}
	else if (a == 4) {//右上到左下对角线检查
		if (x - b >= 0 && y + b < MAX_COL && chessBoard[x + 1][y - 1] == ' ' && chessBoard[x - b][y + b] == ' ') {
			if (x + 5 - b < MAX_ROW && y - 1 >= 0) {
				chessBoard[x + 1][y - 1] = 'O';
				crow = x + 1;
				ccol = y - 1;
				return 1;
			}
		}
		else if (y + 5 - b < MAX_COL && x - 1 >= 0) {
			chessBoard[x - b][y + b] = 'O';
			crow = x - b;
			ccol = y + b;
			return 1;
		}
		else if (Check_5qi(x, y) == 1) {
			if (x + 1 < MAX_ROW && y - 1 >= 0) {
				chessBoard[x + 1][y - 1] = 'O';
				crow = x + 1;
				ccol = y - 1;
				return 1;
			}
			else if (y + b < MAX_COL && x - b >= 0) {
				chessBoard[x - b][y + b] = 'O';
				crow = x - b;
				ccol = y + b;
				return 1;
			}
		}
	}
	return 0;
}

//若有X X或者O O情况，落子到中间
int ComputerAI_4(int a, int b, char ch) {
	if (b + 2 < MAX_COL && chessBoard[a][b] == ch && chessBoard[a][b + 1] == ' ' && chessBoard[a][b + 2] == ch) {//横向判断
		chessBoard[a][b + 1] = 'O';
		crow = a;
		ccol = b + 1;
		return 1;
	}
	if (a + 2 < MAX_ROW && chessBoard[a][b] == ch && chessBoard[a + 1][b] == ' ' && chessBoard[a + 2][b] == ch) {//竖向判断
		chessBoard[a + 1][b] = 'O';
		crow = a + 1;
		ccol = b;
		return 1;
	}
	if (b + 2 < MAX_COL && a + 2 < MAX_ROW && chessBoard[a][b] == ch && chessBoard[a + 1][b + 1] == ' ' && chessBoard[a + 2][b + 2] == ch) {//左上到右下对角线判断
		chessBoard[a + 1][b + 1] = 'O';
		crow = a + 1;
		ccol = b + 1;
		return 1;
	}
	if (b - 2 >= 0 && a + 2 < MAX_ROW && chessBoard[a][b] == ch && chessBoard[a + 1][b - 1] == ' ' && chessBoard[a + 2][b - 2] == ch) {//右上到左下对角线判断
		chessBoard[a + 1][b - 1] = 'O';
		crow = a + 1;
		ccol = b - 1;
		return 1;
	}
	return 0;
}

//检查玩家是否有两个三子对角线如
//  ' '
//  X X
// X   X
int ComputerAI_5(char ch) {
	for (int i = 2; i < MAX_ROW; i++) {
		for (int j = 2; j < MAX_COL; j++) {
			if (chessBoard[i][j] == ' ' && CheckContinuity_2(2, i, j, ch) > 0) {
				chessBoard[i][j] = 'O';
				return 1;
			}
		}
	}
	return 0;
}

//遍历整个棋盘寻找合适的落子位置(对于电脑来说电脑胜利优先度大于堵截玩家)
int ComputerAI_6() {
	srand((unsigned int)time(0));
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'O' && ComputerAI_1(4, CheckContinuity_N(4, i, j, 'O')) == 1) {//如果有四个O连在一起，则连接第五个
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'O' && ComputerAI_3(CheckContinuity_N(3, i, j, 'O'), 3) == 1) {//如果有 OOO 情况，连接第四个O
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'O' && ComputerAI_2(CheckContinuity_N(2, i, j, 'O'), 2, 'O') == 1) {//如果有OO O或者O OO情况往空处落子
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'X' && ComputerAI_2(CheckContinuity_N(2, i, j, 'X'), 2, 'X') == 1) {//如果有XX X或者X XX情况往空处落子
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'X' && ComputerAI_3(CheckContinuity_N(3, i, j, 'X'), 3) == 1) {//如果有 XXX 情况，堵截O
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'O' && ComputerAI_1(3, CheckContinuity_N(3, i, j, 'O')) == 1) {//如果有三个O连在一起，连接第四个O
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'X' && ComputerAI_1(3, CheckContinuity_N(3, i, j, 'X')) == 1) {//如果有三个X连在一起，则堵截
				return 1;
			}
		}
	}
	if (ComputerAI_5('X') == 1) {
		return;
	}
	
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (ComputerAI_4(i, j, 'X') == 1) {//如果有X X情况，空处堵截
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (ComputerAI_3(CheckContinuity_N(2, i, j, 'O'), 2) == 1) {//如果有 OO 情况，连接第三个O
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (ComputerAI_4(i, j, 'O') == 1) {//如果有O O情况，空处落O
				return 1;
			}
		}
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (chessBoard[i][j] == 'O' && ComputerAI_1(2, CheckContinuity_N(2, i, j, 'O')) == 1) {//如果有两个O连在一起，则连接第三个
				return 1;
			}
		}
	}
	int row1 = MAX_ROW / 2;
	int col1 = MAX_COL / 2;
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j < 2 * i - 1; j++) {
			if (chessBoard[row1][col1++] == 'O') {// 如果有1个O则连接第2个O
				x = row1;
				y = col1 - 1;
				if (ComputerAI_1(1, 4) == 1) {//随机竖向或者横向或者对角线落子
					return 1;
				}
			}

		}
		for (int j = 0; j < 2 * i; j++) {
			if (chessBoard[row1++][col1] == 'O') {// 如果有1个O则连接第2个O
				x = row1 - 1;
				y = col1;
				if (ComputerAI_1(1, 4) == 1) {//随机竖向或者横向或者对角线落子
					return 1;
				}
			}
		}
		for (int j = 0; j < 2 * i; j++) {
			if (chessBoard[row1][col1--] == 'O') {// 如果有1个O则连接第2个O
				x = row1;
				y = col1 + 1;
				if (ComputerAI_1(1, rand() % 4 + 1) == 1) {//随机竖向或者横向或者对角线落子
					return 1;
				}
			}
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			if (chessBoard[row1--][col1] == 'O') {
				x = row1 + 1;
				y = col1;
				if (ComputerAI_1(1, rand() % 4 + 1) == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void ComputerMove() {
	srand((unsigned int)time(0));
	if (ComputerAI_1(4, CheckContinuity_N(4, crow, ccol, 'O')) == 1) {//如果有四个O连在一起，连接第五个O
		return;
	}
	if (ComputerAI_2(CheckContinuity_N(2, row, col, 'X'), 3, 'X') == 1) {//XXX X或X XXX情况，堵截
		return;
	}
	if (ComputerAI_1(4, CheckContinuity_N(4, row, col, 'X')) == 1) {//XXXX堵截
		return;
	}
	if (ComputerAI_2(CheckContinuity_N(2, row, col, 'X'), 2, 'X') == 1) {//XX X或X XX情况，堵截
		return;
	}
	if (ComputerAI_3(CheckContinuity_N(3, crow, ccol, 'O'), 3) == 1) {// OOO 情况连第四个O
		return;
	}
	if (ComputerAI_5('O') == 1) {
		return;
	}
	if (ComputerAI_1(3, CheckContinuity_N(3, crow, ccol, 'O')) == 1) {//三个O连在一起，连接第四个O
		return;
	}
	if (ComputerAI_1(3, CheckContinuity_N(3, row, col, 'X')) == 1) {//三个X连在一起，堵截
		return;
	}
	if (ComputerAI_2(CheckContinuity_N(2, crow, ccol, 'O'), 3, 'O') == 1) {//OOO O或O OOO情况，空处落子
		return;
	}
	if (ComputerAI_2(CheckContinuity_N(2, crow, ccol, 'O'), 2, 'O') == 1) {//OO O或O OO情况，空处落子
		return;
	}
	if (ComputerAI_6() == 1) {
		return;
	}
	crow = rand() % MAX_ROW;
	ccol = rand() % MAX_COL;
	if (chessBoard[crow][ccol] == ' ') {
		chessBoard[crow][ccol] = 'O';
		return;
	}
}


void Game() {
	int sult = 0;
	int choice1 = 0;
	printf("1.玩家先行\n");
	printf("0.电脑先行\n");
	scanf("%d", &choice1);
	system("cls");
	Init();
	if (choice1 == 1) {
		while (1) {
			sult++;
			Print();
			PlayerMove();
			Print();
			system("cls");
			if (CheckContinuity_N(5, row, col, 'X') != 0) {
				Print();
				printf("恭喜你，你赢了！\n");
				break;
			}
			ComputerMove();
			Print();
			system("cls");
			if (CheckContinuity_N(5, crow, ccol, 'O') != 0) {
				Print();
				printf("你太菜了，连电脑都下不过！\n");
				break;
			}
			if (sult == 400) {
				printf("和棋了，你和电脑半斤八两！\n");
				break;
			}
		}
	}
	else if (choice1 == 0) {
		while (1) {
			sult++;
			ComputerMove();
			Print();
			if (CheckContinuity_N(5, crow, ccol, 'O') != 0) {
				Print();
				printf("你太菜了，连电脑都下不过！\n");
				break;
			}
			PlayerMove();
			Print();
			system("cls");
			if (CheckContinuity_N(5, row, col, 'X') != 0) {
				Print();
				printf("恭喜你，你赢了！\n");
				break;
			}
			if (sult == 400) {
				printf("和棋了，你和电脑半斤八两！\n");
				break;
			}
		}
	}
	return;
}

int main() {
	int choic = 0;
	BeginGame();
	scanf("%d", &choic);
	if (choic == 1) {
		system("cls");
		Game();
	}
	else {
		printf("再见！\n");
	}
	return 0;
}

