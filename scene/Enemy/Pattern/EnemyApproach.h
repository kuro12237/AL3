#pragma once
#include"scene/Enemy/Enemy.h"

#include"Enemy/Base/EnemyStateBase.h"
#include"scene/Matrix/MatrixTrans.h"
#include"scene/Enemy/Pattern/EnemyStateLeave.h"

class EnemyStateApproach : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;

private:
	Vector3 enemyVelocity = {0.0f, 0.0f, -0.2f};

};