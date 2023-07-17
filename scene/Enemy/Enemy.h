#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include"scene/Enemy/Bullet/EnemyBullet.h"

class Enemy {
public:
	enum class Phase {
		Approach,
		Leave,
	};

	Enemy();
	~Enemy();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

	void PhaseInitialize();
	

private:
	

	void Fire();

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;


	Phase phase_ = Phase();

	std::list<EnemyBullet*> bullets_;

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;

};