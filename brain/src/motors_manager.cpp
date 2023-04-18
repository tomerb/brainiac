#include "motors_manager.h"

using namespace std;

namespace brainiac
{

const int MotorsManager::MAX_NUMBER_OF_MOTORS = 10;

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

    return false;
}

void MotorsManager::Stop()
{
}

void MotorsManager::GetPositions(vector<Position> &motors_positions) const
{
    motors_positions = m_motors_positions;
}

}
