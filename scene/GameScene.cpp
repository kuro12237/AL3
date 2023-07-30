#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<ImGuiManager.h>
#include<PrimitiveDrawer.h>
#include "AxisIndicator.h"
#include<fstream>
GameScene::GameScene() 
{

}

GameScene::~GameScene()
{ 
    player_->~Player();
	//enemy_->~Enemy();
	skydome_->~Skydome();
}
void GameScene::Initialize() {
	// ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//enemy_ = new Enemy();
	skydome_ = new Skydome();
	railCamera_ = new RailCamera();

	Vector3 radian = {0.0f, 0.0f, 0.0f};

	railCamera_->Initialize(player_->GetWorldPosition(), radian);
	player_->SetParent(&railCamera_->GetworldTransform());

	// player
	
	player_->Initialize(playerpos);
	
	//EnemySpawn({-10, 3, 5});
	//EnemySpawn({10, 3, 5});
	LoadEnemyPopData();
	skydome_->Initialize();

	viewProjection_.farZ = 1200.0f;
	// ビュープロジェクション
	viewProjection_.Initialize();
	//でバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
    
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() 
{ 
	
	player_->Update(viewProjection_);

    EnemyObjUpdate();

	UpdateEnemyPopCommands();

	skydome_->Update();

	CheckAllCollosions();

	
	// Camera
	railCamera_->Update();

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;

		// debugCamera_->Update();
	} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}

	if (input_->TriggerKey(DIK_R)) {
		//enemy_->Initialize();
	}
#endif // _DEBUG
	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();

	} else {

		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
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


	EnemyObjDraw();

	skydome_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollosions() 
{
	Vector3 posE, posEb;
	Vector3 posP, posPb;

    const std::list<EnemyBullet*>& enemyBullets = enemyBullet_;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	const int ObjHitRadious = 3;


#pragma region  自キャラと敵弾の当たり判定

   posP = player_->GetWorldPosition();

   for(EnemyBullet *bullet: enemyBullets)  
   {
		posEb = bullet->GetWorldTransform().translation_;

		if (CheckBallCollosion(posP, ObjHitRadious, posEb, ObjHitRadious))
		{
			player_->OnCollision();

			bullet->OnCollision();

		}
   }
#pragma endregion

   #pragma region 自弾と敵との当たり判定

  


   
   for (PlayerBullet* bullet : playerBullets) {
		
	   for (Enemy* enemy : enemys_) {

			posPb = bullet->GetWorldTransform().translation_;
			posE = enemy->GetWorldPosition();
	  
			if (CheckBallCollosion(posE, ObjHitRadious, posPb, ObjHitRadious)) {
				bullet->OnCollision();
				enemy->OnCollision();
			}
		}
   }
   #pragma endregion

   #pragma region 自弾と敵弾の当たり判定
   
   for (PlayerBullet* Pbullet : playerBullets)
   {
	   for (EnemyBullet* Ebullet : enemyBullets)
	   {
			posPb = Pbullet->GetWorldTransform().translation_;
			posEb = Ebullet->GetWorldTransform().translation_;

			if (CheckBallCollosion(posPb,ObjHitRadious,posEb,ObjHitRadious)) 
			{
       			Pbullet->OnCollision();
				Ebullet->OnCollision();        
			}
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

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) 
{
	
	enemyBullet_.push_back(enemyBullet); }

void GameScene::LoadEnemyPopData()
{
	
	std::ifstream file;
	file.open("Resources/EnemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();
	file.close();

}

void GameScene::UpdateEnemyPopCommands()
{
	if (EnemyWaitFlag_) 
	{
		WaitTimer_--;
		if (WaitTimer_<=0)
		{
			EnemyWaitFlag_ = false;
		}
		return;
	}

	std::string line;


	while (std::getline(enemyPopCommands,line))
	{

		std::istringstream line_stream(line);

		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//")==0 )
		{
			continue;
		}
		//POPコマンド
		if (word.find("POP")==0)
		{
			Vector3 pos;
			std::getline(line_stream, word, ',');
			pos.x = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			pos.y = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			pos.z = (float)std::atof(word.c_str());

			EnemySpawn(pos);
		} else if (word.find("WAIT")==0)
		{
			std::getline(line_stream, word, ',');
			int32_t waitTimer = atoi(word.c_str());
			EnemyWaitFlag_ = true;
			WaitTimer_ = waitTimer;
			
			break;

		}

	}

}


void GameScene::EnemySpawn(const Vector3& position) {
	Enemy* enemy_ = new Enemy();
	enemy_->Initialize(position);
	// EnemyにPlayerのアドレスを渡す
	enemy_->SetPlayer(player_);
	enemy_->SetGameScene(this);
	// 敵
	enemys_.push_back(enemy_);
}

void GameScene::EnemyObjUpdate()
{
	for (Enemy* enemy : enemys_)
	{
		enemy->Update();
	}
	
	enemys_.remove_if([](Enemy* enemy_) {
		if (enemy_->IsDead()) {
			delete enemy_;
			return true;
		}
		return false;
	});


	for (EnemyBullet* bullet_ : enemyBullet_) {
		bullet_->Update();
	}
	
	enemyBullet_.remove_if([](EnemyBullet* bullet_) {
		if (bullet_->IsDead()) {
			delete bullet_;
			return true;
		}
		return false;
	});
}

void GameScene::EnemyObjDraw()
{
	for (Enemy* enemy : enemys_) {

		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* bullet_ : enemyBullet_)
	{
		bullet_->Draw(viewProjection_);
	}
}
