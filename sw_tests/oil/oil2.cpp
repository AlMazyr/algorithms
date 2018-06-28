#include <iostream>

using namespace std;

#define MAX_N		25
#define MAX_M		50
#define MAX_CACHE	MAX_M*MAX_M*(MAX_N+1)

int N, M, S;
int delta;
int c[MAX_M*2];
int sums[MAX_M][MAX_M-1];
int cache[MAX_M][MAX_M][MAX_N];
char visited[MAX_M][MAX_M][MAX_N+1];

int find_mx_min(int sh, int len, int n, int max)
{
	if (visited[sh%M][len][n])
		return cache[sh%M][len][n];
	visited[sh%M][len][n] = 1;
	if (n == 1) {
		cache[sh%M][len][n] = sums[sh%M][len-1];
		return sums[sh%M][len-1];
	}
	int mx_min = -1;
	for (int k = 1; k <= len-n+1; ++k) {
		int minl, minr, min;
		minl = sums[sh%M][k-1];
		if (minl > max)
			break;
		if (minl < (max - delta))
			continue;
		minr = find_mx_min(sh+k, len-k, n-1, max);
		if (minr > max || minr < (max - delta))
			continue;
		min = minl < minr ? minl : minr;
		if (min > mx_min)
			mx_min = min;
	}

	cache[sh%M][len][n] = mx_min;
	return mx_min;
}

int exec_test()
{
	int mean = S / N;
	delta = S;
	int i, j;
	if (S % N)
		mean++;
	// calc sums
	for (i = 0; i < M; ++i) {
		sums[i][0] = c[i];
		for (j = 1; j < M-1; ++j)
			sums[i][j] = sums[i][j-1] + c[i+j];
	}
	//iterate over sums
	for (i = 0; i < M; ++i) {
		for (j = 0; j < M-1; ++j) {
			int &max = sums[i][j];
			if (max < mean || max > (mean + delta))
				continue;
			int min = find_mx_min(i+j+1, M-(j+1), N-1, max);
			//drop cache
			long long *ptr = (long long *)visited;
			char *ptr_end = (char*)visited + MAX_CACHE;
			while (ptr != (long long*)ptr_end) {
				*ptr = 0;
				ptr++;
			}
			if (min < 0)
				continue;
			int ldelta = max - min;
			if (ldelta < delta)
				delta = ldelta;
		}
	}

	return delta;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		cin >> N >> M;
		for (int j = 0; j < M; ++j) {
			cin >> c[j];
			c[j+M] = c[j];
			S += c[j];
		}
		cout << '#' << i+1 << ' ' << exec_test() << endl;
		S = 0;
	}
	return 0;
}
