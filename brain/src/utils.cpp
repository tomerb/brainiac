#include "utils.h"

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "global_defs.h"

using namespace std;

namespace brainiac
{

static bool UnsafeFlagCheck(bool flag, const optional<string> &err)
{
    if (flag)
    {
        return true;
    }
    else
    {
        if (err)
        {
            cout << err.value() << endl;
        }
        return false;
    }
}

bool Utils::SafeFlagCheckAndUpdate(mutex &mtx,
                                   bool &flag,
                                   const optional<string> &err)
{
    const lock_guard<mutex> guard(mtx);
    flag = UnsafeFlagCheck(flag == false, err);
    return flag;
}

bool Utils::SafeFlagCheck(mutex &mtx,
                          bool flag,
                          const optional<string> &err)
{
    const lock_guard<mutex> guard(mtx);
    return UnsafeFlagCheck(flag, err);
}

bool Utils::ParseConfigFile(const string &config_file, BrainConfig &brain_config)
{
    YAML::Node config = YAML::LoadFile(config_file);

    if (config[brain_config.number_of_motors.name])
    {
        brain_config.number_of_motors.value =
            config[brain_config.number_of_motors.name].as<int>();
    }

    if (config[brain_config.net_funcs.name])
    {
        brain_config.net_funcs.value =
            config[brain_config.net_funcs.name].as<vector<string>>();
    }

    return true;
}

}
