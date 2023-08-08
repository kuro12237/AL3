#pragma once
#include"GameObject/Enemy/Base/EnemyBase.h"
#include"GameObject/Enemy/Enemy.h"

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;
};