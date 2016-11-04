all:	simulation

simulation: simulation.o graph.o 
	g++ simulation.o graph.o -o simulation

simulation.o: simulation.cpp
	g++ -c -Wall simulation.cpp 

graph.o: graph.cpp
	 g++ -c -Wall graph.cpp

clean:
	rm -rf *o
