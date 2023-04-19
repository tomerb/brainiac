#pragma once

#include <thread>
#include <mutex>
#include <map>
#include <memory>

#include "global_defs.h"
#include "net_func.h"

namespace brainiac
{

class Brain
{
  public:
    Brain(const Brain&) = delete;
    Brain& operator=(const Brain&) = delete;

    bool Start(const std::string &config_file);
    void Stop();

    static Brain& Instance();
 private:
     Brain() : m_running(false) {}
    ~Brain() = default;

    void MainLoop();
    void InitNetFuncs();

    bool m_running;
    std::thread m_thread;
    std::mutex m_running_mutex;
    BrainConfig m_config;
    std::map<std::string, std::unique_ptr<NetFunc>> m_net_funcs;
};

}
