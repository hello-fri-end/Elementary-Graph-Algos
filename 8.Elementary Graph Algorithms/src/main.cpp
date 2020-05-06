#include<iostream>
#include"include/graph.h"
using namespace std;
int main()
{
	cout << "Welcome to Elementary Graph Algorithms' Application" << endl;
	Graph G1;
	
	int mod_flag = 0;
	while (mod_flag!= -1)
	{
		cout << "Enter the module no.(1-5) you want to test.(-1 to exit)" << endl;
		cin >> mod_flag;
		switch(mod_flag)
		{
			case 1:
			{
				int f1 = 0;
				while(f1!=-1)
				{
					cout << "Make a selection:\n1: DFS(Graph G) -- choose start vertex arbitrarily and perform DFS\n2: DFS(Graph G, vertex s)\n3: DFS(Graph G, vertex s, vertex t) -- is t reachable from s\n -1: Exit" << endl;
					cin >> f1;
					switch(f1)
					{
						case 1:
							DFS(G1);
							cout << endl;
						break;

						case 2:
						{
							int s;
							cout << "Enter starting vertex s for DFS:" << endl;
							cin >> s;
							DFS(G1, s);
							cout << endl;
						}
						break;

						case 3:
						{
							int s, t;
							cout << "Enter the vertices s(src) and t(dest) to check reachability:" << endl;
							cin >> s >> t;
							if(DFS(G1, s, t))
								cout << s << " is reachable from " << t << endl;
							else
								cout << s << " is not reachable from " << t << endl;;
						}
						break;

						case -1:
							cout << "No module selected, Exiting." << endl;
						break;

						default:
							cout << "Invalid input" << endl;
						break;
					}
				}
			}
			break;


			case 2:
			{
				int f2 = 0;
				while(f2!=-1)
				{
					cout << "Make a selection:\n1: BFS(Graph G) -- choose start vertex arbitrarily and perform BFS\n2: BFS(Graph G, vertex s)\n3: BFS(Graph G, vertex s, vertex t) -- is t reachable from s\n-1: Exit" << endl;
					cin >> f2;
					switch(f2)
					{
						case 1:
							BFS(G1);
							cout << endl;
						break;

						case 2:
						{
							int s;
							cout << "Enter starting vertex s for BFS:" << endl;
							cin >> s;
							BFS(G1, s);
							cout << endl;
						}
						break;

						case 3:
						{
							int s, t;
							cout << "Enter the vertices s(src) and t(dest) to check reachability:" << endl;
							cin >> s >> t;

							if(BFS(G1, s, t))
								cout << s << " is reachable from " << t << endl;
							else
								cout << s << " is not reachable from " << t << endl;
						}
						break;

						case -1:
							cout << "No module selected, Exiting." << endl;
						break;

						default:
							cout << "Invalid input" << endl;
						break;
					}
				}
			}
			break;


			case 3:
			{
				int f3 = 0;
				while(f3 != -1)
				{
					cout << "1: BFS_SPATH(G,s,flag=0) -- returns spath in unweighted graphs\n2: BFS_SPATH(G,s,flag=1) -- returns spath in weighted graphs\n3: LPATH(Tree T, flag=0) - returns the longest path in T (undirected tree)\n4: LPATH(Tree T, flag=1) - returns the longest path in a DAG\n5: MAX_Weight_MST(Graph)\n-1: Exit" << endl;
					cin >> f3;
					switch(f3)
					{
						case 1:
						{
							int s;
							cout<<"Enter the source vertex:";
							cin >> s;
							BFS_SPATH(G1,s,0);
							break;
						}
						case 2:
						{
							int s;
							cout<<"Enter the source vertex:";
							cin>>s;
							BFS_SPATH(G1,s,1);
							break;
						}
						case 3:
							LPATH(G1,0);
							break;
						case 4:
							LPATH(G1,1);
							break;
						case 5:
							MAX_Weight_MST(G1);
							break;

						case -1:
							cout << "No module selected, Exiting." << endl;
						break;

						default:
							break;
					}
				}
			}
			break;

			case 4:
			{
				int f4 = 0;
				while(f4!=-1)
				{
					cout << "Make a selection:\n 1: Test_bipartite(Graph G)\n2: Test_articulationpoints(Graph G)\n3: Test_bridges(Graph G)\n-1: Exit" << endl;
					cin >> f4;
					switch(f4)
					{
						case 1:
							if(Test_bipartite(G1))
								cout << "The graph entered is bipartite" << endl;
							else
								cout << "The graph entered is not bipartite" << endl;
						break;

						case 2:
							Test_articulationpoints(G1);
						break;

						case 3:
							Test_bridges(G1);
						break;

						case -1:
							cout << "No module selected, Exiting." << endl;
						break;

						default:
							cout << "Invalid input" << endl;
						break;
					}
				}
			}
			break;


			case 5:
			{
				int f5 = 0;
				while(f5 != -1)
				{
					cout<<"1:Prim's MST\n2:Krushkal's MST\n3:YourAlgo\n-1: Exit\n";
					cin >> f5;
					switch(f5)
					{
						case 1:
						{
							Graph MST = MST_Prim(G1);
						}
						break;

						case 2:
						{
							MST_Kruskal(G1);
						}
						break;
						
						case 3:
						{
							Graph MST = MST_yourAlgo(G1);
						}
						break;

						case -1:
							cout << "No module selected, Exiting." << endl;
						break;

						default:
							cout << "Invalid input" << endl;;
						break;
					}
				}
			}
			break;

			case -1:
				cout << "Exiting." << endl;
			break;

			default:
			cout << "No such module exists." << endl;
			break;
		}
	}

	cout << "\n*******************END*******************" << endl;
	return 0; 
}
