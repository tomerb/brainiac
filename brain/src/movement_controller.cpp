#include "movement_controller.h"

#include <iostream>

namespace brainiac
{

const std::string MovementController::NAME = "MovementController";

bool MovementController::Exec([[maybe_unused]] const PositionsData &positions_data,
                              [[maybe_unused]] MotorsPosition &motors_positions) const
{
    return true;
}

}
