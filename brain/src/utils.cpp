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
    lock_guard<mutex> guard(mtx);
    flag = UnsafeFlagCheck(flag, err);
    return flag;
}

bool Utils::SafeFlagCheck(mutex &mtx,
                          bool flag,
                          const optional<string> &err)
{
    lock_guard<mutex> guard(mtx);
    return UnsafeFlagCheck(flag, err);
}

}
