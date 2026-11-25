#include "DxLib.h"
#include "../Sound/Sound.h"
#include "../Player/Player.h"
#include "../Map/MapChip.h"
#include "../Map/MapManager.h"
#include "../Gravity/Gravity.h"
#include "EnemyParameter.h"
#include "Enemy2.h"
#include "../Collision/Collision.h"
#include "../Animetion/Animetion.h"

//設定(あとで変更)
#define ENEMY_2_WIDTH (40.0f)
#define ENEMY_2_HEIGHT (30.0f)
#define ENEMY_2_RADIUS (25.0f)
#define ENEMY_2_SPEED (3.0f)

//矩形判定のサイズ
#define ENEMY_2_COLLISION_WIDTH (40)
#define ENEMY_2_COLLISION_HEIGHT (30)

//デフォルト位置
#define ENEMY_2_DEFAULT_POS_X (500)
#define ENEMY_2_DEFAULT_POS_Y (100)

//ジャンプタイマー
#define ENEMY_2_JAMP_TIMER (5)

EnemyData g_Enemy2Data = { 0 };

void InitEnemy2()
{
	g_Enemy2Data.active = false;
	g_Enemy2Data.body.Ground = false;
	g_Enemy2Data.body.height = 0.0f;
	g_Enemy2Data.body.width = 0.0f;
	g_Enemy2Data.body.move = VGet(0.0f, 0.0f, 0.0f);
	g_Enemy2Data.body.pos = VGet(0.0f, 0.0f, 0.0f);
	g_Enemy2Data.direction = 1;
	g_Enemy2Data.handle = 0;
	g_Enemy2Data.Inversion = false;
	g_Enemy2Data.InversionDie = false;
	g_Enemy2Data.movestate = MOVE;
	g_Enemy2Data.stopTimer = 0;
	
	InitAnimation(&g_Enemy2Data.Enemysutandby);
	InitAnimation(&g_Enemy2Data.Enemymove);
	InitAnimation(&g_Enemy2Data.Enemydie);
}

void LoadEnemy2()
{
	g_Enemy2Data.Enemysutandby.handle = LoadGraph("Data/Enemy/Enemy2_png");
	g_Enemy2Data.Enemymove.handle = LoadGraph("Data/Enemy/Enemy2_move.png");
	g_Enemy2Data.Enemydie.handle = LoadGraph("Data/Enemy/Enemy2_die.png");
}

void StartEnemy2()
{
	//生存フラグ
	g_Enemy2Data.active = true;

	//Enemyのデータ
	g_Enemy2Data.body.height = ENEMY_2_HEIGHT;
	g_Enemy2Data.body.width = ENEMY_2_WIDTH;

	//反転
	g_Enemy2Data.Inversion = false;

	//初期位置
	g_Enemy2Data.body.pos.x = ENEMY_2_DEFAULT_POS_X;
	g_Enemy2Data.body.pos.y = ENEMY_2_DEFAULT_POS_Y;

	//接地
	g_Enemy2Data.body.Ground = false;

	//アニメーション(あとで変更)
	StartAnimation(&g_Enemy2Data.Enemysutandby, g_Enemy2Data.body.pos.x, g_Enemy2Data.body.pos.y, 1, 1, 0, 0, TRUE, 98, 175);
	StartAnimation(&g_Enemy2Data.Enemymove, g_Enemy2Data.body.pos.x, g_Enemy2Data.body.pos.y, 1, 1, 0, 0, TRUE, 98, 175);
	StartAnimation(&g_Enemy2Data.Enemydie, g_Enemy2Data.body.pos.x, g_Enemy2Data.body.pos.y, 1, 1, 0, 0, TRUE, 98, 175);
}

void StepEnemy2()
{
	if (!g_Enemy2Data.active)return;
	if (g_Enemy2Data.movestate == MOVE)
	{
		g_Enemy2Data.body.move.x = ENEMY_2_SPEED;
	}
	else if (g_Enemy2Data.movestate == STOP)
	{
		g_Enemy2Data.body.move.x = 0.0f;
	}
	else if (g_Enemy2Data.movestate == DIE)
	{
		g_Enemy2Data.body.move.x = 0.0f;
	}
}

void UpdateEnemy2()
{
	//移動前の値を保存
	float BeforeMoving = 0.0f;
	if (!g_Enemy2Data.active)return;

	BeforeMoving = g_Enemy2Data.body.move.x;

	MoveWithMapCollisin(&g_Enemy2Data.body);

	//Enemyの前に障害物があったら引き返す
	if (BeforeMoving != 0.0f && g_Enemy2Data.body.move.x == 0.0f)
	{
		g_Enemy2Data.movestate = STOP;
		g_Enemy2Data.stopTimer = 0;
	}

	if (g_Enemy2Data.movestate == STOP)
	{
		g_Enemy2Data.stopTimer++;
		if (g_Enemy2Data.stopTimer >= 60)
		{
			g_Enemy2Data.direction *= -1;
			g_Enemy2Data.movestate = MOVE;
			g_Enemy2Data.stopTimer = 0;
		}
	}

	if (g_Enemy2Data.body.move.x != 0.0f)
	{
		UpdateAnimation(&g_Enemy2Data.Enemymove);
	}
	if (g_Enemy2Data.body.move.x = 0.0f)
	{
		UpdateAnimation(&g_Enemy2Data.Enemysutandby);
	}

	PlayerData* player = GetPlayer();
	if (player->Inversion == true)
	{
		g_Enemy2Data.Inversion = true;

		//1回反転されて地面につくと死亡に変更
		if (g_Enemy2Data.Inversion = false)
		{
			g_Enemy2Data.InversionDie = true;
			g_Enemy2Data.movestate = DIE;
		}
	}

}

void DrawEnemy2()
{
	if (!g_Enemy2Data.active)
	{
		DrawAnimation(&g_Enemy2Data.Enemydie,
			g_Enemy2Data.body.pos.x + ENEMY_2_WIDTH / 2, g_Enemy2Data.body.pos.y + ENEMY_2_HEIGHT / 2,
			FALSE, g_Enemy2Data.Inversion);
	}
	if (g_Enemy2Data.body.move.x != 0.0f)
	{
		DrawAnimation(&g_Enemy2Data.Enemymove,
			g_Enemy2Data.body.pos.x + ENEMY_2_WIDTH / 2, g_Enemy2Data.body.pos.y + ENEMY_2_HEIGHT / 2,
			FALSE, g_Enemy2Data.Inversion);
	}
	if (g_Enemy2Data.body.move.x == 0.0f)
	{
		DrawAnimation(&g_Enemy2Data.Enemysutandby,
			g_Enemy2Data.body.pos.x + ENEMY_2_WIDTH / 2, g_Enemy2Data.body.pos.y + ENEMY_2_HEIGHT / 2,
			FALSE, g_Enemy2Data.Inversion);
	}
}

void FinEnemy2()
{
	DeleteGraph(g_Enemy2Data.handle);
}

//死亡
void Enemy2Dead()
{
	g_Enemy2Data.active = false;
}

void PlayerHitEnemy()
{
	Enemy2Dead();
	//PlaySE();
}