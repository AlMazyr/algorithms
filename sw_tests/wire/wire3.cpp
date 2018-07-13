#include <iostream>

#define MAX_N	2000

using namespace std;

struct Edge {
	int v1;
	int v2;
	int w;
};

struct VNode {
	int v;
	int w;
};

struct MPath {
	int d;
	int r;
};

Edge edges[MAX_N];
VNode adj[MAX_N][MAX_N];
int N;

void print_edges()
{
	cout << "[ ";
	for (int i = 0; i < N-1; ++i)
		cout << edges[i].v1 << ':' << edges[i].v2 << ' ';
	cout << ']' << endl;
}

void print_adj()
{
	for (int i = 0; i < N; ++i) {
		int &num = adj[i][0].v;
		cout << i+1 << ": ";
		for (int j = 1; j < num+1; ++j)
			cout << adj[i][j].v << ',' << adj[i][j].w << ' ';
		cout << endl;
	}
	cout << endl;
}

MPath find_path(int v_st, int v_par)
{
	if (adj[v_st-1][0].v == 1 && adj[v_st-1][1].v == v_par)
		return {0, 0};

	int maxd = 0;
	int maxr1 = 0, maxr2 = 0;
	// iterate over adjecent edges
	int &num = adj[v_st-1][0].v;
	for (int i = 1; i < num+1; ++i) {
		int &av = adj[v_st-1][i].v;
		int &aw = adj[v_st-1][i].w;
		if (av == v_par)
			continue;
		MPath mp = find_path(av, v_st);
		if (mp.d > maxd)
			maxd = mp.d;
		int r = mp.r + aw;
		if (r > maxr1) {
			maxr2 = maxr1;
			maxr1 = r;
		} else if (r > maxr2) {
			maxr2 = r;
		}
	}
	maxd = maxd > (maxr1 + maxr2) ? maxd : (maxr1 + maxr2);
	return {maxd, maxr1};
}

int exec_test()
{
	int max_dist = 0;
	// iterate over edges
	for (int i = 0; i < N-1; ++i) {
		Edge &e = edges[i];
		MPath mp = find_path(e.v1, e.v2);
		int p1 = mp.d;
		mp = find_path(e.v2, e.v1);
		int p2 = mp.d;
		int dist = p1 + p2 + e.w;
		if (dist > max_dist)
			max_dist = dist;
	}
	// clean
	for (int i = 0; i < N; ++i)
		adj[i][0].v = 0;
	return max_dist;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		cin >> N;
		for (int j = 0; j < N-1; ++j) {
			int w, v1, v2;
			cin >> w >> v1 >> v2;
			// add edge to edges list
			edges[j] = {v1, v2, w};
			// add edge to adj list
			int &num1 = adj[v1-1][0].v;
			int &num2 = adj[v2-1][0].v;
			adj[v1-1][++num1] = {v2, w};
			adj[v2-1][++num2] = {v1, w};
		}
		//DEBUG
		//print_edges();
		//print_adj();
		cout << '#' << i+1 << ' ' << exec_test() << endl;
	}

	return 0;
}
