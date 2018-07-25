#include <iostream>

#define MAX_N	100
#define MAX_K	10000

using namespace std;

int N, K;
int asph[MAX_N];
int count[MAX_K+1];
int dist[MAX_N][MAX_K];

void print_dist()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j)
			cout << dist[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int exec_test()
{
	int i, j;
	for (i = 0; i < N; ++i)
		count[asph[i]] = 1;
	j = 0;
	for (i = 0; i <= MAX_K; ++i) {
		if (count[i]) {
			asph[j++] = i;
			count[i] = 0;
		}
		if (j == N)
			break;
	}
	// init first point
	dist[0][K-1] = K;

	for (i = 0; i < N-1; ++i) {
		for (j = 0; j < K; ++j) {
			if (!dist[i][j])
				continue;
			int e = asph[i] + j;
			int jl, jr, dl, dr;
			if (e >= asph[i+1]) {
				// next peace is overlapped
				jr = e - asph[i+1];
				int &d_old = dist[i+1][jr], &d_new = dist[i][j];
				if (!d_old || d_new < d_old)
					d_old = d_new;
				dist[i][j] = 0;
				continue;
			}
			jl = 0;
			int e2 = asph[i+1] - K + 1;
			if (e2 <= e)
				dl = dist[i][j] + asph[i+1] - e;
			else
				dl = dist[i][j] + K;
			jr = K-1;
			dr = dist[i][j] + K;
			int &dl_old = dist[i+1][jl], &dr_old = dist[i+1][jr];
			if (!dl_old || dl < dl_old)
				dl_old = dl;
			if (!dr_old || dr < dr_old)
				dr_old = dr;
			dist[i][j] = 0;
		}
	}
	//getting the answer
	int ans = MAX_K + 1;
	for (j = 0; j < K; ++j) {
		if (dist[N-1][j] != 0 && dist[N-1][j] < ans)
			ans = dist[N-1][j];
		dist[N-1][j] = 0;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		cin >> N >> K;
		for (int j = 0; j < N; ++j)
			cin >> asph[j];
		cout << '#' << i+1 << ' ' << exec_test() << endl;
	}
	return 0;
}
