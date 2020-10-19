#ifndef EDGE
#define EDGE

#include "Vertex.h"

class Edge 
{
    private:
        static Vertex createSourceVertex(const std::string& edge_string);
        static Vertex createDestenationVertex(const std::string& edge_string);
    protected:
        Vertex src;
        Vertex dest;
    public:
        const std::string& getSourceVertex() const
        {
            return src.getVertex();
        }
        const std::string& getDestenationVertex() const
        {
            return dest.getVertex();
        }     
          
        Edge(std::string edge_string);
};
#endif //EDGE