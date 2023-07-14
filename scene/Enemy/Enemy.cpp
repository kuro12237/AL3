#include"Enemy/Enemy.h"
#include"Matrix/MatrixTrans.h"

#include <cassert>

#pragma comment(lib, "dxguid.lib")

Enemy::Enemy() {
	enemyVelocity_ = {0, 0, 0};
	state_ = new EnemyStateApproach();
}


void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	this->worldTransform_.translation_ = {0.0f, 3.0f, 20.0f};
}


void Enemy::SetTranslation(Vector3 enemyTranslate) {
	worldTransform_.translation_ = enemyTranslate;
}

void Enemy::SetVelocity(Vector3 enemyVelocity) { enemyVelocity_ = enemyVelocity; }



// 接近
void EnemyStateApproach::Update(Enemy* enemy) {

	enemy->SetVelocity({0.0f, 0.0f, -0.2f});

	enemy->SetTranslation(Add(enemy->GetTranslation(), enemy->GetVelocity()));


	// 規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
}

void EnemyStateLeave::Update(Enemy* enemy) {

	enemy->SetVelocity({0.3f, 0.3f, -0.2f});
}


void Enemy::Update() {

	
	state_->Update(this);


	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	enemyVelocity_ = TransformNormal(enemyVelocity_, worldTransform_.matWorld_);

	
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


Enemy::~Enemy() { }

void Enemy::ChangeState(BaseEnemyState* newState) {
	
	this->state_ = newState;
}

BaseEnemyState::BaseEnemyState() {}
