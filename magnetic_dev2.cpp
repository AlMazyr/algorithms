#include <iostream>

using namespace std;

#define N_MAX 100
#define QUEUE_MAX 1000000

struct TestIn {
	int N;
	int LC;
	int K;
	char str[N_MAX];
};

struct Elem {
	char bit_arr[13]; // 100 bits == 12.5 bytes
	char it; // number of bits in the array
	char rep; // number of repetitive bits from the right end
};

Elem queue[QUEUE_MAX];
int head, tail;

int extract_bit(char *bit_arr, int idx)
{
	return (bit_arr[idx/8] >> idx%8) & 1;
}

void set_bit(char *bit_arr, int idx)
{
	bit_arr[idx/8] |= 1 << (idx%8);
}

int calc_rec_num(char *bit_arr, int idx, int n)
{
	int recs = 0, rep = 0;
	int prev = extract_bit(bit_arr, 0);
	for (int i = 1; i < idx; ++i) {
		int cur = extract_bit(bit_arr, i);
		if (cur != prev) {
			recs += rep / n;
			if (rep % n)
				recs++;
			rep = 1;
			prev = cur;
		} else {
			rep++;
		}
	}
	recs += rep / n;
	if (rep % n)
		recs++;
	return recs;
}

int calc_score(int lc, int n, int k, int recs)
{
	return lc * n + k * recs;
}

//DEBUG
void print_bitarr(char *ba, int it)
{
	for (int i = 0; i < it; ++i) {
		cout << extract_bit(ba, i);
	}
	cout << endl;
}
void print_elem(Elem &el)
{
	print_bitarr(el.bit_arr, el.it);
	cout << (int)el.it << ' ' << (int)el.rep << endl << endl;
}

int calc_min_recs(int n, char *str, int N)
{
	int rec_min = N;
	char *ch;
	Elem e;
	e.it = 1;
	e.rep = 0;
	for (int i = 0; i < 13; ++i)
		e.bit_arr[i] = 0;
	if (str[0] == '1')
		e.bit_arr[0] |= 1;
	queue[tail] = e;
	tail = (tail + 1) % QUEUE_MAX;
	while (tail != head) {
		Elem &cur = queue[head];
		head = (head + 1) % QUEUE_MAX;
		bool invalid = false;

		// iterate over string until end or fork
		int i = cur.it;
		char prev = extract_bit(cur.bit_arr, i-1) + '0';
		for (ch = &str[i-1]; *ch; ch++) {
			if (*ch != '*') {
				if (*ch != prev) {
					if (cur.rep < n) {
						// invalid elem
						invalid = true;
						break;
					}
					cur.rep = 1;
				} else {
					cur.rep++;
				}
				if (*ch == '1')
					set_bit(cur.bit_arr, i);
				i++;
				prev = *ch;
			} else { // ch == '*'
				if (cur.rep >= n || cur.it == 1) {
					Elem e1 = cur, e2 = cur;
					set_bit(e1.bit_arr, i);
					if (prev == '1') {
						e1.rep++;
						e2.rep = 1;
					} else {
						e2.rep++;
						e1.rep = 1;
					}
					i++;
					e1.it = i;
					e2.it = i;
					queue[tail] = e1;
					tail = (tail + 1) % QUEUE_MAX;
					queue[tail] = e2;
					tail = (tail + 1) % QUEUE_MAX;
					invalid = true;
					break;
				} else {
					// duplicate prev
					cur.rep++;
					if (prev == '1') {
						set_bit(cur.bit_arr, i);
					}
					i++;
				}
			}
		}
		if (invalid)
			continue;
		// DEBUG
//		if (n == 2) {
//			print_elem(cur);
//		}
		if (cur.rep >= n) {
			//DEBUG
			int rec_n = calc_rec_num(cur.bit_arr, cur.it, n);
//			if (n == 2) {
//				cout << "rec num: " << rec_n << endl;
//			}
			if (rec_n < rec_min)
				rec_min = rec_n;
		}
	}

	return rec_min;
}

int exec_test(TestIn &tin)
{
	int &N = tin.N, &LC = tin.LC, &K = tin.K;
	char *ch;
	int recs, score, min_score, n;
	int str_cnt = 0; //DEBUG

//	cout << N << LC << K << endl << str << endl;

	// change to numbers
	int i = 0;
	char prev = tin.str[0];
	for (ch = tin.str; *ch; ch++) {
		str_cnt++;
		if (*ch == '*') {
			continue;
		} else {
			if (*ch != prev) {
				i ^= 1;
				prev = *ch;
			}
			*ch = '0' + i;
		}
	}
	//cout << tin.str << ' ' << str_cnt << endl;

	n = 1;
	min_score = calc_score(LC, n, K, N);
	//cout << "n = 1, mscore = " << min_score << endl;
	// calc min recs for all n from 2 to N
	for (n = 2; n <= N; ++n) {
		recs = calc_min_recs(n, tin.str, N);
//		if (recs == N)
//			continue;
		score = calc_score(LC, n, K, recs);
//		cout << "n = " << n << " recs = " << recs << " sc = "
//			<< score << endl;
		if (score < min_score)
			min_score = score;
	}

	return min_score;
}

int main()
{
	int test_total;
	TestIn *tests;

	cin >> test_total;
	tests = new TestIn[test_total];

	// read input data
	for (int i = 0; i < test_total; ++i)
		cin >> tests[i].N >> tests[i].LC >> tests[i].K >> tests[i].str;

	// evaluate tests
	for (int i = 0; i < test_total; ++i)
		cout << '#' << i+1 << ' ' << exec_test(tests[i]) << endl;
	return 0;
}
