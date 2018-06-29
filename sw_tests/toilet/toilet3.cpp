#include <iostream>

#define MAX_HEAP	10000
#define MAX_N		20000
#define MAX_USERID	1000000
#define IN		1
#define OUT		2

using namespace std;

struct Hole {
	unsigned int key;
	int st;
	int len;
};

struct Keys {
	unsigned int l;
	unsigned int r;
};

int N, M;
int users[MAX_USERID];
Keys cabs[MAX_N];
int heap_sz;
Hole heap_tmp, heap[MAX_HEAP];

#define swap(l,r) do{heap_tmp = l; l = r; r = heap_tmp;} while (0)

void print_heap()
{
	for (int i = 0; i < heap_sz; ++i)
		cout << heap[i].st << ':' << heap[i].len << ' ';
	cout << endl;
}

int sift_up(int pos)
{
	if (!pos)
		return 0;
	int par = (pos - 1) / 2;
	if (heap[pos].key > heap[par].key) {
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

	if (left < heap_sz && heap[left].key > heap[largest].key)
		largest = left;
	if (right < heap_sz && heap[right].key > heap[largest].key)
		largest = right;
	if (largest != pos) {
		swap(heap[pos], heap[largest]);
		sift_down(largest);
	}
}

int insert(Hole &el)
{
	heap[heap_sz++] = el;
	return sift_up(heap_sz-1);
}

Hole extract(int pos)
{
	Hole ans = heap[pos];

	heap[pos] = heap[--heap_sz];
	if (pos != 0 && heap[pos].key > heap[(pos-1)/2].key)
		sift_up(pos);
	else
		sift_down(pos);
	return ans;
}

unsigned int calc_key(int st, int len)
{
	int score1, score2;
	if (st == 0 || ((st+len-1) == M-1))
		score1 = len;
	else
		score1 = (len+1) / 2;
	score2 = M - st;
	return (score1 << 16) | score2;
}

Hole search_hole(unsigned int key)
{
	for (int i = 0; i < heap_sz; ++i)
		if (heap[i].key == key)
			return extract(i);
	return {0,0,0};
}

int occupy_cabin(int id)
{
	Hole h = extract(0);
	int pos, end = h.st + h.len - 1;
	if (h.st == 0)
		pos = h.st;
	else if (end == N-1)
		pos = end;
	else
		pos = ((h.len - 1) / 2) + h.st;

	Hole h1 = h, h2 = h;
	h1.len = pos - h1.st;
	h2.st = pos + 1;
	h2.len = end - pos;
	h1.key = calc_key(h1.st, h1.len);
	h2.key = calc_key(h2.st, h2.len);
	if (h1.key >> 16)
		insert(h1);
	if (h2.key >> 16)
		insert(h2);
	users[id] = pos;
	cabs[pos] = {h1.key, h2.key};
	return pos+1;
}

void free_cabin(int id)
{
	Keys k = cabs[users[id]];
	Hole hl = {0, users[id], 0}, hr = {0, users[id], 0};

	if (k.l >> 16)
		hl = search_hole(k.l);
	if (k.r >> 16)
		hr = search_hole(k.r);

	Hole h = {0, hl.st, hl.len + hr.len + 1};
	h.key = calc_key(h.st, h.len);
	insert(h);
	cabs[users[id]] = {0, 0};
	users[id] = 0;
}

int exec_test()
{
	int ans = 0;
	unsigned int key = calc_key(0, N);
	Hole el = {key, 0, N};
	insert(el);
	for (int j = 0; j < M; ++j) {
		int id, dir;
		cin >> dir >> id;
		if (dir == IN)
			ans += occupy_cabin(id);
		else
			free_cabin(id);
		print_heap();
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tests_num;
	cin >> tests_num;

	for (int i = 0; i < tests_num; ++i) {
		cin >> N >> M;
		cout << '#' << i+1 << ' ' << exec_test() << endl;
	}

	return 0;
}
