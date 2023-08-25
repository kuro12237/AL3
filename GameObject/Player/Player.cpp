#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize() 
{
	model_ = Model::Create();
	input_ = Input::GetInstance();

	worldTransform_.Initialize();	
	worldTransform_.translation_ = {0, -3, 20};
	worldTransform3DReticle_.Initialize();
	uint32_t texReticle_ = TextureManager::Load("reticle.png");
	sprite_=Sprite::Create(texReticle_, SpritePos_, color_,anchor_);

}

void Player::Update(ViewProjection view) {
	
	Move();
	ReticleUpdate(view);

	Vector3 worldPos = {};
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	// BulletKill
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	bulletCoolTimer--;
	if (bulletCoolTimer<=0) {
		Attak(worldPos);
		bulletCoolTimer = 30;
		
	}



	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view) 
{
    model_->Draw(worldTransform_,view); 
    model_->Draw(worldTransform3DReticle_, view);
	for (PlayerBullet* bullet : bullets_) {

		bullet->Draw(view);
	}
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
	worldTransform3DReticle_.translation_.x = offset.x + pos.x;
	worldTransform3DReticle_.translation_.y = offset.y + pos.y;
	worldTransform3DReticle_.translation_.z = offset.z + pos.z;

	Matrix4x4 matViewport =
	    MatrixTransform::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	Matrix4x4 matVPV =
	    MatrixTransform::Multiply(view.matView, MatrixTransform::Multiply(view.matProjection, matViewport));

	Matrix4x4 matInverseVPV = MatrixTransform::Inverse(matVPV);

	// スクリーン座標
	Vector3 posNear = Vector3(
	    (float)sprite_->GetPosition().x, (float)sprite_->GetPosition().y, 0);
	Vector3 posFar = Vector3(
	    (float)sprite_->GetPosition().x, (float)sprite_->GetPosition().y, 1);
	posNear = VectorTransform::Transform(posNear, matInverseVPV);
	posFar = VectorTransform::Transform(posFar, matInverseVPV);

	Vector3 mouseDirection = VectorTransform::Subtract(posFar, posNear);
	mouseDirection = VectorTransform::Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;

	worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x * kDistanceTestObject;
	worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y * kDistanceTestObject;
	worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z * kDistanceTestObject;
	worldTransform3DReticle_.UpdateMatrix();

}

void Player::ReticleDraw() 
{
	
	sprite_->Draw();

}

void Player::Move() {

	Vector3 PlWorldPos, ReWorldPos;

	PlWorldPos.x = worldTransform_.matWorld_.m[3][0];
	PlWorldPos.y = worldTransform_.matWorld_.m[3][1];
	PlWorldPos.z = worldTransform_.matWorld_.m[3][2];

	ReWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	ReWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	ReWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
	velocity_ = VectorTransform::Subtract(ReWorldPos, PlWorldPos);
	velocity_ = VectorTransform::Normalize(velocity_);

}

void Player::Attak(Vector3 position)
{

	if (!Input::GetInstance()->GetJoystickState(0, joystate)) {
		return;
	}
	if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {

		// BulletSpeed
		const float kBulletSpeed = 1.0f;

		Vector3 PlWorldPos, ReWorldPos;

		PlWorldPos.x = worldTransform_.matWorld_.m[3][0];
		PlWorldPos.y = worldTransform_.matWorld_.m[3][1];
		PlWorldPos.z = worldTransform_.matWorld_.m[3][2];

		ReWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
		ReWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
		ReWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
		Vector3 velocity = VectorTransform::Subtract(ReWorldPos, PlWorldPos);
		velocity = VectorTransform::Normalize(velocity);

		velocity.x *= kBulletSpeed;
		velocity.y *= kBulletSpeed;
		velocity.z *= kBulletSpeed;

		// intealize
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, position, velocity);

		bullets_.push_back(newBullet);
		bulletCoolTimer = 20;
	}


}



