/*
* Module 1
*
* DFS(Graph G) -- choose start vertex arbitrarily and perform DFS
* DFS(Graph G, vertex s)
* DFS(Graph G, vertex s, vertex t) -- is t reachable from s
*/

#include "include/graph.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

void DFS(Graph G)
{
	srand(time(0));
	// random integer in range[0..(|V|-1)]
	int s = rand() % (int)G.visit.size();
	// init visit vector to zero
	G.visit.assign(G.visit.size(), 0);
	G.visit[s] = 1;		//visiting starting vertex

	// Create a stack for DFS
	stack<int> stack;

	//push starting vertex
	stack.push(s);

	// iterating till stack is empty
	while(!stack.empty())
	{
		s = stack.top();
		stack.pop();
		cout << s << " ";

		if(!G.visit[s])
		{
			G.visit[s] = 1;
		}

		for (auto i = G.adj[s].begin(); i != G.adj[s].end(); ++i)
		{
			if (!G.visit[i->first])
				stack.push(i->first);
		}
	}
}

void DFS(Graph G, int s)
{
	// init visit vector to zero
	G.visit.assign(G.visit.size(), 0);

	G.visit[s] = 1;		// visiting starting vertex

	// Create a stack for DFS
	stack<int> stack;
	
	//push starting vertex
	stack.push(s);

	// iterating till stack is empty
	while(!stack.empty())
	{
		s = stack.top();
		stack.pop();
		cout << s << " ";
		
		if(!G.visit[s])
		{
			G.visit[s] = 1;
		}

		for (auto i = G.adj[s].begin(); i != G.adj[s].end(); ++i)
		{
			if (!G.visit[i->first])
				stack.push(i->first);
		}
	}
}

int DFS(Graph G, int s, int t)
{
	if(s == t)
		return 1;

	// init visit vector to zero
	G.visit.assign(G.visit.size(), 0);

	G.visit[s] = 1;		// visiting starting node

	// Create a stack for DFS
	stack<int> stack;
	
	//push starting vertex
	stack.push(s);

	// iterating till stack is empty
	while(!stack.empty())
	{
		s = stack.top();
		stack.pop();

		if(!G.visit[s])
			G.visit[s] = 1;

		// for all adjacent nodes, either push them in the stack or return if target vertex found
		for (auto i = G.adj[s].begin(); i != G.adj[s].end(); ++i)
		{
			// check whether adjacent node is t
			if(i->first == t)
				return 1;
		
			// else push them to the stack
			if (!G.visit[i->first])
				stack.push(i->first);
		}
	}

	// if t couldnt be reached from s
	return 0;
}