#pragma once

namespace brainiac
{

class PositionManager
{
  public:
    PositionManager(const PositionManager&) = delete;
    PositionManager& operator=(const PositionManager&) = delete;

    bool Start();
    void Stop();

    static PositionManager& Instance();
 private:
    PositionManager() = default;
    ~PositionManager() = default;
};

}
