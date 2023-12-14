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

	static constexpr int NODENO = 15;  // ƒm[ƒh‚Ì”
	static constexpr double ALPHA = 0.1;  // ŠwKŒW”
	static constexpr double GAMMA = 0.9;  // Š„ˆø—¦

	int rand100();
	double updateQValue(double oldValue, double reward);
	int selectBestAction();
};

#endif // QLEARNING_H
