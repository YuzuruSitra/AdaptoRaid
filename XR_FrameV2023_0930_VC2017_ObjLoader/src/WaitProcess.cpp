// WaitProcess.cpp
#include "WaitProcess.h"
#include <chrono>
#include <thread>

WaitProcess::WaitProcess() : arraySize(1), remainingTimes(arraySize, 0), inWaitProcesses(arraySize, false) {}

bool WaitProcess::WaitForTime(int id, float time, float deltaTime) {
    
    if (id < 0 || id >= arraySize) {
        printf("%i�͖�����ID�ł��B\n",id);
        return false;
    }

    if (!inWaitProcesses[id]) {
        remainingTimes[id] = time;
        inWaitProcesses[id] = true;
    }
    
    if (!inWaitProcesses[id]) return false;

    if (remainingTimes[id] >= 0) {
        remainingTimes[id] -= deltaTime;
        return false;
    }

    inWaitProcesses[id] = false;
    return true;
}

int WaitProcess::SelectID(){
    for (size_t i = 0; i < inWaitProcesses.size(); i++) if (!inWaitProcesses[i]) return i;
    return ResizeArrays();
}

// ID�̒ǉ����s
int WaitProcess::ResizeArrays() {
    arraySize += 1;
    remainingTimes.resize(arraySize, 0);
    inWaitProcesses.resize(arraySize, false);
    return arraySize - 1;
}

// ��~����
void WaitProcess::StopWaiting(int id) {
    if (id < 0 || id >= arraySize) {
        printf("%i�͖�����ID�ł��B\n", id);
        return;
    }
    remainingTimes[id] = 0;
    inWaitProcesses[id] = false;
}