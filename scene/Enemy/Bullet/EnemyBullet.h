#pragma once
#include"scene/Matrix/MatrixTrans.h"
#include"Model.h"


class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(Model* model, Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	WorldTransform GetWorldTransform() { return worldTransform_; }

	bool IsDead() const { return isDead_; }


private:

	int32_t deathTimer_ = 300;

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;

	Vector3 Velocity_ ;

	// BulletLimitTime
	bool BulletDrawFlag = false;
	//int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};

