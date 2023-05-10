#include "Player.h"


Player::Player() 
{ 
	this->position_= {0, 0, 0};
	this->modeltexHandle = 0;
	this->model_ = nullptr;
	
}

Player::~Player() 
{
	model_->~Model();

}

void Player::Initialize()
{
	worldTransform_.Initialize();
	
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("kamata.ico");

}


void Player::Update()
{

	worldTransform_.TransferMatrix();

}
void Player::Draw(ViewProjection ViewProjection_)
{

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);


}
