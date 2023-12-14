#include "WaitProcess.h"
#include <chrono>
#include <thread>

WaitProcess::WaitProcess() : InWaitProcess(false), remainingTime(0) {}

bool WaitProcess::WaitForTime(float time, float deltaTime) {
    
    if (!InWaitProcess) {
        remainingTime = time;
        InWaitProcess = true;
    }

    if (remainingTime >= 0) {
        std::this_thread::sleep_for(std::chrono::duration<float>(deltaTime));
        remainingTime -= deltaTime;
        return false;
    }

    InWaitProcess = false;
    return true;
}
