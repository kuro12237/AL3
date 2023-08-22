#pragma once

#include"GameObject/Player/Player.h"
#include "3d/Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"MatrixTransform.h"
#include"VectorTransform.h"

#include<Xinput.h>

class Player
{
public:

	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	void ReticleDraw();

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }


private:

    void Move();

	void Attak();



	WorldTransform worldTransform_ = {};
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	XINPUT_STATE joystate;



	int HP = {};



};



