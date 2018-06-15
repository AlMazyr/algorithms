#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>
#include <cctype>
#include <cstdlib>

using namespace std;

//#define DEBUG

typedef uint32_t user_id_t;
typedef int action_t;
typedef int cabin_id_t;
typedef map<user_id_t, cabin_id_t> user_cabin_map_t;
typedef vector<pair<action_t,user_id_t>> request_t;

struct cabin_t
{
	cabin_t(bool busy, user_id_t id) : is_busy(busy), user_id(id) {}
	bool is_busy;
	user_id_t user_id;
};

class toilet_t
{
public:
	toilet_t(int cabins_total) : cabins(cabins_total, cabin_t(false, 0)) {}

	void occupy_cabin(cabin_id_t cabin_id, user_id_t user_id)
	{
		this->cabins[cabin_id].is_busy = true;
		this->cabins[cabin_id].user_id = user_id;
		this->cabin_occupied_map[user_id] = cabin_id;
	}

	void free_cabin(user_id_t uid)
	{
		cabin_id_t cid = this->cabin_occupied_map[uid];
		this->cabins[cid].is_busy = false;
		this->cabins[cid].user_id = 0;
		this->cabin_occupied_map.erase(uid);
	}

	cabin_id_t get_free_cabin()
	{
		// cabin searching algorithm implementation

		if (cabin_occupied_map.empty()) {
			// if all cabins are empty
			return 0;
		}
		

		int distance = 0, min_distance = cabins.size();
		pair<cabin_id_t, int> free_cabin(0, 0);
		for (int i = 0; i < cabins.size(); ++i) {
			if (cabins[i].is_busy)
				continue;
			for (int j = 0; j < cabins.size(); ++j) {
				if (!cabins[j].is_busy)
					continue;
				distance = abs(i - j);
				if (distance < min_distance)
					min_distance = distance;
			}
			// i = free cabin id, min distance
			if (min_distance > free_cabin.second) {
				// we found better cabin
				free_cabin.first = i;
				free_cabin.second = min_distance;
			} else if (min_distance == free_cabin.second) {
				// if distance is the same chose cabin with smaler id
				if (i < free_cabin.first) {
					free_cabin.first = i;
					free_cabin.second = min_distance;
				}
			}
			min_distance = cabins.size();
		}
		return free_cabin.first;
	}

private:
	vector<cabin_t> cabins;
	user_cabin_map_t cabin_occupied_map;
};

uint64_t exec_test(uint32_t N, uint32_t M, request_t &requests, toilet_t &toilet)
{
	uint64_t result = 0;
#ifdef DEBUG
	for (auto &req : requests) {
		cout << req.first << " " << req.second << endl;
	}
	cout << endl;
#endif
	int free_cabin;
	// main loop
	for (auto &req : requests) {
#ifdef DEBUG
		cout << "REQ = " << req.first << ", " << req.second << " ";
#endif
		if (req.first == 1) {
			free_cabin = toilet.get_free_cabin();
#ifdef DEBUG
			cout << "cabin = " << free_cabin + 1;
#endif
			toilet.occupy_cabin(free_cabin, req.second);
			result += free_cabin + 1;
		} else {
			toilet.free_cabin(req.second);
		}
#ifdef DEBUG
		cout << endl;
#endif
	}
	return result;
}

int main(int argc, char* argv[])
{
	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		user_id_t id;
		action_t action;
		uint32_t N, M;
		request_t requests;
		cin >> N >> M;
		requests.reserve(M);
		toilet_t toilet(N);
		for (int i = 0; i < M; ++i) {
			cin >> action >> id;
			requests.push_back(make_pair(action, id));
		}
		cout << '#' << i+1 << ' ' << exec_test(N, M, requests, toilet) << endl;
	}
	return 0;
}
