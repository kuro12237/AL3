#include "Enemy.h"
#include "MatrixTrans.h"
Enemy::Enemy() {}

Enemy::~Enemy() {}



Vector3 Enemy::MoveApproch(const float speed, WorldTransform worldTransform_, Phase phase_) { 
	Vector3 result = {0, 0, 0};
	
	result.z += -speed;
	if (worldTransform_.translation_.z<0.0f) 
	{
		phase_ = Phase::Leave;
		return phase_;
	}


	return result;
}




void Enemy::Initialize() {

	phase_ = Phase::Approach;


	worldTransform_.Initialize();
	worldTransform_.translation_.z =30.0f;
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("kamata.ico");
}

void Enemy::Update() {

	
	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	switch (phase_) 
	{

		case Phase::Approach:

			move = MoveApproch(kCharacterSpeed, worldTransform_, phase_);

			/*
	        move.z += -kCharacterSpeed;
		   
			if (worldTransform_.translation_.z<0.0f) {
			    phase_ = Phase::Leave;
			}*/

			break;

		case Phase::Leave:
		    move.x -= kCharacterSpeed;
		    move.z -= kCharacterSpeed;
		   
			
			break;

	default:
		break;
	}

	 
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
}
