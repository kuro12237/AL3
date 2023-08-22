#pragma once

#include"GameObject/Player/Player.h"
#include "3d/Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"MatrixTransform.h"
#include"VectorTransform.h"

#include<Xinput.h>
#include"Sprite.h"
#include"WinApp.h"

class Player
{
public:

	Player();
	~Player();

	void Initialize();

	void Update(ViewProjection view);

	void Draw(ViewProjection view);

	void ReticleUpdate(ViewProjection view);

	void ReticleDraw();

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }


private:

    void Move();

	void Attak();



	WorldTransform worldTransform_ = {};
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	XINPUT_STATE joystate = {};


	Sprite* sprite_ = nullptr;
	Vector2 anchor_ = {0.5f, 0.5f};
	Vector4 color_ = {1, 1, 1, 1};
	Vector2 SpritePos_ = {640, 360};
	WorldTransform worldTransform3DReticle_ = {};


	int HP = {};



};



