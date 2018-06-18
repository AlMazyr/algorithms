#include <iostream>

using namespace std;

#define MAX_N	2000

typedef unsigned short	uint16;
typedef unsigned char	uint8;

struct VertexNode {
	uint16	v;
	uint16	w;
};

struct Edge {
	uint16	e1;
	uint16	e2;
};

VertexNode adj_l[MAX_N][MAX_N];
uint8 adj_m[MAX_N][MAX_N];
Edge edges[MAX_N-1];

uint8 visited[MAX_N][MAX_N];

int exec_test(int N)
{
	int ans = 0;

	return ans;
}

void print_edges(int N)
{
	for (int i = 0; i < N-1; ++i)
		cout << edges[i].e1 << ':' << edges[i].e2 << " ";
	cout << endl;
}
void print_adj_mt(int N)
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			cout << (int)adj_m[i][j] << ' ';
		cout << endl;
	}
}

void print_adj_lst(int N)
{
	for (int i = 0; i < N; ++i) {
		uint16 &j_max = adj_l[i][0].v;
		for (int j = 1; j < j_max+1; ++j) {
			VertexNode &vn = adj_l[i][j];
			cout << vn.v << ':' << vn.w << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int tests_number;
	cin >> tests_number;

	for (int i = 0; i < tests_number; ++i)
	{
		int N;
		cin >> N;
		for (int j = 0; j < N-1; ++j) {
			uint16 w, v1, v2;
			cin >> w >> v1 >> v2;
			edges[j] = {v1, v2}; //edges list
			adj_m[v1-1][v2-1] = 1; // adj matrix
			adj_m[v2-1][v1-1] = 1;
			uint16 &idx1 = adj_l[v1][0].v; // adj list
			uint16 &idx2 = adj_l[v2][0].v;
			adj_l[v1][++idx1] = {v2, w};
			adj_l[v2][++idx2] = {v1, w};
		}
		//DEBUG
		print_edges(N);
		print_adj_mt(N);
		print_adj_lst(N);
		cout << '#' << i+1 << ' ' << exec_test(N) << endl;
	}

	return 0;
}
