#include <iostream>

#define N_MAX 1000000

using namespace std;

int *adj_list[N_MAX];
int v_adj_num[N_MAX];
int edges[N_MAX][2];
int visited[N_MAX];

void dfs_recursive(int start)
{
	visited[start-1] = 1;
	if (adj_list[start-1]) {
		int &adj_num = adj_list[start-1][0];
		for (int i = 1; i < adj_num+1; ++i) {
			int &adj_v = adj_list[start-1][i];
			if (!visited[adj_v-1]) {
				dfs_recursive(adj_v);
			}
		}
	}
	cout << start << ' ';
}

int main()
{
	int N, edges_num = 0;

	cin >> N;

	// preparing input data
	while (1) {
		int v1, v2;
		cin >> v1 >> v2;
		if (cin.eof())
			break;
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

#if 0
	// print adj list
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
#endif
	for (int i = 0; i < N; ++i) {
		if (!visited[i]) {
			dfs_recursive(i+1);
		}
	}
	cout << endl;
	return 0;
}
