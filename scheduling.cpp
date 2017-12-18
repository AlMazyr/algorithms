#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>

using namespace std;

struct task {
	uint16_t id;
	int16_t weight;
	int16_t lenght;
}

typedef int16_t score;

//typedef priority_queue<score, task, less<uint16_t>> max_heap;
typedef vector<task> scheduled_list;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "Err params! Usage: " << argv[0] << "INFILE" << endl;
		return -1;
	}

	ifstream fi(argv[1]);
	uint16_t jobs_number;
	int16_t weight, lenght;
	score job_score;
	//max_heap scheduled_list;

	fi >> jobs_number;
#ifdef DEBUG
	cout << "Number of jobs is " << jobs_number << endl;
#endif
	// reading jobs
	for (int i = 0; i < jobs_number; ++i) {
		fi >> weight >> lenght;
		// calc score here
		score = weight - lenght;
		// fill scheduled list (max heap) here
		scheduled_list.push(task(i, weight, lenght));
#ifdef DEBUG
	cout << "Job: Id - " << i << ", Weight - " << weight <<
	       	", lenght - " << lenght << ", score - " << score << endl;
#endif
	}

	// print scheduled list here
	return 0;
}
