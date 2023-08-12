#include"EnemyBullet.h"

EnemyBullet::EnemyBullet() {}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity) {

    model_ = model;
	modeltexHandle = TextureManager::Load("Stone.png");

	worldTransform_.Initialize();
	
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	
	float velocityXZ = sqrt(velocity.x*velocity.x + velocity.z*velocity.z);
	
	float heightY = -velocity.y;
	
	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);

	worldTransform_.rotation_.x = std::atan2(heightY, velocityXZ);

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
