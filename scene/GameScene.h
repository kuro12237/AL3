#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"DebugCamera.h"

#include"GameObj/Enemy/Enemy.h"
#include "GameObj/Player/Player.h"
#include"Utility/CollisionManager/Collider/Collider.h"
#include"Utility/CollisionManager/CollisionManager.h"
#include<cmath>
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene(

	
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数

 
	void CheckAllCollosions();

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	
	Audio* audio_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;


	 //uint32_t soundDataHandle_ = 0;
	 //uint32_t voiceHandle_ = 0;
	float inputFloat3[3] = {0, 0, 0};

	 DebugCamera* debugCamera_ = nullptr;

	 Player* player_ = new Player();
	 Enemy* enemy_ = nullptr;
	 CollisionManager *collisionManager = nullptr;


	 bool isDebugCameraActive_ = false;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
