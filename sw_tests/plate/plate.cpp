#include <iostream>

using namespace std;

#define MAX_N		50
#define MAX_NUM		1001

typedef unsigned long long	uint64;

int in[MAX_N];
int in2[MAX_N];
int calc[MAX_NUM];

//DEBUG
void print_arr(int *arr, int n)
{
	for (int i = 0; i < n; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int exec_test(int n)
{
	int cnt = 0, i;
	int ans = 0, sum = 0;

	for (i = 0; i < n; ++i)
		calc[in[i]] += 1;
	for (i = 0; i < MAX_NUM; ++i) {
		if (calc[i]) {
			for (int j = 0; j < calc[i]; ++j)
				in[cnt++] = i;
			calc[i] = 0;
		}
		if (cnt == n)
			break;
	}
	//print_arr(in, n);

	for (i = 0; i < n; ++i) {
		if (in[i] == sum) {
			ans = sum;
		} else if (in[i] < sum) {
			uint64 dist = 1ull << i;
			uint64 j, j2;
			for (j = 0; j < dist; ++j) {
				int i2 = 0;
				int l_sum = in[i], r_sum = 0;
				for (int k = 0; k < i; ++k) {
					if ((j >> k) & 1) {
						l_sum += in[k];
					} else {
						in2[i2++] = in[k];
						r_sum += in[k];
					}
				}
				uint64 dist2 = 1ull << i2;
				for (j2 = 1; j2 < dist2; ++j2) {
					r_sum = 0;
					for (int k = 0; k < i2; ++k) {
						if ((j2 >> k) & 1) {
							r_sum += in2[k];
						}
					}
					if (l_sum == r_sum) {
						if (r_sum > ans)
							ans = r_sum;
					} else if (l_sum < r_sum) {
						break;
					}
				}
			}
		}
		sum += in[i];
		//DEBUG:
		//cout << ans << endl;
	}
	return ans;
}

int main()
{
	int tests_number;

	cin >> tests_number;
	for (int i = 0; i < tests_number; ++i) {
		int n;
		cin >> n;
		for (int j = 0; j < n; ++j)
			cin >> in[j];
		cout << '#' << i+1 << ' ' << exec_test(n) << endl;
	}

	return 0;
}
