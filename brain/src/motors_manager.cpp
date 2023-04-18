#include "motors_manager.h"

#include <unistd.h>

#include "utils.h"

using namespace std;

namespace brainiac
{

const int MotorsManager::MAX_NUMBER_OF_MOTORS = 10;

static const int MAIN_LOOP_DELAY_MS = 10*1000; // 100Hz

MotorsManager& MotorsManager::Instance()
{
    static MotorsManager instance;
    return instance;
}

bool MotorsManager::Start(int number_of_motors)
{
    if (number_of_motors <= 0 || number_of_motors > MAX_NUMBER_OF_MOTORS)
    {
        return false;
    }

    if (!Utils::SafeFlagCheckAndUpdate(m_running_mutex,
                                       m_running,
                                       "Brain thread already running; ignoring start request."))
    {
        return false;
    }

    m_thread = thread(&MotorsManager::MainLoop, this);

    return true;
}

void MotorsManager::Stop()
{
    {
        const lock_guard<mutex> guard(m_running_mutex);
        m_running = false;
    }

    m_thread.join();
}

void MotorsManager::GetPositions(vector<Position> &motors_positions)
{
    const lock_guard<mutex> guard(m_running_mutex);
    motors_positions = m_motors_positions;
}

void MotorsManager::MainLoop()
{
    while (true)
    {
        if (!Utils::SafeFlagCheck(m_running_mutex,
                                  m_running,
                                  "Stopping motors thread per request."))
        {
            break;
        }

        {
            const lock_guard<mutex> guard(m_running_mutex);
            m_motors_positions[0] = Position{1,1};
            m_motors_positions[1] = Position{2,2};
            m_motors_positions[2] = Position{3,3};
        }

        usleep(MAIN_LOOP_DELAY_MS);
    }
}

}
