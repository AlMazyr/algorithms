#include <iostream>

using namespace std;

#define MAX_N		50
#define MAX_SUM		1000

int in[MAX_N];
int maxv[MAX_N+1][MAX_SUM+1];

int exec_test(int n)
{
	int sum = 0;
	int i, j;

	for (i = 0; i < n; ++i)
		sum += in[i];
	for (j = 0; j < sum+1; ++j)
		maxv[0][j] = 0;
	for (i = 1; i < n+1; ++i) {
		for (j = 0; j < sum+1; ++j)
			maxv[i][j] = maxv[i-1][j];
		for (j = 0; j < sum+1; ++j) {
			int &delta = j;
			int &mx = maxv[i-1][delta];
			if (mx == 0 && delta)
				continue;
			int l, r;
			l = mx;
			r = mx - delta;
			int l1 = l, l2 = l, r1 = r, r2 = r;
			l1 += in[i-1];
			r2 += in[i-1];
			int d1, mn1 = r1, mx1 = l1, d2, mn2 = r2, mx2 = l2;
			if (l1 < r1) {
				mn1 = l1;
				mx1 = r1;
			}
			if (l2 < r2) {
				mn2 = l2;
				mx2 = r2;
			}
			d1 = mx1 - mn1;
			d2 = mx2 - mn2;
			if (mx1 > maxv[i][d1])
				maxv[i][d1] = mx1;
			if (mx2 > maxv[i][d2])
				maxv[i][d2] = mx2;
		}
	}

	return maxv[n][0];
}

int main()
{
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		int n;
		cin >> n;
		for (int j = 0; j < n; ++j)
			cin >> in[j];
		cout << '#' << i+1 << ' ' << exec_test(n) << endl;
	}
	return 0;
}
