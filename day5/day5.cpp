#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

inline bool is_numeric(char x){return x=='0' || x=='1' || x=='2' || x=='3' || x=='4' || x=='5' || x=='6' || x=='7' || x=='8' || x=='9';}

constexpr int max_size = 15;

int main()
{
    string    filas[max_size]; // I don't like doing it this way... 
    string    cols_p1[max_size];
    string    cols_p2[max_size];
    ifstream        input("input.txt");
    int             it = 0;
    int             movements[3] = {0};
    bool            matrix_checked = false;
    string          number;
    
    // First we have to get the initial matrix...
    for(string line; getline(input, line);)
    {
        for(int k=0; k<line.size(); k++)
        {
            if(is_numeric(line[k])) matrix_checked = !matrix_checked;
            else if(isupper(line[k]))
            {
                cols_p1[(k-1)/4].push_back(line[k]);
                cols_p2[(k-1)/4].push_back(line[k]);
            }
        }
        it++;
        if(matrix_checked){getline(input,line); break;}
    }

    // We keep reading the input file and try to decode the movements
    it = 0;
    cout<<endl;
    for(string line; getline(input, line);)
    {
        for(int k=0; k<line.size(); k++)
        {
            // Decoding lines...
            if(k==line.size()-1)
            {
                number += line[k];
                movements[it] = stoi(number);
                it = 0;
                number = "";
            }
            else if(is_numeric(line[k]))
                number += line[k];
            else if(is_numeric(line[k-1]) && !is_numeric(line[k]))
            {
                movements[it] = stoi(number);
                it++;
                number = "";
            }
        }
        it = 0;
        // Moving elements...
        for(int k=0; k<movements[0]; k++)
        {
            cols_p1[movements[2]-1].insert(cols_p1[movements[2]-1].begin() , cols_p1[movements[1]-1].front());
            cols_p1[movements[1]-1].erase(cols_p1[movements[1]-1].begin());
            cols_p2[movements[2]-1].insert(cols_p2[movements[2]-1].begin() , cols_p2[movements[1]-1][movements[0]-k-1]);
        }
        for(int l=0; l<movements[0]; l++){if(!cols_p2[movements[1]-1].empty())cols_p2[movements[1]-1].erase(cols_p2[movements[1]-1].begin());}
    }

    // Final results: 
    cout<<"1st part solution: "<<endl;
    for(int t=0; t<max_size; t++)
    {
        cout<<cols_p1[t][0];
    }
    cout<<endl<<endl;
    cout<<"2nd part solution: "<<endl;
    for(int t=0; t<max_size; t++)
    {
        cout<<cols_p2[t][0];
    }
    cout<<endl<<endl;

    return 0;
}
