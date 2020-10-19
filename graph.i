%module graph
%include "Code_for_python.h"
%{
#include "Code_for_python.h"
%}

Graph* create();
void destroy(Graph* g);
Graph* addVertex(Graph* g, char* vertex);
Graph* addEdge(Graph* g, char* vertex1, char* vertex2);
void disp(Graph* g);
Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out);
Graph* graphComplement(Graph* graph_in, Graph* graph_out);