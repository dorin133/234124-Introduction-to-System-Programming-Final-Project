#include "Calculator.h"
#define NO_PARENTHESES -1
#define START 0
#define PRINT 1
#define SAVE 2
#define DELETE 3
#define NOT 4

Calculator::Calculator() : g_calc() {}

void Calculator::addGraph(std::string string_graph)
{
    Graph g(string_graph);
    std::string graph_name = splitGraphName(trimSpaces(string_graph));
    bool flag = false;
    for(std::map<std::string,Graph>::iterator it = g_calc.begin(); it != g_calc.end(); ++it) 
    {
        if(graph_name.compare(it->first)==0)
        {
            it->second = g;
            flag = true;
        }
    } 
    if(flag == false)
    {
        g_calc.map::insert(std::pair<std::string, Graph> (graph_name, g));
    }
}

void Calculator::addGraph(std::string graph_name, const Graph& g) 
{
    bool flag = false;
    for(std::map<std::string,Graph>::iterator it = g_calc.begin(); it != g_calc.end(); ++it) 
    {
        if(graph_name.compare(it->first)==0)
        {
            it->second = g;
            flag = true;
        }
    } 
    if(flag == false)
    {
        g_calc.map::insert(std::pair<std::string, Graph> (graph_name, g));
    }
}



void Calculator::verifyGraphExist(std::string graph_name)
{
    if(g_calc.find(graph_name) == g_calc.end())
    {
        throw IllegalAction("'"+graph_name+"'"+" doesn't exist");
    }
}


void Calculator::printKeys(std::ostream& output)
{
    for(std::map<std::string,Graph>::iterator it = g_calc.begin(); it != g_calc.end(); ++it) 
    {
        output << it->first << std::endl;
    } 
}


void Calculator::reset()
{
    g_calc.clear();
}

Graph Calculator::getGraph(const std::string& graph_name)
{
    std::size_t found = graph_name.find('{');
    std::size_t found2 = graph_name.find('}');
    if(found != std::string::npos || found2 != std::string::npos)
    {
        Graph g("temp="+ trimSpaces(graph_name));
        return g;
    }
    verifyGraphExist(graph_name);
    std::map<std::string,Graph>::iterator it = g_calc.find(graph_name);
    return it->second;
}


void Calculator::deleteGraph(std::string graph_name)
{
    noActionsGiven(graph_name);
    verifyGraphExist(graph_name);
    g_calc.map::erase(graph_name);
}

void Calculator::noActionsGiven(std::string graph_name)
{
    std::string actions = "!*^+-=()";
    for (size_t i = 0; i < actions.size() ; i++)
    {
        if(graph_name.find(actions[i]) != std::string::npos)
        {
            throw IllegalAction("no actions *^+-=!() can be given");
        }
    }
    return;
}

Graph stringToGraph(const std::string& element, Calculator& g_calc)
{  
    std::string actions = "+^*-";
    std::size_t found = actions.find(element[element.length()-1]);
    if (element[0]=='!' && found != std::string::npos)
    {
        return handleComplements(element.substr(START, element.length() - 1), g_calc);
    }
    if (element[0]=='!' && found == std::string::npos)
    {
        return handleComplements(element, g_calc);
    }
    if (element[0] != '!' && found != std::string::npos)
    {
        return g_calc.getGraph(element.substr(START, element.length()-1));
    }
    if (element[0] != '!' && found == std::string::npos)
    {
        return g_calc.getGraph(element.substr(START, element.length()));
    }
    return g_calc.getGraph(element);
}

Graph handleComplements(const std::string& element, Calculator& g_calc)
{
    std::size_t found_begin = element.find("!");
    std::size_t found_last = element.rfind("!");
    std::string sub_element = element.substr(found_begin, found_last - found_begin + 1);
    int count = 0;
    for (size_t i = 0 ; i < sub_element.size(); i++)
    {
        if(sub_element[i] == '!')
        {
            count++;
        }
        else if(sub_element[i] == ' ')
        {
            continue;
        }
        else
        {
            throw IllegalGraph("invalid action on at least one graph");
        }
    }
    Graph result = g_calc.getGraph(trimSpaces(element.substr(found_last + 1)));
    if(count % 2 == 0)
    {
        return result;
    }
    return !result;
}

