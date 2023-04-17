#include "position_manager.h"

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

}
