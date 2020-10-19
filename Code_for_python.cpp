#include "Code_for_python.h"


Graph* create()
{
    Graph* graph_ptr = nullptr;
    try
    {
        graph_ptr = new Graph();
    }
    catch(std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_ptr;
}

void destroy(Graph* g)
{
    delete g;
}

Graph* addVertex(Graph* g, char* vertex)
{
    try 
    {
        if(g == nullptr)
        {
            throw GraphIsNull(" the given graph pointer is NULL");
        }
        g->addVertex_aux(vertex);
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return g;
}

Graph* addEdge(Graph* g, char* vertex1, char* vertex2)
{
    try
    {
        if (g == nullptr)
        {
            throw GraphIsNull(" the given graph pointer is NULL");
        }
        g->addEdge_aux(vertex1, vertex2);
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const VertexExceptions& e)
    {
        std::cout << "Error: Illegal Edge" << std::endl;
        return nullptr;
    }
    catch(const EdgeExceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return g;
}

void disp(Graph* g)
{
    try
    {
        if(g == nullptr)
        {
            throw GraphIsNull(" the given graph pointer is NULL");
        }
        print(*g, std::cout);
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return;
    }
    return;
}

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out)
{
    try
    {
        if(graph_out == nullptr || graph_in1 == nullptr || graph_in2 == nullptr)
        {
            throw GraphIsNull(" at least one of the given graph pointers is NULL");
        }
        *graph_out = *graph_in1 + *graph_in2;
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out)
{
    try
    {
        if(graph_out == nullptr || graph_in1 == nullptr || graph_in2 == nullptr)
        {
            throw GraphIsNull(" at least one of the given graph pointers is NULL");
        }
        *graph_out = *graph_in1 ^ *graph_in2;
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out)
{
    try
    {
        if(graph_out == nullptr || graph_in1 == nullptr || graph_in2 == nullptr)
        {
            throw GraphIsNull(" at least one of the given graph pointers is NULL");
        }
        *graph_out = *graph_in1 - *graph_in2;
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out)
{
    try
    {
        if(graph_out == nullptr || graph_in1 == nullptr || graph_in2 == nullptr)
        {
            throw GraphIsNull(" at least one of the given graph pointers is NULL");
        }
        *graph_out = *graph_in1 * *graph_in2;
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_out;
}

Graph* graphComplement(Graph* graph_in, Graph* graph_out)
{
    try
    {
        if(graph_out == nullptr || graph_in == nullptr)
        {
            throw GraphIsNull(" at least one of the given graph pointers is NULL");
        }
        *graph_out = !(*graph_in);
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    catch(const Exceptions& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return graph_out;
}