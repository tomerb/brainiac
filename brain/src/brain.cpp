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
    if (!Utils::SafeFlagCheckAndUpdate(m_running_mutex,
                                       m_running,
                                       "Brain thread already running; ignoring start request."))
    {
        return false;
    }
    cout << "breaking3\n";

    if (!Utils::ParseConfigFile(config_file))
    {
        Stop();
        return false;
    }
        cout << "breaking2\n";

    if (!MotorsManager::Instance().Start(3) ||
        !PositionManager::Instance().Start())
    {
        Stop();
        return false;
    }
        cout << "breaking4\n";

    m_thread = thread(&Brain::MainLoop, this);

    return true;
}

static void DumpStatus(const vector<Position> &motors_positions,
                       const Position &position)
{
    cout << "[Motors positions] - ";
    for (auto &pos : motors_positions) {
        cout << "(" << pos.x << "," << pos.y << "), ";
    }

    cout << endl << "[Position] - " << position.x << "," << position.y << endl;
}

void Brain::MainLoop()
{
        cout << "breaking5\n";
    while (true)
    {
        if (!Utils::SafeFlagCheck(m_running_mutex,
                                  m_running,
                                  "Stopping brain thread per request."))
        {
        cout << "breaking6\n";
            break;
        }
        cout << "breaking7\n";

        vector<Position> motors_positions;
        MotorsManager::Instance().GetPositions(motors_positions);

        Position position;
        PositionManager::Instance().GetPosition(position);

        DumpStatus(motors_positions, position);

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

    {
        const lock_guard<mutex> guard(m_running_mutex);
        m_running = false;
    }

    m_thread.join();
}

}
