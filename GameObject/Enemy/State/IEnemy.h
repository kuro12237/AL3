#pragma once


class Enemy;

class IEnemy {
public:
	//IEnemy();

	virtual void Update(Enemy* enemy) = 0;

protected:
};