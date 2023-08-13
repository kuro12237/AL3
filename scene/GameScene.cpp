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
    player_->~Player();
	enemy_->~Enemy();
	delete collisionManager;
}
void GameScene::Initialize() 
{
    //ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	enemy_ = new Enemy();

	//player
	player_->Initialize();
	enemy_->Initialize();

	enemy_->SetPlayer(player_);
	collisionManager = new CollisionManager;


	// ビュープロジェクション
	viewProjection_.Initialize();
	//でバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
    
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() 
{ 

	player_->Update();


	if (enemy_ != nullptr) {

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

	if (input_->TriggerKey(DIK_R)) {
		enemy_->Initialize();
	}

#endif // _DEBUG

	// Camera
	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();

	} else {

		viewProjection_.UpdateMatrix();
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



	// スプライト描画後処理
	Sprite::PostDraw();
	

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);


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
void GameScene::CheckAllCollosions() {


	collisionManager->ClliderClear();
    //
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	collisionManager->ClliderPush(player_);
	collisionManager->ClliderPush(enemy_);
	
	for (PlayerBullet* bullet : playerBullets) {
		collisionManager->ClliderPush(bullet);
	}
	for (EnemyBullet* bullet : enemyBullets) {
		collisionManager->ClliderPush(bullet);
	}
	//
	collisionManager->CheckAllCollision();

}
