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

#include"GameObject/Player/Player.h"
#include"GameObject/enemy/Enemy.h"
#include"GameObject/Player/RailCamera/RailCamera.h"
#include"GameObject/SkyDome/SkyDome.h"

#include<Xinput.h>

#include"utility/Collider.h"
#include"utility/CollisionManager.h"
#include"utility/GameConfig.h"
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

	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;


	 uint32_t soundDataHandle_ = 0;
	 uint32_t voiceHandle_ = 0;
	 float inputFloat3[3] = {0, 0, 0};

	 DebugCamera* debugCamera_ = nullptr;
	 bool isDebugCameraActive_ = false;

	 Player* player = nullptr;
	 RailCamera* railcamera = nullptr;
	 Skydome* skydome = nullptr;

	 std::list<Enemy*> enemys_;

	 GAMEMODE Game = START; 

	 XINPUT_STATE joystate_;
	 CollisionManager* collisionManager = nullptr;

	 bool IsTrigger = false;

	 Sprite* StarBack_ = nullptr;
	 int32_t StarBackTex_ = {};

	 Sprite* pushA_ = nullptr;
	 int32_t pushATex_ = {};

	 Sprite* pushB_ = nullptr;
	 int32_t pushBTex_ = {};

	 Sprite* GameOver_ = nullptr;
	 int32_t GameOverTex_ = {};

	  Sprite* GameTitle_ = nullptr;
	 int32_t  GameTitleTex_ = {};

	  Sprite* GameClear_ = nullptr;
	  int32_t GameClearTex_ = {};

	 int32_t uvTex_{};

	 Sprite* Contorol_ = nullptr;
	 int32_t ContorolTex = {};

	 int32_t ClearRequirementTex = {};
	 Sprite* ClearRequirement = nullptr;

	 int32_t SelectSound_ = {};
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
