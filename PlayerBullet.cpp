#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() 
{



}

PlayerBullet::~PlayerBullet() {}

void PlayerBullet::Initialize(Model* model, Vector3& position)
{ 
	model_ = model;
	modeltexHandle = TextureManager::Load("kamata.ico");
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

}



void PlayerBullet::Update() 
{
	
	
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, modeltexHandle);

}
