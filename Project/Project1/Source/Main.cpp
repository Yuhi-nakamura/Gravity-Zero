#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "FPS/FPS.h"
#include "Map/MapChip.h"
#include "Map/Block.h"
#include "Pad/Pad.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "UI/Image.h"
#include "UI/Text.h"
#include "Sound/Sound.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモード
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ウィンドウサイズ設定
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 透過色の設定
	SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//入力システム初期化
	InitInput();

	//UI初期化、ロード
	InitUIImage();
	InitUIText();

	LoadUIImage();
	LoadUIText();

	//サウンド
	LoadBGM();
	LoadSE();

	//FPS
	InitFPS();

	// ブロックとマップの初期化
	InitBlock();
	LoadBlock();
	LoadMapChipData();
	CreateMap();

	//ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		//処理前に1ミリ秒止める
		Sleep(1);

		//画面クリア
		ClearDrawScreen();

		//パッド更新
		Pad::Update();

		//マップ描画
		DrawBlock();

		//入力更新
		UpdateInput();

		//シーン管理更新
		SceneManagerUpdate();

		//入力システム描画
		DrawInput();

		//エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//FPS更新
		UpdateFPS();

		//FPDb描画
		DrawFPS();

		//1フレームが早すぎたら待機
		FPSWait();

		//画面フリッぷ
		ScreenFlip();
	}

	//入力しシステムの終了
	FinInput();

	//UI終了
	FinUIImage();
	FinUIText();

	//サウンド終料
	FinBGM();
	FinSE();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}