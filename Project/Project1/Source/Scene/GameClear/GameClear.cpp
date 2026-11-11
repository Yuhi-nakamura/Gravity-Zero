#include "DxLib.h"
#include "GameClear.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
#include <stdio.h>
#include "../../Sound/Sound.h"
#include "../../Pad/Pad.h"
#include "../../UI/Text.h"

//背景スピード
#define BACK_GROUND_SPEED (4.0f)

//GameClear画像
int g_GameClearHandle = 0;

void InitGameClear()
{
	//背景初期化
	InitBackGround();

	//文字画像初期化
	g_GameClearHandle = 0;
}

void LoadGameClear()
{
	//背景ロード
	LoadBackGround("Data/Title/BG.png",BACK_GROUND_LAYER_1);

	//背景スクロール
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	//文字画像
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClear()
{
	//BGM再生
	PlayBGM(BGM_PLAY);
}

void StepGameClear()
{
	//背景ステップ
	StepBackGround();

	//タイトルに戻る
	if (IsTriggerKey(KEY_SPACE) || Pad::IsTrigger)
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClear()
{
	//背景更新
	UpdateBackGround();
}

void DrawGameClear()
{
	//背景描画
	DrawBackGround();

	//文字描画
	DrawGraph(560, 110, g_GameClearHandle, TRUE);
}

void FinGameClear()
{
	//背景終了
	FinBackGround();

	//文字画像削除
	DeleteGraph(g_GameClearHandle);

	//BGMリセット
	StopBGM(BGM_CLEAR);
}