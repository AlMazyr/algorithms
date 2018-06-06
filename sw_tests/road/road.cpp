#include <iostream>

using namespace std;

#define MAX_N			100
#define MAX_K			10000
#define min(x,y)		((x) < (y) ? (x) : (y))
#define intersect(e, x, K) 	((e) - (x) + (K))

int count[MAX_K+1];

void print_arr(int *arr, int sz)
{
	for (int i = 0; i < sz; ++i)
		cout << arr[i] << ' ';
	cout << endl;
}

void trace_data(int dl, int dr, int el, int er, int xi)
{
	cout << "dl: " << dl << " dr: " << dr << " el: " << el << " er: "
		<< er << " xi: " << xi << endl << endl;
}

void trace_ext_data(int dll, int drl, int dlr, int drr, int ell, int erl)
{
	cout << "dll: " << dll << " drl: " << drl << " dlr: " << dlr << " drr: "
		<< drr << " ell: " << ell << " erl: " << erl << endl;
}

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
	dr = K;
	er = arr[0] + K - 1;
	dl = K;
	el = arr[0];

#ifdef DEBUG
	trace_data(dl, dr, el, er, arr[0]);
#endif
	for (int i = 1; i < N; ++i) {
		int dll, drl, dlr, drr;
		int ell = -1, erl = -1, elr, err;
		int dist = arr[i] - arr[i-1];

		if (dist >= (2*K-1)) {
#ifdef DEBUG
			cout << "delta: " << dist << endl;
			cout << "delta >= 2k-1" << endl;
#endif
			dll = dlr = dl + K;
			drl = drr = dr + K;
			el = arr[i];
			er = arr[i] + K - 1;
		} else if (dist <= K-1) {
#ifdef DEBUG
			cout << "delta: " << dist << endl;
			cout << "delta <= k-1" << endl;
#endif
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
#ifdef DEBUG
			cout << "delta: " << dist << endl;
			cout << "k-1 < delta < 2k-1" << endl;
#endif
			dll = dlr = dl + K;
			drr = dr + K;
			drl = dr + K - intersect(er, arr[i], K);
			el = arr[i];
			er = arr[i] + K - 1;
		}
#ifdef DEBUG
		trace_ext_data(dll, drl, dlr, drr, ell, erl);
#endif
		dl = min(dll, drl);
		dr = min(dlr, drr);
#ifdef DEBUG
		trace_data(dl, dr, el, er, arr[i]);
#endif
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
#ifdef DEBUG
		cout << "N: " << N << " K: " << K << endl;
		cout << "k-1: " << K-1 << " 2k-1: " << 2*K -1 << endl << endl;
#endif
		for (int j = 0; j < N; ++j)
			cin >> arr[j];
#ifdef DEBUG
		cout << "In arr: " << endl;
		print_arr(arr, N);
		cout << "Sorted arr: " << endl;
#endif
		sort(arr, N);
#ifdef DEBUG
		print_arr(arr, N);
#endif
		cout << '#' << i+1 << ' ' << exec_test(N, K, arr) << endl;
	}
	return 0;
}
