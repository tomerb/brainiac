#pragma once

#include <string>
#include <memory>

#include "net_func.h"

namespace brainiac
{

class NetFuncFactory
{
 public:
    static std::unique_ptr<NetFunc> Create(const std::string &net_func_name);
 private:
    NetFuncFactory() = default;
};

}
