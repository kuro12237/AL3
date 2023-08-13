#include"GameObj/Player/Bullet/PlayerBullet.h"


PlayerBullet::PlayerBullet() {
	model_ = nullptr;
	velocity_ = {0, 0, 0};

}

PlayerBullet::~PlayerBullet() {}

void PlayerBullet::Initialize(Model* model, Vector3& position,const Vector3& velocity)
{ 
	model_ = model;
	modeltexHandle = TextureManager::Load("Stone.png");
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;

}



void PlayerBullet::Update() 
{
	if (--deathTimer_<=0)
	{

		isDead_ = true;
	}

	
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	

	worldTransform_.UpdateMatrix();



}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, modeltexHandle);

}


Vector3 PlayerBullet::GetWorldPosition() 
{
	Vector3 result;

	result.x = worldTransform_.matWorld_.m[3][0];
	result.y = worldTransform_.matWorld_.m[3][1];
	result.z = worldTransform_.matWorld_.m[3][2];

	return result;
}

void PlayerBullet::OnCollision() {
	isDead_=true;
}
