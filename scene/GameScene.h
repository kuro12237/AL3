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
#include"GameObject/Player/RailCamera/RailCamera.h"
#include"GameObject/SkyDome/SkyDome.h"

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
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;


	 uint32_t textureHandle_ = 0;
	 uint32_t textureModelHandle_ = 0;
	 
	 uint32_t soundDataHandle_ = 0;
	 uint32_t voiceHandle_ = 0;
	 float inputFloat3[3] = {0, 0, 0};

	 DebugCamera* debugCamera_ = nullptr;
	 bool isDebugCameraActive_ = false;

	 Player* player = nullptr;
	 RailCamera* railcamera = nullptr;
	 Skydome* skydome = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
