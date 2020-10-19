#ifndef FINAL_PROJ_EXCEPTIONS
#define FINAL_PROJ_EXCEPTIONS
#include <string>



    class Exceptions : public std::exception
    {
        protected:
            std::string to_print;
        public:
            Exceptions(std::string error) : to_print("Error: "+error) {}
            virtual ~Exceptions() {}
            virtual const char* what() const noexcept
            {
                return to_print.c_str();
            }
    };

//General Exceptions

    class GeneralExceptions : public Exceptions 
    {
        public:
            GeneralExceptions(std::string error) : 
                                    Exceptions(error) {}
            virtual ~GeneralExceptions() {}
    };

    class IllegalFileName : public GeneralExceptions
    {
        public:
            IllegalFileName(std::string error) : GeneralExceptions(error) {}
    };

    class CantOpenFile : public GeneralExceptions
    {
        public:
            CantOpenFile(std::string error) : GeneralExceptions(error) {}
    };

    class GraphIsNull : public GeneralExceptions
    {
        public:
            GraphIsNull(std::string error) : GeneralExceptions(error) {}
    };





//Graph Exceptions

    class GraphException : public Exceptions 
    {
        public:
            GraphException(std::string error) : Exceptions(error) {}
            virtual ~GraphException() {}
    };

    class IllegalGraph :  public GraphException
    {
        public:
            IllegalGraph(std::string error) : GraphException(error) {}
    };
    
//Vertex Exceptions

    class VertexExceptions : public GraphException 
    {
        public:
            VertexExceptions(std::string curr_vertex_error) : 
                                    GraphException(curr_vertex_error) {}
            virtual ~VertexExceptions() {}
    };

    class IllegalVertex :  public VertexExceptions
    {
        public:
            IllegalVertex(std::string error) : VertexExceptions(error) {}
    };

//Edge Excpetions

    class EdgeExceptions : public GraphException 
    {
        public:
            EdgeExceptions(std::string curr_edge_error) : 
                                    GraphException(curr_edge_error) {}
            virtual ~EdgeExceptions() {}
    };

    class IllegalEdge :  public EdgeExceptions
    {
        public:
            IllegalEdge(std::string error) : EdgeExceptions(error) {}
    };

//Calculator Exceptios
    class CalculatorExceptions : public Exceptions 
    {
        public:
            CalculatorExceptions(std::string error) : Exceptions(error) {}
            virtual ~CalculatorExceptions() {}
    };

    class IllegalAction : public CalculatorExceptions
    {
        public:
            IllegalAction(std::string error) : CalculatorExceptions(error) {}
    };

#endif //FINAL_PROJ_EXCEPTIONS