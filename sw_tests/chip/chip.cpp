#include <iostream>

using namespace std;

#define HEIGHT_MAX	11
#define WIDTH_MAX	26

static int array_sample[HEIGHT_MAX][WIDTH_MAX] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static int array_current[HEIGHT_MAX][WIDTH_MAX] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

#ifdef DEBUG
void array_print(int array[][WIDTH_MAX], int h, int w)
{
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}
#endif

void array_read(int h, int w)
{
	int value;
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			cin >> value;
			array_sample[i][j] = value;
			array_current[i][j] = value;
		}
	}
}

void array_clean(int h, int w)
{
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			array_sample[i][j] = 1;
			array_current[i][j] = 1;
		}
	}
}

void restore_current(int h, int w)
{
	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			array_current[i][j] = array_sample[i][j];
		}
	}
}

int main(int argc, char *argv[])
{
	int tests_number;
	int height, width;
	int squares_total_max;

	cin >> tests_number;
	for (int k = 0; k < tests_number; ++k) {
		int squares_total_max = 0;
		// read input data
		cin >> height >> width;
		array_read(height, width);
#ifdef DEBUG
		array_print(array_sample, height, width);
#endif
		// left to right
		int sq1 = 0, sq2 = 0;
		for (int i = 1; i <= height; ++i) {
			for (int j = 1; j <= width; ++j) {
				if (array_current[i][j] == 0) {
					array_current[i][j] = 1;
					// check neighboors
					if (array_current[i+1][j] != 1 && array_current[i][j+1] != 1
							&& array_current[i+1][j+1] != 1) {
						// place new sqare
						array_current[i+1][j] = 1;
						array_current[i+1][j+1] = 1;
						array_current[i][j+1] = 1;
						sq1++;
					}
				}
			}
		}
		restore_current(height, width);
		// right to left
		for (int i = 1; i <= height; ++i) {
			for (int j = width; j >= 1; --j) {
				if (array_current[i][j] == 0) {
					array_current[i][j] = 1;
					// check neighboors
					if (array_current[i+1][j] != 1 && array_current[i][j-1] != 1
							&& array_current[i+1][j-1] != 1) {
						// place new sqare
						array_current[i+1][j] = 1;
						array_current[i+1][j-1] = 1;
						array_current[i][j-1] = 1;
						sq2++;
					}
				}
			}
		}

		squares_total_max = sq1 > sq2 ? sq1 : sq2;
		array_clean(height, width);
		cout << "#" << k + 1 << " " << squares_total_max << endl;
	}
	return 0;
}
