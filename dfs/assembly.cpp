#include <iostream>

<<<<<<< HEAD
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

=======
#define N_MAX 1000000

using namespace std;

int *adj_list[N_MAX];
int v_adj_num[N_MAX];
int edges[N_MAX][2];

int main()
{
	int N, edges_num = 0;

	cin >> N;

	// preparing input data
>>>>>>> a521592fd4c5f28e848203bf4a039e160fe1844f
	while (1) {
		int v1, v2;
		cin >> v1 >> v2;
		if (cin.eof())
			break;
<<<<<<< HEAD
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
=======
		v_adj_num[v1-1]++;
		edges[edges_num][0] = v1;
		edges[edges_num][1] = v2;
		edges_num++;
	}

	for (int i = 0; i < edges_num; ++i) {
		int &v1 = edges[i][0], &v2 = edges[i][1];
		if (adj_list[v1-1] == NULL) {
			adj_list[v1-1] = new int[v_adj_num[v1-1]+1];
			adj_list[v1-1][0] = 1;
			adj_list[v1-1][1] = v2;
		} else {
			int &idx = adj_list[v1-1][0];
			adj_list[v1-1][++idx] = v2;
		}
	}

	// print adj list
>>>>>>> a521592fd4c5f28e848203bf4a039e160fe1844f
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
