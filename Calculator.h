#ifndef FINAL_PROJ_CALCULATOR
#define FINAL_PROJ_CALCULATOR

#include "Graph.h"
#include "Auxiliaries_main.h"
#include <map>

class Calculator
{
    private:
        std::map<std::string, Graph> g_calc;
    public:
        Calculator();       
        void addGraph(std::string string_graph);
        void addGraph(std::string graph_name, const Graph& g);
        void deleteGraph(std::string graph_name);
        void printKeys(std::ostream& output);
        void reset();
        void verifyGraphExist(std::string graph_name);
        void noActionsGiven(std::string graph_name);
        Graph getGraph(const std::string& graph_name);
};

Graph expressionCalculation(std::string equation, Calculator& g_calc);
Graph stringToGraph(const std::string& element, Calculator& g_calc);
Graph calculateVector(std::vector<std::string> elements, const Calculator& g_calc);
Graph noParenthesesCalculation(std::string equation, Calculator& g_calc);
Graph handleComplements(const std::string& element, Calculator& g_calc);
void handleload(std::vector<std::string>& elements, Calculator& g_calc);
void shellWrapper(std::istream& input, std::ostream& output);

#endif //FINAL_PROJ_CALCULATOR