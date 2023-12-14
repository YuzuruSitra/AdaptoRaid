// meta_ai.cpp
#include "meta_ai.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

// �R���X�g���N�^: �d�݂�������
MetaAI::MetaAI() : weights{ 0.0, 0.0, 0.0 } {}

// ��Փx���v�Z���郁�\�b�h
double MetaAI::calculateDifficulty(int hitCount, int bulletCount, int remainingEnemies, int maxEnemies) {
    // ���͒l�𐳋K�����Ĕz��Ɋi�[
    double input[2] = { static_cast<double>(hitCount) / bulletCount, static_cast<double>(remainingEnemies) / maxEnemies };

    // �\���l���v�Z
    double prediction = predict(input);

    // ���ۂ̓�Փx�W�����擾
    double actualDifficulty = getActualDifficulty();

    // �w�K���s���A�d�݂��X�V
    learn(input, actualDifficulty, prediction);

    // �\���l��Ԃ�
    return prediction;
}

// �d�ݕt���̓��͂��V�O���C�h�֐��ɒʂ����\�b�h
double MetaAI::predict(double input[2]) {
    // �d�ݕt�����ꂽ���͂̑��a���v�Z
    double sum = weights[0] + weights[1] * input[0] + weights[2] * input[1];

    // �V�O���C�h�֐���K�p���Č��ʂ�Ԃ�
    return sigmoid(sum);
}

// �w�K���\�b�h: �d�݂̍X�V���s��
void MetaAI::learn(double input[2], double actualDifficulty, double prediction) {
    // �\���덷���v�Z
    double error = actualDifficulty - prediction;

    // �d�݂̍X�V���s��
    for (int i = 0; i < 3; ++i) {
        if (i == 0) continue;
        weights[i] += ALPHA_META * error * input[i - 1];
        printf("Weight %i : %f\n",i, weights[i]);
    }
}

// �V�O���C�h�֐��̎���
double MetaAI::sigmoid(double x) {
    // �V�O���C�h�֐��̌v�Z: 1 / (1 + exp(-x))
    return 1.0 / (1.0 + exp(-x));
}

// ���ۂ̓�Փx�W����Ԃ����\�b�h
double MetaAI::getActualDifficulty() {
    // ���ۂ̓�Փx�W�����v���W�F�N�g�̗v���Ɋ�Â��Ď擾
    // ���̕����̓v���W�F�N�g�̋�̓I�ȗv���ɍ��킹�ĕύX���Ă��������B
    return 0.8;
}
