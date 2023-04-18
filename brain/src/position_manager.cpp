#include "position_manager.h"

using namespace std;

namespace brainiac
{

PositionManager& PositionManager::Instance()
{
    static PositionManager instance;
    return instance;
}

bool PositionManager::Start()
{
    return false;
}

void PositionManager::Stop()
{
}

void PositionManager::GetPosition(Position &position) const
{
    position = m_position;
}

}
