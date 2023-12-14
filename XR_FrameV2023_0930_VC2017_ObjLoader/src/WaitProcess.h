#pragma once

class WaitProcess {
private:
    float remainingTime;

public:
    WaitProcess();
    bool InWaitProcess;
    bool WaitForTime(float time, float deltaTime);
};
