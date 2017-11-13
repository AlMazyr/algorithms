#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>

/*
 * Dijkstra's algorithm.
 * This is a "naive" implementation (whithout heap).
 */

using namespace std;

typedef uint16_t v_num;
typedef uint16_t e_len;
typedef uint32_t shortest_path;
typedef pair<v_num, e_len> edge_tuple;
typedef vector<list<edge_tuple>> adjacency_list;
typedef vector<shortest_path> shortest_path_list;
typedef vector<bool> marked_vertices_list;

bool read_pair(stringstream &ss, edge_tuple &et);
void print_adjacency_list(const adjacency_list &al);
void dijkstra(const adjacency_list &al, v_num src_v, shortest_path_list &sh);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " IN_FILE"
			<< endl;
		return -1;
	}

	ifstream fin(argv[1]);
	adjacency_list al;
	shortest_path_list sh;
	string line;
	int n;

	// read number of vertices(lines)
	fin >> n;
	al.resize(n);
	sh.resize(n, 1000000);

	// build adjacency list
	while (getline(fin, line)) {
		stringstream ss;
		ss.str(line);
		uint16_t v;
		edge_tuple et;

		// read vertex
		ss >> v;
		while (read_pair(ss, et)) {
			al[v - 1].push_back(et);
		}
	}

#ifdef DEBUG
	print_adjacency_list(al);
#endif

	dijkstra(al, 0, sh);

	// print shortest path list
	cout << "Shortest path list:" << endl;
	for (auto &p : sh) {
		cout << " " << p;
	}
	cout << endl;

	return 0;
}

bool read_pair(stringstream &ss, edge_tuple &et)
{
	char ch;
	uint16_t vertex;

	if (!(ss >> vertex)) {
		return false;
	}

	et.first = vertex - 1;
	ss >> ch >> et.second;

	return true;
}

void print_adjacency_list(const adjacency_list &al)
{
	for (int i = 0; i < al.size(); ++i) {
		cout << i + 1 << ": ";
		for (auto &v : al[i]) {
			cout << v.first + 1 << "," << v.second << " ";
		}
		cout << endl;
	}
}

void dijkstra(const adjacency_list &al, v_num src_v, shortest_path_list &sh)
{
	vector<uint16_t> proc_v;
	marked_vertices_list mvl;
	uint16_t vertex;
	uint32_t min_score = 0xffffffff;

#ifdef DEBUG
	cout << "Source vertex: " << src_v + 1 << endl;
#endif
	mvl.resize(al.size(), false);
	proc_v.push_back(src_v);
	mvl[src_v] = true;
	sh[src_v] = 0;

	while (proc_v.size() < al.size()) {
		vertex = al.size();
		// check all the vertices processed so far
		for (auto &v : proc_v) {
			// check all the edges of the vertex
			for (auto &e : al[v]) {
				// find edges with not processed second vertex
				if (!mvl[e.first]) {
					uint16_t score = sh[v] + e.second;
					if (score < min_score) {
						min_score = score;
						vertex = e.first;
					}
				}
			}
		}
		if (vertex == al.size()) {
			// there are no more vertices that can be processed
#ifdef DEBUG
			cout << "Unconnected graph!" << endl;
#endif
			break;
		}
#ifdef DEBUG
		cout << "Next vertex: " << vertex + 1 << ", " << min_score
			<< endl;
#endif
		// add new vertex to processed list
		proc_v.push_back(vertex);
		mvl[vertex] = true;
		sh[vertex] = min_score;
		min_score = 0xffffffff;
	}
}
