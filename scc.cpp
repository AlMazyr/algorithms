#include <iostream>
#include <fstream>
#include <vector>
#include <list>

/*
 * Kosaraju's algorithm - Strongly Connected Components (SCC).
 * This implementation does some extra work and uses additional memory,
 * but it is easier to understand in my opinion.
 */

//#define DEBUG

using namespace std;

typedef vector<list<uint32_t>> adjacency_list;
typedef vector<bool> marked_vertices_list;
typedef vector<uint32_t> scc_list;
typedef vector<uint32_t> finish_table;

void print_adj_list(const adjacency_list &al);
void calc_scc(const adjacency_list &al, scc_list &scc, finish_table &ft);
uint32_t dfs(const adjacency_list &al, marked_vertices_list &mvl, int i,
	       	finish_table &ft, uint32_t &finish_time);
void reverse_graph(adjacency_list &al);
void make_ft_graph(adjacency_list &al, const finish_table &ft);
void make_finish_table(const adjacency_list &al, finish_table &ft);
void dfs_loop(const adjacency_list &al, scc_list *scc, finish_table &ft);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " IN_FILE"
			<< endl;
		return -1;
	}

	ifstream fin(argv[1]);
	adjacency_list al;
	scc_list scc;
	uint32_t v1, v2;
	uint32_t vertices, edges;
	finish_table ft;

	// read number of vertices and edges
	fin >> vertices >> edges;
#ifdef DEBUG
	cout << "Vertices - " << vertices << ", edges - " << edges << endl;
#endif
	al.resize(vertices);
	ft.resize(vertices);
	// build adjacency list
	while (fin >> v1 >> v2) {
		al[v1-1].push_back(v2-1);
	}

#ifdef DEBUG
	print_adj_list(al);
#endif

	// make finish table from reversed graph
	reverse_graph(al);
#ifdef DEBUG
	print_adj_list(al);
#endif
	make_finish_table(al, ft);
#ifdef DEBUG
	// print finish table
	cout << "[ ";
	for (auto &x : ft) {
		cout << x+1 << " ";
	}
	cout << "]" << endl;
#endif
	
	// make mew graph from finish table
	make_ft_graph(al, ft);
	reverse_graph(al);
#ifdef DEBUG
	print_adj_list(al);
#endif

	calc_scc(al, scc, ft);

	// print number of scc
	cout << "Number of scc is " << scc.size() << endl;

	return 0;
}

void print_adj_list(const adjacency_list &al)
{
	cout << "{ ";
	for (int i = 0; i < al.size(); ++i) {
		cout << "[" << i+1 << " : ";
		for (auto &v : al[i]) {
			cout << v+1 << " ";
		}
		cout << "] ";
	}
	cout << " }" << endl;
}

/* Depth-first search */
uint32_t dfs(const adjacency_list &al, marked_vertices_list &mvl, int i,
	       	finish_table &ft, uint32_t &finish_time)
{
	vector<uint32_t> st;
	uint32_t top, sz = 1;

	st.push_back(i);
	mvl[i] = true;

	while(!st.empty()) {
		top = st.back();
		if (al[top].size() == 0) {
			st.pop_back();
			ft[top] = finish_time;
			finish_time++;
			continue;
		}
		// search next unmarked v
		bool found = false;
		for (auto &n : al[top]) {
			if (!mvl[n]) {
				found = true;
				st.push_back(n);
				mvl[n] = true;
				sz++;
				break;
			}
		}
		if (!found) {
			st.pop_back();
			ft[top] = finish_time;
			finish_time++;
		}
	}
	return sz;
}

/* Reverse all the edges in directed graph */
void reverse_graph(adjacency_list &al)
{
	adjacency_list new_al;
	new_al.resize(al.size());
	for (int i = 0; i < al.size(); ++i) {
		for (auto &n : al[i]) {
			new_al[n].push_back(i);
		}
	}
	al = new_al;
}

/* Make new adjacency list from finish table */
void make_ft_graph(adjacency_list &al, const finish_table &ft)
{
	adjacency_list new_al;
	new_al.resize(al.size());
	for (int i = 0; i < al.size(); ++i) {
		for (auto &n : al[i]) {
			new_al[ft[i]].push_back(ft[n]);
		}
	}
	al = new_al;
}

void make_finish_table(const adjacency_list &al, finish_table &ft)
{
	dfs_loop(al, nullptr, ft);
}

void calc_scc(const adjacency_list &al, scc_list &scc, finish_table &ft)
{
	dfs_loop(al, &scc, ft);
}

void dfs_loop(const adjacency_list &al, scc_list *scc, finish_table &ft)
{
	marked_vertices_list mvl;
	mvl.resize(al.size(), false);
	uint32_t finish_time = 0;
	uint32_t scc_size;

	for (int i = al.size() - 1; i >= 0; --i) {
		if (!mvl[i]) {
			scc_size = dfs(al, mvl, i, ft, finish_time);
			if (scc != nullptr)
				scc->push_back(scc_size);
		}
	}
}
