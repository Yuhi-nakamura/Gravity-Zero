#include "DxLib.h"
#include "EnemyParameter.h"
#include "../Collision/Collision.h"
#include "../Map/MapChip.h"
#include "../Map/MapManager.h"
#include "../Sound/Sound.h"
#include "../Gravity/Gravity.h"
#include "../Player/Player.h"
#include "../Animetion/Animetion.h"

//エネミー1関連設定
#define ENEMY_WIDTH (30.0f)
#define ENEMY_HEIGHT (30.0f)
#define ENEMY_RADIUS (20.0f)
#define ENEMY_MOVE_SPEED (3.0f)

//矩形判定のサイズ
#define ENEMY_COLLISION_WIDTH (30)
#define ENEMY_COLLISION_HEIGHT (30)

//デフォルト位置
#define ENEMY_DEFAULT_POS_X (300)
#define ENEMY_DEFAULT_POS_Y (600)


EnemyData g_EnemyData = { 0 };

void InitEnemy1()
{
	g_EnemyData.active = false;
	g_EnemyData.handle = 0;
	g_EnemyData.body.pos = VGet(0.0f, 0.0f, 0.0f);
	g_EnemyData.body.move = VGet(0.0f, 0.0f, 0.0f);
	g_EnemyData.body.width = 0.0f;
	g_EnemyData.body.height = 0.0f;
	g_EnemyData.body.Ground = false;
	g_EnemyData.Inversion = false;
	g_EnemyData.direction = 1;
	g_EnemyData.InversionDie = false;
	g_EnemyData.stopTimer = 0;
	g_EnemyData.movestate = MOVE;
}

void LoadEnemy1()
{
	g_EnemyData.handle = LoadGraph("Data/Enemy/Enemy1.png");
}

void StepEnemy1()
{
	if (!g_EnemyData.active)return;
	
	if (g_EnemyData.movestate == MOVE)
	{
		g_EnemyData.body.move.x = ENEMY_MOVE_SPEED * g_EnemyData.direction;
	}
	else if (g_EnemyData.movestate == STOP)
	{
		g_EnemyData.body.move.x = 0.0f;
	}
	else if (g_EnemyData.movestate == DIE)
	{
		g_EnemyData.body.move.x = 0.0f;
	}
}

void UpdateEnemy1()
{
	//移動前の値を保存
	float BeforeMoving = 0.0f;

	if (!g_EnemyData.active)return;
	
	BeforeMoving = g_EnemyData.body.move.x;

	MoveWithMapCollisin(&g_EnemyData.body);

	//Enemyの前に障害物があったら引き返す
	if (BeforeMoving != 0.0f && g_EnemyData.body.move.x == 0.0f)
	{
		g_EnemyData.movestate = STOP;
		g_EnemyData.stopTimer = 0;
	}

	if (g_EnemyData.movestate == STOP)
	{
		g_EnemyData.stopTimer++;

		if (g_EnemyData.stopTimer >= 60)
		{
			g_EnemyData.direction *= -1;
			g_EnemyData.movestate = MOVE;
			g_EnemyData.stopTimer = 0;
		}
	}
	
	PlayerData* player = GetPlayer();
	if (player->Inversion == true)
	{
		g_EnemyData.Inversion = true;

		//一回反転されて地面についたとき死ぬよう改善
		if (g_EnemyData.Inversion = false)
		{
			g_EnemyData.InversionDie = true;
		}
	}
}

void DrawEnemy1()
{
	g_EnemyData.handle = LoadGraph("Data/Enemy/Enemy1.png");
}

void FinEnemy1()
{
	DeleteGraph(g_EnemyData.handle);
}

//歩く、落ちる、死ぬアニメーション追加
void InitEnemy1Animation()
{
	//待機
}