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
#define PLAYER_HEIGHT (175.0f)
#define PLAYER_WIDTH (98.0f)
#define PLAYER_RADIUS (50.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (300.0f)

//無敵時間
#define PLAYER_INVISIBLE_TIME (3)

//リスポーン待ち
#define PLAYER_RESPAWN_WAIT (1) 

//矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (98)
#define PLAYER_BOX_COLLISION_HEIGHT (175)

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
	g_PlayerData.invincibletimer = 0;
	g_PlayerData.invincible = false;
	g_PlayerData.respawnTimer = 0;
	g_PlayerData.TurnX = false;
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
	StartAnimation(&g_PlayerData.standby, g_PlayerData.body.pos.x, g_PlayerData.body.pos.y, 1, 1, 130, 233, TRUE, 98, 175);
	StartAnimation(&g_PlayerData.Dash, g_PlayerData.body.pos.x, g_PlayerData.body.pos.y, 4, 4, 256, 377, TRUE, 98, 175);
	//g_PlayerData.Dash.sheetWidth = 1024;

	//反転
	g_PlayerData.Inversion = false;

	//サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

	//接地
	g_PlayerData.body.Ground = false;

	g_PlayerData.body.move.y = 0.0f;

	//死亡後無敵時間
	g_PlayerData.invincibletimer = 0;

	g_PlayerData.invincible = false;

	g_PlayerData.respawnTimer = 0;
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
	if (IsInputKey(KEY_Q))
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	if (IsInputKey(KEY_A))
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	if (IsInputKey(KEY_Z))
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}
	if (Pad::GetStickX() < -200)
	{
		g_PlayerData.body.move.x = -PLAYER_SPEED;
	}

	//右入力
	if (IsInputKey(KEY_E))
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	if (IsInputKey(KEY_D))
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	if (IsInputKey(KEY_C))
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}
	if (Pad::GetStickX() > 200)
	{
		g_PlayerData.body.move.x += PLAYER_SPEED;
	}

	//左右反転
	if (g_PlayerData.body.move.x < 0.0f)
	{
		g_PlayerData.TurnX = TRUE;
	}
	else if (g_PlayerData.body.move.x > 0.0f)
	{
		g_PlayerData.TurnX = FALSE;
	}

	//重力反転
	if (IsTriggerKey(KEY_SPACE))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_A))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_B))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_X))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_Y))
	{
		if (g_PlayerData.body.Ground == true)
		{
			ReverseGravity();
		}
	}
	//毎フレーム重力適応
	StepGravity();

	//無敵時間
	if (g_PlayerData.invincible)
	{
		g_PlayerData.invincibletimer--;
	}
}

void UpdatePlayer()
{
	//死んでいたら処理しない
	if (!g_PlayerData.active)return;

	//当たり判定付き移動処理
	MoveWithMapCollisin(&g_PlayerData.body);

	//アニメーション更新
	if (g_PlayerData.body.move.x != 0.0f)
	{
		//ダッシュ
		UpdateAnimation(&g_PlayerData.Dash);
	}
	else
	{
		//待機
		UpdateAnimation(&g_PlayerData.standby);
	}
}

void DrawPlayer()
{
	if (!g_PlayerData.active)return;

	//カメラ取得
	CameraData camera = GetCamera();

	if (g_PlayerData.body.move.x != 0.0f)
	{
		//ダッシュ
		DrawAnimation(&g_PlayerData.Dash,
			g_PlayerData.body.pos.x + PLAYER_WIDTH / 2 - camera.posX,
			g_PlayerData.body.pos.y + PLAYER_HEIGHT / 2 - camera.posY,
			g_PlayerData.TurnX, g_PlayerData.Inversion);

	}
	else
	{
		//待機
		DrawAnimation(&g_PlayerData.standby,
			g_PlayerData.body.pos.x + PLAYER_WIDTH / 2 - camera.posX,
			g_PlayerData.body.pos.y + PLAYER_HEIGHT / 2 - camera.posY, g_PlayerData.TurnX, g_PlayerData.Inversion);

	}

	
}

void  FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

bool ReSpawnPlayer()
{
	if (!g_PlayerData.active)
	{
		g_PlayerData.active = true;

		//無敵状態
		g_PlayerData.invincible = true;
		g_PlayerData.invincibletimer = PLAYER_INVISIBLE_TIME;

		//配置（あとでセーブしたとこに変更）
		g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
		g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;

		//リスポーン
		return true;
	}
	//不可
	return false;
}

void PlayerDead()
{
	g_PlayerData.active = false;

	//リスポーン待ち
	g_PlayerData.respawnTimer = PLAYER_RESPAWN_WAIT;
}

//敵と衝突
void EnemyHit()
{
	PlayerDead();
}

//棘に衝突
void PlayerHitThorn()
{
	PlayerDead();
}