#include<vector>
using namespace std;

class heap
{
private:
	vector<int> elements;
	int* weight;
	int* edge;
    int* pos;
public:
	heap(int v, int s);
	void insert(int n);
	int pop();
	void heapify_up(int v);
	void heapify_down(int t);
	void update_weight(int t, pair<int,int> pair);
	int ret_edge(int);
	int ret_weight(int);
	int size();
};
