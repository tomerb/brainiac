#include "position_manager.h"

#include <unistd.h>

#include "utils.h"

using namespace std;

namespace brainiac
{

static const int MAIN_LOOP_DELAY_USEC = 4*1000; // 250Hz

PositionManager& PositionManager::Instance()
{
    static PositionManager instance;
    return instance;
}

bool PositionManager::Start()
{
    if (!Utils::SafeFlagCheckAndUpdate(m_running_mutex,
                                       m_running,
                                       "Brain thread already running; ignoring start request."))
    {
        return false;
    }

    m_thread = thread(&PositionManager::MainLoop, this);

    return true;
}

void PositionManager::Stop()
{
    {
        const lock_guard<mutex> guard(m_running_mutex);
        m_running = false;
    }

    m_thread.join();
}

void PositionManager::GetPosition(Position &position)
{
    const lock_guard<mutex> guard(m_running_mutex);
    position = m_position;
}

void PositionManager::MainLoop()
{
    while (true)
    {
        if (!Utils::SafeFlagCheck(m_running_mutex,
                                  m_running,
                                  "Stopping position thread per request."))
        {
            break;
        }

        {
            const lock_guard<mutex> guard(m_running_mutex);
            m_position = Position{1,1};
        }

        usleep(MAIN_LOOP_DELAY_USEC);
    }
}

}
