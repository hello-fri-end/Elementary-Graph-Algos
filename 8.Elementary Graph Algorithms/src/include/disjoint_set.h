#include<iostream>
#include<map>
using namespace std;

class disjoint_set
{
	public:
	void MakeSet (int data);  //create a disjoint set with only one element
	void Union(int data1,int data2); //Takes the union of two disjoint sets
	int FindSet(int data); //finds the daddy of current disjoint set
	void printmap();

	//node for our disjoint set tree
	public: class Node
	{
		public:
		int data;
		Node *parent;
		int rank;
	};

	private:
	map <int,Node*> Map; //to store key, node pairs for constant time access later on

	Node* findset(Node* node) //finds daddy recursively ( does  path compression to reduce time complexity as well)
	{
		Node *parent = node->parent;
		//if a dude's parent is the dude himself then he's a daddy 
		if( (Node*)parent == (Node*) node)
		{
			 return node;
		}
		//else do path compression and find daddy
		node->parent = findset(node->parent);
		return node->parent;
	}
};