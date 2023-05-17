#pragma once

#include <Model.h>
#include <WorldTransform.h>

class Enemy {
public:
	enum class Phase {
		Approach,
		Leave,
	};

	Enemy();
	~Enemy();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

	static Vector3 MoveApproch(const float speed, WorldTransform worldTransform_,Phase phase_);

private:
	



	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;


	Phase phase_ = Phase();

};