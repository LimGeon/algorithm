#include <stdio.h>

int mainPath[22] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0 };
int aPath[9] = { 10,13,16,19,25,30,35,40,0 };
int bPath[8] = { 20,22,24,25,30,35,40,0 };
int cPath[9] = { 30,28,27,26,25,30,35,40,0 };
int* pathPointer[4] = { mainPath,aPath,bPath,cPath };

typedef struct token {
	int path;
	int* loc;
}TOKEN;

int dice[10];
TOKEN token[4];
int maxPoint = 0;

void DFS(int cnt, int point);

int main()
{
	for (int i = 0; i < 4; i++) {
		token[i].path = 0;
		token[i].loc = mainPath;
	}
	for (int i = 0; i < 10; i++)
		scanf("%d", dice+i);

	DFS(0,0);

	printf("%d", maxPoint);
	return 0;
}

void DFS(int cnt, int point)
{
	TOKEN temp[4];
	for (int i = 0; i < 4; i++) {
		temp[i].path = token[i].path;
		temp[i].loc = token[i].loc;
	}
	for (int i = 0; i < 4; i++) {
		if (temp[i].path == 0) {
			if (*(temp[i].loc) == 10) {
				temp[i].path = 1;
				temp[i].loc = aPath;
			}
			else if (*(token[i].loc) == 20) {
				temp[i].path = 2;
				temp[i].loc = bPath;
			}
			else if (*(token[i].loc) == 30) {
				temp[i].path = 3;
				temp[i].loc = cPath;
			}
		}
		int* next = temp[i].loc + dice[cnt];
		int index = next - pathPointer[temp[i].path];
		if (cnt < 10 && ((temp[i].path == 0 && index < 21) || (temp[i].path == 1 && index < 8) || (temp[i].path == 2 && index < 7) || (temp[i].path == 3 && index < 8))) {
			point += *next;
			token[i].loc = next;
			printf("token: %d, path: %d, index: %d\n", i, token[i].path, index);
			if (maxPoint < point) maxPoint = point;
			DFS(cnt + 1, point);
		}
	}
}