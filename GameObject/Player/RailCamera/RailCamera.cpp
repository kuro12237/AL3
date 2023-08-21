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

void RailCamera::Move() {

    const float kCharacterSpeed = 0.5f;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		worldTransform_.translation_.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX *kCharacterSpeed;
		worldTransform_.translation_.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX *kCharacterSpeed;
	}

}

void RailCamera::Update() {


	Move();

	worldTransform_.translation_.z += 0.05f;
	worldTransform_.UpdateMatrix();
	viewProjection_.matView = MatrixTransform::Inverse(worldTransform_.matWorld_);

	ImGui::Begin("RailCamera");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
}