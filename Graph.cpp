#include "Graph.h"
#include <fstream>  
#define START 0



bool Graph::isEmptyGraph(const std::string& string_graph)
{
    std::size_t first = string_graph.find("{");
    std::size_t middle = string_graph.find("|");
    std::string string_empty_check = trimSpaces(string_graph).substr(first + 1);
    if(middle != std::string::npos)
    {
        string_empty_check.replace(string_empty_check.find("|"), 1, " ");
    } 
    string_empty_check.erase(std::remove(string_empty_check.begin(), 
            string_empty_check.end(), ' '), string_empty_check.end());
    if(string_empty_check == "}")
    {
        return true;
    }
    return false;
}

std::string Graph::splitGraphEdges(const std::string& string_graph)
{
    std::string string_graph_trimmed = trimSpaces(string_graph);
    std::size_t first = string_graph_trimmed.find("|");
	std::size_t last = string_graph_trimmed.find("}");
    if(last == std::string::npos )
    {
        throw IllegalGraph("illegal Graph syntax");
    }
    if(last != string_graph_trimmed.rfind("}"))
    {
        throw IllegalGraph("more than one }");
    }
    if(string_graph_trimmed[last] != string_graph_trimmed[string_graph_trimmed.length()-1])
    {
        throw IllegalGraph("illegal characters after '}'");
    }
    if(first == std::string::npos)
    {
        return "";
    }
    return trimSpaces(string_graph_trimmed.substr(first + 1, last - first));
}

//must get " <m,k> , <p,o>  }"
std::set<std::string> Graph::splitEdgeStringByComma(const std::string& string_set)
{
    std::string string_set_copy = splitGraphEdges(string_set);
    std::set<std::string> result;
    if(string_set_copy == "}" || string_set_copy == "")
    {
        return result;
    }
    if(string_set_copy.substr(0, 1) != "<")
    {
        throw IllegalGraph("illegal edge syntax <_,_> was found");
    }
	while (trimSpaces(string_set_copy) != "}")
	{
		std::size_t first = string_set_copy.find("<");
		std::size_t last = string_set_copy.find(">");
        std::string sub_string = string_set_copy.substr(0, first);
        sub_string.erase(std::remove(sub_string.begin(), sub_string.end(), ' '), sub_string.end());
		if (first == std::string::npos || last == std::string::npos)
		{
			if (string_set_copy != "}")
			{
				throw IllegalGraph("illegal input of edges");
			}
			return result;
		}
        if (sub_string != "," && first != START)
        {
            throw IllegalGraph("illegal input of ',' between edges");
        }
		std::string edge = string_set_copy.substr(first, last - first + 1);
        auto v = result.find(trimSpaces(edge));
        if (v != result.end())
        {
            throw IllegalGraph("'"+trimSpaces(edge)+"' Edge already exists");
		}
		result.insert(trimSpaces(edge));
		string_set_copy = string_set_copy.substr(last + 1, 
                          string_set_copy.std::string::length() - last - 1);       
	}
	return result;
}

std::set<std::string> Graph::splitVertexStringByComma(const std::string& string_set)
{
    std::size_t first = string_set.find("{");
	std::size_t last_1 = string_set.find("|");
    std::size_t last_2 = string_set.find("}");

    if (first == std::string::npos)
	{
		throw IllegalGraph("illegal Graph syntax");
	}
    if (last_1 == std::string::npos)
    {
        if(last_2 == std::string::npos)
        {
            throw IllegalGraph("illegal Graph syntax");
        }
        last_1 = last_2;
    }
    std::string string_set_copy = string_set.substr(first + 1, last_1 - first - 1);
    std::set<std::string> result = splitStringByComma(string_set_copy);
    return result;
}


