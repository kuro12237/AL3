#include"TransCube.h"

TransCube::TransCube()
{
}

TransCube::~TransCube()
{
}

void TransCube::Initialize()
{
	model_ = new Model();
	worldTransform.Initialize();
	worldTransform.scale_ = { 5,5,5 };
	model_=Model::CreateFromOBJ("TransCube");
	DirectionReticlePos_.FworldTransform.Initialize();
	state_ = new TransCubeRandBulletState();
	state_->Initialize(this);
	

}

void TransCube::Update()
{
	ReticlePosFanc();
	worldTransform.rotation_.y += 0.01f;
	worldTransform.UpdateMatrix();
	state_->Update(this);
}

void TransCube::Draw(ViewProjection view)
{
	state_->Draw(this, view);
	model_->Draw(worldTransform, view);
	//model_.get()->Draw(DirectionReticlePos_.FworldTransform, view);
}

void TransCube::ChangeLaserState()
{
	//state_.release();
	//state_ = std::make_unique<TransCubeRandBulletState>();
	//state_.get()->Initialize(this);
}

Vector3 TransCube::GetWorldPosition()
{
	Vector3 result = {};

	result.x = worldTransform.matWorld_.m[3][0];
	result.y = worldTransform.matWorld_.m[3][0];
	result.z = worldTransform.matWorld_.m[3][0];
	return result;
}

void TransCube::ReticlePosFanc()
{

	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0, 0, 1.0f };

	Vector3 pos = {};
	pos = GetWorldPosition();
	offset =VectorTransform::TransformNormal(offset, worldTransform.matWorld_);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	DirectionReticlePos_.FworldTransform.translation_.x = offset.x + pos.x;
	DirectionReticlePos_.FworldTransform.translation_.y = offset.y + pos.y;
	DirectionReticlePos_.FworldTransform.translation_.z = offset.z + pos.z;

	DirectionReticlePos_.FworldTransform.UpdateMatrix();



}