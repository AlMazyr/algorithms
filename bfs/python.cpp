#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;

#define MOVES_NUMBER 4
#define N_MAX 15
#define M_MAX 15
#define PYTHON_LEN_MAX 9

#define MOVE_UP		0b00
#define MOVE_DOWN	0b01
#define MOVE_RIGHT	0b10
#define MOVE_LEFT	0b11

struct Point {
	int x;
	int y;
};

struct Python {
	Point head;
	short tail;
};

int field[N_MAX + 2][M_MAX + 2];
Python queue[N_MAX * M_MAX];
int head, tail;
Point moves[MOVES_NUMBER] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void print_field(int field[][M_MAX + 2], int n, int m)
{
	for (int i = 1; i < n+1; ++i) {
		for (int j = 1; j < m+1; ++j) {
			cout << setw(3) << field[i][j] << " ";
		}
		cout << endl;
	}
}

void print_python_unpacked(Point *p, int len)
{
	cout << '{';
	for (int i = 0; i < len; ++i) {
		cout << '(' << p[i].x << ", " << p[i].y << ')';
	}
	cout << '}' << endl;
}

void print_python_packed(const Python &pp, int p_len)
{
	std::bitset<16> x(pp.tail);
	cout << "{(" << pp.head.x << ',' << pp.head.y << ')'
		<< "<-(" << x << ')' << endl;
}

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
	short tail = p_packed.tail;
	for (int i = 1; i < p_len; ++i) {
		Point move = moves[(tail >> ((p_len-1 - i) * 2)) & 0b11];
		p[i].x = p[i-1].x + move.x;
		p[i].y = p[i-1].y + move.y;
	}
}

bool tail_crash(Point &head, Python &p, int p_len)
{
	Point p_unpacked[PYTHON_LEN_MAX];
	bool res = false;

	python_unpack(p_unpacked, p_len, p);

	for (int i = 1; i < p_len-1; ++i) {
		if (head.x == p_unpacked[i].x && head.y == p_unpacked[i].y) {
			res = true;
			break;
		}
	}
	return res;
}

int main()
{
	int n, m;
	char ch;
	Point C, python[PYTHON_LEN_MAX];
	int p_len = 0;
	Python p_start;

	cin >> n >> m;

	for (int i = 0; i < n+2; ++i) {
		for (int j = 0; j < m+2; ++j) {
			if (i == 0 || i == n+1 || j == 0 || j == m+1) {
				field[i][j] = -2;
				continue;
			}

			cin >> ch;
			if (ch == '.') {
				field[i][j] = -1;
			} else if (ch == '*') {
				field[i][j] = -2;
			} else if (ch >= '1' && ch <= '9') {
				int pos = ch - '0';
				python[pos-1].x = i;
				python[pos-1].y = j;
				if (pos > p_len) {
					p_len = pos;
				}
				if (pos == 1) {
					field[i][j] = 0;
				} else {
					field[i][j] = -1;
				}
			} else { // ch == C
				field[i][j] = -1;
				C.x = i;
				C.y = j;
			}
		}
	}

	python_pack(python, p_len, p_start);
	// debug print
/*
	cout << n << ' ' << m << endl;
	print_field(field, n, m);
	cout << "C = (" << C.x << ", " << C.y << ")" << endl;
	cout << "Python original:" << endl;
	print_python_unpacked(python, p_len);
	cout << "Python packed:" << endl;
	print_python_packed(p_start, p_len);
	cout << "Python unpacked:" << endl;
	python_unpack(python, p_len, p_start);
	print_python_unpacked(python, p_len);
*/
	queue[tail++] = p_start;
	while (head != tail) {
		Python p_c = queue[head++];
		for (int i = 0; i < MOVES_NUMBER; ++i) {
			Python p_n;
			Point &h_n = p_n.head; // head next
			Point &h_c = p_c.head; // head current
			h_n.x = h_c.x + moves[i].x;
			h_n.y = h_c.y + moves[i].y;
			if (field[h_n.x][h_n.y] == -1 && !tail_crash(h_n, p_c, p_len)) {
				short &t_n = p_n.tail; // tail next
				t_n = p_c.tail >> 2;
				Point move_op;
				move_op.x = moves[i].x * (-1);
				move_op.y = moves[i].y * (-1);
				t_n |= get_move_bit(move_op) << ((p_len-2) * 2);
				queue[tail++] = p_n;
				field[h_n.x][h_n.y] = field[h_c.x][h_c.y] + 1;
				/*
				cout << "Next move:" << endl;
				print_field(field, n, m);
				python_unpack(python, p_len, p_n);
				print_python_unpacked(python, p_len);
				print_python_packed(p_n, p_len);
				cout << endl;
				*/
			}
		}
	}

	cout << field[C.x][C.y] << endl;
	return 0;
}
