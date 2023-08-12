#include"EnemyBullet.h"

EnemyBullet::EnemyBullet() {}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity) {

    model_ = model;
	modeltexHandle = TextureManager::Load("Stone.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	kVelocity_ = velocity;

}

void EnemyBullet::Update() 
{



    worldTransform_.translation_ = Add(worldTransform_.translation_, kVelocity_);
	worldTransform_.UpdateMatrix();	


}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection, modeltexHandle);

}
