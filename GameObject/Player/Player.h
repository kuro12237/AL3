#pragma once
#include<Model.h>
#include<WorldTransform.h>
#include<Vector3.h>
#include<Input.h>
#include"Matrix/MatrixTrans.h"
#include"GameObject/Player/PlayerBullet.h"




#include <list>
//#incude"MatrixTrans.h"

class Player {
public:
	Player();
	~Player();

	void Initialize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

	Vector3 GetWorldPosition();

	WorldTransform GetWorldTransform() { return worldTransform_; }

private:

	void Attack(Vector3 &position);

	Vector3 position_;
	uint32_t modeltexHandle;
	Model* model_;

	WorldTransform worldTransform_;
	


	Input* input_ = nullptr;
	
	std::list<PlayerBullet*> bullets_;


};


