#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	
    worldTransform_.Initialize();	

	model_ = Model::Create();

	input_ = Input::GetInstance();
}

void Player::Update() 
{
	float move = 0;

	if (input_->PushKey(DIK_W))
	{
		move += 0.5f;

	}
	worldTransform_.translation_.z += move;

	worldTransform_.matWorld_ =
	    MatrixTransform::MakeAffineMatrix({1, 1, 1}, {0, 0, 0}, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection view) 
{


    model_->Draw(worldTransform_,view);


}


