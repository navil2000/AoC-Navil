#include <iostream>
#include <string>
#include <fstream>
using namespace std;
    
inline bool need_calculations(int cycle){return cycle == 20 || (cycle-20)%40==0;}
inline int strength_index(int cycle){return (cycle-20)/40;}

int main()
{
    // Input file
    ifstream input("input.txt");
    // Current cycle and register value
    int cycle   = 0;
    int reg     = 1;
    // Signal's strengths
    int str[6]  = {0};
    int str_sum = 0;
    // 1st Part
    for(string cmd;getline(input, cmd);)
    {
        int V           = 0;
        int n_cycles    = 0;

        if(!cmd.find("addx"))
        {
            n_cycles = 2;
            V        = stoi(cmd.substr(4));
        }
        else if(!cmd.find("noop"))
        {
            cycle++;
            if(need_calculations(cycle))
                str[strength_index(cycle)] = cycle*reg;
        }
        for(int i=0;i<n_cycles;i++)
        {
            cycle++;
            if(need_calculations(cycle))
                str[strength_index(cycle)] = cycle*reg;
        }
        reg += V;
    }
    for(int k=0;k<6;k++){str_sum += str[k];}
    cout<<"1st Part solution is: "<<str_sum<<endl;
    return 0;
}

