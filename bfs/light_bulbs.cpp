#include <iostream>
#include <bitset>

using namespace std;

#define V_MAX 1048576 // 2^20
#define M_MAX 100

#define BITSET(x,y) x |= (1 << y)

int queue[V_MAX], head, tail;
int visited[V_MAX];
int dist[V_MAX];
int switches[M_MAX];

void read_bitstring(istream &in, int &value, int n)
{
	int bit;
	for (int i = n-1; i >= 0; --i) {
		in >> bit;
		if (bit) {
			BITSET(value, i);
		}
	}
}

int main(int argc, char *argv[])
{
	int n, m, start = 0, finish = 0, res = -1;
	bool found = false;

	cin >> n >> m;

	read_bitstring(cin, start, n);
	if (start == finish) {
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < m; ++i) {
		read_bitstring(cin, switches[i], n);
	}

	queue[head++] = start;
	visited[start] = 1;

	while (head != tail) {
		int current = queue[tail++];

		for (int i = 0; i < M_MAX; ++i) {
			int adj = current ^ switches[i];
			if (!visited[adj]) {
				dist[adj] = dist[current] + 1;
				visited[adj] = 1;
				queue[head++] = adj;
			}
			if (adj == finish) {
				found = true;
				res = dist[adj];
				break;
			}
		}
		if (found) {
			break;
		}
	}

	cout << res << endl;
	return 0;
}
