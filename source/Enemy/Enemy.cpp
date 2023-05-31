#include "source/Enemy/Enemy.h"
#include "source/Matrix/MatrixTrans.h"
Enemy::Enemy() {}

Enemy::~Enemy() {}






void Enemy::Initialize() {

	phase_ = Phase::Approach;


	worldTransform_.Initialize();
	worldTransform_.translation_.z =30.0f;
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("Stone.png");
}

void Enemy::ApproachUpdate() {
	
	Vector3 kEnemySpeed = {0.0f, 0.0f, -0.2f};
	worldTransform_.translation_ = Add(worldTransform_.translation_,kEnemySpeed);
	
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveUpdate() {

	worldTransform_.translation_.x += 0.2f;
	worldTransform_.translation_.y += 0.02f;
}

void (Enemy::*Enemy::spPhaseTable[])() = {

	&Enemy::ApproachUpdate,
	&Enemy::LeaveUpdate,

};


void Enemy::Update() {

	
	Vector3 move = {0, 0, 0};

	//const float kCharacterSpeed = 0.2f;

	//switch (phase_) 
	//{

	//	case Phase::Approach:
	//		
	//        move.z += -kCharacterSpeed;
	//	   
	//		if (worldTransform_.translation_.z<0.0f) {
	//		    phase_ = Phase::Leave;
	//		}

	//		break;

	//	case Phase::Leave:
	//	    move.x -= kCharacterSpeed;
	//	    move.z -= kCharacterSpeed;
	//	   
	//		
	//		break;

	//default:
	//	break;
	//}

    (this->*spPhaseTable[static_cast<size_t>(phase_)])(); 

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
}
