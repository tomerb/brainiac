#pragma once

#include <thread>
#include <mutex>

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

    void GetPosition(Position &position);

    void MainLoop();

    static PositionManager& Instance();
 private:
    PositionManager() = default;
    ~PositionManager() = default;

    Position m_position;
    bool m_running;
    std::thread m_thread;
    std::mutex m_running_mutex;
};

}
