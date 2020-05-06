#include"include/graph.h"
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//constructor
Graph:: Graph()
{
	E = 0;

	cout << "Enter no. of vertices:" << endl;
	cin >> V;

	//prompt whether graph is directed or undirected
	cout << "Press 1 if graph is directed, 0 otherwise:";
	cin >> dir_flag;

	//prompt for edges
	int check=1;
	int u,v,w;

	cout << "Enter edges" << endl;
	while(check != 0)
	{
		cout << "Enter u,v & w: ";
		cin >> u >> v >> w;
		AddEdge(u, v, w, dir_flag);
		cout << "Press 1 to add another edge, otherwise 0:";
		cin >> check;
	}

	//initilize visit array to zero
	visit.assign(V,0);
	colours.assign(V,0);
};

//overloaded constructor
Graph::Graph(int n, bool flag)
{
    V = n;
    E = 0;

    visit.resize(n);
    for(int i = 0; i < V; i++)
		visit[i] = 0;

    dir_flag = flag;
}

//utility function to add edge to the graph
void Graph::AddEdge(int u, int v, int w, int dir_flag)
{
	if( u == v)
		return;
	
    E++;
	adj[u].push_back(make_pair(v,w));
	//if undirected
	if(dir_flag == 0)
		adj[v].push_back(make_pair(u,w));
}
//returns the no. of vertices
int Graph::ret_size()
{
	return V;
}
//returns the no. of edges
int Graph::ret_edge()
{
	return E;
}
/*Removes the maximum edge from a cycle.
  The start point and the end point of
    the cycle are passed as arguments     */
void Graph::removeMaxEdge(int start, int end)
{
	int v = start;

	int max_edge;
	pair<int,int>max_pair;

    //intializes the max edge to be the edge connecting the start and the end vertex
	for(int i=0; i<(int)adj[end].size();i++)
		if(adj[end][i].first == start)
		{
			max_edge = adj[end][i].second;
			max_pair = make_pair(end,start);
		}

    //this loop traverses from the start vertex all the way to the end vertex along the cycle and gets the maximum edge
	while(1)
	{
		for(int i=0; i<(int)adj[v].size(); i++)
		{
			if( visit[ adj[v][i].first ] - visit[v] == 1 )
			{
				if( adj[v][i].second > max_edge)
				{
					max_pair = make_pair(v , adj[v][i].first);
					max_edge = adj[v][i].second;
				}
				v = adj[v][i].first;
				break;
			}
		}
		if(v == end)
			break;
	}

    //the below mentioned lines just delete the maximum edge
	vector<pair<int,int>>::iterator iter = adj[max_pair.first].begin();
	for(int i=0; i<(int)adj[max_pair.first].size();i++)
	{
		if(adj[ max_pair.first ][ i ].first == max_pair.second)
			break;
		iter++;
	}
	adj[ max_pair.first ].erase(iter);

	if(!dir_flag)
	{
		iter = adj[max_pair.second].begin();
		for(int i=0; i<(int)adj[max_pair.second].size();i++)
		{
			if(adj[ max_pair.second ][i].first == max_pair.first)
				break;	
			iter++;		
		}
		adj[max_pair.second].erase(iter);
	}
    
    //intializing the visit back to default to re-check the presence of cycles
	for(int i=0; i<(int)visit.size();i++)
		visit[i]=0;

	return; 
}
//Detects presence of a cycle
bool Graph::detectCycle(int v, int parent, int counter)
{
    //visit[v] having a positive value means the vertex is currently active
	visit[v] = counter;
	bool result;

	for(int i=0; i<(int)adj[v].size(); i++)
	{
		if( adj[v][i].first == parent)
			continue;
        //if the adjacent vertex is already active, then there is a cycle present.
		if(visit[ adj[v][i].first ] > 0)
		{
            //removes the max. edge from the cycle
			removeMaxEdge(adj[v][i].first , v);
			return true;
		}
		if( visit[ adj[v][i].first ] == 0)
			result = detectCycle(adj[v][i].first,v,counter+1);

		if(result)
			return true;
	}
    //once all the adjacent nodes have been visited, the vertex is marked as inacitve
	visit[v] = -1;
	return false;
}


//print graph

void Graph:: Pgraph()
{
	for(int s=0;s<V;s++)
	{
		cout<<"vertex :"<<s<<"connected to"<<endl;
		for(auto i = adj[s].begin(); i!= adj[s].end();i++)
		{
			cout<<i->first<<"->";
		}
		cout<<endl;
	}
}

