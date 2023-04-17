#pragma once

namespace brainiac
{

class MotorsManager
{
  public:
    MotorsManager(const MotorsManager&) = delete;
    MotorsManager& operator=(const MotorsManager&) = delete;

    bool Start();
    void Stop();

    static MotorsManager& Instance();
 private:
    MotorsManager() = default;
    ~MotorsManager() = default;
};

}
