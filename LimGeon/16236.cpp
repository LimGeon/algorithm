#include <stdio.h>
#include <queue>
#include <windows.h>

using namespace std;

void initVisited();

typedef struct CUR {
	int y, x;
	int size;
	int time;
}CUR;

int map[21][21];
int visited[21][21];
int dx[4] = { 0,-1,1,0 };
int dy[4] = { -1,0,0,1 };
int allTime = 0;
int sharkExp = 0;
int n;
int newStart = 0;

queue<CUR> q;


int main()
{
	int startX, startY;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				startY = i;
				startX = j;
				map[i][j] = 0;
			}
		}
	}

	CUR StartShark = { startY,startX,2,0 };
	q.push(StartShark);
	while (!q.empty()) {
		
		CUR NowShark = q.front();
		printf("%d %d %d\n", NowShark.y+1, NowShark.x+1, NowShark.time);
		q.pop();
		for (int i = 0; i < 4; i++) {
			CUR NextShark = { NowShark.y + dy[i],NowShark.x + dx[i],NowShark.size,NowShark.time+1 };
			if (0 <= NextShark.y && NextShark.y < n && 0 <= NextShark.x && NextShark.x < n) {
				if (0 < map[NextShark.y][NextShark.x] && map[NextShark.y][NextShark.x] < NextShark.size) {
					//Sleep(1000);
					allTime += NextShark.time;
					sharkExp++;
					map[NextShark.y][NextShark.x] = 0;
					
					if (sharkExp == NextShark.size) {
						sharkExp = 0;
						NextShark.size++;
					}
					while (!q.empty()) q.pop();
					newStart = 1;
					if (q.empty() == 1) printf("큐가 비었습니다.\n");
					NextShark.time = 0;
					q.push(NextShark);
					initVisited();
				}
				else if ((map[NextShark.y][NextShark.x] == 0 || map[NextShark.y][NextShark.x] == NextShark.size) && visited[NextShark.y][NextShark.x]==0) {
					q.push(NextShark);
					visited[NextShark.y][NextShark.x] = 1;
				}
			}
			if (newStart == 1) {
				newStart = 0;
				break;
			}
		}
	}
	printf("%d", allTime);
	return 0;
}

void initVisited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}
}