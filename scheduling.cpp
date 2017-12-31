#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef double task_score;

struct task {
	task(task_score score, int16_t weight, int16_t lenght)
		: score(score), weight(weight), lenght(lenght) {}
	task_score score;
	int16_t weight;
	int16_t lenght;
};

typedef vector<task> scheduled_list;

task_score calculate_score(int16_t weight, int16_t lenght);
bool compare(task l, task r);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "Err params! Usage: " << argv[0] << " INFILE" << endl;
		return -1;
	}

	ifstream fi(argv[1]);
	uint16_t jobs_number;
	int16_t weight, lenght;
	uint32_t completion_time = 0;
	uint64_t sum = 0;
	task_score score;
	scheduled_list sch_list;

	fi >> jobs_number;
#ifdef DEBUG
	cout << "Number of jobs is " << jobs_number << endl;
#endif
	// create unsorted list of jobs
	for (int i = 0; i < jobs_number; ++i) {
		fi >> weight >> lenght;
		// calc score
		score = calculate_score(weight, lenght);
		// fill scheduled list
		sch_list.push_back(task(score, weight, lenght));
#ifdef DEBUG
		cout << weight << " " << lenght << " " << score << endl;
#endif
	}

	// sort list of jobs by score and weight
	sort(sch_list.begin(), sch_list.end(), compare);

#ifdef DEBUG
	// print scheduled list
	cout << "Scheduled list: " << endl;
	for (auto job : sch_list) {
		cout << job.weight << " " << job.lenght << " "
			<< job.score << endl;
	}
#endif
	// calculate weighted sum
	for (auto job : sch_list) {
		completion_time += job.lenght;
		sum += job.weight * completion_time;
	}
	cout << "Sum is " << sum << endl;

	return 0;
}

task_score calculate_score(int16_t weight, int16_t lenght)
{
#ifdef SUB
	return weight - lenght;
#else
	return (double)weight / (double)lenght;
#endif
}
bool compare(task l, task r)
{
	// score is primary condition
	if (l.score > r.score)
		return true;
	if (l.score < r.score)
		return false;
	// if scores are equal check weights
	if (l.weight > r.weight)
		return true;
	if (l.weight < r.weight)
		return false;
}