Graph::Graph(const std::string& string_graph) : vertices(), edges()
{
    std::string string_graph_copy = trimSpaces(string_graph);
    std::string graph_name = splitGraphName(string_graph_copy);
    verifyGraphName(graph_name);
    if(!isEmptyGraph(string_graph))
    {
        std::set<std::string> vertices_string = splitVertexStringByComma(string_graph);
        std::set<std::string> edges_string = splitEdgeStringByComma(string_graph);
        for (auto it = vertices_string.begin(); it != vertices_string.end(); ++it)
        {
            Vertex temp_vertex(trimSpaces(*it));
            vertices.insert(temp_vertex.getVertex());
        }       
        for (auto it = edges_string.begin(); it != edges_string.end(); ++it)
        {
            Edge temp_edge(*it);
            if(temp_edge.getSourceVertex() == temp_edge.getDestenationVertex())
            {
                throw IllegalEdge("'"+*it+"' Edge has the same source and destination vertex");
            }
            auto v1 = vertices.find(temp_edge.getSourceVertex());
            auto v2 = vertices.find(temp_edge.getDestenationVertex());
            auto v3 = edges.find("<"+temp_edge.getSourceVertex()+","+temp_edge.getDestenationVertex()+">");
            if (v1 == vertices.end()) 
            {
                throw IllegalEdge("'"+temp_edge.getSourceVertex()+ "' in '"+ *it +"' doesn't exist");
            }
            if (v2 == vertices.end())
            {
                throw IllegalEdge("'"+temp_edge.getDestenationVertex()+ "' in '"+ *it +"' doesn't exist");
            }
            if( v3 != edges.end())
            {
                throw IllegalEdge("'"+*it + "' Edge already exists");
            }
            edges.insert("<"+temp_edge.getSourceVertex()+","+temp_edge.getDestenationVertex()+">");
        }
    }
}

Graph::Graph(std::set<std::string> vertices_string, std::set<std::string> edges_string) 
                                    : vertices(), edges()
{
    for (auto it = vertices_string.begin(); it != vertices_string.end(); ++it)
    {
        Vertex temp_vertex(trimSpaces(*it));
        vertices.insert(temp_vertex.getVertex());
    }       
    for (auto it = edges_string.begin(); it != edges_string.end(); ++it)
    {
        Edge temp_edge(*it);
        if(temp_edge.getSourceVertex() == temp_edge.getDestenationVertex())
        {
            throw IllegalEdge("'"+*it+"' Edge has the same source and destination vertex");
        }
        auto v1 = vertices.find(temp_edge.getSourceVertex());
        auto v2 = vertices.find(temp_edge.getDestenationVertex());
        auto v3 = edges.find("<"+temp_edge.getSourceVertex()+","+temp_edge.getDestenationVertex()+">");
        if (v1 == vertices.end()) 
        {
            throw IllegalEdge("'"+temp_edge.getSourceVertex()+ "' in '"+ *it +"' doesn't exist");
        }
        if (v2 == vertices.end())
        {
            throw IllegalEdge("'"+temp_edge.getDestenationVertex()+ "' in '"+ *it +"' doesn't exist");
        }
        if( v3 != edges.end())
        {
            throw IllegalEdge("'"+*it + "' Edge already exists");
        }
        edges.insert("<"+temp_edge.getSourceVertex()+","+temp_edge.getDestenationVertex()+">");
    }

}

Graph::Graph() : vertices(), edges() {}

Graph operator+(const Graph& g1, const Graph& g2)
{
    Graph g = g1;
    for (auto it = g2.vertices.begin(); it != g2.vertices.end(); ++it)
    {
        g.vertices.insert(*it);
    }
    for (auto it2 = g2.edges.begin(); it2 != g2.edges.end(); ++it2)
    {
        g.edges.insert(*it2);
    }
    return g;
}

Graph operator^(const Graph& g1, const Graph& g2)
{
    Graph g;
    for (auto it = g1.vertices.begin(); it != g1.vertices.end(); ++it)
    {
        auto found = g2.vertices.find(*it);
        if(found != g2.vertices.end())
        {
            g.vertices.insert(*it);
        }
    }
    for (auto it2 = g1.edges.begin(); it2 != g1.edges.end(); ++it2)
    {
        auto found = g2.edges.find(*it2);
        if(found != g2.edges.end())
        {
            g.edges.insert(*it2);
        }
    }
    return g;
}

