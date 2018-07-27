#include <iostream>

#define MAX_HEAP	10000
#define MAX_N		20001
#define MAX_USERID	1000000
#define IN		1

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
	unsigned int score1, score2;
	if (st == 0 || ((st+len-1) == N-1))
		score1 = len;
	else
		score1 = (len+1) / 2;
	score2 = N - st;
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
	// get biggest hole
	Hole h = extract(0);
	// calculate cabin position in the hole
	int pos, end = h.st + h.len - 1;
	if (h.st == 0)
		pos = h.st;
	else if (end == N-1)
		pos = end;
	else
		pos = ((h.len - 1) / 2) + h.st;
	// calculate new holes
	Hole hl = h, hr = h;
	hl.len = pos - hl.st;
	hr.st = pos + 1;
	hr.len = end - pos;
	if (hr.len < 0)
		hr.len = 0;
	hl.key = calc_key(hl.st, hl.len);
	hr.key = calc_key(hr.st, hr.len);
	if (hl.key >> 16)
		insert(hl);
	if (hr.key >> 16)
		insert(hr);
	// update keys for the new holes
	if (hl.st != 0)
		cabs[hl.st-1].r = hl.key;
	if (hr.st + hr.len - 1 != N - 1)
		cabs[hr.st+hr.len].l = hr.key;
	users[id] = pos;
	cabs[pos] = {hl.key, hr.key};
	return pos+1;
}

void free_cabin(int id)
{
	// find cabin
	Keys k = cabs[users[id]];
	// extract left and right holes
	Hole hl = {0, users[id], 0}, hr = {0, users[id], 0};
	if (k.l >> 16)
		hl = search_hole(k.l);
	if (k.r >> 16)
		hr = search_hole(k.r);
	// merge left and right to new hole
	Hole h = {0, hl.st, hl.len + hr.len + 1};
	h.key = calc_key(h.st, h.len);
	insert(h);
	// update keys for new hole
	if (h.st != 0)
		cabs[h.st-1].r = h.key;
	if (h.st + h.len - 1 != N - 1)
		cabs[h.st+h.len].l = h.key;
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
	}
	heap_sz = 0;
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
