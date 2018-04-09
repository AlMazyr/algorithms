#include <iostream>

#define V_MAX 100

using namespace std;

int stack_flags[V_MAX];
int top;
int N, K;
int is_symmetry;
int count;

void dfs(int start, bool is_count)
{
	if (top == K) {
		count++;
		if (is_count)
			return;
		for (int i = 0; i < N; ++i) {
			if (stack_flags[i]) {
				if (!is_symmetry)
					cout << i+1 << " ";
			} else {
				if (is_symmetry)
					cout << i+1 << " ";
			}
		}
		cout << endl;
		return;
	}

	for (int i = start+1; i <= N; ++i) {
		stack_flags[i-1] = 1;
		top++;
		dfs(i, is_count);
		stack_flags[i-1] = 0;
		top--;
	}
}

int main()
{
	cin >> N >> K;

	if (N < K) {
		cout << 0 << endl;
		return 0;
	}
	if ((N - K) < K) {
		K = N - K;
		is_symmetry = 1;
	}

	if (!K) {
		cout << 1 << endl;
		for (int i = 1; i <= N; ++i) {
			cout << i << " ";
		}
		cout << endl;
		return 0;
	}

	dfs(0, true);
	cout << count << endl;
	dfs(0, false);
	return 0;
}
