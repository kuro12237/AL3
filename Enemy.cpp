#include "Enemy.h"
#include "MatrixTrans.h"
Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize() {

	worldTransform_.Initialize();
	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("kamata.ico");
}

void Enemy::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	move.z -= kCharacterSpeed;

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection ViewProjection_) {

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
}