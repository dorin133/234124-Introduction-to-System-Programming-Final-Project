#include "Calculator.h"

int main(int argc , char* argv[])
{
    if(argc == 3)
    {
        std::ifstream infile(argv[1]);
        std::string filename_in(argv[1]);
        if(!infile.is_open())
        {
            throw CantOpenFile("cant open file " + filename_in + " for reading");
        }
        std::ofstream outfile(argv[2]);
        std::string filename_out(argv[2]);
        if(!outfile.is_open())
        {
            throw CantOpenFile("cant open file " + filename_out + " for writting");
        }

        shellWrapper(infile, outfile);
    }
    if(argc ==1)
    {
        shellWrapper(std::cin, std::cout);
    }
    if (argc != 1 && argc !=3)
    {
        std::cerr << "Error: not the right amount of arguments to function call" << std::endl;
    }
    return 0;
}