#pragma once
#include "Model.h"
#include"Vector3.h"
#include "WorldTransform.h"
#include "source/Matrix/MatrixTrans.h"
class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position"></param>
	void Initialize(Model* model, Vector3& position,const Vector3& velocity);

	/// <summary>
	/// 
	/// </summary>
	void Update();
	
	/// <summary>
	///
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	// BulletLimitTime
	static const int32_t kLifeTime = 60 * 5;

    /// Getter
	bool IsDead() const { return isDead_; }

private:

	uint32_t modeltexHandle;
	Model * model_;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	// BulletLimitTime
	
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};

