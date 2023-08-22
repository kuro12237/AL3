#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	model_ = Model::Create();
	input_ = Input::GetInstance();

	worldTransform_.Initialize();	
	worldTransform_.translation_ = {3, 0, 20};
	worldTransform3DReticle_.Initialize();
	uint32_t texReticle_ = TextureManager::Load("reticle.png");

	sprite_=Sprite::Create(texReticle_, SpritePos_, color_,anchor_);

}

void Player::Update(ViewProjection view) {
	Move();
	ReticleUpdate(view);

	worldTransform_.UpdateMatrix();
	
}

void Player::Draw(ViewProjection view) 
{
    model_->Draw(worldTransform_,view); 
    model_->Draw(worldTransform3DReticle_, view);
}

void Player::ReticleUpdate(ViewProjection view) {

	
	
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0, 0, 1.0f};

	Vector3 pos = {};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];

	offset = VectorTransform::TransformNormal(offset, worldTransform_.constMap->matWorld);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	worldTransform3DReticle_.translation_.x = offset.x + pos.x + 3;
	worldTransform3DReticle_.translation_.y = offset.y + pos.y;
	worldTransform3DReticle_.translation_.z = offset.z + pos.z;

	worldTransform3DReticle_.UpdateMatrix();
	


	//Matrix4x4 matViewport =
	//   MatrixTransform::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	//Matrix4x4 matVPV =
	//    MatrixTransform::Multiply(view.matView,MatrixTransform::Multiply(view.matProjection, matViewport));

	//Matrix4x4 matInverseVPV = MatrixTransform::Inverse(matVPV);



	//worldTransform3DReticle_.UpdateMatrix();



}

void Player::ReticleDraw() 
{
	
	sprite_->Draw();

}

void Player::Move()
{
	const float kCharacterSpeed = 0.5f;
	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		worldTransform_.translation_.x =
		    (float)joystate.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed-3;
		worldTransform_.translation_.y =
		    (float)joystate.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
}

void Player::Attak()
{




}


