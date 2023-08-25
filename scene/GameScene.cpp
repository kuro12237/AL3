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
	
	delete debugCamera_;
	delete player;
	delete railcamera;
	delete skydome;
}
void GameScene::Initialize() {
	// ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player = new Player();
	railcamera = new RailCamera();
	skydome = new Skydome();
	
	player->Initialize();
	railcamera->Initialize({0, 0, -10}, {0, 0, 0});
	skydome->Initialize();
	
	player->SetParent(&railcamera->GetworldTransform());

	viewProjection_.Initialize();

	Game = START;

#ifdef _DEBUG



	debugCamera_ = new DebugCamera(1280, 720);
    
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

#endif // _DEBUG
}

void GameScene::Update() 
{ 
	switch (Game) {
	case START:

		if (!Input::GetInstance()->GetJoystickState(0, joystate_)) {
			return;
		}
		if (joystate_.Gamepad.wButtons &XINPUT_GAMEPAD_A)
		{
			Game = RESET;
		}

		break;
	case RESET:

		Game = PLAY;

		break;
	case PLAY:
		player->Update(viewProjection_);
		railcamera->Update(player->Getvelocity());

#ifdef _DEBUG

		if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;

			// debugCamera_->Update();
		} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
			isDebugCameraActive_ = false;
		}
#endif // _DEBUG
		if (isDebugCameraActive_) {
			debugCamera_->Update();

			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

			viewProjection_.TransferMatrix();

		} else {

			viewProjection_.matView = railcamera->GetViewProjection().matView;
			viewProjection_.matProjection = railcamera->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		}

		break;
	case CLEAR:
		break;
	case OVER:
		break;
	default:
		break;
	}





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
	//sprite_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();
	// ライン描画


	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	switch (Game) {
	case START:
		break;
	case RESET:
		break;
	case PLAY:

		player->Draw(viewProjection_);
		skydome->Draw(viewProjection_);

		break;
	case CLEAR:
		break;
	case OVER:
		break;
	default:
		break;
	}

	//spaceBack->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (Game) {
	case START:
		break;
	case RESET:
		break;
	case PLAY:
		player->ReticleDraw();

		break;
	case CLEAR:
		break;
	case OVER:
		break;
	default:
		break;
	}
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
