#ifndef FINAL_PROJ_GRAPH
#define FINAL_PROJ_GRAPH

#include "Edge.h"
#include "Vertex.h"

  
class Graph
{
       private:      
              static std::string splitGraphEdges(const std::string& string_graph);
              static std::set<std::string> splitEdgeStringByComma(const std::string& string_set);
              static std::set<std::string> splitVertexStringByComma(const std::string& string_set);           
              static bool isEmptyGraph(const std::string& string_graph);
              std::set<std::string> vertices;
              std::set<std::string> edges;    

       public:
              Graph(const std::string& string_graph);
              Graph(std::set<std::string> vertices_string, std::set<std::string> edges_string);
              Graph();  
              const std::set<std::string>& getVertices() const
              {
                     return vertices;
              }
              const std::set<std::string>& getEdges() const
              {
                     return edges;
              }
              Graph* addVertex_aux(char* vertex);
              Graph* addEdge_aux(char* vertex1, char* vertex2);
              friend void print(const Graph& g1, std::ostream& output);                   
              friend Graph operator+(const Graph& g1, const Graph& g2);
              friend Graph operator^(const Graph& g1, const Graph& g2);
              friend Graph operator-(const Graph& g1, const Graph& g2);
              friend Graph operator*(const Graph& g1, const Graph& g2);
              friend Graph operator!(const Graph& g1);
              friend void save(const Graph& g1, std::string filename);
};

Graph load(std::string filename);



#endif //FINAL_PROJ_GRAPH