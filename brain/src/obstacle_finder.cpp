#include "obstacle_finder.h"

#include <iostream>

namespace brainiac
{

const std::string ObstacleFinder::NAME = "ObstacleFinder";

bool ObstacleFinder::Exec([[maybe_unused]] const PositionsData &positions_data,
                          [[maybe_unused]] MotorsPosition &motors_positions) const
{
    std::cout << positions_data.pos.x << std::endl;
    return true;
}

}
