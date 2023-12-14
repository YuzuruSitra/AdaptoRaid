// meta_ai.h
#pragma once

class MetaAI {
public:
    MetaAI();

    double calculateDifficulty(int hitCount, int bulletCount, int remainingEnemies, int maxEnemies);

private:
    static constexpr double ALPHA_META = 0.1;

    double weights[3];  // 重み (w0: バイアス, w1: 命中率の係数, w2: 残りの敵の係数)

    double predict(double input[2]);

    void learn(double input[2], double actualDifficulty, double prediction);

    double sigmoid(double x);

    double getActualDifficulty();
};
