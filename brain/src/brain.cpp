#include "brain.h"

#include <iostream>

#include "utils.h"
#include "motors_manager.h"
#include "position_manager.h"
#include "global_defs.h"

using namespace std;

namespace brainiac
{

Brain& Brain::Instance()
{
    static Brain instance;
    return instance;
}

bool Brain::Start(const string &config_file)
{
    if (Utils::SafeFlagCheckAndUpdate(m_running_mutex,
                                      m_running,
                                      "Brain thread already running; ignoring start request."))
    {
        return false;
    }

    if (!Utils::ParseConfigFile(config_file))
    {
        Stop();
        return false;
    }

    if (!MotorsManager::Instance().Start(3) ||
        !PositionManager::Instance().Start())
    {
        Stop();
        return false;
    }

    m_thread = thread(&Brain::MainLoop, this);
    return true;
}

void Brain::MainLoop()
{
    while (true)
    {
        if (!Utils::SafeFlagCheck(m_running_mutex,
                                  m_running,
                                  "Stopping brain thread per request."))
        {
            break;
        }

        vector<Position> motors_positions;
        MotorsManager::Instance().GetPositions(motors_positions);

        Position position;
        PositionManager::Instance().GetPosition(position);

        // 1. Get motors + position
        // 2. Call net functions
        // 3. Handle camera
        // 4. sleep(100)
    }
}

void Brain::Stop()
{
    MotorsManager::Instance().Stop();
    PositionManager::Instance().Stop();

    lock_guard<mutex> guard(m_running_mutex);
    m_running = false;
    //guard.unlock();

    m_thread.join();
}

}
