#include "include/graph.h"
#include <iostream>
#include <vector>
#include <deque>
#include <ctime> //this is for rand function seeding

void BFS(Graph G)
{
	srand(time(0));
	int s=rand() % G.visit.size();
	vector <int> visited ;
	visited.assign(G.visit.size(),0);

	// Create a queue for BFS using deque which is sam as vector with more functionsuch as push and pop
	deque  <int> queue;

	// Mark the current node as visited and enqueue it
	visited[s] = 1;
	queue.push_back(s);
	// cout<<"value"<<queue.at(0);
	// 'i' will be used to get all adjacent

	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		s = queue.at(0);
		queue.pop_front();
		cout << s << " ";
		for (auto i = G.adj[s].begin(); i!= G.adj[s].end(); i++)
		{
			if (visited[i->first]==0)
			{
				visited[i->first] = 1;
				queue.push_back(i->first);
			}
		}
	}
}

void BFS(Graph G, int s) 
{
	vector <int> visited;
	visited.assign(G.visit.size(),0);

	// Create a queue for BFS using deque which is sam as vector with more functionsuch as push and pop
	deque <int> queue;

	// Mark the current node as visited and enqueue it
	visited[s] = 1;
	queue.push_back(s);
	//cout<<"value"<<queue.at(0);
	// 'i' will be used to get all adjacent

	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		s = queue.at(0);
		queue.pop_front();
		cout << s << " ";
		for (auto i = G.adj[s].begin(); i!= G.adj[s].end(); i++)
		{
			if (visited[i->first]==0)
			{
				visited[i->first] = 1;
				queue.push_back(i->first);
			}
		}
	}
}

int BFS(Graph G,int s,int t) 
{
	vector <int > visited ;
	visited.assign(G.visit.size(),0);
	// Create a queue for BFS using deque which is same as vector with more function such as push and pop
	deque <int> queue;

	// Mark the current node as visited and enqueue it 
	visited[s] = 1;
	queue.push_back(s);
	// 'i' will be used to get all adjacent

	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.at(0); 
		queue.pop_front(); 
		for (auto i = G.adj[s].begin(); i!= G.adj[s].end(); i++) 
		{
			if (visited[i->first] == 0) 
			{
				visited[i->first] = 1; 
				queue.push_back(i->first); 
			}

		}
	}

	if(visited[t]==1)//if t is visited
		return(1);
	else
		return(0);
}