Graph operator-(const Graph& g1, const Graph& g2)
{
    Graph g;
    for (auto it = g1.vertices.begin(); it != g1.vertices.end(); ++it)
    {
        auto found = g2.vertices.find(*it);
        if(found == g2.vertices.end())
        {
            g.vertices.insert(*it);
        }       
    }
    for (auto it = g1.edges.begin(); it != g1.edges.end(); ++it)
    {
        Edge curr_edge(*it);
        auto found_source = g.vertices.find(curr_edge.getSourceVertex());
        auto found_dest = g.vertices.find(curr_edge.getDestenationVertex());
        if (found_source != g.vertices.end() && found_dest != g.vertices.end())
        {
            g.edges.insert(*it);
        }
    }
    return g;
}

Graph operator*(const Graph& g1, const Graph& g2)
{
    Graph g;
    std::set<std::string> edges_result;
    std::set<std::string> vertices_result;
    for (auto it = g1.edges.begin(); it !=  g1.edges.end(); ++it)
    {
        Edge temp_edge(*it);
        std::string src_vertex_g1 = temp_edge.getSourceVertex();
        std::string dest_vertex_g1 = temp_edge.getDestenationVertex();
        for (auto it2 = g2.edges.begin(); it2 != g2.edges.end(); ++it2)
        {
            Edge temp_edge(*it2);
            std::string new_edge = "<["+src_vertex_g1+";"+temp_edge.getSourceVertex()
                    +"],["+dest_vertex_g1+";"+temp_edge.getDestenationVertex()+"]>";
            edges_result.insert(new_edge);
        }
    }
    for (auto it = g1.vertices.begin(); it !=  g1.vertices.end(); ++it)
    {
        for (auto it2 = g2.vertices.begin(); it2 != g2.vertices.end(); ++it2)
        {
            std::string new_vertex = "["+(*it)+";"+(*it2)+"]";
            vertices_result.insert(new_vertex);
        }
    }
    g.vertices = vertices_result;
    g.edges = edges_result;
    return g;
}

Graph operator!(const Graph& g1)
{
    Graph g = g1;
    std::set<std::string> edges_new;
    for (auto it = g1.vertices.begin(); it !=  g1.vertices.end(); ++it)
    {
        for (auto it2 = g1.vertices.begin(); it2 !=  g1.vertices.end(); ++it2)
        {
            if(*it == *it2)
            {
                continue;
            }
            std::string curr_edge = "<"+*it+","+*it2+">";
            if(g1.edges.find(curr_edge) == g1.edges.end())
            {
                edges_new.insert(curr_edge);
            }
        }
    }
    g.edges = edges_new;
    return g;
}

void print(const Graph& g1, std::ostream& output)
{
    for (auto it = (g1.vertices).begin(); it != (g1.vertices).end(); ++it)
    {
        output << *it << std::endl;
    }
    output << "$" << std::endl;

    for (auto it = (g1.edges).begin(); it != (g1.edges).end(); ++it)
    {
        Edge temp_edge(*it);
        std::string src_vertex_g = temp_edge.getSourceVertex();
        std::string dest_vertex_g = temp_edge.getDestenationVertex();
        output << src_vertex_g + " " + dest_vertex_g << std::endl;
    }
    return;      
}

void save(const Graph& g1, std::string filename)
{
    verifyFileName(filename);
    int count_vertices = 0;
    int count_edges = 0;
    for (auto it = g1.vertices.begin(); it != g1.vertices.end(); ++it)
    {
        count_vertices++;
    }
    for (auto it = g1.edges.begin(); it != g1.edges.end(); ++it)
    {
        count_edges++;
    }
    std::ofstream outfile(filename, std::ios_base::binary);
    if(!outfile.is_open())
    {
        throw CantOpenFile("cant open file " + filename + " for writing");
    }
    outfile.write((const char*)&count_vertices, sizeof(int));
    outfile.write((const char*)&count_edges, sizeof(int));
    for (auto it = g1.vertices.begin(); it != g1.vertices.end(); ++it)
    {
        std::string str(*it);
        int size=str.size();
        outfile.write((const char*)&size, sizeof(int));
        outfile.write(str.c_str(), str.size());
    }
    for (auto it = g1.edges.begin(); it != g1.edges.end(); ++it)
    {
        Edge temp_edge(*it);
        std::string src_vertex_g1 = temp_edge.getSourceVertex();
        std::string dest_vertex_g1 = temp_edge.getDestenationVertex();
        int size_src_vertex_g1 = src_vertex_g1.size();
        int size_dest_vertex_g1 = dest_vertex_g1.size();
        outfile.write((const char*)&size_src_vertex_g1, sizeof(int));
        outfile.write(src_vertex_g1.c_str(), size_src_vertex_g1);
        outfile.write((const char*)&size_dest_vertex_g1, sizeof(int));
        outfile.write(dest_vertex_g1.c_str(), size_dest_vertex_g1);
    }
}

