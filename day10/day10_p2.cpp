#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void screenshot(char screen[][40]);
int cycle2screen_col(int cycle);
int cycle2screen_row(int cycle);

int main()
{
    // Input file
    ifstream input("input.txt");
    // Screen representation
    char         screen[6][40];
    // Actual cycle
    int          cycle  = 0;
    // Sprite postition in the matrix
    int          sprite = 0;
    // Init the screen
    for(int i=0;i<6;i++)
        for(int j=0;j<40;j++)
            screen[i][j] = '.';
    // 2nd Part
    for(string cmd;getline(input,cmd);)
    {
        int V           = 0;
        int n_cycles    = 0;

        if(!cmd.find("addx"))
        {
            n_cycles = 2;
            V        = stoi(cmd.substr(4));
        }
        else if(!cmd.find("noop"))
            n_cycles = 1;
        for(int k=0;k<n_cycles;k++)
        {
            if(sprite==cycle2screen_col(cycle))
                screen[cycle2screen_row(cycle)][cycle2screen_col(cycle)] = '#';
            else if(sprite+1==cycle2screen_col(cycle))
                screen[cycle2screen_row(cycle)][cycle2screen_col(cycle)] = '#';
            else if(sprite+2==cycle2screen_col(cycle))
                screen[cycle2screen_row(cycle)][cycle2screen_col(cycle)] = '#';
            cycle++;
        }
        sprite += V;
    }

    cout<<"\n\t\tSCREEN MSG"<<endl;
    screenshot(screen);
    cout<<endl;
    return 0;
}

void screenshot(char screen[][40])
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<40;j++)
        {
            cout<<screen[i][j];
        }
        cout<<endl;
    }
}

int cycle2screen_col(int cycle)
{
    for(int i=0;i<6;i++)
    {
        if(cycle>=40)
            cycle -= 40;
        else
            return cycle;
    }
    return -1;
}

int cycle2screen_row(int cycle)
{
    for(int i=0;i<6;i++)
    {
        if(cycle>=40)
            cycle -= 40;
        else
            return i;
    }
    return -1;
}