void handleload(std::string& equation, Calculator& g_calc)
{
    int count = 0;
    size_t found = equation.find("load");
    while(found != std::string::npos)
    {
        std::string sub_equation = equation.substr(found);
        size_t found_begin = sub_equation.find("(");
        size_t found_last = sub_equation.find(")");
        if(found_begin == std::string::npos || found_last == std::string::npos)
        {
            throw IllegalAction("illegal action was attempted. load must include '(', ')'");
        }
        if (trimSpaces(sub_equation.substr(found_begin +1, found_last - found_begin - 1)) == "")
        {
            throw IllegalAction("no parametes were given to load function");
        }
        Graph g_load = load(sub_equation.substr(found_begin + 1, found_last - found_begin -1));
        g_calc.addGraph("temp_d"+std::to_string(count) ,g_load);
        equation.replace(equation.begin() + found , 
                            equation.begin() + found + found_last + 1, "temp_d"+std::to_string(count));
        found = equation.find("load");
        count++;
    }
    return;
}

Graph calculateVector(std::vector<std::string> elements,const Calculator& g_calc)
{
    Graph result;
    Graph g1;
    Graph g2;
    std::size_t found = 0;
    std::string actions = "+^*-";
    std::string curr_action;
    std::string curr_element;
    Calculator g_calc_copy = g_calc;
    if(elements.size() == 1)
    {
        curr_action = elements[0][elements[0].size()-1];
        found = actions.find(curr_action);
        if(found == std::string::npos)
        {
            return stringToGraph(elements[0], g_calc_copy);
        }
        throw IllegalAction("illegal action was attempted");
    }
    for (size_t i=0 ; i < elements.size() - 1; i++)
    {
        curr_element = elements[i];
        curr_action = curr_element[curr_element.size()-1];
        found = actions.find(curr_action);
        if(found == std::string::npos)
        {
            throw IllegalAction("no action was given after "+curr_element);
        }
        g1 = stringToGraph(elements[i], g_calc_copy);
        g2 = stringToGraph(elements[i+1], g_calc_copy);
        if(curr_action.std::string::compare("+") == 0)
        {
            result = g1 + g2; 
        }
        if(curr_action.std::string::compare("^") == 0)
        {
            result = g1 ^ g2; 
        }
        if(curr_action.std::string::compare("-") == 0)
        {
            result = g1 - g2; 
        }        
        if(curr_action.std::string::compare("*") == 0)
        {
            result = g1 * g2; 
        }        
        g_calc_copy.addGraph( "helper"+std::to_string(i), result);
        elements[i+1] = "helper"+std::to_string(i)+elements[i+1][elements[i+1].size() -1];
    } 
    return result;
}

Graph noParenthesesCalculation(std::string equation, Calculator& g_calc)
{
    std::vector<std::string> v = createVector(equation);
    
    for (size_t i=0 ; i < v.size() ; i++)
    {
        if(v[i].find("printhelper") != std::string::npos || 
            v[i].find("deletehelper") != std::string::npos ||
                    v[i].find("savehelper") != std::string::npos)
        {
            throw IllegalAction("illegal action, print/save/delete outputs can't be graph values");
        }
    }
    return calculateVector(v, g_calc);
}

Graph expressionCalculation(std::string equation, Calculator& g_calc)
{
    Graph end_result;
    int count = 0;
    while(findInnerSubstring(equation).first != NO_PARENTHESES && 
            findInnerSubstring(equation).second != NO_PARENTHESES)
    {
        std::string sub_equation = equation.substr(findInnerSubstring(equation).first + 1, 
                findInnerSubstring(equation).second - findInnerSubstring(equation).first - 1);
        end_result = noParenthesesCalculation(trimSpaces(sub_equation), g_calc);
        g_calc.addGraph("helper"+std::to_string(count), end_result);
        equation.replace(equation.begin() + findInnerSubstring(equation).first , 
                equation.begin() + findInnerSubstring(equation).second +1, "helper"+std::to_string(count));
        count++;
    }
    return noParenthesesCalculation(trimSpaces(equation), g_calc);
}



