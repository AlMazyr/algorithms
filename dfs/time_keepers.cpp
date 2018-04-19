#include <iostream>

using namespace std;

#define N_MAX 100000
#define M_MAX 1000000

#define UNVISITED 0
#define IN 1
#define OUT 2

int *adj_list[N_MAX];
int visited[N_MAX];
int stack[N_MAX], top;

int get_unvisited(int n)
{
	int res = -1;
	for (int i = 0; i < n; ++i) {
		if (visited[i] == UNVISITED) {
			res = i;
			break;
		}
	}
	return res;
}

void dfs(int start)
{
	visited[start] = IN;
	for (int i = 1; i < adj_list[start][0]+1; ++i) {
		if (visited[adj_list[start][i]-1]  == OUT) {
			continue;
		} else if (visited[adj_list[start][i]-1] == IN) {
			// we found a cycle! 
			cout << "Cycle!" << endl;
			int stack_idx = top-1;
			while (stack[stack_idx] != adj_list[start][i]) {
				stack_idx--;
			}
			cout << top - stack_idx << endl;
			while (stack_idx != top) {
				cout << stack[stack_idx++] << " ";
			}
			cout << endl;
			continue;
		}
		stack[top++] = adj_list[start][i];
		dfs(adj_list[start][i]-1);
		top--;
	}
	visited[start] = OUT;
}

int main()
{
	int N, M;

	cin >> N >> M;
	cout << N << " " << M << endl;

	for (int i = 0; i < N; ++i) {
		int edges_num;
		cin >> edges_num;
		adj_list[i] = new int[edges_num+1];
		adj_list[i][0] = edges_num;
		for (int j = 1; j < edges_num+1; ++j) {
			cin >> adj_list[i][j];
		}
	}

	// debug: print adj list
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < adj_list[i][0]+1; ++j) {
			cout << adj_list[i][j] << " ";
		}
		cout << endl;
	}

	int start;
	while ((start = get_unvisited(N)) != -1) {
		stack[top++] = start+1;
		dfs(start);
		top--;
	}
	return 0;
}
