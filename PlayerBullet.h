#pragma once
#include "Model.h"
#include"Vector3.h"
#include "WorldTransform.h"
#include "MatrixTrans.h"
class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position"></param>
	void Initialize(Model* model, Vector3& position);

	/// <summary>
	/// 
	/// </summary>
	void Update();
	
	/// <summary>
	///
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	

private:

	uint32_t modeltexHandle;
	Model * model_;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	// BulletLimitTime
	
};

