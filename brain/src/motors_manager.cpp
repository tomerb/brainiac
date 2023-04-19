#include "motors_manager.h"

#include <unistd.h>

#include "utils.h"

using namespace std;

namespace brainiac
{

const int MotorsManager::MAX_NUMBER_OF_MOTORS = 10;

static const int MAIN_LOOP_DELAY_USEC = 10*1000; // 100Hz

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

    m_motors_positions.resize(number_of_motors);

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
            for (auto &pos : m_motors_positions)
            {
                pos.x *= 1.1;
                pos.y *= 1.1;
            }
        }

        usleep(MAIN_LOOP_DELAY_USEC);
    }
}

}
