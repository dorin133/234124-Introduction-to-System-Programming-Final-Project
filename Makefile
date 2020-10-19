CXX=/usr/local/bin/g++
OBJS = Auxiliries_main.o Calculator.o Edge.o Vertex.o Graph.o main.o Code_for_python.o
LIBGRAPH_OBJS = Auxiliries_main.o Edge.o Vertex.o Graph.o Code_for_python.o
EXEC=gcalc
DEBUG= #now empty, assign -g for debug
COMP_FLAG= -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -fPIC
DEBUG_FLAG = #not used now
ZIP_FILES = Makefile graph.i Edge.cpp Edge.h Vertex.cpp Vertex.h Calculator.cpp Calculator.h \
Auxiliries_main.cpp Auxiliaries_main.h Code_for_python.cpp Code_for_python.h \
Graph.cpp Graph.h main.cpp

$(EXEC) : $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

libgraph.a : $(LIBGRAPH_OBJS)
	ar -rs $@ $^

Auxiliries_main.o: Auxiliries_main.cpp Auxiliaries_main.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Calculator.o: Calculator.cpp Calculator.h Graph.h Edge.h Vertex.h Exceptions.h Auxiliaries_main.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Edge.o: Edge.cpp Edge.h Vertex.h Exceptions.h Auxiliaries_main.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Graph.o: Graph.cpp Graph.h Edge.h Vertex.h Exceptions.h Auxiliaries_main.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

main.o: main.cpp Calculator.h Graph.h Edge.h Vertex.h Exceptions.h Auxiliaries_main.h 
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Code_for_python.o: Code_for_python.cpp Code_for_python.h Graph.h Edge.h Vertex.h Exceptions.h Auxiliaries_main.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Vertex.o: Vertex.cpp Vertex.h Exceptions.h Auxiliaries_main.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

tar: $(ZIP_FILES)
	zip gcalc.zip $(ZIP_FILES)

clean:
	rm -f $(OBJS) 