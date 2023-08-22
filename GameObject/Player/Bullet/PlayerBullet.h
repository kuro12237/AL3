#pragma once
#include"Model.h"
#include"WorldTransform.h"


class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize();

	void Update();


	void Draw();

	static const int32_t kLifeTime = 60 * 2;

	bool IsDead() const { return isDead_; }


private:

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	// BulletLimitTime

	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;


};
