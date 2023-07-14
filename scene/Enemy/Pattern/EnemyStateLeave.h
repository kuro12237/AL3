#pragma once
#include"scene/Enemy/Base/EnemyStateBase.h"
#include"scene/Enemy/Enemy.h"

class EnemyStateLeave : public BaseEnemyState {
public:
	void Update(Enemy* enemy) override;

};