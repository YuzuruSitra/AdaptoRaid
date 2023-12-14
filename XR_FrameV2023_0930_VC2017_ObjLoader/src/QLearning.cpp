// qlearning.cpp
#include "QLearning.h"
#include <iostream>
#include <cmath>

QLearning::QLearning() {
	for (int i = 0; i < NODENO; ++i) {
		qValues.push_back(rand100());
	}
}

QLearning::~QLearning() {
}

double QLearning::updateQValue(double oldValue, double reward) {
	return oldValue + ALPHA * (GAMMA * reward - oldValue);
}

int QLearning::selectBestAction() {
	int bestAction = 1;
	double maxQValue = qValues[1];

	for (int i = 2; i < NODENO; ++i) {
		if (qValues[i] > maxQValue) {
			maxQValue = qValues[i];
			bestAction = i;
		}
	}

	return bestAction;
}

double QLearning::calculateSkill() {
	// ���̏�肳�̌v�Z���@
	double skill = 0.0;
	for (int i = 1; i < NODENO; ++i) {
		skill += qValues[i];
	}

	return skill / (NODENO - 1); // ���ς����
}

void QLearning::updateScores(double accuracy, int buttonPresses, int enemiesDestroyed) {
	int action = selectBestAction();
	// ���̕�V�̌v�Z���@
	double reward = (accuracy + 1.0 - static_cast<double>(buttonPresses) / 100.0 + static_cast<double>(enemiesDestroyed) / 10.0) / 3.0;

	// Q�l�̍X�V
	qValues[action] = updateQValue(qValues[action], reward);

	// Q�l�̏o��
	for (int i = 1; i < NODENO; ++i) {
		std::cout << qValues[i] << "\t";
	}
	std::cout << std::endl;
}

int QLearning::rand100() {
	int rnd;
	while ((rnd = rand()) == RAND_MAX);
	return static_cast<int>((static_cast<double>(rnd) / RAND_MAX) * 101);
}