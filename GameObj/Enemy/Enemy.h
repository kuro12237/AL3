#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include"Obj/Enemy/Bullet/EnemyBullet.h"
#include"Obj/Player/Player.h"

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

	void OnCollision();

	Vector3 GetWorldPosition();

	Vector3 LerpFanc(Vector3 v1, Vector3 v2);

	
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }


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