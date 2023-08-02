#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>
#include<Input.h>
#include"math/Matrix/MatrixTrans.h"
#include"GameObj/Player/Bullet/PlayerBullet.h"
#include"math/Vector/VectorTransform.h"

#include"WinApp.h"
#include"Sprite.h"

#include <list>
//#incude"MatrixTrans.h"

class Player {
public:
	Player();
	~Player();

	void Initialize(Vector3 pos);

	void Update(ViewProjection viewProjection);

	void UpdateUI(ViewProjection viewProjection);

	void Draw(ViewProjection ViewProjection_);

	void DrawUI();
	Vector3 GetWorldPosition();

	WorldTransform GetWorldTransform() { return worldTransform_; }

	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	Vector3 GetRotateMove() { return RotateMove_; }
	void SetParent(const WorldTransform* parent);
	void SetPlayerPos(Vector3 v);
		 
private:

	void Attack(Vector3 &position);

	void GetmousePointer();

	void GetReticlePointer();

	POINT mousePosition;

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;

	WorldTransform worldTransform_;
	
	Vector3 RotateMove_ = {0, 0, 0};

	Input* input_ = nullptr;
	
	std::list<PlayerBullet*> bullets_;

	int bulletCoolTimer = 0;

	WorldTransform worldTransform3DReticle_;
	Sprite* sprite2DReticle_ = nullptr;
	Vector2 ReticlePos_ = {640, 360};
	Vector4 color_ = {1, 1, 1, 1};
	Vector2 anchor_ = {0.5f, 0.5f};

	XINPUT_STATE joyState;
	Vector2 JoyPos = {640.0f, 360.0f};
};


