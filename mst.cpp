#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>
#include <map>

using namespace std;

typedef uint16_t vertex;
typedef int16_t edge_cost;
typedef pair<vertex, edge_cost> edge_tuple;
typedef vector<vertex> processed_vertices;
typedef vector<list<edge_tuple>> adjacency_list;
typedef vector<bool> marked_vertices_list;

struct frontier_edge {
	edge_cost ec;
	vertex vtx1;
	vertex vtx2;
};

typedef vector<frontier_edge> frontier_list;

void print_adjacency_list(const adjacency_list &al);
frontier_edge find_mincost_edge(const frontier_list &fl);
void print_frontier_list(const frontier_list &fl);
void print_pv_list(const processed_vertices &pv);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " IN_FILE"
			<< endl;
		return -1;
	}


	int edges_number, vertecis_number;
	int64_t min_sum = 0;
	vertex vtx;
	adjacency_list adj_list;
	frontier_list ft_list;
	processed_vertices pvert_list;
	marked_vertices_list mvl;
	string line;
	ifstream fi(argv[1]);
	stringstream ss;

	getline(fi, line);
	ss.str(line);
	ss >> vertecis_number;
	ss >> edges_number;
	adj_list.resize(vertecis_number);
	mvl.resize(vertecis_number, false);
#ifdef DEBUG
	cout << adj_list.size() << endl;
	cout << vertecis_number << " " << edges_number << endl;
#endif

	// build adgacency list
	while (getline(fi, line)) {
		stringstream ss;
		edge_tuple et;
		vertex vtx1, vtx2;
		ss.str(line);

		ss >> vtx1 >> vtx2 >> et.second;
		et.first = vtx2 - 1;
		adj_list.at(vtx1 - 1).push_back(et);
		et.first = vtx1 - 1;
		adj_list.at(vtx2 - 1).push_back(et);
	}
#ifdef DEBUG
	cout << "Adjacency list" << endl;
	print_adjacency_list(adj_list);
#endif

	// initialization
	// start from first vertex
	vtx = 0;
	pvert_list.push_back(vtx);
	mvl[vtx] = true;
	// add all edges adjacent to new vertex
	for (auto et :  adj_list[vtx]) {
		frontier_edge fe;
		fe.ec = et.second;
		fe.vtx1 = vtx;
		fe.vtx2 = et.first;
		ft_list.push_back(fe);
	}
#ifdef DEBUG
	print_pv_list(pvert_list);
	print_frontier_list(ft_list);
#endif
	// algorithm
	while (pvert_list.size() < vertecis_number) {
		frontier_edge fe_min;
		vertex new_vtx;
		fe_min = find_mincost_edge(ft_list);
#ifdef DEBUG
		cout << "Min edge: " << fe_min.ec << endl;
		print_pv_list(pvert_list);
#endif
		min_sum += fe_min.ec;
		// add new vertex to processed list
		new_vtx = fe_min.vtx2;
		pvert_list.push_back(new_vtx);
		mvl[new_vtx] = true;
		// add edges adjacent to new vertex
		for (auto et : adj_list[new_vtx]) {
			if (!mvl[et.first]) {
				frontier_edge fe;
				fe.ec = et.second;
				fe.vtx1 = new_vtx;
				fe.vtx2 = et.first;
				ft_list.push_back(fe);
			}
		}
#ifdef DEBUG
		cout << "Add edges adjacent to new vertex " << new_vtx + 1 << endl;
		print_frontier_list(ft_list);
#endif
		// remove unnecessary edges
		for (int i = 0; i < ft_list.size(); ++i) {
			if (mvl[ft_list[i].vtx1] && mvl[ft_list[i].vtx2]) {
				ft_list.erase(ft_list.begin() + i);
				i--;
			}
		}
#ifdef DEBUG
		//print new frontier list here
		cout << "Remove edges: " << endl;
		print_frontier_list(ft_list);
#endif
	}
	cout << "Answer is " << min_sum << endl;
	return 0;
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

frontier_edge find_mincost_edge(const frontier_list &fl)
{
	frontier_edge fe_res = fl[0];
	for (auto fe : fl) {
		if (fe.ec < fe_res.ec) {
			fe_res = fe;
		}
	}
	return fe_res;
}

void print_frontier_list(const frontier_list &fl)
{
	for (auto fe : fl) {
		cout << fe.vtx1 + 1 << " " << fe.vtx2 + 1 << " " 
			<< fe.ec << ",  ";
	}
	cout << endl;
}

void print_pv_list(const processed_vertices &pv)
{
	for (auto v : pv) {
		cout << v + 1 << " ";
	}
	cout << endl;
}
