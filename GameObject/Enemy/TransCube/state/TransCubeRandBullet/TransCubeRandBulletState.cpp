#include "TransCubeRandBulletState.h"


Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result{};
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);
	return result;
}
TransCubeRandBulletState::TransCubeRandBulletState()
{
}

TransCubeRandBulletState::~TransCubeRandBulletState()
{
}

void TransCubeRandBulletState::Initialize(TransCube* state)
{
	state;
	CoolTime = 0;

}

void TransCubeRandBulletState::Update(TransCube* state)
{
	

	Vector3 FlontVelocity = Lerp( state->GetWorldPosition(),state->GetReticlePos().FworldTransform.translation_,1);

	FlontVelocity = VectorTransform::Normalize(FlontVelocity);
	CoolTime++;
	Fire(FlontVelocity);
	for (TransCubeBullet* bullet : bullets_)
	{
		bullet->Update();
	}

}

void TransCubeRandBulletState::Draw(TransCube* state, ViewProjection view)
{
	state;
	for (TransCubeBullet* bullet : bullets_)
	{

		bullet->Draw(view);

	}
}

void TransCubeRandBulletState::SetParent(const WorldTransform* parent)
{

	parent; }

void TransCubeRandBulletState::Fire(Vector3 velocity)
{
	if (CoolTime >= 300)
	{

		TransCubeBullet* Fbullet = new TransCubeBullet();
		Fbullet->Initialize(velocity);
		bullets_.push_back(Fbullet);

		CoolTime = 0;
	}


}