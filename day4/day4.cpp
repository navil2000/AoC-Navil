#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

inline bool isnumeric(char x){return x!=',' && x!='-';}
inline bool iscoma(char x){return x==',';}
inline bool isbar(char x){return x=='-';}
inline bool is_ge(int a, int b){return a >= b;}
inline bool is_le(int a, int b){return a <= b;}
inline bool inside(int a, int b, int c){return a<=c && b>=c;}

int main()
{
    string number_string;
    int aux             = 0;
    int elfs[4]         = {0};
    int count_p1        = 0;
    int count_p2        = 0;
    bool full_overlap   = false;

    ifstream input("input.txt");
    for(string line; getline(input, line);)
    {
        for(auto ch : line)
        {
            if(isnumeric(ch))number_string += ch;
            else
            {
                elfs[aux]       = stoi(number_string);    
                aux++;
                number_string   = "";
            } 
        }

        elfs[aux]       = stoi(number_string);   
        aux             = 0;
        number_string   = "";

        full_overlap = (is_ge(elfs[0], elfs[2]) && is_le(elfs[1], elfs[3])) || (is_ge(elfs[2], elfs[0]) && is_le(elfs[3], elfs[1]));
        if(full_overlap)count_p1++;
        if(inside(elfs[2],elfs[3],elfs[1]) || inside(elfs[2],elfs[3],elfs[0]) || full_overlap)count_p2++;
        for(int i=0;i<4;i++){elfs[i]=0;}
    }

    cout<<"(1st part) The solution is: "<<count_p1<<endl;
    cout<<"(2nd part) The solution is: "<<count_p2<<endl;

    return 0;
}