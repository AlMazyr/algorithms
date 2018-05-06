#include <iostream>

#define N_MAX 1000000

using namespace std;

int *adj_list[N_MAX];
int v_adj_num[N_MAX];
int edges[N_MAX][2];
int visited[N_MAX];
int stack_v[N_MAX], stack_adj_idx[N_MAX], top;

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

void dfs(int start)
{
	stack_v[top] = start;
	stack_adj_idx[top++] = 1;
	visited[start-1] = 1;

	while (top) {
		bool found = false;
		int &current = stack_v[top-1];
		if (adj_list[current-1]) {
			int &adj_idx = stack_adj_idx[top-1];
			int &adj_num = adj_list[current-1][0];
			for (; adj_idx < adj_num+1; ++adj_idx) {
				int &adj_v = adj_list[current-1][adj_idx];
				if (!visited[adj_v-1]) {
					found = true;
					stack_v[top] = adj_v;
					stack_adj_idx[top++] = 1;
					visited[adj_v-1] = 1;
					break;
				}
			}
		}
		if (!found) {
			top--;
			cout << current << ' ';
		}
	}
}

int main()
{
	int N, edges_num = 0;

	cin >> N;

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

	for (int i = 0; i < N; ++i) {
		if (!visited[i]) {
			dfs(i+1);
		}
	}
	cout << endl;
	return 0;
}
