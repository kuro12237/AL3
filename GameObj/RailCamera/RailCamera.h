#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Matrix/MatrixTrans.h"
#include"ImGuiManager.h"
#include"../math/Vector3.h"

class RailCamera {
public:
	RailCamera();
	~RailCamera();

	void Initialize(Vector3 pos,Vector3 rotate);

	void Update();
	

	ViewProjection GetViewProjection()
	{
		return viewProjection_;
	}
    const WorldTransform &GetworldTransform() const{ return worldTransform_; }


private:

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


};

