#include <iostream>

using namespace std;

#define MAX_N	2000

typedef unsigned char	uint8;

struct VertexNode {
	int	v;
	int	w;
};

struct Edge {
	int	v1;
	int	v2;
};

VertexNode adj_l[MAX_N][MAX_N];
int adj_m[MAX_N][MAX_N];
Edge edges[MAX_N-1];

int N;
uint8 visited[MAX_N];
int head, tail;
VertexNode queue[MAX_N];

VertexNode bfs(int src)
{
	int max_sc = 0;
	int max_v = src;
	queue[head++] = {src, 0};
	visited[src-1] = 1;

	while(head != tail) {
		VertexNode cur = queue[tail++];
		int &num = adj_l[cur.v-1][0].v;
		for (int i = 1; i < num+1; ++i) {
			int &v_n = adj_l[cur.v-1][i].v;
			int &v_w = adj_l[cur.v-1][i].w;
			if (!visited[v_n-1] && adj_m[cur.v-1][v_n-1]) {
				visited[v_n-1] = 1;
				int sc = cur.w + v_w;
				queue[head++] = {v_n, sc};
				if (sc > max_sc) {
					max_sc = sc;
					max_v = v_n;
				}
			}
		}
	}
	//clean
	head = 0;
	tail = 0;
	int n_recs = (N + 8 - 1) / 8;
	int i = 0;
	for (int j = 0; j < n_recs; ++j) {
		*(unsigned long long*)&visited[i] = 0;
		i += 8;
	}
	return {max_v, max_sc};
}

int exec_test()
{
	int ans = 0;

	for (int i = 0; i < N-1; ++i) {
		Edge &e  = edges[i];
		int w = adj_m[e.v1-1][e.v2-1];
		// mark edge as deleted
		adj_m[e.v1-1][e.v2-1] = 0;
		adj_m[e.v2-1][e.v1-1] = 0;
		// find max path for first half
		VertexNode vn1 = bfs(e.v1);
		vn1 = bfs(vn1.v);
		// find max path for second half
		VertexNode vn2 = bfs(e.v2);
		vn2 = bfs(vn2.v);
		//cout << endl;
		int p = vn1.w + vn2.w + w;
		//cout << p1 << ":" << p2 << ":" << w << ":" << p << endl;
		if (p > ans)
			ans = p;
		// restore edge
		adj_m[e.v1-1][e.v2-1] = w;
		adj_m[e.v2-1][e.v1-1] = w;
	}
	// clean
	for (int i = 0; i < N; ++i) {
		int &j_max = adj_l[i][0].v;
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tests_number;
	cin >> tests_number;

	for (int i = 0; i < tests_number; ++i)
	{
		cin >> N;
		for (int j = 0; j < N-1; ++j) {
			int w, v1, v2;
			cin >> w >> v1 >> v2;
			edges[j] = {v1, v2}; //edges list
			adj_m[v1-1][v2-1] = w; // adj matrix
			adj_m[v2-1][v1-1] = w;
			int &num1 = adj_l[v1-1][0].v; // adj list
			int &num2 = adj_l[v2-1][0].v;
			adj_l[v1-1][++num1] = {v2, w};
			adj_l[v2-1][++num2] = {v1, w};
		}
		cout << '#' << i+1 << ' ' << exec_test() << endl;
	}

	return 0;
}
