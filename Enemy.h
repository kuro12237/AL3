#pragma once

#include <Model.h>
#include <WorldTransform.h>

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

private:
	enum class Phase {
		Approach,
		Leave,
	};

	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;
};