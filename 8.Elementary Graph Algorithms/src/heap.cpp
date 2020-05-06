#include<vector>
#include<bits/stdc++.h>
#include"include/heap.h"
using namespace std;

//Constructor
heap::heap(int v, int s)
{
	weight = (int*)malloc(v*sizeof(int));
	edge = (int*)malloc(v*sizeof(int));
    pos = (int*)malloc(v*sizeof(int));

	for(int i=0; i<v; i++)
		weight[i] = INT_MAX;
	weight[s] = 0;
	edge[s] = s;
	elements.push_back(0);
}

//inseting elements into heap
void heap::insert(int n)
{
	for(int i=0; i<n; i++)
	{
		elements.push_back(i);
		pos[i] = i+1;
	}

	for(int i=n; i>0; i--)
		heapify_down(i);

	return;
}

//removing top element from heap
int heap::pop()
{
	int x = elements[1];
	elements[1] = elements[ elements.size() - 1 ];
	elements.erase(elements.begin() + elements.size() - 1);
	heapify_down(1);

	return x;
}

//Heapifying upwards from a given vertex
void heap::heapify_up(int v)
{
	int n = v;

	while(n/2 >= 1)
	{
		if( weight[ elements[n/2] ] > weight[ elements[n] ])
		{
			elements[n/2] = elements[n/2]^elements[n];
			elements[n] = elements[n/2]^elements[n];
			elements[n/2] = elements[n/2]^elements[n];
           
            pos[ elements[n/2] ] = n;
            pos[ elements[n] ] = n/2;

			n = n/2;
			continue;
		}
		break;
	}
	return;
}

//Heapify downwards from a given vertex
void heap::heapify_down(int t)
{
	int y;

	while( 2*t < (int)elements.size() )
	{
		y = 2*t;
		if(2*t + 1 < (int)elements.size())
			if( weight[ elements[2*t + 1]] > weight[ elements[2*t] ])
				y = 2*t + 1;

		if( weight[ elements[y] ] < weight[ elements[t] ] )
		{
			elements[y] = elements[y]^elements[t];
			elements[t] = elements[y]^elements[t];
			elements[y] = elements[y]^elements[t];

            pos[ elements[y] ] = t;
            pos[ elements[t] ] = y;

			t = y;
			continue;
		}
		break;
	}
	return;
}

//update weight of a vertex
void heap::update_weight(int t, pair<int,int> pair)
{
	if( weight[pair.first] > pair.second)
	{
		weight[pair.first] = pair.second;
		edge[pair.first] = t;
	}

	heapify_up(pair.first);
	return;
}

int heap::ret_edge(int v)
{
	return edge[v];
}

int heap::ret_weight(int v)
{
	return weight[v];
}

int heap::size()
{
	return elements.size();
}