#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"MatrixTransform.h"
#include"VectorTransform.h"
#include"ImGuiManager.h"
#include"Vector3.h"

#include < Input.h>
#include <Xinput.h>



class RailCamera {
public:
	RailCamera();
	~RailCamera();

	void Initialize(Vector3 pos, Vector3 rotate);

	void Update();

	ViewProjection GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetworldTransform() const { return worldTransform_; }

	Vector3 GetPlayerWorldPos();

private:
    void Move();

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	XINPUT_STATE joyState = {};
	Input* input_ = nullptr;
};