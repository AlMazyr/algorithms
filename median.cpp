#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>

/*
 * Median Maintanence.
 */

using std::cout;
using std::cerr;
using std::endl;
using std::priority_queue;
using std::vector;
using std::less;
using std::greater;
using std::ifstream;

typedef priority_queue<uint16_t, vector<uint16_t>, less<uint16_t>> max_heap;
typedef priority_queue<uint16_t, vector<uint16_t>, greater<uint16_t>> min_heap;

void balance_halfs(max_heap &l_half, min_heap &u_half);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err params! Usage: " << argv[0] << " INFILE" << endl;
		return -1;
	}

	ifstream fi(argv[1]);
	uint32_t median_sum = 0;
	uint16_t num;
	max_heap lower_half;
	min_heap upper_half;

	while (fi >> num) {
		if ((lower_half.size() == 0) || (num < lower_half.top())) {
			lower_half.push(num);
		} else {
			upper_half.push(num);
		}

		// balance halfs if neccessary
		if (abs(lower_half.size() - upper_half.size()) == 2) {
			balance_halfs(lower_half, upper_half);
		}

		// get new median
		if (lower_half.size() < upper_half.size()) {
			median_sum += upper_half.top();
		} else {
			median_sum += lower_half.top();
		}
	}

	cout << "Median sum is " << median_sum << endl;
	return 0;
}

void balance_halfs(max_heap &l_half, min_heap &u_half)
{
	if (l_half.size() > u_half.size()) {
		u_half.push(l_half.top());
		l_half.pop();
	} else {
		l_half.push(u_half.top());
		u_half.pop();
	}
}
