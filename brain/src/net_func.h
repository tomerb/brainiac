#pragma once

#include "global_defs.h"

namespace brainiac
{

class NetFunc
{
 public:
    virtual ~NetFunc() {}
    virtual bool Exec(const PositionsData &positions_data,
                      MotorsPosition &motors_positions) const = 0;
};

}
