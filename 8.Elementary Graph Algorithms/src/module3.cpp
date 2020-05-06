#include<iostream>
#include<vector>
#include <bits/stdc++.h> 
#include"include/graph.h"
#include"include/disjoint_set.h"
using namespace std;

//fix graph function(Add bogus nodes to make BFS spath work for weighted graphs)
void Fix_Graph(Graph *G)
{
	int V= G->getV();
	int bogusnode= V; //index of largest bogus node

	//iterate across the adjanceny list
	//wherever edge weight>1 , add bogus nodes
	for(int i=0;i<V;i++)
	{
		int problem_index_1=0; //index of problem causing edge,node pair
		for(auto it= G->adj[i].begin(); it!= G->adj[i].end(); it++)
		{
			if( (it->second) > 1 ) //if edgeweight>1
			{
				int fake_nodes= (it->second) -1 ; //no of fake nodes to fix this edge
				int x= (it->first); //destination node

				//replace the current node,edge pair causing the problem with a fake node
				G->adj[i][problem_index_1] = make_pair(bogusnode,1);

				//since it's undirected
				G->adj[bogusnode].push_back(make_pair(i,1));

				//now one bogus node was added--add rest
				int u= bogusnode;
				int v= u+1; //next bogus node

				for(int j=0; j<fake_nodes-1; j++)
				{
					G->adj[u].push_back(make_pair(v,1));
					G->adj[v].push_back(make_pair(u,1));
					u++;v++;
				}

				//till this point, bogus nodes have been added b/w the problem causing edge (x,y)
				//now, join bogus nodes with y
				//first, find problem causing pair's index
				int problem_index_2 = 0;
				for(auto jt = G->adj[x].begin(); jt!= G->adj[x].end(); jt++)
				{
					if(jt->first ==i)
					break;
					problem_index_2++;
				}

				 //Now, fix the nodes
				 G->adj[x][problem_index_2]= make_pair(u,1);
				 G->adj[u].push_back(make_pair(x,1));

				 //update highest index bogus node
				 if(fake_nodes==1)
				 bogusnode++;
				 else
				 bogusnode= u+1;
			}
			problem_index_1++; //problem at this index has been fixed, move fwd.
		}
	}
	G->setV(bogusnode);
}

//1.single source shortest paths
void BFS_SPATH(Graph G, int s, int flag)
{
	if(flag==0)
	{
		//distance array
		int dis[G.getV()];
		//initilize distances to -1
		memset(dis,-1,sizeof(dis));

		//distance from s to s is 0
		dis[s]=0;

		//queue
		queue <int> q;
		q.push(s);

		//iterate while queue is non empty
		while(!q.empty())
		{
			int v = q.front();      q.pop();

			

			//for every adjacent unvisited neighbour of v , add to queue and update distance
			for(auto i= G.adj[v].begin(); i!= G.adj[v].end(); i++)
			{
				int nbr_v = i->first;
				
				if(dis[nbr_v]==-1)
				{
					q.push(nbr_v);
					dis[nbr_v] = dis[v] + 1;
				}
			}
		}

		//all the distances have been updated by now
		//print them

		int V= G.visit.size();
		for(int i=0; i<V; i++)
			cout<<"Distance of "<<i<<" from the given vertex is :"<<dis[i]<<endl;
	}

	else if(flag==1)
	{
		Fix_Graph(&G);
		BFS_SPATH(G,s,0);
	}
}


//longest path in a tree
void LPATH(Graph T,int flag)
{
	if(flag==0)
	{
		//n1: n1.first= max degree vertex from 0(one end point) and n2.second= it's distance
		//n2: n2.first= second end point and n2.second= distance
		pair<int,int> n1, n2;

		n1= bfs(0,T);

		n2= bfs(n1.first,T);

		cout<<"Longest path in the given tree is from "<<n1.first<<" to " <<n2.first<<endl;
		cout<<"The length of longest path is "<<n2.second<<endl;
	}
	else if(flag==1)
	{
		int V= T.visit.size();

		vector<int> TPA;
		Topological_Ordering(T,TPA);
		//initlize longest path to minus infinity
		int longestpath = INT8_MIN;


		int longest_path[V];
		int longest_distance_vertex;
		int source;
		int current_path[V];

		pair<int,int>longestpath_wrt_i;
		//compute longest path wrt to each vertex and update longest path when longestpath< longestpath wrt to current vertex
		for(int i=0;i<V; i++ )
		{
			longestpath_wrt_i = lpath_s(i,TPA,T,current_path);
			if(longestpath < (longestpath_wrt_i.first) )
			{
				longestpath= (longestpath_wrt_i.first);
				longest_distance_vertex = longestpath_wrt_i.second ;
				source= i;

				//update path
				for(int j=0; j<V; j++)
					longest_path[j]= current_path[j];
			}
		}

		//extract longest path
		cout<<"The longest path in the given DAG is of length: " <<longestpath<<endl;

		stack<int> temp;
		int x= longest_distance_vertex;

		do
		{
			temp.push(x);
			x = longest_path[x];
		}
		while(longest_path[x]!= source);

		temp.push(x);
		temp.push(source);

		cout<<"The longest path is :"<<endl;
		while(!temp.empty())
		{
			cout<<temp.top()<<" ";
			temp.pop();
		}
		cout<<endl;
	}
}

