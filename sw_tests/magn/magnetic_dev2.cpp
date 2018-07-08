#include <iostream>

using namespace std;

#define N_MAX 100
#define QUEUE_MAX 10000000

#define extract_bit(bit_arr,idx) ((bit_arr[(idx)/8] >> (idx)%8) & 1)
#define set_bit(bit_arr,idx) (bit_arr[(idx)/8] |= 1 << ((idx)%8))

typedef unsigned char uint8;

struct Elem {
	uint8 bit_arr[13]; // 100 bits == 12.5 bytes
	uint8 it; // number of bits in the array
	uint8 rep; // number of repetitive bits from the right end
	uint8 min_rep;
	uint8 recs; // number of recs for min_rep
};

unsigned long long v_cnt = 0; //DEBUG
int head, tail;
Elem queue[QUEUE_MAX];
int used[N_MAX][N_MAX][N_MAX][2]; //[min_rep][rep][bits][last_bit]

int calc_rec_num(uint8 *bit_arr, int idx, int n)
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
void print_bitarr(uint8 *ba, int it)
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

int is_val(Elem &el, int min_sc, int LC, int K)
{
	if (el.rep < el.min_rep)
		return 1;
	int score = calc_score(LC, el.min_rep, K, el.recs);
	return score > min_sc ? 0 : 1;
}

uint8 bitarr_r[5] = {0b11110000, 0b11000000, 0b11};

int exec_test(int N, int LC, int K, char *str)
{
	char *ch;
	int str_cnt = 0; //DEBUG
	int min_score;
	Elem e;

	for (int i = 0; i < N_MAX; ++i) {
		for (int j = 0; j < N_MAX; ++j) {
			for (int k = 0; k < N_MAX; ++k) {
				used[i][j][k][0] = 0;
				used[i][j][k][1] = 0;
			}
		}
	}
	v_cnt = 0;
	int i = 0;
	char prev = str[0];
	for (ch = str; *ch; ch++) {
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

	// we can calculate score for n=1
	min_score = calc_score(LC, 1, K, N);
	//cout << "Min score for n=1 : " << min_score << endl;

	head = 0;
	tail = 0;
	e.it = 1;
	e.rep = 0;
	e.min_rep = N;
	e.recs = 0;
	for (int i = 0; i < 13; ++i)
		e.bit_arr[i] = 0;
	if (str[0] == '1')
		e.bit_arr[0] |= 1;
	queue[tail++] = e;
	while (tail != head) {
		Elem &cur = queue[head++];
		bool invalid = false;

		// iterate over string until end or fork
		int i = cur.it;
		char prev = extract_bit(cur.bit_arr, i-1) + '0';
		for (ch = &str[i-1]; *ch; ch++) {
			uint8 bit = extract_bit(cur.bit_arr, i-1);
			v_cnt++; //DEBUG
			if (*ch != '*') {
				if (*ch != prev) {
					if (cur.rep < 2) {
						// invalid elem
						invalid = true;
						break;
					}
					if (cur.rep < cur.min_rep) {
						cur.min_rep = cur.rep;
						cur.recs = calc_rec_num(cur.bit_arr, i,
						cur.min_rep);
					} else {
						cur.recs += cur.rep / cur.min_rep;
						if (cur.rep % cur.min_rep)
							cur.recs += 1;
					}
					// check used array
					if (used[cur.min_rep][cur.recs][i][bit]) {
						invalid = true;
						break;
					}
					used[cur.min_rep][cur.recs][i][bit] = 1;
					cur.rep = 1;
				} else {
					cur.rep++;
				}
				if (*ch == '1')
					set_bit(cur.bit_arr, i);
				i++;
				prev = *ch;
			} else { // ch == '*'
				bool e1_bad = false, e2_bad = false;
				if (cur.rep >= 2 || cur.it == 1) {
					Elem e1 = cur, e2 = cur;
					set_bit(e1.bit_arr, i);
					if (prev == '1') {
						e1.rep++;
						if (cur.it != 1) {
							if (e2.rep < e2.min_rep) {
								e2.min_rep = e2.rep;
								e2.recs = calc_rec_num(e2.bit_arr, i, e2.min_rep);
							} else {
								e2.recs += e2.rep / e2.min_rep;
								if (e2.rep % e2.min_rep)
									e2.recs += 1;
							}
							if (used[e2.min_rep][e2.recs][i][bit])
								e2_bad = true;
							else
								used[e2.min_rep][e2.recs][i][bit] = 1;
						}
						e2.rep = 1;
					} else {
						e2.rep++;
						if (cur.it != 1) {
							if (e1.rep < e1.min_rep) {
								e1.min_rep = e1.rep;
								e1.recs = calc_rec_num(e1.bit_arr, i, e1.min_rep);
							} else {
								e1.recs += e1.rep / e1.min_rep;
								if (e1.rep % e1.min_rep)
									e1.recs += 1;
							}
							if (used[e1.min_rep][e1.recs][i][bit])
								e1_bad = true;
							else
								used[e1.min_rep][e1.recs][i][bit] = 1;
						
						}
						e1.rep = 1;
					}
					i++;
					e1.it = i;
					e2.it = i;
					if (!e1_bad)
						queue[tail++] = e1;
					if (!e2_bad)
						queue[tail++] = e2;
					//DEBUG
					/*
					if (tail >= QUEUE_MAX) {
						cout << "Queue overflow!" << endl;
						cout << tail << endl;
					}
					*/
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
			cur.it = i;
			/*
			if (!is_val(cur, min_score, LC, K)) {
				invalid = true;
				break;
			}
			*/
		}
		if (invalid || cur.rep < 2)
			continue;
		if (cur.rep < cur.min_rep) {
			cur.min_rep = cur.rep;
			cur.recs = calc_rec_num(cur.bit_arr, cur.it, cur.min_rep);
		} else {
			cur.recs += cur.rep / cur.min_rep;
			if (cur.rep % cur.min_rep)
				cur.recs += 1;
		}
		//cout << "n:" << (int)cur.min_rep << " r:" << (int)cur.recs << endl;
		//cout << "rep:" << (int)cur.rep << endl;
		/*
		if (cur.min_rep == 4) {
			print_bitarr(cur.bit_arr, cur.it);
		}*/

		for (int i = 2; i <= cur.min_rep; ++i) {
			cur.recs = calc_rec_num(cur.bit_arr, cur.it, i);
			int score = calc_score(LC, i, K, cur.recs);
			if (score < min_score) {
				min_score = score;
			}
		}
		/*
		int score = calc_score(LC, cur.min_rep, K, cur.recs);
		if (score < min_score) {
			min_score = score;
			//DEBUG
			cout << "min_score: " << min_score << endl;
			cout << "n:" << (int)cur.min_rep << " r:" << (int)cur.recs << endl;
			cout << "rep:" << (int)cur.rep << endl;
			print_bitarr(cur.bit_arr, cur.it);
		}
		*/
	}

	//DEBUG
	//cout << "tail: " << tail << " head: " << head << " v_cnt: " << v_cnt
	//	<< endl;
	return min_score;
}

int main()
{
	int test_total;
	int N, LC, K;
	char str[N_MAX+1];
	cin >> test_total;

	cout << "REF bitarr:" << endl;
	print_bitarr(bitarr_r, 22);
	for (int i = 0; i < test_total; ++i) {
		cin >> N >> LC >> K >> str;
		cout << '#' << i+1 << ' ' << exec_test(N, LC, K, str) << endl;
	}

	return 0;
}
