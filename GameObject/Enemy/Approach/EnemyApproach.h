#pragma once

#include"Vector3.h"
#include"Matrix/MatrixTrans.h"
#include"GameObject/Enemy/Enemy.h"
#include"GameObject/Enemy/Approach/EnemyApproach.h"
#include"GameObject/Enemy/Leave/EnemyLeave.h"
class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;

private:
	Vector3 enemyVelocity = {0.0f, 0.0f, -0.2f};
};