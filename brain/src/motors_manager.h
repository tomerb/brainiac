#pragma once

#include <vector>

#include "global_defs.h"

namespace brainiac
{

class MotorsManager
{
  public:
    static const int MAX_NUMBER_OF_MOTORS;

    MotorsManager(const MotorsManager&) = delete;
    MotorsManager& operator=(const MotorsManager&) = delete;

    bool Start(int number_of_motors);
    void Stop();

    void GetPositions(std::vector<Position> &motors_positions) const;

    static MotorsManager& Instance();
 private:
    MotorsManager() = default;
    ~MotorsManager() = default;

    std::vector<Position> m_motors_positions;
    int m_number_of_motors;
};

}
