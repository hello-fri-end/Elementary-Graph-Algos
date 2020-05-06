#include<iostream>
#include"include/disjoint_set.h"
using namespace std;

//disjoint set with only one element
void disjoint_set :: MakeSet(int data)
{
	Node *node = new Node();
	node->data = data;
	node->parent = node; //initial self loop
	node->rank= 0;

	Map.emplace( pair<int,Node*>(data,node) );  // this will give constant time access to each key's node.
};

//union of two disjoint sets if they don't have the same daddy
void disjoint_set :: Union (int data1, int data2)
{
	// find their parents first
	Node* node1 = Map[data1];
	Node* node2 = Map[data2];

	//find their daddys(also compress paths simoustaneouly if required)
	Node *daddy1= findset(node1);
	Node *daddy2 = findset(node2);
	cout<<"check"<<endl;

	//if they have same daddy, do nothing
	if(daddy1->data == daddy2->data)
	return;

	//else whoever's rank is higher becomes daddy of other
	if(daddy1->rank>= daddy2->rank)
	{
		//increment only if both sets have same rank
		daddy1->rank = (daddy1->rank==daddy2->rank)? daddy1->rank +1 : daddy1->rank;
		daddy2->parent= daddy1;
	}
	else
		daddy1->parent = daddy2;
};

int disjoint_set :: FindSet(int data)
{
	int x = findset(Map[data])->data;
	return x;
}

void disjoint_set :: printmap()
{
	for(auto it= Map.begin(); it != Map.end(); it++)
	{
		int data = it->first;
		Node* node = Map[data];

		cout<<data<<" has parent "<< (node->parent)->data <<" and rank "<<node->rank<<endl;
	}
}