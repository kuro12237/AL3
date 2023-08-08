#pragma once

#include"Vector3.h"
#include"MatrixTrans.h"
#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyLeave.h"
#include"IEnemyState.h"
class EnemyStateApproach : public IEnemyState {

public:
	void Update(Enemy* enemy) override;

private:
	Vector3 enemyVelocity = {0.0f, 0.0f, -0.2f};
};