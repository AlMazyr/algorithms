#include <iostream>

using namespace std;

#define MAX_N			100
#define MAX_K			10000
#define min(x,y)		((x) < (y) ? (x) : (y))
#define intersect(e, x, K) 	((e) - (x) + (K))

int count[MAX_K+1];

void sort(int *arr, int sz)
{
	int j = 0, i;
	for (i = 0; i < sz; ++i)
		count[arr[i]] = 1;
	for (i = 0; i < MAX_K+1; ++i) {
		if (count[i]) {
			arr[j++] = i;
			count[i] = 0;
			if (j == sz)
				break;
		}
	}
}

int exec_test(int N, int K, int *arr)
{
	int dl, dr, el, er; // dist left/right, end left/right

	// first point init
	dr = dl = K;
	er = arr[0] + K - 1;
	el = arr[0];

	for (int i = 1; i < N; ++i) {
		int dll, drl, dlr, drr;
		int ell = -1, erl = -1, elr, err;
		int dist = arr[i] - arr[i-1];

		if (dist >= (2*K-1)) {
			dll = dlr = dl + K;
			drl = drr = dr + K;
			el = arr[i];
			er = arr[i] + K - 1;
		} else if (dist <= K-1) {
			if (arr[i] > er) {
				drr = dr + K;
				err = arr[i] + K - 1;
				drl = dr + K - intersect(er, arr[i], K);
				erl = arr[i];
			} else {
				drr = drl = dr;
				erl = err = er;
			}
			if (arr[i] > el) {
				dll = dl + K - intersect(el, arr[i], K);
				dlr = dl + K;
				ell = arr[i];
				elr = arr[i] + K - 1;
			} else {
				dll = dlr = dl;
				ell = elr = el;
			}
			er = drr < dlr ? err : elr;
			el = dll < drl ? ell : erl;
		} else { // k-1 < dist < 2k-1
			dll = dlr = dl + K;
			drr = dr + K;
			drl = dr + K - intersect(er, arr[i], K);
			el = arr[i];
			er = arr[i] + K - 1;
		}
		dl = min(dll, drl);
		dr = min(dlr, drr);
	}
	return dl;
}

int main()
{
	int tests_number, N, K;
	int arr[MAX_N];

	cin >> tests_number;
	for (int i = 0; i < tests_number; ++i) {
		cin >> N >> K;
		for (int j = 0; j < N; ++j)
			cin >> arr[j];
		sort(arr, N);
		cout << '#' << i+1 << ' ' << exec_test(N, K, arr) << endl;
	}
	return 0;
}
