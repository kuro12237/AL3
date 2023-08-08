#pragma once
#include"EnemyBase.h"
#include"Enemy.h"

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;
};