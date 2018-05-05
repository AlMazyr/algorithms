#include <iostream>

#define V_MAX 100

using namespace std;

int stack_flags[V_MAX];
int top;
int N, K;
int use_symmetry;

void dfs(int start)
{
	if (top == K) {
		for (int i = 0; i < N; ++i) {
			if (stack_flags[i] ^ use_symmetry) {
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
	int count = 1;
	cin >> N >> K;

	if (N < K) {
		cout << 0 << endl;
		return 0;
	}
	if ((N - K) < K) {
		K = N - K;
		use_symmetry = 1;
	}

	if (!K) {
		cout << 1 << endl;
		for (int i = 1; i <= N; ++i) {
			cout << i << " ";
		}
		cout << endl;
		return 0;
	}

	for (int i = 1; i <= K; ++i) {
		count = ((N + 1 - i) * count) / i;
	}

	cout << count << endl;
	dfs(0);
	return 0;
}
