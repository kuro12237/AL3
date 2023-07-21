#include"Skydome.h"

Skydome::Skydome() {}

Skydome::~Skydome() {}

void Skydome::Initialize() 
{ 
	//modelSkydome_=Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("CelestialSphere", true);
	worldTransform_.Initialize();
	
	//worldTransform_.scale_ = {100, 100, 100};


}

void Skydome::Update() 
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	// 小さすぎたかも・・
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 更新処理
	worldTransform_.UpdateMatrix();


}

void Skydome::Draw(ViewProjection view) {

modelSkydome_->Draw(worldTransform_, view);

}
