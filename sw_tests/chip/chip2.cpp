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

uint_t exec_test(int h, int w)
{
	uint_t ans = 0;
	uint_t dist_sz = 1 << h;

	for (int i = 1; i < w; ++i) {
		for (uint_t j = 0; j < dist_sz; ++j) {
			uint_t p2 = j & ~column_mask[i];
			for (uint_t k = 0; k < dist_sz; ++k) {
				uint_t p1 = k & ~column_mask[i-1];
				uint_t p1_d = k | column_mask[i-1];
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

	// calculate dist table (2^2h * h)
	for (uint_t p1 = 0; p1 < MAX_PROF_SZ; ++p1) {
		for (uint_t p2 = 0; p2 < MAX_PROF_SZ; ++p2) {
			int p2_bits = 0;
			int prev = 0;
			bool invalid_p2 = false;
			// calculate number of bits in p2
			for (int j = 0; j <= MAX_H; ++j) {
				int bit = (p2 >> j) & 1;
				if (bit) {
					p2_bits++;
				} else if (prev) {
					if (p2_bits % 2) {
						invalid_p2 = true;
						break;
					}
				}
				prev = bit;
			}
			if (invalid_p2)
				continue;
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
