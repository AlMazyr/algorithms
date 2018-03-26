#include <iostream>

using namespace std;

#define MOVES_NUMBER 4

struct Point {
	int x;
	int y;
};

struct Cell {
	int dist;
	Point prev;
};

char get_char(const Point &p)
{
	char res;
	if (p.x == 0 && p.y == 1) {
		res = 'r';
	} else if (p.x == 0 && p.y == -1) {
		res = 'l';
	} else if (p.x == 1 && p.y == 0) {
		res = 'd';
	} else { // {-1,0}
		res = 'u';
	}
	return res;
}

int main()
{
	int n, m;
	Cell **field;
	char symb, *path;
	Point R, S, *queue;
	int head = 0, tail = 0;
	Point moves[MOVES_NUMBER] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	cin >> n >> m;

	queue = new Point[n*m];
	field = new Cell*[n+2];
	for (int i = 0; i < n+2; ++i) {
		field[i] = new Cell[m+2];
	}

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
				field[adj.x][adj.y].prev = moves[i];
			}
		}
	}

	int &dist = field[S.x][S.y].dist;
	cout << dist << endl;
	Point next = S;
	if (dist != -1) {
		path = new char[dist+1];
		path[dist] = 0;
		for (int i = dist-1; i >= 0; --i) {
			Point &prev = field[next.x][next.y].prev;
			path[i] = get_char(prev);
			next.x += prev.x * (-1);
			next.y += prev.y * (-1);
		}
		cout << path << endl;
		delete[] path;
	}

	for (int i = 0; i < n+2; ++i) {
		delete[] field[i];
	}
	delete[] field;
	delete[] queue;

	return 0;
}
