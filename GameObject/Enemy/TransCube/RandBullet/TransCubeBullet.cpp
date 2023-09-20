#include "TransCubeBullet.h"
#include"MatrixTransform.h"

TransCubeBullet::TransCubeBullet()
{
}

TransCubeBullet::~TransCubeBullet()
{
}

void TransCubeBullet::Initialize(Vector3 &velocity)
{

	model_ = new Model();
	model_ = Model::CreateFromOBJ("TransCube");

	worldTransform_.Initialize();
	velocity_ = velocity;


}

void TransCubeBullet::Update()
{
	//velocity_ = Multiply(velocity_, { 0.5f,0.5f,0.5f });
	worldTransform_.translation_ = VectorTransform::Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();
}

void TransCubeBullet::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);

}
