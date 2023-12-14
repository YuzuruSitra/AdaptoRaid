// 追加
// Time.deltaTimeクラス
#include "FrameRateCounter.h"
#include <iostream>
#include <chrono>

FrameRateCounter::FrameRateCounter() : frameCount(0), DeltaTime(0.0f) {
    time(&startTime);
    lastTimePoint = std::chrono::high_resolution_clock::now();
}

void FrameRateCounter::Update() {
    // フレームレート用
    time_t currentTime;
    time(&currentTime);
    // Time.deltaTime用
    auto currentTimePoint = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTimePoint - lastTimePoint);

    DeltaTime = static_cast<float>(duration.count()) / 1e9f; // 経過時間を秒単位に変換

    // フレームレートを表示
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


