#pragma once


class Enemy;

class BaseEnemyState {
public:
	BaseEnemyState();

	virtual void Update(Enemy* enemy) = 0;

protected:
};