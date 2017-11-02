#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>

using namespace std;

typedef uint16_t v_num;
typedef uint16_t e_len;
typedef pair<v_num, e_len> edge_tuple;
typedef vector<list<edge_tuple>> adjacency_list;
typedef vector<bool> marked_vertices_list;

bool read_pair(stringstream &ss, edge_tuple &et);
void print_adjacency_list(const adjacency_list &al);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " IN_FILE"
			<< endl;
		return -1;
	}

	ifstream fin(argv[1]);
	adjacency_list al;
	string line;
	int n;

	// read number of vertices(lines)
	fin >> n;
	al.resize(n);

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

	// TODO: implement dijkstra
	return 0;
}

bool read_pair(stringstream &ss, edge_tuple &et)
{
	char ch;

	if (!(ss >> et.first)) {
		return false;
	}

	ss >> ch >> et.second;

	return true;

}

void print_adjacency_list(const adjacency_list &al)
{
	for (int i = 0; i < al.size(); ++i) {
		cout << i + 1 << ": ";
		for (auto &v : al[i]) {
			cout << v.first << "," << v.second << " ";
		}
		cout << endl;
	}
}
