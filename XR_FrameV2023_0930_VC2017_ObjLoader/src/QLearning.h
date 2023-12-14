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

private:
	std::vector<double> qValues;

	static constexpr int NODENO = 15;  // �m�[�h�̐�
	static constexpr double ALPHA = 0.1;  // �w�K�W��
	static constexpr double GAMMA = 0.9;  // ������

	int rand100();
	double updateQValue(double oldValue, double reward);
	int selectBestAction();
};

#endif // QLEARNING_H
