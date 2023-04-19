#include "brain.h"

#include <iostream>
#include <unistd.h>

#include "utils.h"
#include "motors_manager.h"
#include "position_manager.h"
#include "net_func_factory.h"

using namespace std;

namespace brainiac
{

static const int MAIN_LOOP_DELAY_USEC = 100*1000; // 10Hz

Brain& Brain::Instance()
{
    static Brain instance;
    return instance;
}

void Brain::InitNetFuncs()
{
    m_net_funcs.clear();

    for (auto func : m_config.net_funcs.value)
    {
        m_net_funcs[func] = NetFuncFactory::Create(func);
    }
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

    if (!MotorsManager::Instance().Start(m_config.number_of_motors.value) ||
        !PositionManager::Instance().Start())
    {
        Stop();
        return false;
    }

    InitNetFuncs();

    m_thread = thread(&Brain::MainLoop, this);

    return true;
}

static void DumpStatus(const PositionsData &positions_data,
                       const MotorsPosition &new_motors_positions)
{
    cout << "[Motors positions] - ";
    for (auto &pos : positions_data.motors)
    {
        cout << "(" << pos.x << "," << pos.y << "), ";
    }

    cout << endl << "[Position] - " << positions_data.pos.x << "," << positions_data.pos.y;

    cout << endl << "[Net actions] - ";
    for (auto &pos : new_motors_positions)
    {
        cout << "(" << pos.x << "," << pos.y << "), " << endl;
    }
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

        MotorsPosition new_motors_positions;
        for (auto &func : m_net_funcs)
        {
            func.second->Exec(positions_data, new_motors_positions);
        }

        // TODO: handle camera data

        DumpStatus(positions_data, new_motors_positions);

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
