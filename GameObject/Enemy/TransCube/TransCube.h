#pragma once
#include"Model.h"
#include"state/TransCubeRandBullet/TransCubeRandBulletState.h"

struct TransCubeReticle
{
	Vector3 Left = {};
	Vector3 Right = {};
	Vector3 Front = {};
	Vector3 Back = {};
	WorldTransform LworldTransform = {};
	WorldTransform RworldTransform = {};
	WorldTransform FworldTransform = {};
	WorldTransform BworldTransform = {};

};

class TransCube
{
public:
	TransCube();
	~TransCube();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	void ChangeLaserState();

	Vector3 GetWorldPosition();
	TransCubeReticle GetReticlePos() { return DirectionReticlePos_; }

private:

	void ReticlePosFanc();

	Model* model_;
	WorldTransform worldTransform = {};


	ITransCubeState*state_ = nullptr;

	TransCubeReticle DirectionReticlePos_ = {};
	Model* Fmodel_ = nullptr;
	const float DirectionReticleSpace = 5.0f;
};
