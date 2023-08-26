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
	for (Enemy* enemy_ : enemys_) 
	{
		delete enemy_;
	}
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
	collisionManager = new CollisionManager;

	player->Initialize();
	railcamera->Initialize({0, 0, -10}, {0, 0, 0});
	skydome->Initialize();

	player->SetParent(&railcamera->GetworldTransform());
	viewProjection_.Initialize();

	StarBackTex_ = TextureManager::Load("StarBack.png");
	uvTex_ = TextureManager::Load("uvChecker.png");
	StarBack_ = new Sprite;
	StarBack_ = Sprite::Create(StarBackTex_, {0, 0});

	pushATex_ = TextureManager::Load("pushA.png");
	pushA_ = new Sprite;
	pushA_ = Sprite::Create(pushATex_, {320, 320});

	pushB_ = new Sprite;
	pushBTex_ = TextureManager::Load("pushB.png");
	pushB_ = Sprite::Create(pushBTex_, {0, 0});

	GameTitle_ = new Sprite;
	GameTitleTex_ = TextureManager::Load("Title.png");
	GameTitle_ = Sprite::Create(GameTitleTex_, {0, 0});

	GameClear_ = new Sprite;
	GameClearTex_ = TextureManager::Load("GameClear.png");
	GameClear_ = Sprite::Create(GameClearTex_, {0, 0});

	GameOver_ = new Sprite;
	GameOverTex_ = TextureManager::Load("GameOver.png");
	GameOver_ = Sprite::Create(GameOverTex_, {0, 0});


	

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
			IsTrigger = true;
			Game = RESET;
		}

		break;
	case RESET:
		player->Reset();
		railcamera->Reset();

		Enemy* enemy[5];
		Vector3 pos[5];
		pos[0] = {0, 0, 100};
		pos[1] = {120, 0, 50};
		pos[2] = {60, 0, 300};
		pos[3] = {120, 0, -250};
		pos[4] = {-120, -60, 200};

		for (int i = 0; i < 5; i++) {
			enemy[i] = new Enemy;
			enemy[i]->Initialize(pos[i]);
		}

		for (int i = 0; i < 5; i++) {

			enemys_.push_back(enemy[i]);
		}
		Game = PLAY;

		break;
	case PLAY:
		player->Update(viewProjection_);
		railcamera->Update(player->Getvelocity());

		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

		for (Enemy* enemy_ : enemys_) {

			enemy_->SetPlayer(player);
			enemy_->Update();
		}
		CheckAllCollosions();

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

		if (player->GetMode()==OVER)
		{
			Game = OVER;
			
		} 
		if (enemys_.size()==0) 
		{

			Game = CLEAR;
		}


		break;
	case CLEAR:

		if (!Input::GetInstance()->GetJoystickState(0, joystate_)) {
			return;
		}
		if (joystate_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			Game = START;
			
		}


		break;
	case OVER:
		if (!Input::GetInstance()->GetJoystickState(0, joystate_)) {
			return;
		}
		if (joystate_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			Game = START;
		
		}


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


	switch (Game) {
	case START:

		StarBack_->Draw();
		GameTitle_->Draw();
		pushA_->Draw();


		break;
	case RESET:
		break;
	case PLAY:

		break;
	case CLEAR:
		StarBack_->Draw();
		GameClear_->Draw();
		pushB_->Draw();
		break;
	case OVER:
		StarBack_->Draw();
		GameOver_->Draw();
		pushB_->Draw();
		break;
	default:
		break;
	}
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
		
		for (Enemy* enemy_ : enemys_) {

			enemy_->Draw(viewProjection_);
		}
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
void GameScene::CheckAllCollosions() {

	collisionManager->ClliderClear();
	//
	//const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	const std::list<PlayerBullet*>& playerBullets = player->GetBullets();

	collisionManager->ClliderPush(player);
	
	
	for (Enemy* enemy : enemys_) {
		collisionManager->ClliderPush(enemy);
	
	}
	for (PlayerBullet* bullet : playerBullets) {
		collisionManager->ClliderPush(bullet);

	}
	/*
	for (EnemyBullet* bullet : enemyBullets) {
		collisionManager->ClliderPush(bullet);
	}
	*/
	collisionManager->CheckAllCollision();
}