#include <iostream>
#include<vector>
using namespace std;

class Graph
{
	private:
	int V;
	int E;
	int dir_flag;

	public:
	Graph(); // constructor
	Graph(int n, bool flag); // overloaded constructor

	#define SIZE 1000
	vector <pair<int,int>> adj[SIZE]; //adjacency list

	void AddEdge(int u, int v, int w, int dir_flag); // utilitity function for adding edge

	vector<int> visit; // visit vector
	vector<int> colours;

	void Pgraph();

	// getters for V and E
	int getV()
	{
		return V;
	}

	int getE()
	{
		return E;
	}
	void setV(int x)
	{
		V = x;

	};

	// utility functions for module 5
	int ret_size();
	int ret_edge();
	bool detectCycle(int v, int parent, int counter);
	void removeMaxEdge(int start, int end);

};

class Edge
{
	private:
	int source;
	int dest;
	int weight;

	public:

	// getters and setters
	void setter(int s, int d, int w)
	{
		source= s;
		dest = d;
		weight = w;
	}

	// utility functions for module 3
	int getsource()
	{
		return source;
	}

	int getdest()
	{
		return dest;
	}

	int getweight()
	{
		return weight;
	}
};

// Module 1:

void DFS(Graph G);
void DFS(Graph G, int s);
int DFS(Graph G, int s, int t);


// Module 2:

void BFS(Graph G);
void BFS(Graph G,int s);
int BFS(Graph G,int s,int t);


// Module 3:

void BFS_SPATH(Graph G, int s, int flag);
void Fix_Graph(Graph *G);
void LPATH(Graph T,int flag);

// returns Topologically sorted vector.
void Topological_Ordering (Graph G, vector<int>& TPV);
pair<int,int> bfs(int s, Graph T); // utility function for LPATH, returns maximum distance vertex from s and it's distance.
pair<int,int> lpath_s(int s, vector<int>&TPV, Graph G, int *path);

// Max weight MST using krushkal
void MAX_Weight_MST(Graph G);
void fillup_edges(Edge edges[], Graph G); // utility function for MST
int comp_edge(const void* e1, const void* e2); // utility function for qsort


// Module 4:

// functions to check whether a graph is bipartite or not
int biparty(Graph G, int src);
int Test_bipartite(Graph G);

// functions to find all the articulation points in a graph
void APUtil(int u, bool visited[], int disc[],int low[], int parent[], bool ap[],Graph G);
void Test_articulationpoints(Graph G);

// functions to find all bridges in a graph
void bridges_till(int u, int disc[],Graph G ,int low[],vector<vector<int>>&op);
void Test_bridges(Graph G);


// Module 5:

Graph MST_Prim(Graph G);
void MST_Kruskal(Graph G);
Graph MST_yourAlgo(Graph G);