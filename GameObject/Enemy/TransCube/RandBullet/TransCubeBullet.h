#pragma once


#include"Model.h"
#include"VectorTransform.h"
using std::unique_ptr;


class TransCubeBullet
{
public:
	TransCubeBullet();
	~TransCubeBullet();


	void Initialize(Vector3 &velocity);

	void Update();

	bool IsDead() { return true; }

	void Draw(ViewProjection view);
private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};

	Vector3 velocity_ = {};

};



