#include <iostream>
#include <map>
#include <string>
#include <fstream> 

using namespace std;

enum RPS {_, Rock, Paper, Scissors};
enum LWD {Lost,Draw=3,Win=6};

std::map<string, int> map_part_1 = {    {"A X\r",   Rock+Draw,},
                                        {"A Y\r",   Paper+Win,},
                                        {"A Z\r",   Scissors+Lost,},
                                        {"B X\r",   Rock+Lost,},
                                        {"B Y\r",   Paper+Draw,},
                                        {"B Z\r",   Scissors+Win,},
                                        {"C X\r",   Rock+Win,},
                                        {"C Y\r",   Paper+Lost,},
                                        {"C Z\r",   Scissors+Draw,},
                                        };


std::map<string, int> map_part_2 = {    {"A X\r",   Scissors+Lost,},
                                        {"A Y\r",   Rock+Draw,},
                                        {"A Z\r",   Paper+Win,},
                                        {"B X\r",   Rock+Lost,},
                                        {"B Y\r",   Paper+Draw,},
                                        {"B Z\r",   Scissors+Win,},
                                        {"C X\r",   Paper+Lost,},
                                        {"C Y\r",   Scissors+Draw},
                                        {"C Z\r",   Rock+Win,},
                                        };

int main()
{
    std::map<string, int> resultados_p1(map_part_1);
    std::map<string, int> resultados_p2(map_part_2);
    int points = 0;    

    ifstream file1("input.txt");
    for(std::string line; std::getline(file1, line);) points += resultados_p1.find(line)->second;
    cout<<"En la primera parte se han obtenido "<<points<<" puntos"<<endl;
    file1.close();

    points = 0;
    ifstream file2("input.txt");
    for(std::string line; std::getline(file2, line);) points += resultados_p2.find(line)->second;
    cout<<"En la segunda parte se han obtenido "<<points<<" puntos"<<endl;
    file2.close();

    return 0;
}