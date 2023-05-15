#include "Player.h"
#include"ImGuiManager.h"

Player::Player() 
{ 
	this->position_= {0, 0, 0};
	this->modeltexHandle = 0;
	this->model_ = nullptr;
	
}

Player::~Player() 
{
	model_->~Model();

	for (PlayerBullet *bullet:bullets_) 
	{
		delete bullet;

	}

}


void Player::Attack(Vector3& position) {

	

	if (input_->PushKey(DIK_SPACE)) {

	

		//intealize
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, position);

		bullets_.push_back(newBullet);
	}
}

void Player::Initialize()
{
	worldTransform_.Initialize();
	
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("kamata.ico");
	input_ = Input::GetInstance();

}

void Player::Update()
{
	
	//move
	Vector3 VelocityMove = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	
	if (input_->PushKey(DIK_LEFT))
	{
		VelocityMove.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		VelocityMove.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		VelocityMove.y += kCharacterSpeed;
	}
    if (input_->PushKey(DIK_DOWN)) {
		VelocityMove.y -= kCharacterSpeed;
	}
    //Rotate
	Vector3 RotateMove = {0, 0, 0};
	const float kRotSpeed = 0.2f;
	if (input_->PushKey(DIK_A))
	{
		RotateMove.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		RotateMove.y -= kRotSpeed;
	}
	
	//bullet
	Attack(worldTransform_.translation_);

	for (PlayerBullet* bullet : bullets_)
	{
		bullet->Update();
	}
	
	
	//MoveLimit
	const float kmoveLimitX = 35.0f;
	const float kmoveLimitY = 18.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kmoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, kmoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kmoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kmoveLimitY);



    //VelocityMatrix
	worldTransform_.translation_ = Add(worldTransform_.translation_, VelocityMove);

	//RotateMatrix
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, RotateMove);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	


	
}
void Player::Draw(ViewProjection ViewProjection_)
{

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
	
	// bullet
	
for (PlayerBullet*bullet:bullets_) 
	{

		bullet->Draw(ViewProjection_);
	}

}

