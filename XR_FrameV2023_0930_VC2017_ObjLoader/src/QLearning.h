#pragma once
#ifndef QLEARNING_H
#define QLEARNING_H

#include <vector>


class QLearning {

public:
	QLearning();
	~QLearning();

	double calculateSkill();
	void updateScores(double accuracy, int buttonPresses, int enemiesDestroyed);
	double CalcHitRate;
	double CalcPushRate;
	double CalcKillRate;

private:
	std::vector<double> qValues;

	static constexpr int NODENO = 15;  // �m�[�h�̐�
	static constexpr double ALPHA = 0.7;  // �w�K�W��
	static constexpr double GAMMA = 0.99;  // ������
	static constexpr double INITIAL = 50; // Q�l�̏����l
	static constexpr double EXPLORATION_RATE = 0.5;  // �T����
	double CalcHitRatio(double hitRate);
	double CalcPushButtonRatio(int buttonPresses);
	double CalcEnemyDestroyRatio(int enemiesDestroyed);
	double updateQValue(double oldValue, double reward);
	int selectActionWithExploration();
};

#endif // QLEARNING_H
