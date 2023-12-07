// qlearning.h
#pragma once
#include "meta_ai.h"

class QLearning {
public:
    void train();

private:
    static constexpr int NODENO = 15;
    static constexpr int SEED = 32767;
    static constexpr int GENMAX = 1000;
    static constexpr double ALPHA = 0.1;
    static constexpr double GAMMA = 0.9;
    static constexpr double EPSILON = 0.3;

    int updateq(int s, int qvalue[NODENO], MetaAI& metaAI);

    int selecta(int olds, int qvalue[NODENO]);

    void printqvalue(int qvalue[NODENO]);

    double rand1();

    int rand01();

    int rand100();
};