void shellWrapper(std::istream& input, std::ostream& output)
{
    Calculator g_calc;
    bool status = true;       
    while(status && !input.eof())
    {
        try
       {
            if (&output==&std::cout)
            {
                std::cout << "Gcalc> ";
            }
            std::string command;
            std::getline(input , command);
            command = trimSpaces(command);
            if(command == "")
            {
                break;
            }
            if(command == "quit")
            {
                status = false;
                continue;
            }
            if(command == "who")
            {
                g_calc.printKeys(output);
                continue; 
            }
            if(command == "reset")
            {
                g_calc.reset();
                continue;
            }
            if(if_print1_save2_delete3_not4(command) == PRINT)
            {
                try
                {
                    Calculator g_calc_copy = g_calc;
                    std::string equation = trimSpaces(command.substr(command.find("(") + 1, 
                                            command.rfind(")") - command.find("(") - 1));
                    if (equation == "")
                    {
                        throw IllegalAction("no Graph was given");
                    }
                    handleload(equation, g_calc_copy);
                    Graph g = expressionCalculation(equation ,g_calc_copy);
                    print(g , output);
                }
                catch(const GraphException& e)
                {
                    output << "Error: can't execute print due to Illegal Graph Syntax" << std::endl;
                }
                catch(const Exceptions& e)
                {
                    output << "Error: can't execute print" << std::endl;
                }
                continue;
            }
            if(if_print1_save2_delete3_not4(command) == SAVE)
            {
                try
                {
                    Calculator g_calc_copy = g_calc;
                    std::string equation = trimSpaces(command.substr(command.find("(") + 1, 
                                            command.rfind(",") - command.find("(") - 1));
                    if (equation == "")
                    {
                        throw IllegalAction("no Graph was given");
                    }
                    handleload(equation, g_calc_copy);
                    Graph g = expressionCalculation(equation ,g_calc_copy);
                    std::string filename = trimSpaces(command.substr(command.rfind(",") + 1,
                                                command.rfind(")") - command.rfind(",") -1));
                    save(g, filename);
                }
                catch(const Exceptions& e)
                {
                    output << "Error: can't execute save" << std::endl;
                }
                continue;
            }
            if(if_print1_save2_delete3_not4(command) == DELETE)
            {
                try
                {
                    size_t first = command.find("(");
                    size_t last = command.rfind(")");
                    Calculator g_calc_copy = g_calc;
                    std::string equation = trimSpaces(command.substr(first + 1, last - first - 1 ));
                    if (equation == "")
                    {
                        throw IllegalAction("no Graph was given");
                    }
                    g_calc_copy.deleteGraph(equation);
                    g_calc = g_calc_copy;
                }
                catch(const Exceptions& e)
                {
                    output << "Error: can't execute delete due to " << e.what() << std::endl;
                }
                continue;
            }
            if(if_print1_save2_delete3_not4(command) == NOT)
            {
                std::string graph_name = trimSpaces(command.substr(0, command.rfind("=")));
                verifyGraphName(graph_name);
                std::string equation = trimSpaces(command.substr(command.find("=") +1, 
                                            command.length() - command.find("=")));
                Calculator g_calc_copy = g_calc;
                handleload(equation, g_calc_copy);
                Graph g = expressionCalculation(equation ,g_calc_copy);
                g_calc.addGraph(graph_name, g);
                continue;
            }
        }
       catch(const Exceptions& e)
       {
           output << e.what() << std::endl;
       }
       catch (std::bad_alloc& ba)
       {
           std::cerr << ba.what() << std::endl;
       }
    }
    return;
}