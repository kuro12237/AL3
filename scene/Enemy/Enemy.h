#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include"scene/Enemy/Bullet/EnemyBullet.h"
#include"scene/Player/Player.h"

class Player;


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
	
	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	Vector3 LerpFanc(Vector3 v1, Vector3 v2);

private:
	

	void Fire();

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;


	Phase phase_ = Phase();

	std::list<EnemyBullet*> bullets_;

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;

	Player* player_ = nullptr;
};