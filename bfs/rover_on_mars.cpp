#include <iostream>

using namespace std;

#define MOVES_NUMBER 4
#define N_MAX 1000
#define M_MAX 1000

struct Point {
	int x;
	int y;
};

struct Cell {
	int dist;
	int prev;
};

Point queue[N_MAX * M_MAX];
int head, tail;

Cell field[N_MAX + 2][M_MAX + 2];
Point moves[MOVES_NUMBER] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
char moves_c[] = "rldu";
char path[N_MAX * M_MAX];

int main()
{
	int n, m;
	char symb;
	Point R, S;

	cin >> n >> m;

	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			if (i == 0 || i == n+1 || j == 0 || j == m+1) {
				field[i][j].dist = -2;
				continue;
			}
			cin >> symb;
			if (symb == '.') {
				field[i][j].dist = -1;
			} else if (symb == '*') {
				field[i][j].dist = -2;
			} else if (symb == 'R') {
				field[i][j].dist = 0;
				R.x = i;
				R.y = j;
			} else {  // symb == 'S'
				field[i][j].dist = -1;
				S.x = i;
				S.y = j;
			}
		}
	}

	queue[tail++] = R;
	while (head != tail) {
		Point cur = queue[head++];
		for (int i = 0; i < MOVES_NUMBER; ++i) {
			Point adj;
			adj.x = cur.x + moves[i].x;
			adj.y = cur.y + moves[i].y;
			if (field[adj.x][adj.y].dist == -1) {
				queue[tail++] = adj;
				field[adj.x][adj.y].dist = field[cur.x][cur.y].dist + 1;
				field[adj.x][adj.y].prev = i;
			}
		}
	}

	int &dist = field[S.x][S.y].dist;
	cout << dist << endl;
	Point next = S;
	if (dist != -1) {
		for (int i = dist-1; i >= 0; --i) {
			int &prev = field[next.x][next.y].prev;
			path[i] = moves_c[prev];
			next.x -= moves[prev].x;
			next.y -= moves[prev].y;
		}
		cout << path << endl;
	}

	return 0;
}
