#include <iostream>

#define V_MAX 10

using namespace std;

/* Simple example of how to use nonrecursive DFS */

int array[V_MAX][V_MAX];
int stack[V_MAX];
int top;
int visited[V_MAX];

void print_stack(int *stack, int sz)
{
	cout << "Stack: ";
	for (int i = 0; i < sz; ++i) {
		cout << stack[i]+1 << " ";
	}
	cout << endl;
}

int main()
{
	int N, S, current;

	cin >> N >> S;
	cout << N << " " << S << endl;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> array[i][j];
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	stack[top++] = S-1;
	visited[S-1] = 1;

	while (top) {
		current = stack[top-1];
		bool found = false;

		for (int i = 0; i < N; ++i) {
			if (array[current][i] && !visited[i]) {
				stack[top++] = i;
				visited[i] = 1;
				found = true;
				break;
			}
		}
		if (!found) {
			top--;
		}
		print_stack(stack, top);
	}

	return 0;
}
