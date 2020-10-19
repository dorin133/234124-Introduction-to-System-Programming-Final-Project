#ifndef FINAL_PROJ_AUXILIARIES_MAIN
#define FINAL_PROJ_AUXILIARIES_MAIN

#include "Exceptions.h"
#include <set>
#include <string>
#include <algorithm> 
#include <stack>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>

std::string trimSpaces(const std::string& input);
std::set<std::string> splitStringByComma(const std::string& string_set);
void verifyGraphName(const std::string& string_set);
std::string splitGraphName(const std::string& string_graph); 
void verifyFileName(const std::string& filename);
std::pair<int, int> findInnerSubstring(std::string equation);
std::vector<std::string> createVector(std::string equation);
int if_print1_save2_delete3_not4(std::string string_input);

#endif //FINAL_PROJ_AUXILIARIES_MAIN