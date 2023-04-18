#pragma once

#include <vector>
#include <thread>
#include <mutex>

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

    void GetPositions(std::vector<Position> &motors_positions);

    static MotorsManager& Instance();
 private:
    MotorsManager() = default;
    ~MotorsManager() = default;

    void MainLoop();

    std::vector<Position> m_motors_positions;
    int m_number_of_motors;
    bool m_running;
    std::thread m_thread;
    std::mutex m_running_mutex;
};

}
