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

	if (!Input::GetInstance()->GetJoystickState(0, joyState))
	{
		return;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {

		// BulletSpeed
		const float kBulletSpeed = 1.0f;

		Vector3 PlWorldPos, ReWorldPos;

		PlWorldPos.x = worldTransform_.matWorld_.m[3][0];
		PlWorldPos.y = worldTransform_.matWorld_.m[3][1];
		PlWorldPos.z = worldTransform_.matWorld_.m[3][2];

		ReWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
		ReWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
		ReWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
		Vector3 velocity = Substract(ReWorldPos, PlWorldPos);
		velocity = Normalize(velocity);

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

void Player::GetmousePointer() 
{

	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	ReticlePos_.x = float(mousePosition.x);
	ReticlePos_.y = float(mousePosition.y);

	sprite2DReticle_->SetPosition(ReticlePos_);
}

void Player::GetReticlePointer() 
{
	

	if (Input::GetInstance()->GetJoystickState(0,joyState))
	{
		JoyPos.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		JoyPos.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		sprite2DReticle_->SetPosition(JoyPos);

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
	

	if (Input::GetInstance()->GetJoystickState(0,joyState))
	{
		VelocityMove.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		VelocityMove.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;


	}
	


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

	  //  worldTransform3DReticle_.UpdateMatrix();
		

	}
	GetmousePointer();
	GetReticlePointer();
	UpdateUI(viewProjection);


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

	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);



	Matrix4x4 matVPV =
	    Multiply(viewProjection.matView,
			Multiply(viewProjection.matProjection, matViewport));

	Matrix4x4 matInverseVPV = Inverse(matVPV);



		// スクリーン座標
	Vector3 posNear = Vector3(
	    (float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 0);
	Vector3 posFar = Vector3(
	    (float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 1);
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 mouseDirection = Substract(posFar,posNear);
	mouseDirection = Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;

	worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x * kDistanceTestObject;
	worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y * kDistanceTestObject;
	worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z * kDistanceTestObject;
	worldTransform3DReticle_.UpdateMatrix();

	#ifdef _DEBUG


	ImGui::Begin("Player");
	ImGui::Text(
	    "2DReticle(%f,%f)",
		sprite2DReticle_->GetPosition().x,
		sprite2DReticle_->GetPosition().y);
	ImGui::Text(
	    "3DreticleObj %f,%f,%f", worldTransform3DReticle_.translation_.x,
	    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z

	);
	ImGui::End();


#endif // _DEBUG


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

