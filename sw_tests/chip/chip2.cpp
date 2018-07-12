#include <iostream>

using namespace std;

#define MAX_H		10
#define MAX_W		25
#define MAX_PROF_SZ	1024 //2^10

typedef unsigned int uint_t;

uint_t	column_mask[MAX_W];
uint_t	dist[MAX_PROF_SZ][MAX_PROF_SZ];
uint_t valid[MAX_PROF_SZ][MAX_PROF_SZ];
uint_t	maxi[MAX_W][MAX_PROF_SZ];
uint_t profiles[MAX_PROF_SZ];
uint_t prof_bits[MAX_PROF_SZ];
int p_cnt;

uint_t exec_test(int h, int w)
{
	uint_t ans = 0;
	uint_t dist_sz = 1 << h;

	for (int i = 1; i < w; ++i) {
		//iterate over correct profiles
		for (int j = 0; j < p_cnt; ++j) {
			if (profiles[j] >= dist_sz)
				continue; //skip bigger profile
			uint_t p2 = profiles[j];
			p2 &= ~column_mask[i];
			for (int k = 0; k < p_cnt; ++k) {
				if (profiles[k] >= dist_sz)
					continue; // skip bigger profile
				uint_t p1 = profiles[k];
				uint_t p1_d = p1 | column_mask[i-1];
				p1 &= ~column_mask[i-1];
				uint_t m = (maxi[i-1][p1] + dist[p1_d][p2]) *
						valid[p1_d][p2];
				if (m > maxi[i][p2])
					maxi[i][p2] = m;
			}
		}
		//cleaning
		for (uint_t j = 0; j < dist_sz; ++j)
			maxi[i-1][j] = 0;
	}
	// answer
	for (uint_t p1 = 0; p1 < dist_sz; ++p1) {
		uint_t m = (maxi[w-1][p1] + dist[p1][0]) * valid[p1][0];
		if (m > ans)
			ans = m;
	}
	//cleaning
	for (uint_t j = 0; j < dist_sz; ++j)
		maxi[w-1][j] = 0;
	return ans;
}

int main()
{
	int h, w;
	int tests_num;

	// generate valid profiles
	for (uint_t p = 0; p < MAX_PROF_SZ; ++p) {
		int prev = 0;
		int bit_num = 0;
		bool invalid = false;
		for (int j = 0; j <= MAX_H; ++j) {
			int bit = (p >> j) & 1;
			if (bit) {
				bit_num++;
			} else if (prev && (bit_num % 2)) {
				invalid = true;
				break;
			}
			prev = bit;
		}
		if (invalid)
			continue;
		profiles[p_cnt] = p;
		prof_bits[p_cnt++] = bit_num;
	}

	// calculate dist table
	for (uint_t p1 = 0; p1 < MAX_PROF_SZ; ++p1) {
		//iterate over valid profiles
		for (int i = 0; i < p_cnt; ++i) {
			uint_t &p2 = profiles[i];
			uint_t &p2_bits = prof_bits[i];
			if ((~p1 & p2) == p2) {
				dist[p1][p2] = p2_bits / 2;
				valid[p1][p2] = 1;
			}
		}
	}

	cin >> tests_num;
	int i = 0, j;
	for (; i < tests_num; ++i) {
		cin >> h >> w;
		for (j = 0; j < MAX_W; ++j)
			column_mask[j] = 0;
		for (j = 0; j < h; ++j) {
			for (int k = 0; k < w; ++k) {
				int bit;
				cin >> bit;
				column_mask[k] |= bit << j;
			}
		}
		cout << '#' << i+1 << ' ' << exec_test(h, w) << endl;
	}
	return 0;
}
