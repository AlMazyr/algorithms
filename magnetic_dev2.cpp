#include <iostream>

using namespace std;

#define N_MAX 100
#define QUEUE_MAX 1000000

struct TestIn {
	int N;
	int LC;
	int K;
	char str[N_MAX+1];
};

struct Elem {
	char bit_arr[13]; // 100 bits == 12.5 bytes
	char it; // number of bits in the array
	char rep; // number of repetitive bits from the right end
	char min_rep;
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

int calc_min_score(char *str, int N, int LC, int K)
{
	int min_score;
	char *ch;
	Elem e;
	unsigned long long v_cnt = 0; //DEBUG

	// we can calculate score for n=1
	min_score = calc_score(LC, 1, K, N);
	cout << "Min score for n=1 - " << min_score << endl;

	e.it = 1;
	e.rep = 0;
	e.min_rep = N;
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
			v_cnt++; //DEBUG
			if (*ch != '*') {
				if (*ch != prev) {
					if (cur.rep < 2) {
						// invalid elem
						invalid = true;
						break;
					}
					if (cur.rep < cur.min_rep)
						cur.min_rep = cur.rep;
					cur.rep = 1;
				} else {
					cur.rep++;
				}
				if (*ch == '1')
					set_bit(cur.bit_arr, i);
				i++;
				prev = *ch;
			} else { // ch == '*'
				if (cur.rep >= 2 || cur.it == 1) {
					Elem e1 = cur, e2 = cur;
					set_bit(e1.bit_arr, i);
					if (prev == '1') {
						e1.rep++;
						if (cur.it != 1 &&
						    e2.rep < e2.min_rep) {
							e2.min_rep = e2.rep;
						}
						e2.rep = 1;
					} else {
						e2.rep++;
						if (cur.it != 1 &&
						    e1.rep < e1.min_rep) {
							e1.min_rep = e1.rep;
						}
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
		//if (!invalid) {
			//print_elem(cur); //DEBUG
		//}
		if (invalid || cur.rep < 2)
			continue;
		print_elem(cur); //DEBUG
		for (int i = 2; i <= cur.min_rep; ++i) {
			int rec_n = calc_rec_num(cur.bit_arr, cur.it, i);
			int score = calc_score(LC, i, K, rec_n);
			if (score < min_score)
				min_score = score;
		}
	}

	cout << "Vertices count: " << v_cnt << endl;
	return min_score;
}

int exec_test(TestIn &tin)
{
	int &N = tin.N, &LC = tin.LC, &K = tin.K;
	char *ch;
	int str_cnt = 0; //DEBUG

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

	return calc_min_score(tin.str, N, LC, K);
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
