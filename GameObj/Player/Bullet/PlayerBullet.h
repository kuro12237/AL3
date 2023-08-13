#pragma once
#include "Model.h"
#include"Vector3.h"
#include "WorldTransform.h"
#include "GameObj/Player/Bullet/PlayerBullet.h"
#include"math/Matrix/MatrixTrans.h"
#include"Utility/Collider/Collider.h"
#include"Utility/Collider/Collisionconfig.h"

class PlayerBullet :public Collider{
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

	Vector3 GetWorldPosition() override;

	void OnCollision() override;



    /// Getter
	bool IsDead() const { return isDead_; }

	WorldTransform GetWorldTransform() { return worldTransform_; }


private:



	uint32_t modeltexHandle;
	Model * model_;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	// BulletLimitTime
	
	int32_t deathTimer_ = kLifeTime;
	
	bool isDead_ = false;
};

