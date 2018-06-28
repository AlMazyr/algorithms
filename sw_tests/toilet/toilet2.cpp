#include <iostream>

using namespace std;

#define MAX_N	20
#define MAX_ID	1000000
#define IN	1
#define OUT	2

char cabins[MAX_N+1];
int users[MAX_ID];

int occupy_cabin(int uid, int N)
{
	int hole_len = 0, hole_st = 0, hole_end = 0, hole_sc = 0, score;
	int prev = cabins[0];
	int cnt = 0, start = 0;
	int pos;
	for (int i = 0; i < N+1; ++i) {
		if (cabins[i]) {
			if (!prev) {
				if (start > 0 && (start + cnt - 1) < N-1)
					score = (cnt + 1) / 2;
				else
					score = cnt;
				if (score > hole_sc) {
					hole_len = cnt;
					hole_st = start;
					hole_sc = score;
				}
				cnt = 0;
			}
		} else {
			if (prev)
				start = i;
			cnt++;
		}
		prev = cabins[i];
	}
	hole_end = hole_st + hole_len - 1;
	if (hole_st == 0)
		pos = 0;
	else if (hole_end == N-1)
		pos = N-1;
	else
		pos = hole_st + ((hole_len - 1) / 2);
	users[uid] = pos;
	cabins[pos] = 1;

	return pos+1;
}

int exec_test(int N, int M)
{
	int ans = 0, i;
	cabins[N] = 1;
	for (i = 0; i < M; ++i) {
		int dr, id;
		cin >> dr >> id;

		if (dr == OUT) {
			cabins[users[id]] = 0;
			users[id] = 0;
		} else {
			ans += occupy_cabin(id, N);
		}
	}
	for (i = 0; i < N; ++i)
		cabins[i] = 0;
	cabins[N] = 0;
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		int N, M;
		cin >> N >> M;
		cout << '#' << i+1 << ' ' << exec_test(N, M) << endl;
	}
	return 0;
}
