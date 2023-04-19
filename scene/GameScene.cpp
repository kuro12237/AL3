#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<ImGuiManager.h>
#include<PrimitiveDrawer.h>
#include "AxisIndicator.h"
GameScene::GameScene() 
{

}

GameScene::~GameScene()
{
	delete sprite_;
	delete model_;
	delete debugCamera_;
}
void GameScene::Initialize() 
{
    //ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 音
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	// 2D
	textureHandle_ = TextureManager::Load("kamata.ico");
	// 3D
	textureModelHandle_ = TextureManager::Load("kamata.ico");

	// 2D
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3D
	model_ = Model::Create();
	

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクション
	viewProjection_.Initialize();
	//でバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
    
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() 
{ Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);

	if (input_->TriggerKey(DIK_W))
	{
		// 音声再生
		audio_->PlayWave(soundDataHandle_);

	}
	debugCamera_->Update();

	
	ImGui::Text("aiueo %f", 4090.0f);
	ImGui::Begin("Debug1");
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
	ImGui::ShowDemoWindow();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();
	// ライン描画
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});


	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureModelHandle_);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, textureModelHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
