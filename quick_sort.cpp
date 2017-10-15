#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<int> my_vector;

int quick_sort_int(int *in_array, int size);
int get_pivot(int *in_array, int size);
int get_median(int a, int b, int c);

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " <FILE>"
			<< endl;
		return -1;
	}

	ifstream fi(argv[1]);
	my_vector in_arr;
	in_arr.reserve(10000);
	int num;
	uint64_t number_of_comp;

	// read the input file
	while (fi >> num) {
		in_arr.push_back(num);
	}

	// sorting
	number_of_comp = quick_sort_int(&in_arr[0], in_arr.size());

	cout << "Number of comparisons is " << number_of_comp
		<< endl;
	return 0;
}

// implementation of quicksort algorithm with median of three values strategy
// returns number of comparisons
int quick_sort_int(int *in_array, int size)
{
	if (size <= 1) {
		return 0; // base case
	}

	uint64_t res = size - 1;

	// find pivot element
	int i_pivot = get_pivot(in_array, size);
	swap(in_array[0], in_array[i_pivot]);
	int &pivot = in_array[0];
	
	// partitioning around pivot
	int i = 1, j = 1;
	for (j = 1; j < size; ++j) {
		if (in_array[j] < pivot) {
			swap(in_array[j], in_array[i++]);
		}
	}

	// move pivot in correct position
	swap(pivot, in_array[i - 1]);

	// recursive calls
	int sub1_size = i - 1, sub2_size = size - i;
	if (sub1_size > 0)
		res += quick_sort_int(in_array, sub1_size);
	if (sub2_size > 0)
		res += quick_sort_int(&in_array[i], sub2_size);
	return res;
}

// returns index of the pivot element
int get_pivot(int *in_array, int size)
{
	int first = 0, last = size - 1, middle = size / 2 - 1 + size % 2;
	int res = 0;
	int median = get_median(in_array[first], in_array[last],
			in_array[middle]);
	if (median == in_array[first])
		res = first;
	else if (median == in_array[last])
		res = last;
	else
		res = middle;
	return res;
}

// returns middle (median) of three numbers
int get_median(int a, int b, int c)
{
	return a > b ? (c > a ? a : (b > c ? b : c))
			: (c > b ? b : (a > c ? a : c));
}
