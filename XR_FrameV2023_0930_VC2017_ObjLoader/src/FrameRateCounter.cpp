// �ǉ�
// Time.deltaTime�N���X
#include "FrameRateCounter.h"
#include <iostream>
#include <chrono>

FrameRateCounter::FrameRateCounter() : frameCount(0), DeltaTime(0.0f) {
    time(&startTime);
    lastTimePoint = std::chrono::high_resolution_clock::now();
}

void FrameRateCounter::Update() {
    // �t���[�����[�g�p
    time_t currentTime;
    time(&currentTime);
    // Time.deltaTime�p
    auto currentTimePoint = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTimePoint - lastTimePoint);

    DeltaTime = static_cast<float>(duration.count()) / 1e9f; // �o�ߎ��Ԃ�b�P�ʂɕϊ�

    // �t���[�����[�g��\��
    float updateTime = difftime(currentTime, startTime);
    if (updateTime >= 1) {
        PrintInfo();
        startTime = currentTime;
        frameCount = 0;
    }

    lastTimePoint = currentTimePoint;
    frameCount++;
}

void FrameRateCounter::PrintInfo() {
    std::cout << "Time.deltaTime: " << DeltaTime << " Frame Rate: " << frameCount << std::endl;
}

float FrameRateCounter::GetElapsedTime() const {
    return DeltaTime;
}


