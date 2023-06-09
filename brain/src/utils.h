#pragma once

#include <optional>
#include <thread>
#include <mutex>

#include "global_defs.h"

namespace brainiac
{

class Utils
{
 public:
    static bool SafeFlagCheckAndUpdate(std::mutex &mtx,
                                       bool &condition,
                                       const std::optional<std::string> &err = std::nullopt);
    static bool SafeFlagCheck(std::mutex &mtx,
                              bool condition,
                              const std::optional<std::string> &err = std::nullopt);
    static bool ParseConfigFile(const std::string &config_file, BrainConfig &brain_config);
 private:
    Utils() = default;
};

}
