#include "DxLib.h"
#include "Player.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"
#include "../Map/MapChip.h"
#include "../Input/Input.h"

//プレイヤーデータ(のち変更)
#define PLAYER_SPEED (7)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_WIDTH (50.0f)
#define PLAYER_RADIUS (36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)

//重力
#define PLAYER_GRAVITY (0.4f)

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
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");
}

void StartPlayer()
{
	//生存フラグ
	g_PlayerData.active = true;

	//初期位置
	g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;
	
	//反転
	g_PlayerData.Inversion = false;

	//サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;
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

	//Y方向移動量に重力
	g_PlayerData.body.move.y += PLAYER_GRAVITY;

	//左入力
	if (IsInputKey(KEY_Q) || IsInputKey(KEY_A) || IsInputKey(KEY_Z))
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	//右入力
	if (IsInputKey(KEY_E) || IsInputKey(KEY_D) || IsInputKey(KEY_C))
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	//重力反転
	if (IsInputKey(KEY_SPACE))
	{
		g_PlayerData.Inversion = false;
	}
}

void UpdatePlayer()
{
	//死んでいたら処理しない
	if (!g_PlayerData.active)return;

	//当たり判定付き移動処理
	MoveWithMapCollisin(&g_PlayerData.body);

	//空中
	if (g_PlayerData.body.move.y < 0.0f || g_PlayerData.body.move.y > PLAYER_GRAVITY)
	{
		g_PlayerData.body.isAir = true;
	}
}

void DrawPlayer()
{
	if (!g_PlayerData.active)return;

	int x = (int)(g_PlayerData.body.pos.x + 0.5f);
	int y = (int)(g_PlayerData.body.pos.y + 0.5f);
	DrawGraph(x, y, g_PlayerData.handle, TRUE);
}

void  FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}
