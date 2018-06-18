#include <iostream>

using namespace std;

#define MAX_N	20
#define MAX_ID	1000000
#define IN	1
#define OUT	2

int cabins[MAX_N];
int users[MAX_ID];

void free_cabin(int uid)
{
	cabins[users[uid]] = 0;
	users[uid] = 0;
}

int occupy_cabin(int uid, int N)
{
	int free_id = 0, free_max = 0;
	for (int i = 0; i < N; ++i) {
		if (cabins[i])
			continue;
		int min_dist = N;
		for (int j = 0; j < N; ++j) {
			if (!cabins[j])
				continue;
			int dist = j-i;
			if (dist < 0)
				dist *= -1;
			if (dist < min_dist) {
				min_dist = dist;
			}
		}
		if (min_dist > free_max) {
			free_id = i;
			free_max = min_dist;
		}
	}
	users[uid] = free_id;
	cabins[free_id] = uid;
	return free_id+1;
}

int exec_test(int N, int M)
{
	int ans = 0, i;
	for (i = 0; i < M; ++i) {
		int dr, id;
		cin >> dr >> id;

		if (dr == OUT)
			free_cabin(id);
		else
			ans += occupy_cabin(id, N);
	}
	for (i = 0; i < N; ++i) {
		users[cabins[i]] = 0;
		cabins[i] = 0;
	}
	return ans;
}

int main()
{
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		int N, M;
		cin >> N >> M;
		cout << '#' << i+1 << ' ' << exec_test(N, M) << endl;
	}
	return 0;
}
