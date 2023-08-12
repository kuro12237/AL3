#include "Enemy.h"
#include "math/Matrix/MatrixTrans.h"

Enemy::Enemy() {}

Enemy::~Enemy() 
{
	model_->~Model();

	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	for (TimedCall* timedCall : timedCall_)
	{
		delete timedCall;

	}
}


void Enemy::Initialize() {

	phase_ = Phase::Approach;

	PhaseInitialize();

	worldTransform_.Initialize();
	worldTransform_.translation_ = {-10.0f, 5.0f, 30.0f};
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("Dirt.png");
	TimedCall* timeCall = new TimedCall(std::bind(&Enemy::FireReset,this),60);
	
	timedCall_.push_back(timeCall);

}

void Enemy::Update() {

	
	Vector3 move = {0, 0, 0};

	

	const float kCharacterSpeed = 0.2f;
	
	switch (phase_) 
	{
		//FireReset();

		case Phase::Approach:
			
	        move.z += -kCharacterSpeed;
		   
			if (worldTransform_.translation_.z<0.0f) {
			    phase_ = Phase::Leave;
			}

		
	
			break;

		case Phase::Leave:
		    move.x -= kCharacterSpeed;
		    move.z -= kCharacterSpeed;
		   
			
			break;

	default:
		break;
	}

	for (TimedCall* timeCall : timedCall_)
	{

		timeCall->Update();
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	 
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);

	for (EnemyBullet* bullet : bullets_) {

		bullet->Draw(ViewProjection_);
	}
}

void Enemy::PhaseInitialize() 
{
	FireTimer = kFireInterval;

}

void Enemy::FireReset()
{
    Fire();
	timedCall_.push_back(new TimedCall(std::bind(&Enemy::FireReset,this),60));

}

void Enemy::Fire() {

	// BulletSpeed
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// intealize
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);
}
