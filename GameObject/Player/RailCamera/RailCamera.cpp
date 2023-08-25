#include "RailCamera.h"

RailCamera::RailCamera() {}

RailCamera::~RailCamera() {}

void RailCamera::Initialize(Vector3 pos, Vector3 rotate) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	worldTransform_.rotation_ = rotate;

	viewProjection_.Initialize();
	viewProjection_.farZ = 1200.0f;
}

void RailCamera::Move(Vector3 velocity) {


	const float kCharacterRotate = -0.02f;
	//回転
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		worldTransform_.rotation_.y -=
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterRotate;
		worldTransform_.rotation_.x +=
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterRotate;
	}


	
	kCharacterSpeed = 0.4f;
	
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		kCharacterSpeed = 0.9f;
		BoostOver += 0.02f;
	} else {

		if (BoostOver > 0.0f) {

			BoostOver -= 0.03f;
		}
	}
	
	if (BoostOver>=3.0f) 
	{
		isOverBoost = true;
	}
	if (isOverBoost) 
	{
		kCharacterSpeed = 0.2f;
		BoostOver -= 0.03f;
		if (BoostOver<=0.0f)
		{
			isOverBoost = false;
			BoostOver = 0.0f;
		}
	}

	ImGui::Begin("Boost");
	ImGui::Text("Over::%f", BoostOver);
	ImGui::End();
	velocity.x = velocity.x * kCharacterSpeed;
	velocity.y = velocity.y * kCharacterSpeed;
	velocity.z = velocity.z * kCharacterSpeed;

	worldTransform_.translation_ = VectorTransform::Add(worldTransform_.translation_, velocity);
}



void RailCamera::Update(Vector3 velocity) {


	Move(velocity);


	worldTransform_.UpdateMatrix();
	viewProjection_.matView = MatrixTransform::Inverse(worldTransform_.matWorld_);

	ImGui::Begin("RailCamera");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
}