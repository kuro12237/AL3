#pragma once
#include"IEnemy.h"
#include"Enemy.h"

class EnemyStateLeave : public IEnemy {
public:
	void Update(Enemy* enemy) override;
};