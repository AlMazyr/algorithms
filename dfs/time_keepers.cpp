#include <iostream>

using namespace std;

#define N_MAX 100000
#define M_MAX 1000000

#define UNVISITED 0
#define IN 1
#define OUT 2

int *adj_list[N_MAX];
int visited[N_MAX];
int stack_cycle[N_MAX], top, stop_cycle;

int dfs(int start)
{
	int res;
	visited[start-1] = IN;
	int &adj_sz = adj_list[start-1][0];
	for (int i = 1; i < adj_sz+1; ++i) {
		int &adj_v = adj_list[start-1][i];
		if (visited[adj_v-1]  == OUT) {
			continue;
		} else if (visited[adj_v-1] == IN) {
			stack_cycle[top++] = adj_v;
			stack_cycle[top++] = start;
			return adj_v;
		}
		if ((res = dfs(adj_v)) != 0) {
			if (res == start)
				stop_cycle = 1;
			if (!stop_cycle)
				stack_cycle[top++] = start;
			return res;
		}
	}
	visited[start-1] = OUT;
	return 0;
}

int main()
{
	int N, M;

	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		int edges_num;
		cin >> edges_num;
		adj_list[i] = new int[edges_num+1];
		adj_list[i][0] = edges_num;
		for (int j = 1; j < edges_num+1; ++j) {
			cin >> adj_list[i][j];
		}
	}

	int res;
	for (int i = 0; i < N; ++i) {
		if (visited[i] == UNVISITED) {
			if ((res = dfs(i+1)) != 0)
				break;
		}
	}
	if (res) {
		cout << top << endl;
		for (int i = top-1; i >= 0; --i)
			cout << stack_cycle[i] << ' ';
		cout << endl;
	} else {
		cout << -1 << endl;
	}
	return 0;
}
