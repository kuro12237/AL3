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


}


void Player::Attack(Vector3& position) {

	if (input_->PushKey(DIK_SPACE)) {

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, position);

		bullet_ = newBullet;
	}
}

void Player::Rotate(Vector3& RotateMove)
{

	const float kRotSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
		RotateMove.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		RotateMove.y -= kRotSpeed;
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
	
	Rotate(RotateMove);
	//bullet
	Attack(worldTransform_.translation_);

	if (bullet_!=nullptr) 
	{

		bullet_->Update();

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

	
	ImGui::Begin("Player");

	ImGui::Text("bullet::Space");
	ImGui::Text("DebugCamera::K");
	ImGui::End();
	
}
void Player::Draw(ViewProjection ViewProjection_)
{

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
	
	// bullet
	
	if (bullet_!=nullptr) {

		bullet_->Draw(ViewProjection_);
	}

}

