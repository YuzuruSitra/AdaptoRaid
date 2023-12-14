#ifndef FRAMERATECOUNTER_H
#define FRAMERATECOUNTER_H

#include <chrono> // chrono���C�u�������C���N���[�h

class FrameRateCounter {
public:
    FrameRateCounter();

    // �t���[�����Ƃ̍X�V���s�����\�b�h
    void Update();

    // �t���[�����[�g��\�����郁�\�b�h
    void PrintInfo();

    // �O�t���[������̌o�ߎ��Ԃ��擾���郁�\�b�h
    float GetElapsedTime() const;

private:
    time_t startTime;
    int frameCount;       // �t���[����
    float DeltaTime;      // �O�t���[������̌o�ߎ��ԁi�b�j
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTimePoint;
};

#endif // FRAMERATECOUNTER_H
