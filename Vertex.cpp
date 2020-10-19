
#include "Vertex.h"

//static functions

bool Vertex::verifyLegalLetters(const std::string& input_vertex)
{
    std::string input_vertex_check = trimSpaces(input_vertex);
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[]0123456789;";
    std::string::iterator it;
    for (size_t i = 0; i < input_vertex_check.std::string::length(); i++) 
    {
        char x = input_vertex_check[i];
        size_t found = letters.std::string::find(x);
        if(found == std::string::npos)
        {
            return false;
        }
    }
    return true;
}

bool Vertex::verifyLegalParenthesesAndSemicolon(const std::string& input_vertex)
{
    std::stack<char> s;   
    for (size_t i = 0; i < input_vertex.std::string::length(); i++) 
    { 
        if (input_vertex[i] == '[') 
        { 
            s.push(input_vertex[i]); 
        }
        if (input_vertex[i] == ']')
        {
            if (s.empty()) 
            {
                return false;
            }
            s.pop();
        }
        if (input_vertex[i] == ';')
        {
            if (s.empty()) 
            {
                return false;
            }
        } 
    }
    if(!s.empty())
    {
        return false;
    }
    return true;        
}

//end of static functions

void Vertex::verifyLegalVertex() const 
{
    if(!verifyLegalLetters(this->getVertex()))
    {
        throw IllegalVertex("expression " + this->getVertex() + " contains illegal Vertex syntax");
    }
    if (!verifyLegalParenthesesAndSemicolon(this->getVertex()))
    {
        throw IllegalVertex("expression "+this->getVertex()+" has an illegal Vertex syntax");
    }
    return;
}

Vertex::Vertex(std::string input_vertex) : vertex(input_vertex)
{
    this->verifyLegalVertex();
}