Graph load(std::string filename)
{
    verifyFileName(filename);
    std::ifstream infile(filename, std::ios_base::binary); 
    if(!infile.is_open())
    {
        throw CantOpenFile("cant open file " + filename + " for reading");
    }
    int num_vertices = 0;
    int num_edges = 0;
    std::set<std::string> vertices;
    std::set<std::string> edges;
    infile.read((char*)&num_vertices, sizeof(int));
    infile.read((char*)&num_edges, sizeof(int));
    int len = 0;
    for (int i = 0 ; i < num_vertices ; i++) 
    {
        infile.read((char*)&len, sizeof(int));
        char* curr_vertex_char = new char[len+1];
        infile.read(curr_vertex_char, len);
        curr_vertex_char[len] = '\0';
        std::string curr_vertex_string(curr_vertex_char, len);
        Vertex temp_vertex(curr_vertex_string);        
        delete[] curr_vertex_char;
        vertices.insert(curr_vertex_string);
    }
    for (int i = 0 ; i < num_edges ; i++) 
    {
        infile.read((char*)&len, sizeof(int));
        char* curr_src_vertex_char = new char[len+1];
        infile.read(curr_src_vertex_char, len);
        curr_src_vertex_char[len] = '\0';
        std::string curr_src_vertex_string(curr_src_vertex_char, len);
        delete[] curr_src_vertex_char;

        infile.read((char*)&len, sizeof(int));
        char* curr_dest_vertex_char = new char[len+1];
        infile.read(curr_dest_vertex_char, len);
        curr_dest_vertex_char[len] = '\0';
        std::string curr_dest_vertex_string(curr_dest_vertex_char, len);
        delete[] curr_dest_vertex_char;

        std::string edge_string = "<"+curr_src_vertex_string+","+curr_dest_vertex_string+">";
        Edge temp_edge(edge_string);
        edges.insert(edge_string);
    }
    Graph g(vertices, edges);
    return g;
}

Graph* Graph::addVertex_aux(char* vertex)
{
    Vertex curr_vertex(vertex);
    auto found = vertices.find(vertex);
    if(found != vertices.end())
    {
        throw IllegalVertex("'"+curr_vertex.getVertex()+ "' already exists");
    }
    vertices.insert(vertex);
    return this;
}

Graph* Graph::addEdge_aux(char* vertex1, char* vertex2)
{
    Vertex vertex_src(vertex1);
    Vertex vertex_dest(vertex2);
    std::string edge_string = "<"+vertex_src.getVertex()+","+vertex_dest.getVertex()+">";
    auto found1 = edges.find(edge_string);
    auto found2 = vertices.find(vertex_src.getVertex());
    auto found3 = vertices.find(vertex_dest.getVertex());
    if(found1 != edges.end())   
    {
        throw IllegalEdge("'"+edge_string+ "' Edge already exists");
    }
    if (found2  == vertices.end())
    {
        throw IllegalEdge("'"+vertex_src.getVertex()+"' in "+ edge_string +" doesn't exist");
    }
    if (found3 == vertices.end())
    {
        throw IllegalEdge("'"+vertex_dest.getVertex()+"' in "+ edge_string +" doesn't exist");
    }
    if(found2 == found3)
    {
        throw IllegalEdge("'"+edge_string+"'"+" Edge has the same source and destination vertex");
    }
    edges.insert(edge_string);
    return this;
}
       