//utility function for longest path
pair<int,int> bfs(int s, Graph T)
{
	//distance array
	int dis[T.visit.size()];

	//initilize distances to -1
	memset(dis,-1,sizeof(dis));

	//distance from s to s is 0
	dis[s]=0;

	//queue
	queue <int> q;
	q.push(s);

	//iterate while queue is non empty
	while(!q.empty())
	{
		int v = q.front();      q.pop();

		//for every adjacent unvisited neighbour of v , add to queue and update distance
		for(auto i= T.adj[v].begin(); i!= T.adj[v].end(); i++)
		{
			int nbr_v = i->first;
			
			if(dis[nbr_v]==-1)
			{
				q.push(nbr_v);
				dis[nbr_v] = dis[v] + 1;
			}
		}
	}

	//all the distances have been updated by now
	//find max
	pair <int, int> max;
	max.first = 0;
	max.second= dis[0];
	int V = T.visit.size();
	for(int i=1; i<V; i++)
	{
		if(dis[i]>max.second)
		{
			max.second= dis[i];
			max.first= i;
		}
	}
	return max;
}

//Topologically Sorted Vector
void Topological_Ordering (Graph G,vector<int>&TPV)
{
	int V = G.visit.size();
	
	//in degrees array and initlize it with 0's
	int indegrees[V];
	memset(indegrees,0,sizeof(indegrees));


	//calculte initial indegrees
	for(int i=0;i<V;i++)
	{
		for(auto j= G.adj[i].begin(); j!=G.adj[i].end(); j++)
			indegrees[j->first]++;
	}
		int counter= 0; 
		int x;

		while(counter!=V) //until TP vector doesn't contain all V vertices
		{
			  
			//choose the vertex with 0 in degree
			for(int i=0; i<V; i++)
				if(indegrees[i]==0)
				{
					x=i;
					break;
				}

			//Remove x from the graph and make necessary changes to the indegrees
			//utility function for the same
			for(auto i=G.adj[x].begin(); i!=G.adj[x].end(); i++ )
				indegrees[i->first]--;

			//update x's indegree to infinity so that it'll not be chosen again
			indegrees[x]=  1000000;
			
			//add x to TP vector
			TPV.push_back(x);
			counter++;
		}
}

//lpath with respect to vertex s
pair<int,int> lpath_s(int s, vector<int>&TPV, Graph G, int *path)
{
	int V = G.visit.size();

	//to store distances wrt to s
	int dis[V]; int i;

	//intilize distances to minus infinity
	for(i=0;i<V;i++)
		dis[i]= INT8_MIN;
	dis[s]= 0; //disance of s wrt to s is 0

	
	//initlize paths to infinity
	for(i=0; i<V ; i++)
		path[i] = INT8_MAX;

	//update paths of s and it's neighbours
	path[s] = s;

	for(auto it = G.adj[s].begin(); it!=G.adj[s].end(); it++)
		path[it->first] = s;

	//iterate through TPV
	//for every vertex whose distance is not infinity
	//update it's neighbours distances if going through it is more expensive
	for(i=0 ; i< V ; i++)
	{
		int v = TPV[i];
		if(dis[v]!=INT8_MIN)
		{
			for(auto it = G.adj[v].begin(); it!=G.adj[v].end(); it++ )
				if( dis[it->first]<= dis[v]+(it->second) )
				{
					dis[it->first] = dis[v]+(it->second);
					path[it->first]= v;
				}
		}
	}

	//find max in distance array and return that
	pair<int,int> max;
	max.first= dis[0]; 
	for(i=1;i<V;i++)
		if((max.first)<dis[i])
		{
			max.first = dis[i];
			max.second= i;
		}

	return max;
}


//Max weight MST using krushkal
void MAX_Weight_MST(Graph G)
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
		//pickslargest
		Edge largest_edge = edges[i++];

		//find the daddy's of source and destination
		int daddy_source = Vertices.FindSet(largest_edge.getsource());
		int daddy_dest = Vertices.FindSet(largest_edge.getdest());

		//Union allowed only if they don't have the same daddy( if they are siblings, including this edge will create a cycle)
		// #saynotoincest!
		if(daddy_source!= daddy_dest)
		{
			Vertices.Union(daddy_dest,daddy_source);
			MST.push_back(largest_edge);
			e++;
		}
	}
	//MST is ready
	//find total cost
	int cost=0;
	cout<<"MAX Weight Spannning Tree for the given graph :"<<endl;

	for(auto it = MST.begin(); it!= MST.end(); it++)
	{
		cout<<it->getsource()<<"-"<<it->getdest()<<"-";
		cost = cost + it->getweight();
	}

	cout<<endl<<"Total Weight of the spanning tree is: "<<cost<<endl;
}

void fillup_edges(Edge edges[], Graph G) //utility function for MST
{
	int counter =0;
	int V= G.getV();

	for(int i=0; i<V; i++)
		for(auto it= G.adj[i].begin(); it!= G.adj[i].end(); it++)
		{
			if(it->first >= i) //rest has already been added
			{
				edges[counter].setter(i,it->first,it->second);
				counter++;
			}
		}
}

int comp_edge(const void* a, const void* b) //utility function for qsort
{
	Edge* e1= (Edge*)(a);
	Edge* e2= (Edge*)(b);

	const int w1= (e1->getweight());
	const int w2= (e2->getweight());

	if(w1>w2)
		return -1;
	else if(w1<w2)
		return 1;
	else
		return 0;
}