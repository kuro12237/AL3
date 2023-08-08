#pragma once
#include <Model.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include"Base/EnemyBase.h"
#include"Approach/EnemyApproach.h"

class Enemy {
public:
	Enemy();
	~Enemy();

	
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	// ビュープロジェクション
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetTranslation() { return worldTransform_.translation_; }
	Vector3 GetVelocity() { return enemyVelocity_; }

	void SetTranslation(Vector3 enemyTranslate);

	void SetVelocity(Vector3 enemyVelocity);

	
	void ChangeState(BaseEnemyState* newState);

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデルのポインタ
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 enemyPosition_ = {0.0f, 0.0f, 0.0f};

	Vector3 enemyVelocity_;
	const float kEnemySpeed_ = -0.2f;

	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱
	};

	Phase phase_ = Phase();

	// メンバ関数ポインタのテーブル
	static void (Enemy::*spFuncTable[])();

	// StatePattern
	BaseEnemyState* state_ = nullptr;
};