#ifndef VERTEX
#define VERTEX

#include "Exceptions.h"
#include "Auxiliaries_main.h"


class Vertex 
{
    private:
        static bool verifyLegalLetters(const std::string& input_vertex);
        static bool verifyLegalParenthesesAndSemicolon(const std::string& input_vertex);
    protected:
        std::string vertex;
    public:
        Vertex(std::string vertex);
        const std::string& getVertex() const
        {
            return vertex;
        }
        Vertex& operator=(const Vertex& other) = default;
        Vertex(const Vertex& other) = default;
        void verifyLegalVertex() const;
        ~Vertex() {};
};
#endif //VERTEX