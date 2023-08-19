#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	
    worldTransform_.Initialize();	

	model_ = Model::Create();


}

void Player::Update() 
{


}

void Player::Draw(ViewProjection view) 
{


    model_->Draw(worldTransform_,view);


}


