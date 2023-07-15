#pragma once
#include"Enemy/Base/EnemyBase.h"
#include"Enemy/Enemy.h"

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;
};