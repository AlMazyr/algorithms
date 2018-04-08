#include <iostream>

#define V_MAX 100

using namespace std;

int stack[V_MAX];
int top;
int N, K;

void dfs(int start)
{
	if (top == K) {
		for (int i = 0; i < top; ++i) {
			cout << stack[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = start+1; i <= N; ++i) {
		stack[top++] = i;
		dfs(i);
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
	K = ((N - K) < K) ? (N - K) : K;
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
