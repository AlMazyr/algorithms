#include <iostream>

using namespace std;

#define N_MAX 1000000

int *adj_list[N_MAX];

struct Edge {
	int v1;
	int v2;
};

int main()
{
	int N;

	cin >> N;
	cout << N << endl;;

	while (1) {
		int v1, v2;
		cin >> v1 >> v2;
		if (cin.eof())
			break;
		cout << v1 << " " << v2 << endl;

		int adj_sz;
		if (adj_list[v1-1] == NULL) {
			adj_sz = 1;
			adj_list[v1-1] = new int[adj_sz+1];
			adj_list[v1-1][1] = v2;
		} else {
			adj_sz = adj_list[v1-1][0];
			adj_sz += 1;
			int *adj_new = new int[adj_sz+1];
			for (int i = 1; i < adj_sz; ++i) {
				adj_new[i] = adj_list[v1-1][i];
			}
			delete adj_list[v1-1];
			adj_list[v1-1] = adj_new;
			adj_list[v1-1][adj_sz] = v2;
		}
		adj_list[v1-1][0] = adj_sz;
	}

	//print adj_list
	for (int i = 0; i < N; ++i) {
		cout << i+1 << " -> ";
		if (adj_list[i] == NULL) {
			cout << "NULL";
		} else {
			for (int j = 1; j < adj_list[i][0]+1; ++j) {
				cout << adj_list[i][j] << ' ';
			}
		}
		cout << endl;
	}
	return 0;
}
