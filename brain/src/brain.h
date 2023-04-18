#pragma once

#include <thread>
#include <mutex>

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
    Brain() = default;
    ~Brain() = default;

    void MainLoop();

    bool m_running;
    std::thread m_thread;
    std::mutex m_running_mutex;
};

}
