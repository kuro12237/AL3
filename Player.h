#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>



class Player {
public:
	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

private:

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;
	WorldTransform worldTransform_;

};


