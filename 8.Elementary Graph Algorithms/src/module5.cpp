#include"include/heap.h"
#include"include/graph.h"
#include<utility>
#include"include/disjoint_set.h"
#include<bits/stdc++.h>
using namespace std;

//Max weight MST using krushkal
void MST_Kruskal(Graph G)
{
	int V = G.getV();
	int E = G.getE();

	//Final Result
	vector <Edge> MST;

	//extracting edges from adj list into edges array for easy access
	Edge edges[E];
	fillup_edges(edges,G);

	//arrange the array in decreasing order of weights
	qsort(edges,E,sizeof(Edge),comp_edge);

	int e=0; // for iteration(iterate till e<V-1)
	int i=0; //for iterating across Edges array

	 //making single sized Disjoint sets with Vertices
	disjoint_set Vertices;
	for(i=0; i<V; i++)
	Vertices.MakeSet(i);

	i=0;
	while(e<V-1 && i<E)
	{
		//pickssmallest
		Edge smallest_edge = edges[i++];
		//find the daddy's of source and destination
		int daddy_source = Vertices.FindSet(smallest_edge.getsource());
		int daddy_dest = Vertices.FindSet(smallest_edge.getdest());
		//Union allowed only if they don't have the same daddy( if they are siblings, including this edge will create a cycle)
		// #saynotoincest!
		if(daddy_source!= daddy_dest)
		{
			Vertices.Union(daddy_dest,daddy_source);
			MST.push_back(smallest_edge);
			e++;

		}
	}
	//MST is ready
	//find total cost
	int cost=0;
	cout<<"Min Weight Spannning Tree for the given graph :"<<endl;

	for(auto it = MST.begin(); it!= MST.end(); it++)
	{
		cout<<it->getsource()<<"-"<<it->getdest()<<"-";
		cost = cost + it->getweight();
	}
	cout<<endl<<"Total Weight of the spanning tree is: "<<cost<<endl;
}

Graph MST_Prim(Graph G)
{
	int s,t;
	int v=G.getV();

	int min = INT_MAX;

	//deciding the source vertex
	for(int i=0; i<v; i++)
	{
		for(int j=0; j < (int)G.adj[i].size(); j++)
		{
			if(min > G.adj[i][j].second)
				s = i;
			min = G.adj[i][j].second;
		}
	}

	//New MST
	Graph MST(v , 0);

	/*All vertices yet to be added to the MST(consistes of all vertices initially)
	  Vertices are arranged in order of their distance from the MST*/

	heap vertex_set(v , s);
	//pushing all vertices into vertex_set
	vertex_set.insert(v);

	while(vertex_set.size() > 1)
	{
		//gets the closest vertex
		t = vertex_set.pop(); 
		//adds the corresponding edge to MST
		// yaha pe add 4th argument dir_flag plox
			MST.AddEdge(vertex_set.ret_edge(t) , t , vertex_set.ret_weight(t), 0);

		//updates weights of adjacent vertices
		for(int i=0; i < (int)G.adj[t].size(); i++)
			vertex_set.update_weight(t , G.adj[t][i] );
	}

	cout<<"Prim's MST:"<<endl;
	v = MST.getV();
   	for(int i=0; i<v; i++)
		for(int j=0; j < (int)MST.adj[i].size(); j++)
			cout<<i<<" "<<MST.adj[i][j].first<<" "<<MST.adj[i][j].second<<endl;

	return MST;
}

Graph MST_yourAlgo(Graph G)
{
	Graph MST = G;

    //Loop runs until there are no more cycles present
	while( MST.detectCycle(0,-1,1) );

	cout<<"YourAlgo MST:"<<endl;
	int v = MST.getV();
   	for(int i=0; i<v; i++)
		for(int j=0; j < (int)MST.adj[i].size(); j++)
			cout<<i<<" "<<MST.adj[i][j].first<<" "<<MST.adj[i][j].second<<endl;

	return MST;
}
