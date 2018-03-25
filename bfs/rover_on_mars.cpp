#include <iostream>

using namespace std;

#define MOVES_NUMBER 4

struct Point {
	int x;
	int y;
};

struct Cell {
	int dist;
	int prev;
};

int main(int argc, char *argv[])
{
	int n, m;
	Cell **field;
	char symb;
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
				field[adj.x][adj.y].dist = field[][].dist + 1;
				// update prev
			}

		}
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
