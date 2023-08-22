#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	model_ = Model::Create();
	input_ = Input::GetInstance();

	worldTransform_.Initialize();	
	worldTransform_.translation_ = {-3, 0, 20};
	worldTransform3DReticle_.Initialize();
	uint32_t texReticle_ = TextureManager::Load("reticle.png");

	sprite_=Sprite::Create(texReticle_, SpritePos_, color_,anchor_);

}

void Player::Update(ViewProjection view) {
	Move();
	ReticleUpdate(view);

	worldTransform_.UpdateMatrix();
	
}

void Player::Draw(ViewProjection view) 
{
    model_->Draw(worldTransform_,view); 
    model_->Draw(worldTransform3DReticle_, view);
}

void Player::ReticleUpdate(ViewProjection view) {

	
	
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0, 0, 1.0f};

	Vector3 pos = {};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];

	offset = VectorTransform::TransformNormal(offset, worldTransform_.constMap->matWorld);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	worldTransform3DReticle_.translation_.x = offset.x + pos.x;
	worldTransform3DReticle_.translation_.y = offset.y + pos.y;
	worldTransform3DReticle_.translation_.z = offset.z + pos.z;

	worldTransform3DReticle_.UpdateMatrix();
	

}

void Player::ReticleDraw() 
{
	
	sprite_->Draw();

}

void Player::Move() {

	
	Vector3 PlWorldPos, ReWorldPos;

	PlWorldPos.x = worldTransform_.matWorld_.m[3][0];
	PlWorldPos.y = worldTransform_.matWorld_.m[3][1];
	PlWorldPos.z = worldTransform_.matWorld_.m[3][2];

	ReWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	ReWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	ReWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
	velocity_ = VectorTransform::Subtract(ReWorldPos, PlWorldPos);
	velocity_ = VectorTransform::Normalize(velocity_);

}

void Player::Attak()
{




}


