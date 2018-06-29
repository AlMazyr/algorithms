#include <iostream>

#define MAX_HEAP	1000

using namespace std;

int heap_sz, tmp;
int heap[MAX_HEAP];

#define swap(l,r) do{tmp = l; l = r; r = tmp;} while (0)

int sift_up(int pos)
{
	if (!pos)
		return 0;
	int par = (pos - 1) / 2;
	if (heap[pos] > heap[par]) {
		swap(heap[pos], heap[par]);
		pos = sift_up(par);
	}
	return pos;
}

void sift_down(int pos)
{
	int left = 2 * pos + 1;
	int right = 2 * pos + 2;
	int largest = pos;

	if (left < heap_sz && heap[left] > heap[largest])
		largest = left;
	if (right < heap_sz && heap[right] > heap[largest])
		largest = right;
	if (largest != pos) {
		swap(heap[pos], heap[largest]);
		sift_down(largest);
	}
}

int insert(int key)
{
	heap[heap_sz++] = key;
	return sift_up(heap_sz-1);
}

int extract(int pos)
{
	int ans = heap[pos];

	heap[pos] = heap[--heap_sz];
	if (pos != 0 && heap[pos] > heap[(pos-1)/2])
		sift_up(pos);
	else
		sift_down(pos);
	return ans;
}

void print_heap()
{
	for (int i = 0; i < heap_sz; ++i)
		cout << heap[i] << ' ';
	cout << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


	return 0;
}
