#include "brain.h"

#include <iostream>

#include "utils.h"
#include "motors_manager.h"
#include "position_manager.h"

using namespace std;

static mutex running_mutex;

namespace brainiac
{

Brain& Brain::Instance()
{
    static Brain instance;
    return instance;
}

bool Brain::Start()
{
    if (Utils::SafeFlagCheckAndUpdate(running_mutex,
                                      m_running,
                                      "Brain thread already running; ignoring start request."))
    {
        return false;
    }

    if (!MotorsManager::Instance().Start() ||
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
        if (!Utils::SafeFlagCheck(running_mutex,
                                  m_running,
                                  "Stopping brain thread per request."))
        {
            break;
        }

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

    lock_guard<mutex> guard(running_mutex);
    m_running = false;

    m_thread.join();
}

}
