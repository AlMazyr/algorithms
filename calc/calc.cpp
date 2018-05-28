#include <iostream>

using namespace std;

#define MAX_QUEUE 4000000
#define MAX_NUMBER 999

#define OP_PLUS 0
#define OP_MINUS 1
#define OP_MULT 2
#define OP_DIV 3
#define MAX_OP OP_DIV

struct Oper {
	int l;
	int r;
	int sign;
	int r_digits;
	int dist;
};

Oper queue[MAX_QUEUE];
int head, tail;
int visited[MAX_NUMBER+1][MAX_OP+1][MAX_NUMBER+1];

int calc(Oper &o)
{
	int res;
	switch(o.sign) {
		case OP_PLUS:
			res = o.l + o.r;
			break;
		case OP_MINUS:
			res = o.l - o.r;
			break;
		case OP_MULT:
			res = o.l * o.r;
			break;
		case OP_DIV:
			if (!o.r || o.l % o.r)
				res = -1;
			else
				res = o.l / o.r;
			break;
	}
	return res;
}

int exec_test(int N, int S, int M, int W, int *numbers, int *signs)
{
	bool stop = false;
	int res = -1;
	head = 0;
	tail = 0;
	for (int i = 0; i <= MAX_NUMBER; ++i)
		for (int j = 0; j <= MAX_OP; ++j)
			for (int k = 0; k <= MAX_NUMBER; ++k)
				visited[i][j][k] = 0;
	Oper init = {0, 0, OP_PLUS, 0, 1};
	visited[0][OP_PLUS][0] = 1;
	queue[tail++] = init;

	while (head != tail) {
		Oper &cur = queue[head++];
		if (cur.r_digits >= 0 && cur.r_digits <= 2) {
			for (int i = 0; i < N; ++i) {
				Oper adj = cur;
				adj.r = cur.r * 10 + numbers[i];
				int value = calc(adj);
				if (value < 0 || value > MAX_NUMBER)
					continue;
				if (!visited[adj.l][adj.sign][adj.r]) {
					adj.r_digits++;
					adj.dist = cur.dist + 1;
					if (value == W) {
						stop = true;
						res = adj.dist;
						if (!adj.l) res--;
						break;
					}
					if (adj.dist > M)
						continue;
					queue[tail++] = adj;
					visited[adj.l][adj.sign][adj.r] = 1;
				}
			}
		}
		if (stop)
			break;

		if (cur.r_digits >= 1 && cur.r_digits <= 3) {
			for (int i = 0; i < S; ++i) {
				Oper adj = {0, 0, 0, 0, 0};
				adj.l = calc(cur);
				adj.sign = signs[i] - 1;
				if (!visited[adj.l][adj.sign][adj.r]) {
					adj.dist = cur.dist + 1;
					if (adj.dist > M)
						continue;
					queue[tail++] = adj;
					visited[adj.l][adj.sign][adj.r] = 1;
				}
			}
		}
	}

	return res;
}

int main()
{
	int numbers[10], signs[4];
	int N, S, M, W;
	int test_num;

	cin >> test_num;
	for (int i = 0; i < test_num; ++i) {
		int j;
		cin >> N >> S >> M;
		for (j = 0; j < N; ++j)
			cin >> numbers[j];
		for (j = 0; j < S; ++j)
			cin >> signs[j];
		cin >> W;
		cout << '#' << i + 1 << ' '
			<< exec_test(N, S, M, W, numbers, signs) << endl;
	}

	return 0;
}
