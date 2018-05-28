#include <iostream>

using namespace std;

int strsz(const char*);

uint32_t find_min_sum(const char *str, uint32_t lc, uint32_t k);
uint32_t calc_min_sum(const char *str, int level, uint32_t lc, uint32_t k);
int calc_min_score(const char *str);

class StringRepetition
{
public:
	StringRepetition(const char* str) : str_pattern(str), start(true)
	{
		str_size = strsz(str);
		coded_str = new int[str_size];
		// encoding
		for (int i = 0; i < str_size; ++i) {
			if (str[i] == '*') {
				coded_str[i] = 0;
			} else {
				coded_str[i] = -1;
			}
		}
	}

	~StringRepetition()
	{
		delete[] coded_str;
	}

	bool get_next_string(char *next_str)
	{
		// TODO: Think how to improve this algorithm
		if (start) {
			decode(next_str);
			start = false;
			return true;
		}
		int *first = coded_str;
		int *last = &coded_str[str_size - 1];
		while (last != first) {
			if (*first == -1) {
				first++;
				continue;
			}
			if (*first < max) {
				(*first)++;
				decode(next_str);
				return true;
			}
			while (last != first) {
				*first = 0;
				first++;
				// skip all 'fixed' elements
				while (*first == -1) {
					if (first == last) {
						start = true;
						return false;
					}
					first++;
				}
				if (*first < max) {
					(*first)++;
					decode(next_str);
					return true;
				}
			}
			break;
		}
		*last = 0;
		// restart sequence
		start = true;
		return false;
	}

	int len() const
	{
		return str_size;
	}

private:
	static const char alphabet[];
	static const int max = 2;

	int *coded_str;
	const char *str_pattern;
	int str_size;
	bool start;

	void decode(char *str)
	{
		for (int i = 0; i < str_size; ++i) {
			if (coded_str[i] == -1) {
				str[i] = str_pattern[i];
			} else {
				str[i] = alphabet[coded_str[i]];
			}
		}
	}
};

const char StringRepetition::alphabet[] = {'S', 'M', 'N'};

int main(int argc, char *argv[])
{
#ifdef MAIN
	int test_cnt, n;
	uint32_t lc, k;
	char line[101] = {0};
	uint32_t min_sum;

	cin >> test_cnt;
	for (int i = 0; i < test_cnt; ++i) {
		cin >> n >> lc >> k;
		cin.getline(line, 101);
		cin.getline(line, 101);
#ifdef DEBUG
		cout << "N = " << n << " LC = " << lc << " K = " << k << endl;
		cout << line << endl;
#endif
		min_sum = find_min_sum(line, lc, k);
		// print answer
		cout << "#" << i + 1 << " " << min_sum << endl;
	}
#endif

#ifdef MINSCORE
	// calc_min_score unit test
	cout << calc_min_score(argv[1]) << endl;
#endif

#ifdef RECCOUNT
	// calculate record count unit test
	cout << calc_min_sum(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << endl;
#endif

#ifdef MINSUM
	// calc_min_sum unit test
	cout << calc_min_sum(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << endl;
#endif
	return 0;
}

uint32_t find_min_sum(const char *str, uint32_t lc, uint32_t k)
{
	StringRepetition str_rep(str);
	char *next_str = new char[str_rep.len()];
	uint32_t min_sum = 0xffffffff;

	// find min sum for each possible string
	while (str_rep.get_next_string(next_str)) {
		uint32_t min_sum_str = 0xffffffff;
		int min_score;
		// calculate min sum for L=1
		min_sum_str = calc_min_sum(next_str, 1, lc, k);

		// calculate min score
		min_score = calc_min_score(next_str);

		if (min_score < 2) {
			// min_sum for L=1 is the only possible
			goto UPDATE_SUM;
		}

		// calculate min_sum for each possible L
		for (int i = 2; i <= min_score; ++i) {
			uint32_t min_sum_l = 0xffffffff;
			min_sum_l = calc_min_sum(next_str, i, lc, k);
			if (min_sum_l < min_sum_str) {
				min_sum_str = min_sum_l;
			}
		}

		// update global min_sum
UPDATE_SUM:
		if (min_sum_str < min_sum) {
			min_sum = min_sum_str;
		}
#ifdef DEBUG
		cout << next_str << " : " << min_sum_str << endl;
#endif
	}
	delete[] next_str;
	return min_sum;
}

int calc_min_score(const char *str)
{
	int min_score = 100;
	int cnt = 0;
	char prev = *str;

	while (*str != '\0') {
		if (*str != prev) {
			if (cnt < min_score) {
				min_score = cnt;
			}
			cnt = 0;
			prev = *str;
		}
		cnt++;
		str++;
	}
	if (cnt < min_score)
		min_score = cnt;
	return min_score;
}

uint32_t calc_min_sum(const char *str, int level, uint32_t lc, uint32_t k)
{
	// calculate record count
	int record_count = 0;
	int cnt = 0;
	char prev = *str;

	while (*str != '\0') {
		if (*str != prev) {
			record_count += cnt / level;
			if (cnt % level)
				record_count += 1;
			cnt = 0;
			prev = *str;
		}
		cnt++;
		str++;
	}
	record_count += cnt / level;
	if (cnt % level)
		record_count += 1;
#ifdef RECCOUNT
	return record_count;
#endif
	// calculate min_sum
	return lc * level + record_count * k;
}

int strsz(const char* str)
{
	int sz = 0;
	while(*str != '\0') {
		str++;
		sz++;
	}
	return sz;
}

