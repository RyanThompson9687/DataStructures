#include <iostream>
#include <stack>
#include <list>
using namespace std;

class Graph {
  int V; // Num of vertices

  // Pointer to an array containing adjacency lists
  list<int> *adj;

public:
  Graph(int V); // constructor

  // function to add an edge to graph
  void addEdge(int v, int W);

  // prints BFS traversal from a given source s
  void BFS(int s);

  // print DFS traversal from a given source x
  void DFS(int x);
};

Graph::Graph(int V) {
  this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to the end of v’s list
}

void Graph::BFS(int s) {
  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  // init to false
  for(int i = 0; i < V; i++) {
    visited[i] = false;
  }

  // Create a queue for BFS
	list<int> queue;

  // Mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push_back(s);

  // 'i' will be used to get all adjacent vertices of a vertex
	list<int>::iterator i;

  while(!queue.empty()) {
    // Dequeue a vertex from queue and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

    /* Get all adjacent vertices of the dequeued vertex s. If a adjacent has not been visited, then mark it visited and enqueue it */

    for (i = adj[s].begin(); i != adj[s].end(); i++) {
      if (!visited[*i]) {
        visited[*i] = true;
				queue.push_back(*i);
      }
    }
  }
}

void Graph::DFS(int x) {
  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  // init to false
  for(int i = 0; i < V; i++) {
    visited[i] = false;
  }

  // create a stack for DFS
  stack<int> stack;

  // Mark the current node as visited and push it to the stack
  visited[x] = true;
  stack.push(x);

  // index for all adjacent vertices of a vertex
  list<int>::iterator i; // creating an int variable from adjaceny list, this iterator variable looks at the element itself in memory instead of the index

  while (!stack.empty()) {
    // Pop a vertex from stack and print it
    x = stack.top();
    cout << x << " ";
    stack.pop();

    // Get all adjacent vertices of the popped vertex x. If an adjacent vertex has not been visited, then mark it visited and push it

    for (i = adj[x].begin(); i != adj[x].end(); i++) {
      if (!visited[*i]) {
        visited[*i] = true;
				stack.push(*i);
      }
    }
  }
}

int main() {
  // Create a graph given in the above diagram
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Breadth First Traversal " << "(starting from vertex 2)\n";
	g.BFS(2);

  cout << endl;

  Graph G(4);
	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(1, 2);
	G.addEdge(2, 0);
	G.addEdge(2, 3);
	G.addEdge(3, 3);

  cout << "Deapth First Traversal: " << "(starting from vertex 2)" << endl;
  G.DFS(2);

	return 0;
}
