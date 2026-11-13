#include "DxLib.h"
#include "Player.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"
#include "../Map/MapChip.h"
#include "../Input/Input.h"
#include "../Camera/Camera.h"
#include "../Gravity/Gravity.h"
#include "../Pad/Pad.h"
#include "../Animetion/Animetion.h"

//プレイヤーデータ(のち変更)
#define PLAYER_SPEED (7)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_WIDTH (50.0f)
#define PLAYER_RADIUS (36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)

//矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (50)
#define PLAYER_BOX_COLLISION_HEIGHT (50)

//キャラの周囲何マス
#define PLAYER_CHECK_NUM (5)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.active = false;
	g_PlayerData.handle = 0;
	g_PlayerData.body.pos = VGet(0.0f, 0.0f, 0.0f);
	g_PlayerData.body.move = VGet(0.0f, 0.0f, 0.0f);
	g_PlayerData.body.width = 0.0f;
	g_PlayerData.body.height = 0.0f;
	g_PlayerData.Inversion = false;
	g_PlayerData.body.Ground = false;
	InitAnimation(&g_PlayerData.Dash);
	InitAnimation(&g_PlayerData.InversionAnime);
	InitAnimation(&g_PlayerData.standby);
}

void LoadPlayer()
{
	g_PlayerData.standby.handle = LoadGraph("Data/Player/Player.png");
	g_PlayerData.Dash.handle = LoadGraph("Data/Player/Player_Dash.png");
	g_PlayerData.InversionAnime.handle = LoadGraph("Data/Player/Player_Inversion.png");
}

void StartPlayer()
{
	//生存フラグ
	g_PlayerData.active = true;

	//初期位置
	g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;
	
	//アニメーション
	StartAnimation(&g_PlayerData.standby, g_PlayerData.body.pos.x, g_PlayerData.body.pos.y, 1, 1, 130, 233, TRUE);

	//反転
	g_PlayerData.Inversion = false;

	//サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

	//接地
	g_PlayerData.body.Ground = true;

	g_PlayerData.body.move.y = 0.0f;
}

void StepPlayer()
{
	//死んでいたら処理しない
	if (!g_PlayerData.active)
	{
		return;
	}

	//移動量リセット
	g_PlayerData.body.move.x = 0.0f;

	//左入力
	if (IsInputKey(KEY_Q) || IsInputKey(KEY_A) || IsInputKey(KEY_Z) || Pad::IsPress(PAD_INPUT_LEFT) || Pad::GetStickX() < -200)
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	//右入力
	if (IsInputKey(KEY_E) || IsInputKey(KEY_D) || IsInputKey(KEY_C) || Pad::IsPress(PAD_INPUT_RIGHT) || Pad::GetStickX() > 200)
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	//重力反転
	if (IsTriggerKey(KEY_SPACE) || Pad::IsTrigger(PAD_INPUT_A) || Pad::IsTrigger(PAD_INPUT_B) || Pad::IsTrigger(PAD_INPUT_X) || Pad::IsTrigger(PAD_INPUT_Y))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	//毎フレーム重力適応
	StepGravity();
}

void UpdatePlayer()
{
	//死んでいたら処理しない
	if (!g_PlayerData.active)return;

	//当たり判定付き移動処理
	MoveWithMapCollisin(&g_PlayerData.body);

	//アニメーション更新
	UpdateAnimation(&g_PlayerData.standby);
}

void DrawPlayer()
{
	if (!g_PlayerData.active)return;

	//カメラ取得
	CameraData camera = GetCamera();

	//int x = (int)(g_PlayerData.body.pos.x + 0.5f);
	//int y = (int)(g_PlayerData.body.pos.y + 0.5f);
	DrawAnimation(&g_PlayerData.standby, g_PlayerData.body.pos.x - camera.posX, g_PlayerData.body.pos.y - camera.posY, FALSE, FALSE);
}

void  FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

