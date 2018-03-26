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
	char res = 'f';
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

int main(int argc, char *argv[])
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

	queue[head++] = R;
	while (head != tail) {
		Point current = queue[tail++];

		for (int i = 0; i < MOVES_NUMBER; ++i) {
			Point adj;
			adj.x = current.x + moves[i].x;
			adj.y = current.y + moves[i].y;
			if (field[adj.x][adj.y].dist == -1) {
				queue[head++] = adj;
				field[adj.x][adj.y].dist = field[current.x][current.x].dist + 1;
				field[adj.x][adj.y].prev = moves[i];
			}
			/*
			if (adj.x == S.x && adj.y == S.y) {
				found = true;
				res = field[adj.x][adj.y].dist;
				break;
			}
			*/
		}
	}

	int &dist = field[S.x][S.y].dist;
	cout << dist << endl;
	Point next = S;
	if (dist != -1) {
		path = new char[dist+1];
		path[dist] = 0;
		for (int i = dist-1; i >= 0; --i) {
			path[i] = get_char(field[next.x][next.y].prev);
			next.x += field[next.x][next.y].prev.x * (-1);
			next.y += field[next.x][next.y].prev.y * (-1);
		}
		cout << (const char*)path << endl;
		delete[] path;
	}


	// debug
/*
	cout << n << " " << m << endl;
	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			cout << field[i][j] << " ";
		}
		cout << endl;
	}
	cout << "R.x=" << R.x << " R.y=" << R.y << endl;
	cout << "S.x=" << S.x << " S.y=" << S.y << endl;
*/

	for (int i = 0; i < n+2; ++i) {
		delete[] field[i];
	}
	delete[] field;
	delete[] queue;

	return 0;
}
