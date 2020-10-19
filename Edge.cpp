#include "Edge.h"
#include "Auxiliaries_main.h"

Vertex Edge::createSourceVertex(const std::string& edge_string)
{
    std::size_t first = edge_string.find("<");
	std::size_t middle = edge_string.find(",");
    if(middle == edge_string.std::string::npos || first == edge_string.std::string::npos)
    {
        throw IllegalEdge("'"+edge_string+"'"+" Edge has an illegal edge syntax <_,_>");
    }
    Vertex src_vertex(trimSpaces(edge_string.substr(first + 1, middle - first - 1)));
    return src_vertex;
}

Vertex Edge::createDestenationVertex(const std::string& edge_string)
{
	std::size_t last = edge_string.find(">");
	std::size_t middle = edge_string.find(",");
    if(last == edge_string.std::string::npos || middle == edge_string.std::string::npos)
    {
        throw IllegalEdge(edge_string+ " Edge has an illegal edge syntax <_,_>");
    }
    Vertex dest_vertex(trimSpaces(edge_string.substr(middle + 1, last - middle - 1)));
    return dest_vertex;
}

Edge::Edge(std::string edge_string) : src(Vertex(createSourceVertex(edge_string))) ,  
                                      dest(Vertex(createDestenationVertex(edge_string))) 
{}