#include <iostream>

using namespace std;

typedef unsigned int Weight;
typedef int Vertex;
typedef int Score;

struct Edge {
	Edge() : v1(0), v2(0), w(0) {}
	Edge(Vertex vt1, Vertex vt2, Weight wt) : v1(vt1), v2(vt2), w(wt) {}
	Vertex v1;
	Vertex v2;
	Weight w;
#ifdef DEBUG
	void print()
	{
		cout << v1 << ":" << v2 << ":" << w <<  endl;
	}
#endif
};

struct VertexScore {
	VertexScore() : v(-1), sc(0) {}
	VertexScore(Vertex vertex, Score score) : v(vertex), sc(score) {}
	Vertex v;
	Score sc;
#ifdef DEBUG
	void print()
	{
		cout << v << " " << sc << endl;
	}
#endif
};

class Stack {
public:
	Stack(int max) : max_sz(max), stack(new VertexScore[max]), top_p(-1)
	{
	}

	~Stack()
	{
		delete[] stack;
	}

	void push(VertexScore &x)
	{
		if (top_p == (max_sz - 1))
			return;
		stack[++top_p] = x;
	}

	VertexScore pop()
	{
		if (top_p == -1)
			return VertexScore();
		return stack[top_p--];
	}

	VertexScore top()
	{
		return stack[top_p];
	}

	bool is_empty()
	{
		return (top_p == -1) ? true : false;
	}
#ifdef DEBUG
	void print() const
	{
		for (int i = 0; i < top_p + 1; ++i)
		{
			cout << stack[i].v << ":" << stack[i].sc << " ";
		}
		cout << endl;
	}
#endif
private:
	int max_sz;
	VertexScore *stack;
	int top_p;
};


struct AdjListNode {
	Vertex v;
	Weight w;
	AdjListNode *next;
};

struct AdjList {
	AdjListNode *head;
};

class Graph {
public:
	Graph() : v_num(0), array(NULL) {}

	Graph(int v) : v_num(v)
	{
		array = new AdjList[v_num];
		// init graph wothout edges
		for (int i = 0; i < v_num; ++i) {
			array[i].head = NULL;
		}
	}

	~Graph()
	{
		// delete every linked list in the array
		for (int i = 0; i < v_num; ++i) {
			AdjListNode *current = array[i].head;
			AdjListNode *next;
			while (current != NULL) {
				next = current->next;
				delete current;
				current = next;
			}
		}
		// delete array
		delete[] array;
	}

	void add_edge(Vertex v1, Vertex v2, Weight w)
	{
		AdjListNode *node = create_node(v2, w);
		// v1 -> v2 edge
		node->next = array[v1 - 1].head;
		array[v1 - 1].head = node;
		// v2 -> v1 edge
		node = create_node(v1, w);
		node->next = array[v2 - 1].head;
		array[v2 - 1].head = node;
	}

	void delete_edge(Vertex v1, Vertex v2)
	{
		AdjListNode *current = array[v1 - 1].head;

		// find and delete first node
		delete_node(&(array[v1 - 1].head), v2);

		// find and delete second node
		delete_node(&(array[v2 - 1].head), v1);
	}

	VertexScore dfs(Vertex src_v)
	{
		Stack stack(v_num);
		bool *visited = new bool[v_num];
		//Vertex v_max = src_v;
		VertexScore vs_max(src_v, 0);

		for (int i = 0; i < v_num; ++i)
		{
			visited[i] = false;
		}
		stack.push(vs_max);
		visited[src_v - 1] = true;

		while (!stack.is_empty()) {
			VertexScore vs = stack.top();
			bool found = false;

			// iterate throught all adjacent vertices
			AdjListNode *current = array[vs.v - 1].head;
			while (current != NULL) {
				if (!visited[current->v - 1])
				{
					// found new unvisited vertex
					VertexScore vs_new(current->v, vs.sc + current->w);
					stack.push(vs_new);
					visited[vs_new.v - 1] = true;
					found = true;
					if (vs_new.sc > vs_max.sc) {
						// found new max score
						vs_max.v = vs_new.v;
						vs_max.sc = vs_new.sc;
					}
					break;
				}
				current = current->next;
			}
			if (!found) {
				stack.pop();
			}
#ifdef DEBUG
			stack.print();
#endif
		}

		delete[] visited;
		return vs_max;
	}

	unsigned int find_lp(Vertex src_v)
	{
		VertexScore vs = dfs(src_v);
		vs = dfs(vs.v);
		return vs.sc;
	}

#ifdef DEBUG
	void print() const
	{
		for (int i = 0; i < v_num; ++i) {
			cout << i + 1 << ": ";
			AdjListNode *current = array[i].head;
			while (current != NULL) {
				cout << "(" << current->v << " "
					<< current->w << ") ";
				current = current->next;
			}
			cout << endl;
		}
	}
#endif
private:
	AdjListNode* create_node(Vertex v, Weight w)
	{
		AdjListNode *node = new AdjListNode;
		node->v = v;
		node->w = w;
		return node;
	}

	void delete_node(AdjListNode **head, Vertex v)
	{
		AdjListNode *current = *head;
		AdjListNode *prev = NULL;

		while (current->v != v && current->next != NULL) {
			prev = current;
			current = current->next;
		}
		if (current->v == v) {
			if (prev) {
				prev->next = current->next;
			} else {
				*head = current->next;
			}
			delete current;
		}
	}

	int v_num; 		// number of vertices in a graph
	AdjList *array;		// array of linked lists
};

int main(int argc, char *argv[])
{
#ifdef GRAPH_TEST
	Graph g1(4);

	g1.add_edge(1, 2, 100);
	g1.add_edge(1, 3, 200);
	g1.add_edge(1, 4, 500);

	g1.print();

	g1.delete_edge(1, 3);

	g1.print();

	// dfs test
	cout << endl;
	unsigned int ans;
	ans = g1.find_lp(1);
	cout << ans << endl;
#endif

#ifdef MAIN
	int tests_number;
	int vertices_number;
	int edges_number;
	Edge *edge_array = NULL;

	cin >> tests_number;

	for (int i = 0; i < tests_number; ++i) {
		unsigned int graph_max = 0;
		cin >> vertices_number;
		Graph g(vertices_number);
		edges_number = vertices_number - 1;
		edge_array = new Edge[edges_number];

		// build graph and array of edges
		for (int j = 0; j < edges_number; ++j) {
			Weight w;
			Vertex v1, v2;
			cin >> w >> v1 >> v2;

			Edge e(v1, v2, w);
			edge_array[j] = e;
			g.add_edge(v1, v2, w);
		}
#ifdef DEBUG
		g.print();
		cout << endl;
		for (int j = 0; j < edges_number; ++j) {
			edge_array[j].print();
		}
#endif
		// iterate over edges
		for (int j = 0; j < edges_number; ++j) {
			g.delete_edge(edge_array[j].v1, edge_array[j].v2);
			unsigned int max1, max2, res_max;

			// find max path on every peace
			max1 = g.find_lp(edge_array[j].v1);
			max2 = g.find_lp(edge_array[j].v2);
			res_max = max1 + max2 + edge_array[j].w;
			if (res_max > graph_max) {
				graph_max = res_max;
			}
			g.add_edge(edge_array[j].v1, edge_array[j].v2, edge_array[j].w);
		}
		delete[] edge_array;
		
		// test answer
		cout << "#" << i + 1 << " " << graph_max << endl;
	}
#endif
	return 0;
}
