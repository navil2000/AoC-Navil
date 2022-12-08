#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Auxiliar functions 
bool inline find_word(string searched_str,string line){return line.find(searched_str)!=string::npos;}
inline bool is_numeric(char x){return x=='0' || x=='1' || x=='2' || x=='3' || x=='4' || x=='5' || x=='6' || x=='7' || x=='8' || x=='9';}
int get_size(string cmd);

// Dir struct
struct Dir
{   
    Dir*            parent;
    string          dir;
    int             size;
    vector<Dir*>    sub_dirs;
    Dir():dir(""),size(0){};
}; 

// Functions
Dir* new_node(string _dir, int _size);
void add_subdir(Dir* _dir, string _subdir, int _size);
void Print(Dir* _root);
void send_info2parent(Dir* _actual_dir, int new_size);
string get_subdir_string(string cmd);
bool subdir_exist(Dir* _actual_dir, string _subdir_name);
int fn_part1(Dir* _root);
int fn_part2(Dir* _root, int min);

int main()
{
    
    Dir* actual_dir;
    Dir* root;
    root = new_node("\0", 0);
    root->parent = NULL;
    actual_dir = root;
    int aux_int = 0;
    ostringstream ss;
    string aux = "";

    ifstream input("input.txt");

    for(string cmd; getline(input,cmd);)
    {
        // cout<<cmd<<endl;
        if(find_word("$ cd", cmd))
        {
            if(find_word("..", cmd))
                    actual_dir = actual_dir->parent;
            else
            {
                if(!subdir_exist(actual_dir,get_subdir_string(cmd)))
                {
                    add_subdir(actual_dir,get_subdir_string(cmd), 0);
                    actual_dir = actual_dir->sub_dirs.back();
                    aux = "";
                }
            }
        }
        else if(is_numeric(cmd.front()))
        {
            send_info2parent(actual_dir,get_size(cmd));
        }
    }

    cout<<"\nThe 1st part solution is: "<<fn_part1(root)<<endl;
    
    cout<<"\nSize occupaid: "<<root->size<<endl;
    cout<<"Size requeried: "<<root->sub_dirs[0]->size-40000000<<endl;
    cout<<"The 2nd part solution is: "<<fn_part2(root, root->sub_dirs[0]->size-40000000)<<endl;

    return 0;
}

Dir* new_node(string _dir, int _size)
{
    Dir* new_dir = new Dir();

    new_dir->dir    = _dir;
    new_dir->size   = _size;

    return new_dir;
}

void add_subdir(Dir* _dir,  string _subdir, int _size)
{
    Dir* new_dir = new_node(_subdir, _size);
    new_dir->parent = _dir;
    _dir->sub_dirs.push_back(new_dir);
}

int get_size(string cmd)
{
    string number;
    for(auto ch : cmd){if(is_numeric(ch))number.push_back(ch);}
    return stoi(number);
}

string get_subdir_string(string cmd)
{
    string output = "";

    for(int i=5; i<cmd.length(); i++)
    {
        output += cmd[i];
    }

    return output;
}

bool subdir_exist(Dir* _actual_dir, string _subdir_name)
{
    for(int j=0;j<_actual_dir->sub_dirs.size(); j++)
    {
        if(_actual_dir->sub_dirs[j]->dir==_subdir_name)
            return true;
    }
    return false;
}

void Print(Dir* _root)
{
    for(int i=0; i<_root->sub_dirs.size(); i++)
    {
        cout<<_root->sub_dirs[i]->dir<<endl;
        cout<<_root->sub_dirs[i]->size<<endl;

        if(!_root->sub_dirs[i]->sub_dirs.empty())
                Print(_root->sub_dirs[i]);
    }
}

void send_info2parent(Dir* _actual_dir, int new_size)
{
    _actual_dir->size += new_size;

    if(_actual_dir->parent!=NULL)
        send_info2parent(_actual_dir->parent,new_size);
}

int fn_part1(Dir* _root)
{
    int result = 0;
    int aux    = 0;
    for(int i=0; i<_root->sub_dirs.size(); i++)
    {
        if(_root->size<=100000)
            result += _root->size;
        if(!_root->sub_dirs[i]->sub_dirs.empty())  
            result += fn_part1(_root->sub_dirs[i]);
        else if(_root->sub_dirs[i]->sub_dirs.empty() && _root->sub_dirs[i]->size<=100000)
            result += _root->sub_dirs[i]->size;
    }
    return result;
}

int fn_part2(Dir* _root, int min)
{
    int result = 2147483647; // "inf." 

    if(_root->size>min && _root->size<result)
        result = _root->size;
    for(int i=0; i<_root->sub_dirs.size(); i++)
    {
        if(fn_part2(_root->sub_dirs[i],min)>min && fn_part2(_root->sub_dirs[i],min)<result)
            result = fn_part2(_root->sub_dirs[i],min);
    }
    return result;
}