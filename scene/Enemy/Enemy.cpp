#include"Enemy/Enemy.h"
#include"Matrix/MatrixTrans.h"

#include <cassert>

//#pragma comment(lib, "dxguid.lib")

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




void Enemy::Update() {

	
	//state_->Update(this);


	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocity_);
	enemyVelocity_ = TransformNormal(enemyVelocity_, worldTransform_.matWorld_);

	
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


Enemy::~Enemy() { }

void Enemy::ChangeState(BaseEnemyState* newState) {
	
	delete state_;
	this->state_ = newState;
}
