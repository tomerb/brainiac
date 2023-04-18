#pragma once

#include "global_defs.h"

namespace brainiac
{

class PositionManager
{
  public:
    PositionManager(const PositionManager&) = delete;
    PositionManager& operator=(const PositionManager&) = delete;

    bool Start();
    void Stop();

    void GetPosition(Position &position) const;

    static PositionManager& Instance();
 private:
    PositionManager() = default;
    ~PositionManager() = default;

    Position m_position;
};

}
