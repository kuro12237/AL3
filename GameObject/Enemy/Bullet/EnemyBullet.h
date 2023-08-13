#pragma once
#include"Matrix/MatrixTrans.h"
#include"Model.h"
#include<numbers>
class Player;

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(Model* model, Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

private:

	Vector3 SlerpFanc(Vector3 start,Vector3 end,float t);

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;
	Player* player_ = nullptr;

	Vector3 kVelocity_ = {};

	float Count = 0.0f;
	bool isDead_ = false;
};

