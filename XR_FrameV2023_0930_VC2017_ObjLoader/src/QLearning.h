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

	static constexpr int NODENO = 15;  // ƒm[ƒh‚Ì”
	static constexpr double ALPHA = 0.3;  // ŠwKŒW”
	static constexpr double GAMMA = 0.9;  // Š„ˆø—¦
	static constexpr double INITIAL = 50; // Q’l‚Ì‰Šú’l
	static constexpr double EXPLORATION_RATE = 0.3;  // ’Tõ—¦
	double CalcHitRatio(double hitRate);
	double CalcPushButtonRatio(int buttonPresses);
	double CalcEnemyDestroyRatio(int enemiesDestroyed);
	double updateQValue(double oldValue, double reward);
	int selectActionWithExploration();
};

#endif // QLEARNING_H
