#include"RailCamera.h"


RailCamera::RailCamera() {}

RailCamera::~RailCamera() {}

void RailCamera::Initialize(Vector3 pos, Vector3 rotate)
{

worldTransform_.translation_ = pos;

worldTransform_.rotation_ = rotate;
worldTransform_.Initialize();

viewProjection_.farZ = 1200.0f;
viewProjection_.Initialize();

}

void RailCamera::Update()
{


  // worldTransform_.translation_ = Add(worldTransform_.translation_, {0.0f, 0.0f, -0.2f});


   Vector3 rotate = {0.0f, 0.0f, 0.0f};
   worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);


   worldTransform_.UpdateMatrix();
   viewProjection_.matView = Inverse(worldTransform_.matWorld_);


   ImGui::Begin("RailCamera");
   ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
   ImGui::SliderFloat3("rotate", &worldTransform_.rotation_.x, -10.0f, 10.0f);
   ImGui::End();

}
