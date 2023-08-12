#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include"GameObject/Enemy/Bullet/EnemyBullet.h"
#include"GameObject/TimedCall/TimedCall.h"

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
	
	void FireReset();

	void Fire();

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;


	Phase phase_ = Phase();

	std::list<EnemyBullet*> bullets_;

	std::list<TimedCall*> timedCall_;

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;


};