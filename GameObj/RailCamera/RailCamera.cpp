#include"RailCamera.h"


RailCamera::RailCamera() {}

RailCamera::~RailCamera() {}

void RailCamera::Initialize(Vector3 pos, Vector3 rotate)
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

    worldTransform_.rotation_ = rotate;

 
   
     viewProjection_.Initialize();
	 viewProjection_.farZ = 1200.0f;
}

void RailCamera::Update()
{

	 worldTransform_.translation_.z += 0.05f;
	
 // worldTransform_.matWorld_ = MakeAffineMatrix(
//	  worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
   worldTransform_.UpdateMatrix();
   viewProjection_.matView = Inverse(worldTransform_.matWorld_);


   ImGui::Begin("RailCamera");
   ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
   ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
   ImGui::End();
   
}

