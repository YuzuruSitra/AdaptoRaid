// WaitProcess.h

#pragma once
#include <vector>

class WaitProcess {
private:
    int arraySize;
    std::vector<float> remainingTimes;
    std::vector<bool> inWaitProcesses;
    int ResizeArrays();

public:
    WaitProcess();
    int SelectID();
    bool WaitForTime(int id, float time, float deltaTime);
    void StopWaiting(int id);
    static constexpr int WAIT_ERROR_VALUE = -1;
};
