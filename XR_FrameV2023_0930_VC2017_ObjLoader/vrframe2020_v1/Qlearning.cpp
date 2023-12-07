// qlearning.cpp
#include "qlearning.h"
#include "meta_ai.h"
#include <stdio.h>
#include <stdlib.h>

void QLearning::train() {
    int i;
    int s = 0;
    int t;
    int qvalue[NODENO];

    srand(SEED);

    for (i = 0; i < NODENO; i++)
        qvalue[i] = rand100();
    //printqvalue(qvalue);

    MetaAI metaAI;

    for (i = 0; i < GENMAX; i++) {
        s = 0;
        for (t = 0; t < 3; t++) {
            s = selecta(s, qvalue);
            qvalue[s] = updateq(s, qvalue, metaAI);
        }
        //printqvalue(qvalue);
    }
}

int QLearning::updateq(int s, int qvalue[NODENO], MetaAI& metaAI) {
    int qv;
    int qmax;

    if (s > 6) {
        if (s == 14)
            qv = qvalue[s] + ALPHA * (1000 - qvalue[s]) * metaAI.calculateDifficulty(80, 100, 5, 24);
        else if (s == 11)
            qv = qvalue[s] + ALPHA * (500 - qvalue[s]) * metaAI.calculateDifficulty(70, 100, 10, 24);
        else
            qv = qvalue[s];
    }
    else {
        if ((qvalue[2 * s + 1]) > (qvalue[2 * s + 2]))
            qmax = qvalue[2 * s + 1];
        else
            qmax = qvalue[2 * s + 2];
        qv = qvalue[s] + ALPHA * (GAMMA * qmax - qvalue[s]);
    }

    return qv;
}

int QLearning::selecta(int olds, int qvalue[NODENO]) {
    int s;

    if (rand1() < EPSILON) {
        if (rand01() == 0)
            s = 2 * olds + 1;
        else
            s = 2 * olds + 2;
    }
    else {
        if ((qvalue[2 * olds + 1]) > (qvalue[2 * olds + 2]))
            s = 2 * olds + 1;
        else
            s = 2 * olds + 2;
    }

    return s;
}

void QLearning::printqvalue(int qvalue[NODENO]) {
    int i;

    for (i = 1; i < NODENO; i++)
        printf("%d\t", qvalue[i]);

    printf("\n");
}

// 0.0-1.0
double QLearning::rand1() {
    return (double)rand() / RAND_MAX;
}

// 0or1
int QLearning::rand01() {
    int rnd;

    while ((rnd = rand()) == RAND_MAX);

    return (int)((double)rnd / RAND_MAX * 2);
}

// 0-100
int QLearning::rand100() {
    int rnd;

    while ((rnd = rand()) == RAND_MAX);

    return (int)((double)rnd / RAND_MAX * 101);
}