#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nRet, nFiled[102][102], nVisit[102][102][5];
int n, m, start_x, start_y, start_dir;
int end_x, end_y, end_dir;
int dirx[] = { 0, 1, -1, 0, 0 }; // 1 : µ¿, 2 : ¼­, 3 : ³², 4 : ºÏ
int diry[] = { 0, 0, 0, 1, -1 };

typedef struct inf{
	int x, y, dir, count;
};

int bfs()
{
	queue <inf> bfs_q;
	bfs_q.push({ start_x, start_y, start_dir, 0 });
	nVisit[start_y][start_x][start_dir] = 1;
	inf next_inf = { 0, 0, 0, 0 };

	while (!bfs_q.empty())
	{
		inf cur_inf = bfs_q.front();
		bfs_q.pop();

		if (cur_inf.x == end_x && cur_inf.y == end_y && cur_inf.dir == end_dir)
			return cur_inf.count;

		for (int i = 1; i < 5; i++){
			next_inf.x = cur_inf.x;
			next_inf.y = cur_inf.y;
			next_inf.dir = i;

			if (nVisit[next_inf.y][next_inf.x][next_inf.dir])
				continue;

			if (cur_inf.dir + next_inf.dir == 3) // µ¿ -> ¼­, ¼­ -> µ¿ À¸·Î ¹Ù²ð°æ¿ì
				next_inf.count = cur_inf.count + 2;
			else if (cur_inf.dir + next_inf.dir == 7) // ³² -> ºÏ, ºÏ -> ³² À¸·Î ¹Ù²ð°æ¿ì
				next_inf.count = cur_inf.count + 2;
			else					  
				next_inf.count = cur_inf.count + 1;
			

			nVisit[next_inf.y][next_inf.x][next_inf.dir] = 1;
			bfs_q.push(next_inf);
		}

		for (int i = 1; i < 4; i++){
			next_inf.x = cur_inf.x + (dirx[cur_inf.dir] * i);
			next_inf.y = cur_inf.y + (diry[cur_inf.dir] * i);
			next_inf.dir = cur_inf.dir;

			if (nFiled[next_inf.y][next_inf.x] || next_inf.x <= 0 || next_inf.y <= 0 || next_inf.x > n || next_inf.y > m)
				break;

			if (nVisit[next_inf.y][next_inf.x][next_inf.dir])
				continue;

			nVisit[next_inf.y][next_inf.x][next_inf.dir] = 1;
			next_inf.count = cur_inf.count + 1;
			bfs_q.push(next_inf);
		}
	}

}

int main()
{	
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &nFiled[i][j]);
		}
	}

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 1; k < 5; k++){
				nVisit[i][j][k] = 0;
			}
		}
	}

	scanf("%d %d %d %d %d %d", &start_y, &start_x, &start_dir, &end_y, &end_x, &end_dir);

	nRet = bfs();
	printf("%d\n", nRet);

	return 0;
}