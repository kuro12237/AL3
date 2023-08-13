#include"EnemyBullet.h"

EnemyBullet::EnemyBullet() { }

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, Vector3& position, const Vector3& velocity) {
	



	model_ = model;
	modeltexHandle = TextureManager::Load("Stone.png");

	
	worldTransform_.Initialize();

		
	worldTransform_.translation_ = position;
 
	Velocity_ =velocity;
	BulletDrawFlag = true;

}

void EnemyBullet::Update() 
{
	//worldTransform_.translation_.x += Velocity_.x;
	//worldTransform_.translation_.y += Velocity_.y;
	//worldTransform_.translation_.z += Velocity_.z;

	//worldTransform_.translation_ = Add(worldTransform_.translation_, Velocity_);
	
	worldTransform_.translation_ = Add(worldTransform_.translation_, Velocity_);
	
		if (--deathTimer_ <= 0) {

		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();	


}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	

	if (BulletDrawFlag) {

		model_->Draw(worldTransform_, viewProjection, modeltexHandle);
	}
}

void EnemyBullet::OnCollision() 
{ 
	
	isDead_ = true;
	
}

Vector3 EnemyBullet::GetWorldPosition() 
{

	Vector3 result;


	result.x = worldTransform_.matWorld_.m[3][0];
	result.y = worldTransform_.matWorld_.m[3][1];
	result.z = worldTransform_.matWorld_.m[3][2];

	return result;

}
