#include"GameObj/Player/Bullet/PlayerBullet.h"


PlayerBullet::PlayerBullet() 
{
	model_ = nullptr;
	velocity_ = {0, 0, 0};

}

PlayerBullet::~PlayerBullet() {}

void PlayerBullet::Initialize(Model* model, Vector3& position,const Vector3& velocity)
{ 
	model_ = model;
	modeltexHandle = TextureManager::Load("Stone.png");
	
	worldTransform_.translation_ = position;
	
	worldTransform_.Initialize();
	
	velocity_ = velocity;

}



void PlayerBullet::Update() 
{
	if (--deathTimer_<=0)
	{

		isDead_ = true;
	}

	
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	

	//worldTransform_.UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();


}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, modeltexHandle);

}


void PlayerBullet::OnCollision() 
{
	isDead_=true;
}
