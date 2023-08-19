#pragma once

#include"GameObject/Player/Player.h"
#include "3d/Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"

class Player {
public:
	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);



private:

	WorldTransform worldTransform_ = {};
	Model* model_ = nullptr;



};



