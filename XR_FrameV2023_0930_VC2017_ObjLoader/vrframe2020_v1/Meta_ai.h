// meta_ai.h
#pragma once

class MetaAI {
public:
    MetaAI();

    double calculateDifficulty(int hitCount, int bulletCount, int remainingEnemies, int maxEnemies);

private:
    static constexpr double ALPHA_META = 0.1;

    double weights[3];  // �d�� (w0: �o�C�A�X, w1: �������̌W��, w2: �c��̓G�̌W��)

    double predict(double input[2]);

    void learn(double input[2], double actualDifficulty, double prediction);

    double sigmoid(double x);

    double getActualDifficulty();
};
