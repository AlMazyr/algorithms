#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

//#define DEBUG

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Err arguments! Usage: " << argv[0] << " IN_FILE"
			<< endl;
		return -1;
	}

	srand(time(NULL));
	ifstream fin(argv[1]);
	string line;
	int first_v, next_v;
	int num_v = 0;
	set<pair<int,int>> edges_s;
	vector<pair<int,int>> edges_m;

	// building set of edges
	while (getline(fin, line)) {
		num_v++;
		stringstream ss;
		ss.str(line);

		ss >> first_v;
		while(ss >> next_v) {
			if (first_v < next_v) {
				edges_s.insert(make_pair(first_v, next_v));
			} else if (first_v > next_v) {
				edges_s.insert(make_pair(next_v, first_v));
			}
		}
	}

	if (num_v < 2)
		return -1;
#ifdef DEBUG
	cout << "Num of verteces is " << num_v << endl;
	cout << "Num of edges is " << edges_s.size() << endl;
	for (auto &edge : edges_s) {
		cout << "(" << edge.first << ", " << edge.second << ") ";
	}
	cout << endl;
#endif // DEBUG

	// transform set to vector
	for (auto &e : edges_s) {
		edges_m.push_back(e);
	}
	// clear set of edges, because we don't need it anymore
	edges_s.clear();

	while (num_v-- > 2) {
		// choose random edge
		int rand_e = rand() % edges_m.size();
		int v_first, v_second;
		v_first = edges_m[rand_e].first;
		v_second = edges_m[rand_e].second;
		// delete the choosen one
#ifdef DEBUG
		cout << "Delete edge: (" << edges_m[rand_e].first
			<< ", " << edges_m[rand_e].second << ")" << endl;
#endif
		edges_m.erase(edges_m.begin() + rand_e);
		// rebuild the edges vector
		for (int i = 0; i < edges_m.size(); ++i) {
			if (edges_m[i].first == v_second) {
				edges_m[i].first = v_first;
			} else if (edges_m[i].second == v_second) {
				edges_m[i].second = v_first;
			}
			if (edges_m[i].first > edges_m[i].second) {
				swap(edges_m[i].first, edges_m[i].second);
			}
			if (edges_m[i].first == edges_m[i].second) {
				// self loop
				edges_m.erase(edges_m.begin() + i);
				i--;
			}
		}
		if (edges_m.size() == 0)
			return -1;

#ifdef DEBUG
		cout << "Num of verteces is " << num_v << endl;
		cout << "Num of edges is " << edges_m.size() << endl;
		for (auto &edge : edges_m) {
			cout << "(" << edge.first << ", " << edge.second << ") ";
		}
		cout << endl;
#endif // DEBUG
	}

	cout << "Answer is " << edges_m.size() << endl;;
	return 0;
}
