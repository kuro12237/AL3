#pragma once
#include"math/Matrix/MatrixTrans.h"
#include"Model.h"


class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();


	void Initialize(Model* model, Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);


private:


	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;

	Vector3 kVelocity_ = {};


	bool isDead_ = false;
};

