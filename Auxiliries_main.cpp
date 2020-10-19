#include "Auxiliaries_main.h"

#define NO_PARENTHESES -1
#define START 0
#define PRINT 1
#define SAVE 2
#define DELETE 3
#define NOT 4


std::string trimSpaces(const std::string& input)
{
    int begin = 0;	
    std::string input_copy = input;
	while (*input_copy.begin() == ' ' && input_copy != "")
	{
        input_copy = input_copy.substr(begin + 1);
	}
    int end = input_copy.std::string::length() - 1;
    while (input_copy[end] == ' ' && input_copy != "")
	{
        input_copy = input_copy.substr(begin, end - begin);
        end--;
	}
	return input_copy;
}

std::set<std::string> splitStringByComma(const std::string& string_set) 
{
    std::set<std::string> result;
    std::stringstream s_stream(trimSpaces(string_set)); //create string stream from the string
    while(s_stream.good()) 
    {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        if(trimSpaces(substr) == "")
        {
            throw IllegalGraph("illegal input of ',' between vertices");
        }
        auto v = result.find(trimSpaces(substr));
        if (v != result.end())
        {
            throw IllegalGraph(trimSpaces(substr)+" Vertex was written more than once");
        }
        result.insert(trimSpaces(substr));
    }
    return result;
}

std::string splitGraphName(const std::string& string_graph)
{
	std::size_t find_equal = string_graph.rfind("=");
    std::size_t find_start = string_graph.rfind("{");
    std::string legal_between = string_graph.substr(find_equal+1 , find_start - find_equal -1);
    if (find_equal == std::string::npos)
    {
        throw IllegalGraph("missing a '=' symbol");
    }
    if (trimSpaces(legal_between) != "" && find_start != std::string::npos)
    {
        throw IllegalGraph("illegal characters were entered");
    }
    if (find_start == std::string::npos)
    {
        throw IllegalGraph("missing { in the beginning");
    }
    return trimSpaces(string_graph.substr(START, find_equal));
}

void verifyGraphName(const std::string& graph_name)
{
    std::string graph_name_check = trimSpaces(graph_name);
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    std::string not_first_letter = "1234567890";
    std::vector<std::string> special_words =
            {"load", "save","print", "quit", "who", "reset", "delete"};
    std::string::iterator it;
    for (size_t i = 0; i < graph_name_check.length(); i++) 
    {
        char x = graph_name_check[i];
        size_t found = letters.std::string::find(x);
        if (i == 0)
        {
            size_t found_first = not_first_letter.std::string::find(x);
            if(found_first != std::string::npos)
            {
                std::string str = graph_name_check.substr(i, 1);
                throw IllegalGraph("'"+str+"'"+" is an illegal first letter of a graph name"); //maybe make an IllegalGraphName error
            }
        }        
        if(found == std::string::npos)
        {
            std::string str = graph_name_check.substr(i, 1);
            throw IllegalGraph("'"+str+"'"+" is an illegal letter of a graph name");
        }
    }
    for(size_t i = 0 ; i < special_words.size() ; i++)
    {
        if(graph_name.compare(special_words[i]) == 0)
        {
            throw IllegalGraph(special_words[i]+" can't be used as a graph name");
        }
    }
    return;
}

void verifyFileName(const std::string& filename)
{
    for (size_t i = 0; i < filename.length(); i++)
    {
        if(filename[i] == ',')
        {
            throw IllegalFileName("',' is an illegal character in a file name");
        }
    }
}

std::vector<std::string> createVector(std::string equation)
{
    bool last = false;
    std::size_t last_letter = 0;
    std::string actions = "+^*-";
    std::string equation_copy = equation;
    std::vector<std::string> calculation_order;
    while (equation_copy != "")
    {
        last_letter = 0;
        last = false;
        for (size_t i = 0 ; i <= equation_copy.length(); i++)
        {
            if(i == equation_copy.length())
            {
                last_letter = i;
                break;
            }
            size_t found = actions.find(equation_copy[i]);
            if(found != std::string::npos)
            {
                last = true;
                last_letter = i;
                break;
            }
        }
        std::string element = trimSpaces(equation_copy.substr(0, last_letter));      
        if(last)
        {
            element +=  equation_copy[last_letter];
            equation_copy = equation_copy.substr(last_letter + 1);
        }
        else 
        {
            equation_copy = "";
        }
        if (trimSpaces(element) == "" || 
                actions.find(trimSpaces(element)) != std::string::npos)
        {
            throw IllegalAction("illegal action due to missing components");
        }
        calculation_order.push_back(element);      
    }
    return calculation_order;
}

std::pair<int, int> findInnerSubstring(std::string equation)
{
    std::size_t first = equation.find("(");
    std::size_t last = equation.find(")");
    if(first == std::string::npos && last == std::string::npos)
    {
        return std::make_pair(NO_PARENTHESES, NO_PARENTHESES); 
    }
    if((first == std::string::npos && last != std::string::npos) || 
            (first != std::string::npos && last == std::string::npos))
    {
        throw IllegalAction("illegal parentheses. missing '(' or ')'");
    }
    if (trimSpaces(equation.substr(first + 1, last - first - 1)) == "")
    {
        throw IllegalAction("illegal action of empty parentheses ()");
    }
	std::stack<char> s;
	s.push(first);
	for (size_t i = first + 1; i < equation.std::string::length(); i++)
	{
		if (equation[i] == ')')
		{
			return std::make_pair(s.top(), i);
        }
		if (equation[i] == '(')
		{
			s.push(i);
		}
	}
	throw IllegalAction("illegal parentheses. missing '(' or ')'");
}



int if_print1_save2_delete3_not4(std::string string_input)
{
    std::size_t found = string_input.find("=");
    if(found == std::string::npos)
    {
        std::size_t first = string_input.find("(");
        std::size_t last = string_input.find(")");
        if(last == std::string::npos || first == std::string::npos || 
                string_input[last] != string_input[string_input.length()-1])
        {
            throw IllegalAction("illegal action was attempted");
        }
        std::string action = trimSpaces(string_input.substr(0, first));
        if(trimSpaces(action.substr(0, first)).compare("print")==0)
        {
            return PRINT;
        }
        if(trimSpaces(action.substr(0, first)).compare("save")==0)
        {
            return SAVE;
        }
        if(trimSpaces(action.substr(0, first)).compare("delete")==0)
        {
            return DELETE;
        }
        throw IllegalAction("illegal action was attempted");
    }
    return NOT;
}

