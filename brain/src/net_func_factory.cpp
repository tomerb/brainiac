#include "net_func_factory.h"

#include "movement_controller.h"
#include "obstacle_finder.h"

using namespace std;

namespace brainiac
{

unique_ptr<NetFunc> NetFuncFactory::Create(const string &net_func_name)
{
    if (net_func_name.compare(MovementController::NAME) == 0)
    {
        return make_unique<MovementController>();
    }
    else if (net_func_name.compare(ObstacleFinder::NAME) == 0)
    {
        return make_unique<ObstacleFinder>();
    }
    else
    {
        return nullptr;
    }
}

}
