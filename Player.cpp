#include "Player.h"
#include"ImGuiManager.h"

Player::Player() 
{ 
	this->position_= {0, 0, 0};
	this->modeltexHandle = 0;
	this->model_ = nullptr;
	matrixTransform = new MatrixTransform();
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
	input_ = Input::GetInstance();

}


void Player::Update()
{
	
	//move
	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	
	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
    if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} 

	//MoveLimit
	const float kmoveLimitX = 35.0f;
	const float kmoveLimitY = 18.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kmoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, kmoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kmoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kmoveLimitY);



    //matrix
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	
	worldTransform_.matWorld_ = matrixTransform->MakeAffine4x4Matrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();



	///ImGui
	ImGui::Begin("Player");

	ImGui::InputFloat3("Position", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("Slide", &worldTransform_.translation_.x, -20.0f, 30.0f);
	ImGui::Text("DebugCamera::K");
	ImGui::End();
}
void Player::Draw(ViewProjection ViewProjection_)
{

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);


}
