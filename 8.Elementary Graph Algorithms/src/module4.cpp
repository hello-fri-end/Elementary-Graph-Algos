#include "include/graph.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int biparty(Graph G, int src) 
{ 
	// init visit vector to zero

	for(int i = 0; i < (int)G.visit.size(); i++)
		G.visit[i] = 0;
	
 
   
	G.colours[src] = 1;//colouring starting vertex

	G.visit[src] = 1;		// visiting starting vertex

  	 	
  	// Create a queue for BFS
	queue <int> q; 

	//push starting vertex
	q.push(src); 
  	
	// iterating till stack is empty
	while (!q.empty()) 
	{  
		src = q.front(); 
		q.pop(); 

	if(!G.visit[src])
	{
		G.visit[src] = 1;
	}
		for (auto i = G.adj[src].begin(); i != G.adj[src].end(); ++i)
		{ 
			
			if (i->first == src ) //to check self loop
			return 0;  	
			if (G.colours[i->first] == -1) 
			{ 
				
				// giving alt. colour to adj. vertex
				G.colours[i->first] = 1 - G.colours[src]; 
				q.push(i->first); 
			} 
  
			
 			else if (G.colours[i->first] == G.colours[src]) 
				return 0; 
		} 
	} 
  
	return 1; 
}

int Test_bipartite(Graph G)
{
	for (int i = 0; i < (int)G.colours.size(); ++i) 
		G.colours[i] = -1; 
	for (int i = 0; i < (int)G.colours.size(); i++)
	{
		if (G.colours[i] == -1 && biparty(G, i) == 0)
			return 0;
	}
	return 1;
}

void APUtil(int u, bool visited[], int disc[],int low[], int parent[], bool ap[],Graph G) 
{ 
	// A static variable is used for simplicity, we can avoid use of static 
	// variable by passing a pointer. 
	static int time = 0; 
  
	// Count of children in DFS Tree 
	int children = 0; 
  
	// Mark the current node as visited 
	visited[u] = true; 
  
	// Initialize discovery time and low value 
	disc[u] = low[u] = ++time; 
  
	// Go through all vertices aadjacent to this  
	for (auto i = G.adj[u].begin(); i != G.adj[u].end(); ++i) 
	{ 
		int v = i->first;  // v is current adjacent of u 
  
		// If v is not visited yet, then make it a child of u 
		// in DFS tree and recur for it 
		if (!visited[v]) 
		{ 
			children++; 
			parent[v] = u; 
			APUtil(v, visited, disc, low, parent, ap,G); 
  
			// Check if the subtree rooted with v has a connection to 
			// one of the ancestors of u 
			low[u]  = min(low[u], low[v]); 
  
			// u is an articulation point in following cases 
  
			// (1) u is root of DFS tree and has two or more chilren. 
			if (parent[u] == -1 && children > 1) 
			   ap[u] = true; 
  
			// (2) If u is not root and low value of one of its child is more 
			// than discovery value of u. 
			if (parent[u] != -1 && low[v] >= disc[u]) 
			   ap[u] = true; 
		} 
  
		// Update low value of u for parent function calls. 
		else if (v != parent[u]) 
			low[u]  = min(low[u], disc[v]); 
	} 
}

// The function to do DFS traversal. It uses recursive function APUtil() 
void Test_articulationpoints(Graph G) 
{ 
	// Mark all the vertices as not visited 
	int flag = 0;
	bool *visited = new bool[G.colours.size()]; 
	int *disc = new int[G.colours.size()]; 
	int *low = new int[G.colours.size()]; 
	int *parent = new int[G.colours.size()]; 
	bool *ap = new bool[G.colours.size()]; // To store articulation points 
  
	// Initialize parent and visited, and ap(articulation point) arrays 
	for (int i = 0; i < (int)G.colours.size(); i++) 
	{ 
		parent[i] = -1; 
		visited[i] = false; 
		ap[i] = false; 
	} 
  
	// Call the recursive helper function to find articulation points 
	// in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < (int)G.colours.size(); i++) 
		if (visited[i] == false) 
			APUtil(i, visited, disc, low, parent, ap,G); 
  
	// Now ap[] contains articulation points, print them 
	for (int i = 0; i < (int)G.colours.size(); i++) 
		{
			if (ap[i] == true) 
		   	{
				if(flag == 0)
					cout<< "Articulation points of the graph are: "<<endl;
				flag = 1;
			 	cout << i << " ";
			} 
		}
	cout<<endl;
	if(flag == 0)
	{
		cout<<"No articulation points are present in the graph. "<<endl;
	}
}


void bridges_till(int u, int disc[],Graph G ,int low[],vector<vector<int>>&op) 
{ 
	// A static variable is used for simplicity, we can  
	// avoid use of static variable by passing a pointer. 
	static int time = 0;
	int flag = 0;
	 
	// Mark the current node as visited 
	G.visit[u] = 1; 
  
	// Initialize discovery time and low value 
	disc[u] = low[u] = ++time; 
  
	// Go through all vertices aadjacent to this  
	for (auto i = G.adj[u].begin(); i != G.adj[u].end(); ++i) 
	{ 
		int v = i->first;  // v is current adjacent of u 
  
		// If v is not visited yet, then recur for it 
		if (!G.visit[v]) 
		{ 
			G.colours[v] = u; 
			bridges_till(v, disc,G, low,op); 
  
			// Check if the subtree rooted with v has a  
			// connection to one of the ancestors of u 
			low[u]  = min(low[u], low[v]); 
  
			// If the lowest vertex reachable from subtree  
			// under v is  below u in DFS tree, then u-v  
			// is a bridge 
			if (low[v] > disc[u]) 
			{
				for(int i = 0; i < (int)op.size();i++)
				{
					if((v == op[i][0]&& u == op[i][1])||(v == op[i][1] && u == op[i][0]))
						{
							flag = 1;
							break;
						}
				}
				if(flag == 0)
				{
					op.push_back(vector<int>());
					op.back().push_back(u);
					op.back().push_back(v);
				}					 
			} 
		
  		}
		// Update low value of u for parent function calls. 
		else if (v != G.colours[u]) 
			low[u]  = min(low[u], disc[v]); 
	} 
}

void Test_bridges(Graph G) 
{ 
	// Mark all the vertices as not visited 
	int *disc = new int[G.visit.size()]; 
	int *low = new int[G.visit.size()]; 
	vector<vector<int>>op;
	int x = 0;
	
	// Initialize parent and visited, and ap(articulation point) arrays 
	for (int i = 0; i < (int)G.visit.size(); i++) 
	{ 
		G.colours[i] = -1;//used as parent
		G.visit[i] = 0;
	} 
  
	/* Call the recursive helper function to find articulation points 
	 in DFS tree rooted with vertex 'i' */
	for (int i = 0; i < (int)G.visit.size(); i++)
	{
		if (G.visit[i] == 0) 
			bridges_till(i,  disc,G, low,op);
	}
	for(int i = 0 ; i < (int)op.size();i++)
	{
		if(i == 0)
			cout<<"Bridges in graph:"<<endl;
		cout<<op[i][0]<<" " << op[i][1]<<endl;
		x = i + 1;
	}
		if(x == 0)
			cout<<"There are no bridges in graph."<<endl;
}
