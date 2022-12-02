#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main()
{
    int max_calories[3] = {0};
    int input = 0;
    int line_read = 0;

    std::ifstream infile("input.txt");

    for(std::string line; std::getline(infile, line);)
    {
        // Cast std::string to int
        std::istringstream ( line ) >> line_read;

        if(line == "\r")
        {
            // std::cout<<"New elf..."<<std::endl;
            // New Elf.
            for(int i=0; i<3; i++)
            {
                if(input >= max_calories[i])
                {
                    max_calories[i] = input;
                    break;
                }
            }
            input = 0;
        }
        else input += line_read;
    }   

    std::cout<<max_calories[0]+max_calories[1]+max_calories[2]<<std::endl;

    return 0;

}




