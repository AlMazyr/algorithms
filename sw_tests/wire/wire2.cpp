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
	uint16	v1;
	uint16	v2;
};

VertexNode adj_l[MAX_N][MAX_N];
uint16 adj_m[MAX_N][MAX_N];
Edge edges[MAX_N-1];

uint8 visited[MAX_N];
uint16 stack[MAX_N];
uint16 stack_i[MAX_N];
uint16 stack_s[MAX_N];
int top;

VertexNode dfs(uint16 src)
{
	uint16 max_sc = 0, max_v = src;
	stack[top] = src;
	stack_i[top++] = 1;
	visited[src-1] = 1;
	while(top) {
		bool found = false;
		uint16 cur = stack[top-1];
		uint16 sc = stack_s[top-1];
		uint16 &idx = stack_i[top-1];
		uint16 &num = adj_l[cur-1][0].v;
		for(; idx < num+1; ++idx) {
			uint16 &v_n = adj_l[cur-1][idx].v;
			uint16 &v_w = adj_l[cur-1][idx].w;
			if (!visited[v_n-1] && adj_m[cur-1][v_n-1]) {
				visited[v_n-1] = 1;
				sc += v_w;
				if (sc > max_sc) {
					max_sc = sc;
					max_v = v_n;
				}
				found = true;
				stack[top] = v_n;
				stack_s[top] = sc;
				stack_i[top++] = 1;
				break;
			}
		}
		if (!found)
			top--;
	}
	for (int j = 0; j < MAX_N; ++j)
		visited[j] = 0;
	return {max_v, max_sc};
}

int find_path(uint16 src)
{
	VertexNode vn = dfs(src);
	vn = dfs(vn.v);
	return vn.w;
}

int exec_test(int N)
{
	int ans = 0;

	for (int i = 0; i < N-1; ++i) {
		Edge &e  = edges[i];
		uint16 w = adj_m[e.v1-1][e.v2-1];
		// mark edge as deleted
		adj_m[e.v1-1][e.v2-1] = 0;
		adj_m[e.v2-1][e.v1-1] = 0;
		// find path for first half
		int p1 = find_path(e.v1);
		int p2 = find_path(e.v2);
		//cout << endl;
		int p = p1 + p2 + w;
		//cout << p1 << ":" << p2 << ":" << w << ":" << p << endl;
		if (p > ans)
			ans = p;
		// restore edge
		adj_m[e.v1-1][e.v2-1] = w;
		adj_m[e.v2-1][e.v1-1] = w;
	}

	// clean
	for (int i = 0; i < N; ++i) {
		uint16 &j_max = adj_l[i][0].v;
		for (int j = 1; j < j_max+1; ++j) {
			VertexNode &vn = adj_l[i][j];
			adj_m[i][vn.v-1] = 0;
			adj_m[vn.v-1][i] = 0;
		}
		j_max = 0;
	}

	return ans;
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
			adj_m[v1-1][v2-1] = w; // adj matrix
			adj_m[v2-1][v1-1] = w;
			uint16 &num1 = adj_l[v1-1][0].v; // adj list
			uint16 &num2 = adj_l[v2-1][0].v;
			adj_l[v1-1][++num1] = {v2, w};
			adj_l[v2-1][++num2] = {v1, w};
		}
		cout << '#' << i+1 << ' ' << exec_test(N) << endl;
	}

	return 0;
}
