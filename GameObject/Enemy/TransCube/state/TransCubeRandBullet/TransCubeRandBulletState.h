#pragma once

#include"Model.h"
#include"../GameObject/Enemy/TransCube/state/ITransCubeState.h"
#include"../GameObject/Enemy/TransCube/RandBullet/TransCubeBullet.h"
#include"../GameObject/Enemy/TransCube/TransCube.h"



class TransCubeRandBulletState :public ITransCubeState
{
public:
	TransCubeRandBulletState();
	~TransCubeRandBulletState();


	void Initialize(TransCube* state) override;

	void Update(TransCube* state) override;

	void Draw(TransCube* state, ViewProjection view)override;

	void SetParent(const WorldTransform* parent)override;

private:

	void Fire(Vector3 velocity);

	std::list<TransCubeBullet*> bullets_;

	int32_t CoolTime = 0;
};



