#include <iostream>
#include <map>
#include <string>
#include <fstream> 

using namespace std;

int main()
{
    // Variables -> 1st part
    string  line_h1;
    string  line_h2;
    int     points_p1   = 0;

    // Variables -> 2nd part
    string  line_2;
    string  line_3;
    int     it          = 0;
    int     points_p2   = 0;

    // For both parts
    bool    found       = false;
    
    ifstream input("input.txt");

    for(string line; getline(input, line);)
    {
        line_h1 = line.substr(0, line.length()/2);
        line_h2 = line.substr(line.length()/2);

        for(auto &ch1 : line_h1)
        {
            found = line_h2.find(ch1) != string::npos;

            if(found && isupper(ch1))
            {
                points_p1 += 27+(int)ch1-(int)'A';
                break;
            }
            else if(found && !isupper(ch1))
            {
                points_p1 += 1+(int)ch1-(int)'a';
                break;
            }
        }
    }
    cout<<"Puntos obtenidos en la parte 1: "<<points_p1<<endl;

    // Relocate the cursor position
    input.clear();
    input.seekg(0, input.beg);
    for(string line; getline(input, line);)
    {
        if(it==2)
        {
            for(auto ch1 : line)
            {
                found = line_2.find(ch1)!=string::npos && line_3.find(ch1)!=string::npos;
                if(found && isupper(ch1))
                {
                    points_p2 += 27+(int)ch1-(int)'A';
                    break;
                }
                else if(found && !isupper(ch1))
                {
                    points_p2 += 1+(int)ch1-(int)'a';
                    break;
                }
            }
            it = -1;
        }
        else if(it==1)
        {
            line_2 = line;
        }
        else if(it==0)
        {
            line_3 = line;
        }
        it++;
    }
    cout<<"Puntos obtenidos en la parte 2: "<<points_p2<<endl;

    return 0;
}