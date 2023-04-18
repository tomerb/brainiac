#pragma once

#include <vector>
#include <map>
#include <string>

namespace brainiac
{

struct Position
{
    int x;
    int y;
};

typedef std::vector<Position> MotorsPosition;

struct PositionsData
{
    MotorsPosition motors;
    Position pos;
};

class NetFunc;

struct BrainConfig
{
    template<typename T> struct Pair
    {
        std::string name;
        T value;
    };

    Pair<int> number_of_motors;
    Pair< std::map<std::string, NetFunc*> > net_funcs;

    BrainConfig()
    {
        number_of_motors.name = "number_of_motors";
        net_funcs.name = "net_funcs";
    }
};

}
