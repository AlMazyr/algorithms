#include <iostream>

using namespace std;

#define MOVES_NUMBER 4
#define N_MAX 15
#define M_MAX 15
#define PYTHON_LEN_MAX 9
#define V_MAX 65536 // 4^8

struct Point {
	short x;
	short y;
};

struct Python {
	Point head;
	unsigned short tail;
};

int field[N_MAX + 2][M_MAX + 2];
Python queue[N_MAX * M_MAX * V_MAX];
int qhead, qtail;
int dist[N_MAX][M_MAX][V_MAX];
Point moves[MOVES_NUMBER] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int get_move_bit(Point &mv)
{
	for (int i = 0; i < MOVES_NUMBER; ++i) {
		if (mv.x == moves[i].x && mv.y == moves[i].y) {
			return i;
		}
	}
	return -1;
}

void python_pack(Point *p, int p_len, Python &p_packed)
{
	p_packed.head = p[0];
	p_packed.tail = 0;
	for (int i = 1; i < p_len; ++i) {
		p_packed.tail <<= 2;
		Point move;
		move.y = p[i].y - p[i-1].y;
		move.x = p[i].x - p[i-1].x;
		p_packed.tail |= get_move_bit(move);
	}
}

void python_unpack(Point *p, int p_len, const Python &p_packed)
{
	p[0] = p_packed.head;
	unsigned short tail = p_packed.tail;
	for (int i = 1; i < p_len; ++i) {
		Point move = moves[(tail >> ((p_len-1 - i) * 2)) & 0b11];
		p[i].x = p[i-1].x + move.x;
		p[i].y = p[i-1].y + move.y;
	}
}

bool tail_crash(const Point &head, Point *p, int p_len)
{
	bool res = false;
	int k = 1;

	if (p_len == 2) {
		k = 0;
	}
	for (int i = 1; i < p_len-k; ++i) {
		if (head.x == p[i].x && head.y == p[i].y) {
			res = true;
			break;
		}
	}
	return res;
}

int main()
{
	int n, m, p_len = 0, res = -1;
	char ch;
	Point C, python[PYTHON_LEN_MAX];
	Python p_start;
	bool found = false;

	cin >> n >> m;

	for (int i = 0; i < N_MAX; ++i) {
		for (int j = 0; j < M_MAX; ++j) {
			for (int k = 0; k < V_MAX; ++k) {
				dist[i][j][k] = -1;
			}
		}
	}
	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			if (i == 0 || i == n+1 || j == 0 || j == m+1) {
				field[i][j] = -2;
				continue;
			}

			cin >> ch;
			if (ch == '*') {
				field[i][j] = -2;
			} else {
				field[i][j] = -1;
				if (ch >= '1' && ch <= '9') {
					int pos = ch - '0';
					python[pos-1].x = i;
					python[pos-1].y = j;
					if (pos > p_len) {
						p_len = pos;
					}
				} else if (ch == 'C') {
					C.x = i;
					C.y = j;
				}
			}
		}
	}

	python_pack(python, p_len, p_start);
	queue[qtail++] = p_start;
	dist[p_start.head.x-1][p_start.head.y-1][p_start.tail] = 0;

	while (qhead != qtail) {
		Python p_c = queue[qhead++];
		python_unpack(python, p_len, p_c);

		for (int i = 0; i < MOVES_NUMBER; ++i) {
			Python p_n;
			Point &h_n = p_n.head;
			Point &h_c = p_c.head;
			h_n.x = h_c.x + moves[i].x;
			h_n.y = h_c.y + moves[i].y;

			if (field[h_n.x][h_n.y] == -2 || tail_crash(h_n, python, p_len)) {
				continue;
			}

			unsigned short &t_n = p_n.tail;
			t_n = p_c.tail >> 2;
			Point move_op;
			move_op.x = moves[i].x * (-1);
			move_op.y = moves[i].y * (-1);
			t_n |= get_move_bit(move_op) << ((p_len-2) * 2);

			if (dist[h_n.x-1][h_n.y-1][t_n] == -1) {
				queue[qtail++] = p_n;
				dist[h_n.x-1][h_n.y-1][t_n] = dist[h_c.x-1][h_c.y-1][p_c.tail] + 1;
				if (h_n.x == C.x && h_n.y == C.y) {
					found = true;
					res = dist[h_n.x-1][h_n.y-1][t_n];
					break;
				}
			}
		}
		if (found) {
			break;
		}
	}

	cout << res << endl;
	return 0;
}
