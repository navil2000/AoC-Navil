#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int decode(string msg, int n_char);

int main()
{
    ifstream    input("input.txt");
    string      encoded_msg;

    /** Take the msg**/
    getline(input,encoded_msg);
    /** PART 1 **/
    cout<<"The solution of the first part is: "<<decode(encoded_msg, 4)<<endl;
    /** PART 2 **/
    cout<<"The solution of the second part is: "<<decode(encoded_msg, 14)<<endl;

    return 0; 
}

int decode(string msg, int n_char)
{
    string block    = "";
    string aux      = "";     
    for(int i=n_char;i<msg.size();i++)
    {
        // 1st we take the block of 4 chars.
        for(int n=0;n<n_char;n++){block.push_back(msg[i-n]);}
        // Now we analyze each block.
        for(int j=0;j<n_char;j++)
        {
            aux = "";
            for(int k=0;k<n_char;k++)
            {
                if(k!=j)
                    aux.push_back(block[k]);
            }
            if(aux.find(block[j])!=string::npos)
                break;
            else if(j==n_char-1) return i+1;
        }
        block = "";
    }
    return -1;    
}
