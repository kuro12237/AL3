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
#include"GameObj/Skydome/Skydome.h"
#include<cmath>
#include"../GameObj/RailCamera/RailCamera.h"
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

	void CheckAllCollosions();

	bool CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious);

private: // メンバ変数
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
	 Skydome* skydome_ = nullptr;
	 RailCamera* railCamera_ = nullptr;
	 Vector3 playerpos = {0.0f, 0.0f, 14.0f};
	 bool isDebugCameraActive_ = false;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
