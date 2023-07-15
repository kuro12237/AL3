#pragma once
#include"Enemy/Base/EnemyBase.h"
#include"Vector3.h"
#include"Matrix/MatrixTrans.h"
#include"Enemy/Enemy.h"
#include"Enemy/Leave/EnemyLeave.h"
class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;

private:
	Vector3 enemyVelocity = {0.0f, 0.0f, -0.2f};
};