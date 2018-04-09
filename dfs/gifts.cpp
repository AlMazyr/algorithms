#include <iostream>

#define V_MAX 100

using namespace std;

int stack_flags[V_MAX];
int top;
int N, K;
int is_symmetry;

void dfs(int start)
{
	if (top == K) {
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
		dfs(i);
		stack_flags[i-1] = 0;
		top--;
	}
}

int main()
{
	cin >> N >> K;
	double res = 1;

	if (N < K) {
		cout << 0 << endl;
		return 0;
	}
	if ((N - K) < K) {
		K = N - K;
		is_symmetry = 1;
	}
	for (int i = 1; i <= K; ++i) {
		res *= (N - i + 1) / (double)i;
	}
	cout << (int)res << endl;
	if (K) {
		dfs(0);
	} else {
		for (int i = 1; i <= N; ++i) {
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}
