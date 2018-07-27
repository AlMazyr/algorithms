#include <iostream>

#define MAX_N	100
#define calc_score(lc, l, k, r)		((lc) * (l) + (k) * (r))
#define upper(l, r)			(((l) + (r) - 1) / (r))

using namespace std;

int N, LC, K;
char str[MAX_N];
int d[MAX_N][MAX_N];
int sm[MAX_N][MAX_N+1];

void print_d()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			cout << d[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int same(int st, int len)
{
	if (sm[st][len])
		return sm[st][len] - 1;
	int s = 0;
	for (int i = st; i < st + len; ++i) {
		if (str[i] == 'S')
			s |= 1;
		else if (str[i] == 'N')
			s |= 2;
		else if (str[i] == 'M')
			s |= 4;
	}
	sm[st][len] = !((s-1) & s) + 1;
	return sm[st][len] - 1;
}

int exec_test()
{
	int min_score = calc_score(LC, 1, K, N);

	// L - window
	// l - len of peace
	// i - start of peace
	for (int L = 2; L <= N; ++L) {
		// prepare d[][]
		for (int i = 0; i < N; ++i)
			for (int j = i; j < N; ++j)
				d[i][j] = N;
		for (int l = L; l <= N; ++l) {
			for (int i = 0; i <= N-l; ++i) {
				if (same(i, l)) {
					d[i][i+l-1] = upper(l, L);
				} else {
					for (int k = L; k <= l-L; ++k) {
						int m = (d[i][i+k-1] + d[i+k][i+l-1]) *
							!!d[i][i+k-1] *
							!!d[i+k][i+l-1];
						if (!m)
							continue;
						if (m < d[i][i+l-1])
							d[i][i+l-1] = m;
					}
					if (d[i][i+l-1] == N)
						d[i][i+l-1] = 0;
				}
			}
		}
		print_d();
		if (!d[0][N-1])
			break;
		int score = calc_score(LC, L, K, d[0][N-1]);
		if (score < min_score)
			min_score = score;
	}
	//clean sm
	for (int i = 0; i < N; ++i) {
		for (int j = 1; j <= N-i; ++j)
			sm[i][j] = 0;
	}
	return min_score;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		cin >> N >> LC >> K >> str;
		cout << '#' << i+1 << ' ' << exec_test() << endl;
	}
	return 0;
}
