#include "Skydome.h"

Skydome::Skydome() {}

Skydome::~Skydome() {}

void Skydome::Initialize() {

	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	worldTransform_.Initialize();

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
}

void Skydome::Update() {

	// 更新処理
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw(ViewProjection view) { modelSkydome_->Draw(worldTransform_, view); }
