#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

typedef vector<int> my_vector;
uint64_t count_inversions(my_vector& in_array);

int main(int argc, char* argv[])
{

	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0]
			<< " FILE" << endl;
		return -1;
	}
	
	ifstream ifs(argv[1]);
	int integer;
	uint64_t inv_number;
	my_vector int_array;


	// read the input file
	int_array.reserve(100000);
	while (ifs >> integer) {
		int_array.push_back(integer);
	}

	// compute the number of inversions
	inv_number = count_inversions(int_array);

	cout << "Number of inversions - " << inv_number << endl;

	return 0;
}

uint64_t count_inversions(my_vector& in_array)
{
	if (in_array.size() == 1) {
		return 0;
	}

	uint64_t first_n, second_n, split_n = 0;
	my_vector first_half(in_array.begin(), in_array.begin() + in_array.size() / 2);
	my_vector second_half(in_array.begin() + in_array.size() / 2, in_array.end());

	first_n = count_inversions(first_half);
	second_n = count_inversions(second_half);

	int j = 0, k = 0;
	for (auto& it : in_array) {
		if (j >= first_half.size()) {
			it = second_half[k++];
			continue;
		}
		if (k >= second_half.size()) {
			it = first_half[j++];
			continue;
		}
		if (first_half[j] <= second_half[k]) {
			it = first_half[j++];
		} else {
			it = second_half[k++];
			split_n += first_half.size() - j;
		}
	}

	return first_n + second_n + split_n;
}
