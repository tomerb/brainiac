#include "motors_manager.h"

namespace brainiac
{

MotorsManager& MotorsManager::Instance()
{
    static MotorsManager instance;
    return instance;
}

bool MotorsManager::Start()
{
    return false;
}

void MotorsManager::Stop()
{
}

}
