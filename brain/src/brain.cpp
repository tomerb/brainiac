#include "brain.h"

#include <iostream>
#include <unistd.h>

#include "utils.h"
#include "motors_manager.h"
#include "position_manager.h"

using namespace std;

namespace brainiac
{

static const int MAIN_LOOP_DELAY_USEC = 100*1000; // 10Hz

Brain& Brain::Instance()
{
    static Brain instance;
    return instance;
}

bool Brain::Start(const string &config_file)
{
    if (!Utils::SafeFlagCheckAndUpdate(m_running_mutex,
                                       m_running,
                                       "Brain thread already running; ignoring start request."))
    {
        return false;
    }

    if (!Utils::ParseConfigFile(config_file, m_config))
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

static void DumpStatus(const PositionsData &positions_data)
{
    cout << "[Motors positions] - ";
    for (auto &pos : positions_data.motors) {
        cout << "(" << pos.x << "," << pos.y << "), ";
    }

    cout << endl << "[Position] - " << positions_data.pos.x << "," << positions_data.pos.y << endl;
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

        PositionsData positions_data;

        MotorsManager::Instance().GetPositions(positions_data.motors);

        PositionManager::Instance().GetPosition(positions_data.pos);

        // call net functions
        // handle camera

        DumpStatus(positions_data);

        usleep(MAIN_LOOP_DELAY_USEC);
    }
}

void Brain::Stop()
{
    MotorsManager::Instance().Stop();
    PositionManager::Instance().Stop();

    {
        const lock_guard<mutex> guard(m_running_mutex);
        m_running = false;
    }

    m_thread.join();
}

}
