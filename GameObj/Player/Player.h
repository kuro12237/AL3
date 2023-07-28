#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>
#include<Input.h>
#include"math/Matrix/MatrixTrans.h"
#include"GameObj/Player/Bullet/PlayerBullet.h"





#include <list>
//#incude"MatrixTrans.h"

class Player {
public:
	Player();
	~Player();

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection ViewProjection_);

	Vector3 GetWorldPosition();

	WorldTransform GetWorldTransform() { return worldTransform_; }

	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	Vector3 GetRotateMove() { return RotateMove_; }
	void SetParent(const WorldTransform* parent);
	void SetPlayerPos(Vector3 v);
		 
private:

	void Attack(Vector3 &position);

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;

	WorldTransform worldTransform_;
	
	Vector3 RotateMove_ = {0, 0, 0};

	Input* input_ = nullptr;
	
	std::list<PlayerBullet*> bullets_;

	int bulletCoolTimer = 0;
};


