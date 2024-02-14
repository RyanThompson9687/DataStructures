/*
  Project3.cpp
  Ryan Thompson
  COP4415
  Last Modified: 12/5/2022
*/

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Graph {
  // Number of vertices
  int V;

  // Adjacency list representation
  // Pair of a neighbor vertex and a weight for every edge
  list <pair<int, int> > *adj;

public:
  Graph(int V);

  // Function to add an edge to graph
  void addEdge(int u, int v, int w);

  // Print MST using Prim's algorithm
  void primMST();
};

// Allocates memory for adjacency list
Graph::Graph(int V) {
  this->V = V;
  adj = new list< pair<int, int>> [V];
}

void Graph::addEdge(int u, int v, int w) {
  adj[u].push_back(make_pair(v,w));
  adj[v].push_back(make_pair(u,w));
}

void Graph::primMST() {
  // create a priority queue (min heap) to store vertices in MST
  priority_queue < pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;

  // set vertex 0 as source
  int src = 0;

  // int vector for all the keys and set it to an arbitrary large number above weights
  vector<int> key(V, 1000);

  // int vector to hold parent array that holds MST
  vector<int> parent(V, -1);

  // keeps track of vertices in MST
  vector<bool> inMST(V, false);

  // Insert source in priority queue and initialize key to 0
  pq.push(make_pair(0, src));
  key[src] = 0;

  // Loop until priority queue is empty
  while (!pq.empty()) {
    // pops the first vertex in the pair (min key)
    int u = pq.top().second;
    pq.pop();

    // if the vertex is in the mst, continue
    if(inMST[u] == true) {
      continue;
    }
    
    inMST[u] = true;  // Include vertex in MST

    // 'i' is used to get all adjacent vertices of a vertex
    list< pair<int, int> >::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      // get label and weight of current vertex adjacent of u
      int v = (*i).first;
      int weight = (*i).second;

      //  if v is not in MST and weight of (u,v) is smaller than current key of v
      if (inMST[v] == false && key[v] > weight) {
        // ppdate v key
        key[v] = weight;
        pq.push(make_pair(key[v], v));
        parent[v] = u;
      }
    }
  }
  // print edges of MST using parent array
  for (int i = 1; i < V; ++i) {
    printf("%d - %d\n", parent[i], i);
  }
}

int main() {
  int V = 8;
  Graph g(V);
  g.addEdge(0, 1, 5);
  g.addEdge(0, 4, 8);
  g.addEdge(1, 2, 8);
  g.addEdge(1, 7, 11);
  g.addEdge(2, 3, 7);
  g.addEdge(2, 7, 2);
  g.addEdge(3, 6, 9);
  g.addEdge(3, 5, 14);
  g.addEdge(4, 5, 10);
  g.addEdge(5, 6, 2);
  g.addEdge(6, 7, 3);
  g.primMST();
  return 0;
}
