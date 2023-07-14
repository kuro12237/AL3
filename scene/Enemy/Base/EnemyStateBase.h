#pragma once
#include"scene/Enemy/Enemy.h"


class BaseEnemyState {
public:
	BaseEnemyState();

	virtual void Update(Enemy* enemy) = 0;

protected:
};