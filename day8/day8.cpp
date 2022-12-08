#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int inline ch2int(char x){return (int)x-'0';}
int check_row_visibility(vector<string> trees, int i, int k);
int check_col_visibility(vector<string> trees, int i, int k);
int get_tree_score(vector<string> trees, int i, int k);

int main()
{
    ifstream input("input.txt");
    vector<string>  trees;
    int visible_trees = 0;
    int max_score = 0;

    for(string line; getline(input, line);){trees.push_back(line);}
    for(int i=0;i<trees.size();i++)
    {
        for(int k=0;k<trees[i].length();k++)
        {
            if(k==trees[i].length()-1||k==0) visible_trees++;
            else if(i==trees.size()-1||i==0) visible_trees++;            
            else if(check_row_visibility(trees,i,k)+check_col_visibility(trees,i,k)>0) visible_trees++;
        
            if(max_score<get_tree_score(trees,i,k)) max_score = get_tree_score(trees,i,k);
        }
    }
    cout<<"The 1st part solution is: "<<visible_trees<<endl;
    cout<<"The 2nd part solution is: "<<max_score<<endl;
    return 0;
}

int check_row_visibility(vector<string> trees, int i, int k)
{  
    int r       = 1;
    int l       = 1;
    for(int h=k+1;h<trees[i].length();h++)
        if(ch2int(trees[i][k])<=ch2int(trees[i][h]))
            r = 0;
    for(int h=k-1;h>=0;h--)
        if(ch2int(trees[i][k])<=ch2int(trees[i][h]))
            l = 0;
    return r+l;
}

int check_col_visibility(vector<string> trees, int i, int k)
{
    int up      = 1;
    int down    = 1;
    for(int v=i+1;v<trees.size();v++)
        if(ch2int(trees[i][k])<=ch2int(trees[v][k]))
            up = 0;
    for(int v=i-1;v>=0;v--)
        if(ch2int(trees[i][k])<=ch2int(trees[v][k]))
            down = 0;
    return up+down;
}

int get_tree_score(vector<string> trees, int i, int k)
{
    int scores[4] = {0};
    // Up
    for(int v=i+1;v<trees.size();v++)
    {
        if(ch2int(trees[i][k])<=ch2int(trees[v][k]))
        {
            scores[0]++;
            break;
        }
        else
            scores[0]++;
    }    
    // Down
    for(int v=i-1;v>=0;v--)
    {
        if(ch2int(trees[i][k])<=ch2int(trees[v][k]))
        {
            scores[1]++;
            break;
        }
        else
            scores[1]++;
    }
    // Right
    for(int h=k+1;h<trees[i].length();h++)
    {
        if(ch2int(trees[i][k])<=ch2int(trees[i][h]))
        {
            scores[2]++;
            break;
        }
        else
            scores[2]++;
    }
    // Left
    for(int h=k-1;h>=0;h--)
    {    
        if(ch2int(trees[i][k])<=ch2int(trees[i][h]))
        {
            scores[3]++;
            break;
        }
        else
            scores[3]++;
    }
    return scores[0]*scores[1]*scores[2]*scores[3];
}