#pragma once

#include <string>

#include "net_func.h"

namespace brainiac
{

class ObstacleFinder : public NetFunc
{
 public:
    static const std::string NAME;

    virtual bool Exec(const PositionsData &positions_data,
                      MotorsPosition &motors_positions) const;
};

}
