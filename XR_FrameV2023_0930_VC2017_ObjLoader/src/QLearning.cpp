// qlearning.cpp
#include "QLearning.h"
#include <iostream>
#include <cmath>

QLearning::QLearning() {
	for (int i = 0; i < NODENO; ++i) {
		qValues.push_back(INITIAL);
	}
}

QLearning::~QLearning() {
}

double QLearning::updateQValue(double oldValue, double reward) {
	return oldValue + ALPHA * (GAMMA * reward - oldValue);
}

int QLearning::selectActionWithExploration() {
	if (rand() / static_cast<double>(RAND_MAX) < EXPLORATION_RATE) {
		// �Â̊m���Ń����_���ȍs����I��
		return rand() % NODENO;
	}
	else {
		// 1-�Â̊m���ōł�����Q�l�����s����I��
		int bestAction = 0;
		double maxQValue = qValues[0];

		for (int i = 1; i < NODENO; ++i) {
			if (qValues[i] > maxQValue) {
				maxQValue = qValues[i];
				bestAction = i;
			}
		}
		return bestAction;
	}
}

double QLearning::calculateSkill() {
	// ���̏�肳�̌v�Z���@
	double skill = 0.0;
	for (int i = 0; i < NODENO; ++i) {
		skill += qValues[i];
	}
	return skill / NODENO; // ���ς����
}

void QLearning::updateScores(double hitRate, int buttonPresses, int enemiesDestroyed) {
	int action = selectActionWithExploration();
	// �v�Z�l�ɕϊ�
	CalcHitRate = CalcHitRatio(hitRate);
	CalcPushRate = CalcPushButtonRatio(buttonPresses);
	CalcKillRate = CalcEnemyDestroyRatio(enemiesDestroyed);
	
	// ��V�̌v�Z���@
	double reward = (CalcHitRate + 1.0 - CalcPushRate + CalcKillRate) / 3.0 * 100;
	double updateValue = std::max(0.0, std::min(100.0, updateQValue(qValues[action], reward)));
	// Q�l�̍X�V
	qValues[action] = updateValue;

	// Q�l�̏o��
	//for (int i = 1; i < NODENO; ++i) {
	//	std::cout << qValues[i] << "\t";
	//}
	//std::cout << std::endl;
}

double QLearning::CalcHitRatio(double hitRate)
{
	if (hitRate > 1) hitRate = 1;
	return hitRate;
}

double QLearning::CalcPushButtonRatio(int buttonPresses)
{
	const double ASSUME_MAX_PUSH = 50.0;
	if (buttonPresses == 0) return 0;
	return static_cast<double>(buttonPresses) / ASSUME_MAX_PUSH;
}

double QLearning::CalcEnemyDestroyRatio(int enemiesDestroyed)
{
	const double ASSUME_MAX_ENEMY = 10.0;
	double value = static_cast<double>(enemiesDestroyed) / ASSUME_MAX_ENEMY;
	return value;
}

