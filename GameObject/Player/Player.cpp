#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	
    worldTransform_.Initialize();	

	model_ = Model::Create();

	input_ = Input::GetInstance();
	worldTransform_.translation_ = {0, 0, 20};

}

void Player::Update() 
{
	Move();

	worldTransform_.UpdateMatrix();
	
}

void Player::Draw(ViewProjection view) 
{
    model_->Draw(worldTransform_,view);
}

void Player::Move()
{
	const float kCharacterSpeed = 0.5f;
	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		worldTransform_.translation_.x =
		    (float)joystate.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		worldTransform_.translation_.y =
		    (float)joystate.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
}

void Player::Attak()
{




}


