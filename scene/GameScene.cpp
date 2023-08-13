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
void GameScene::CheckCollisionPair(Collider* cA, Collider* cB)
{
	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();


	bool isHit=CheckBallCollosion(cApos, cAradious, cBpos, cBradious);

	if (isHit) 
	{
		cA->OnCollision();
		cB->OnCollision();
	}
}

void GameScene::CheckAllCollosions() 
{

    const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

#pragma region  自キャラと敵弾の当たり判定

   for(EnemyBullet *bullet: enemyBullets)  
   {
		CheckCollisionPair(player_, bullet);	
   }
#pragma endregion

   #pragma region 自弾と敵との当たり判定


   for (PlayerBullet* bullet : playerBullets)
   {
		CheckCollisionPair(bullet, enemy_);
   }
   #pragma endregion

   #pragma region 自弾と敵弾の当たり判定
   
   for (PlayerBullet* Pbullet : playerBullets)
   {
	   for (EnemyBullet* Ebullet : enemyBullets)
	   {
	
		   CheckCollisionPair(Pbullet, Ebullet);
       }
   }


#pragma endregion

}

bool GameScene::CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious) 
{
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x* x) + (y* y) + (z* z);
	
	 float resultRadious = v1Radious + v2Radious;

	bool Flag = false;



	if (resultPos<=(resultRadious*resultRadious))
	{
		Flag = true;
	}

	return Flag;
}
