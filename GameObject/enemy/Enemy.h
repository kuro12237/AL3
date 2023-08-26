#pragma once

//#include "GameObj/Enemy/Bullet/EnemyBullet.h"
#include "GameObject/Player/Player.h"
#include <Model.h>
#include <WorldTransform.h>

class Player;

class GameScene;

class Enemy {
public:
	enum class Phase {
		Approach,
		Leave,
	};

	Enemy();
	~Enemy();

	void Initialize(Vector3 v);

	void Update();

	void Draw(ViewProjection ViewProjection_);

	void PhaseInitialize();

	void SetPlayer(Player* player) { player_ = player; }

	void OnCollision();

	Vector3 GetWorldPosition();

	Vector3 LerpFanc(Vector3 v1, Vector3 v2);

	// const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const { return isDead_; }

private:
	void Fire();

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;

	static const int kFireInterval = 60;

	int32_t FireTimer = 0;

	Player* player_ = nullptr;
	GameScene* gameScene_ = nullptr;

	bool isDead_ = false;
};