// meta_ai.cpp
#include "meta_ai.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

// コンストラクタ: 重みを初期化
MetaAI::MetaAI() : weights{ 0.0, 0.0, 0.0 } {}

// 難易度を計算するメソッド
double MetaAI::calculateDifficulty(int hitCount, int bulletCount, int remainingEnemies, int maxEnemies) {
    // 入力値を正規化して配列に格納
    double input[2] = { static_cast<double>(hitCount) / bulletCount, static_cast<double>(remainingEnemies) / maxEnemies };

    // 予測値を計算
    double prediction = predict(input);

    // 実際の難易度係数を取得
    double actualDifficulty = getActualDifficulty();

    // 学習を行い、重みを更新
    learn(input, actualDifficulty, prediction);

    // 予測値を返す
    return prediction;
}

// 重み付きの入力をシグモイド関数に通すメソッド
double MetaAI::predict(double input[2]) {
    // 重み付けされた入力の総和を計算
    double sum = weights[0] + weights[1] * input[0] + weights[2] * input[1];

    // シグモイド関数を適用して結果を返す
    return sigmoid(sum);
}

// 学習メソッド: 重みの更新を行う
void MetaAI::learn(double input[2], double actualDifficulty, double prediction) {
    // 予測誤差を計算
    double error = actualDifficulty - prediction;

    // 重みの更新を行う
    for (int i = 0; i < 3; ++i) {
        if (i == 0) continue;
        weights[i] += ALPHA_META * error * input[i - 1];
        printf("Weight %i : %f\n",i, weights[i]);
    }
}

// シグモイド関数の実装
double MetaAI::sigmoid(double x) {
    // シグモイド関数の計算: 1 / (1 + exp(-x))
    return 1.0 / (1.0 + exp(-x));
}

// 実際の難易度係数を返すメソッド
double MetaAI::getActualDifficulty() {
    // 実際の難易度係数をプロジェクトの要件に基づいて取得
    // この部分はプロジェクトの具体的な要件に合わせて変更してください。
    return 0.8;
}
