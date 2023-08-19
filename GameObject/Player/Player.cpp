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



}

void Player::Draw(ViewProjection view) 
{


    model_->Draw(worldTransform_,view);


}


