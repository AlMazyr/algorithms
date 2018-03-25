#include <iostream>

using namespace std;

#define N_MAX 100

int cities[N_MAX][N_MAX];
int queue[N_MAX];
int head, tail;
int visited[N_MAX];
int dist[N_MAX];

int main(int argc, char *argv[])
{
	int N, S, F;
	bool found = false;
	int current, i, res = -1;

	cin >> N >> S >> F;
	if (S == F) {
		return 0;
	}

	for (i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> cities[i][j];
		}
	}

	queue[head++] = S-1;
	visited[S-1] = 1;

	while (head != tail) {
		current = queue[tail++];

		for (i = 0; i < N; ++i) {
			if (cities[current][i] && !visited[i]) {
				dist[i] = dist[current] + 1;
				queue[head++] = i;
				visited[i] = 1;
				if (i == (F-1)) {
					found = true;
					break;
				}
			}
		}
		if (found) {
			res = dist[i];
			break;
		}
	}

	cout << res << endl;

	return 0;
}
