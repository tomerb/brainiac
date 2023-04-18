#include "utils.h"

#include <iostream>

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
    cout << "test";
    return UnsafeFlagCheck(flag, err);
}

bool Utils::ParseConfigFile(const string &config_file)
{
    cout << config_file << endl;
    return true;
}

}
