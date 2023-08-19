#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	
    worldTransform_.Initialize();	

	model->Create();


}

void Player::Update() 
{


}

void Player::Draw(ViewProjection view) 
{


    model->Draw(worldTransform_,view);


}


