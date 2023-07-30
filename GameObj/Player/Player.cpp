#include "Player.h"
#include"ImGuiManager.h"

Player::Player() 
{ 
	this->position_= {0, 0, 0};
	this->modeltexHandle = 0;
	this->model_ = nullptr;
	
}

Player::~Player() 
{
	model_->~Model();

	for (PlayerBullet *bullet:bullets_) 
	{
		delete bullet;

	}
	delete sprite2DReticle_;
}


void Player::Attack(Vector3& position) {

	

	if (input_->PushKey(DIK_SPACE)&&bulletCoolTimer<=0) {
		
		// BulletSpeed
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	    

		Vector3 posR;//= worldTransform3DReticle_.translation_;
		
		posR.x = worldTransform3DReticle_.translation_.x, worldTransform_.translation_.x;
		posR.y = worldTransform3DReticle_.translation_.y, worldTransform_.translation_.y;
		posR.z == worldTransform3DReticle_.translation_.z, worldTransform_.translation_.z;


		//intealize
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, position,velocity);

		bullets_.push_back(newBullet);
		bulletCoolTimer = 20;
	}
}

void Player::Initialize(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();

	model_ = Model::Create();
	modeltexHandle = TextureManager::Load("Dirt.png");
	input_ = Input::GetInstance();

	uint32_t texReticle_ = TextureManager::Load("reticle.png");
	sprite2DReticle_= Sprite::Create(texReticle_, ReticlePos_, color_, anchor_);


}

void Player::Update(ViewProjection viewProjection)
{
	// BulletKill
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	bulletCoolTimer--;
	//move
	Vector3 VelocityMove = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	
	if (input_->PushKey(DIK_LEFT))
	{
		VelocityMove.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		VelocityMove.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		VelocityMove.y += kCharacterSpeed;
	}
    if (input_->PushKey(DIK_DOWN)) {
		VelocityMove.y -= kCharacterSpeed;
	}
    //Rotate
	
	const float kRotSpeed = 0.2f;
	RotateMove_ = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_A))
	{
		RotateMove_.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		RotateMove_.y -= kRotSpeed;
	}
	worldTransform_.TransferMatrix();

	//MoveLimit
	const float kmoveLimitX = 35.0f;
	const float kmoveLimitY = 18.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kmoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, kmoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kmoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kmoveLimitY);


    //VelocityMatrix
	worldTransform_.translation_ = Add(worldTransform_.translation_, VelocityMove);

	//RotateMatrix
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, RotateMove_);

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	
	// bullet
	Attack(worldPos);
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	{
		const float kDistancePlayerTo3DReticle = 50.0f;
		Vector3 offset = {0, 0, 1.0f};
		
		Vector3 pos;
		pos.x = worldTransform_.matWorld_.m[3][0];
		pos.y = worldTransform_.matWorld_.m[3][1];
		pos.z = worldTransform_.matWorld_.m[3][2];

		offset = TransformNormal(offset, worldTransform_.constMap->matWorld);
		offset = Normalize(offset);

		offset.x *=  kDistancePlayerTo3DReticle;
		offset.y *= kDistancePlayerTo3DReticle;
		offset.z *= kDistancePlayerTo3DReticle;
		worldTransform3DReticle_.translation_.x = offset.x +pos.x;
		worldTransform3DReticle_.translation_.y = offset.y + pos.y;
		worldTransform3DReticle_.translation_.z = offset.z + pos.z;

		worldTransform3DReticle_.UpdateMatrix();
		UpdateUI(viewProjection);

	}

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	
	

	ImGui::Begin("Player");

	ImGui::Text("bullet::Space");
	ImGui::Text("DebugCamera::K");
	ImGui::Text("EnemyInitialize::R");
	ImGui::End();
	
	
}
void Player::UpdateUI(ViewProjection viewProjection)
{
	
	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	
	Matrix4x4 matViewprojectionviewport =

	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	positionReticle = 
		Transform(positionReticle, matViewprojectionviewport);
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
		



}
void Player::Draw(ViewProjection ViewProjection_)
{

	model_->Draw(worldTransform_, ViewProjection_, modeltexHandle);
	

for (PlayerBullet*bullet:bullets_) 
	{

		bullet->Draw(ViewProjection_);
	}

}

void Player::DrawUI() 
{
	
	sprite2DReticle_->Draw();

}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;
	
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;

}

void Player::OnCollision() {}

void Player::SetParent(const WorldTransform* parent)
{

    worldTransform_.parent_ = parent;

}

void Player::SetPlayerPos(Vector3 v)
{
	position_ = v;

} 

