all: Elementary_Graph_Algorithms.o

Elementary_Graph_Algorithms.o: obj/main.o obj/module1.o obj/module2.o obj/module3.o obj/module4.o obj/module5.o obj/disjoint_set.o obj/graph.o obj/heap.o
	g++ obj/main.o obj/module1.o obj/module2.o obj/module3.o obj/module4.o obj/module5.o obj/disjoint_set.o obj/graph.o obj/heap.o -o Elementary_Graph_Algorithms

obj/main.o: src/main.cpp
	g++ -c -Wall src/main.cpp && MOVE main.o obj/main.o

obj/graph.o: src/graph.cpp
	g++ -c -Wall src/graph.cpp && MOVE graph.o obj/graph.o

obj/module1.o: src/module1.cpp
	g++ -c -Wall src/module1.cpp && MOVE module1.o obj/module1.o

obj/module2.o: src/module2.cpp
	g++ -c -Wall src/module2.cpp && MOVE module2.o obj/module2.o

obj/module3.o: src/module3.cpp
	g++ -c -Wall src/module3.cpp && MOVE module3.o obj/module3.o

obj/module4.o: src/module4.cpp
	g++ -c -Wall src/module4.cpp && MOVE module4.o obj/module4.o

obj/module5.o: src/module5.cpp
	g++ -c -Wall src/module5.cpp && MOVE module5.o obj/module5.o

obj/heap.o: src/heap.cpp
	g++ -c -Wall src/heap.cpp && MOVE heap.o obj/heap.o

obj/disjoint_set.o: src/disjoint_set.cpp
	g++ -c -Wall src/disjoint_set.cpp && MOVE disjoint_set.o obj/disjoint_set.o