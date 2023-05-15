#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>
#include<Input.h>
#include"MatrixTrans.h"
#include "PlayerBullet.h" 

//#incude"MatrixTrans.h"


class Player {
public:
	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

private:

	void Attack(Vector3 &position);

    void Rotate(Vector3& RotateMove);

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;
	


	Input* input_ = nullptr;
	
	PlayerBullet * bullet_=nullptr;
};


