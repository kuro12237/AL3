#pragma once
#include"IEnemyState.h"
#include"Enemy.h"

class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* enemy) override;
};