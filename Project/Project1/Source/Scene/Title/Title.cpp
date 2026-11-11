#include "DxLib.h"
#include "Title.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../Pad/Pad.h"
#include "../../BackGround/BackGround.h"
#include "../../Sound/Sound.h"
#include <math.h>

//背景スピード
#define BACK_GROUND_SPEED (-0.4f)

//タイトルの位置
#define TITLE_POS_X (280)
#define TITLE_POS_Y (130)

//PressBottonの位置
#define PRESS_BOTTON_POS_X (500)
#define PRESS_BPTTON_POS_Y (530)

//点滅
#define PRESS_BOTTON_BLINK_SPEED (0.04f)

//画像
int g_BGHandle = 0;
int g_TitleHandle = 0;
int g_PressBottonHandle = 0;

//点滅用変数
float g_PressBottonAlpha = 0.0f;//アルファ値
float g_PressBottonRadian = 0.0f; //coa関数に渡すラジアン値

void InitTitle()
{
	g_BGHandle = 0;
	g_TitleHandle = 0;
	g_PressBottonHandle = 0;
	g_PressBottonAlpha = 0.0f;
	g_PressBottonRadian = 0.0f;

	//背景初期化
	InitBackGround();
}

void LoadTitle()
{
	LoadBackGround("Data/Title/BG.png",BACK_GROUND_LAYER_1);

	//各画像
	g_BGHandle = LoadGraph("Data/Title/BG.png");
	g_TitleHandle = LoadGraph("Data/Title/Title.png");
	g_PressBottonHandle = LoadGraph("Data/Title/PressBotton.png");
}

void StartTitle()
{
	//BGM再生
	PlayBGM(BGM_TITLE);
}

void StepTitle()
{
	//sin波の値からPressBottonのアルファ値（透明度）を計算
	//sinfが-1～1の値を返却するので加工して0～1の値にしている
	g_PressBottonAlpha = (sinf(g_PressBottonRadian) + 1) / 2;

	//ラジアン値を点滅速度で加算
	g_PressBottonRadian += PRESS_BOTTON_BLINK_SPEED;

	//ラジアン値をループ
	if (g_PressBottonRadian > DX_TWO_PI_F)
	{
		g_PressBottonRadian -= DX_TWO_PI_F;
	}

	//ボタンが押されたらプレイシーン
	if (IsTriggerKey(KEY_SPACE) || Pad::IsTrigger)
	{
		ChangeScene(SCENE_PLAY);
	}

	StepBackGround();
}

void UpdateTitle()
{
	//背景更新
	UpdateBackGround();
}

void DrawTitle()
{
	//背景描画
	DrawBackGround();

	//タイトル
	DrawGraph(TITLE_POS_X, TITLE_POS_Y, g_TitleHandle, TRUE);

	//点滅のブレンドモード設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(g_PressBottonAlpha * 255));

	//Press描画
	DrawGraph(PRESS_BOTTON_POS_X, PRESS_BPTTON_POS_Y, g_PressBottonHandle, TRUE);

	//ブレンドモードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FinTitle()
{
	//背景終了
	FinBackGround();

	//各画像削除
	DeleteGraph(g_TitleHandle);
	DeleteGraph(g_PressBottonHandle);

	//BGM停止
	StopBGM(BGM_TITLE);
}