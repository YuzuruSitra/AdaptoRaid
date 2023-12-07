#ifndef FRAMERATECOUNTER_H
#define FRAMERATECOUNTER_H

#include <chrono> // chronoライブラリをインクルード

class FrameRateCounter {
public:
    FrameRateCounter();

    // フレームごとの更新を行うメソッド
    void Update();

    // フレームレートを表示するメソッド
    void PrintInfo();

    // 前フレームからの経過時間を取得するメソッド
    float GetElapsedTime() const;

private:
    time_t startTime;
    int frameCount;       // フレーム数
    float DeltaTime;      // 前フレームからの経過時間（秒）
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTimePoint;
};

#endif // FRAMERATECOUNTER_H
