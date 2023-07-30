#include "Enemy.h"
#include"math/Matrix/MatrixTrans.h"
#include"GameScene.h"
Enemy::Enemy() {}

Enemy::~Enemy() 
{
	model_->~Model();
	/*
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	*/
}



void Enemy::Initialize(Vector3 v) {

	phase_ = Phase::Approach;
	PhaseInitialize();

	worldTransform_.Initialize();
	worldTransform_.translation_ = v;
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("Dirt.png");
}

void Enemy::Update() {




	switch (phase_) 
	{

		case Phase::Approach:
			
	       // worldTransform_.translation_.z += -kCharacterSpeed;
		   
			if (worldTransform_.translation_.z<0.0f) {
			    phase_ = Phase::Leave;
			}

			FireTimer--;
		    if (FireTimer<=0) {
			    Fire();
			    FireTimer = kFireInterval;
			
			}
			

		

			break;

		case Phase::Leave:
		    //worldTransform_.translation_.x -= kCharacterSpeed;
		    //worldTransform_.translation_.z -= kCharacterSpeed;
		   
			
			break;

	default:
		break;
	}

	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);

}

void Enemy::PhaseInitialize() 
{
	FireTimer = kFireInterval;

}

void Enemy::OnCollision(){ isDead_ = true; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;


}

Vector3 Enemy::LerpFanc(Vector3 v1, Vector3 v2) 
{ 
	Vector3 result;


	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;

	return result;

}

void Enemy::Fire()
{

	Vector3 v;
	v.x = player_->GetWorldTransform().matWorld_.m[3][0];
	v.y = player_->GetWorldTransform().matWorld_.m[3][1];
	v.z = player_->GetWorldTransform().matWorld_.m[3][2];

	//ホーミング処理
	Vector3 PlayerPos = v;
	//player_->GetWorldPosition();
	Vector3 EnemyPos = GetWorldPosition();

	Vector3 PiEnLerp = LerpFanc(EnemyPos, PlayerPos);

	Vector3 PiEnNormalize = Normalize(PiEnLerp);



	PiEnNormalize= TransformNormal(PiEnNormalize, worldTransform_.matWorld_);

	// intealize
	EnemyBullet* newBullet = new EnemyBullet();

	newBullet->Initialize(model_, worldTransform_.translation_, PiEnNormalize);

	gameScene_->AddEnemyBullet(newBullet);
	//bullets_.push_back(newBullet);
}
