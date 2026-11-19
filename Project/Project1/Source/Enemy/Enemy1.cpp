#include "DxLib.h"
#include "EnemyParameter.h"
#include "../Collision/Collision.h"
#include "../Map/MapChip.h"
#include "../Map/MapManager.h"
#include "../Sound/Sound.h"
#include "../Gravity/Gravity.h"
#include "../Player/Player.h"
#include "../Animetion/Animetion.h"
#include "Enemy1.h"
#include "../Sound/Sound.h"

//エネミー1関連設定(後で変更)
#define ENEMY_WIDTH (30.0f)
#define ENEMY_HEIGHT (30.0f)
#define ENEMY_RADIUS (20.0f)
#define ENEMY_MOVE_SPEED (3.0f)

//矩形判定のサイズ
#define ENEMY_COLLISION_WIDTH (30)
#define ENEMY_COLLISION_HEIGHT (30)

//デフォルト位置
#define ENEMY_DEFAULT_POS_X (300)
#define ENEMY_DEFAULT_POS_Y (100)


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
	InitAnimation(&g_EnemyData.Enemysutandby);
	InitAnimation(&g_EnemyData.Enemymove);
	InitAnimation(&g_EnemyData.Enemydie);
}

void LoadEnemy1()
{
	g_EnemyData.Enemysutandby.handle = LoadGraph("Data/Enemy/Enemy1.png");
	g_EnemyData.Enemymove.handle = LoadGraph("Data/Enemy/Enemy1_move.png");
	g_EnemyData.Enemydie.handle = LoadGraph("Data/Enemy/Enemy1_Die.png");
}

void StartEnemy1()
{
	//生存フラグ
	g_EnemyData.active = true;
	
	//初期位置
	g_EnemyData.body.pos.x = ENEMY_DEFAULT_POS_X;
	g_EnemyData.body.pos.y = ENEMY_DEFAULT_POS_Y;

	//アニメーション(大きさはあとで変更)
	StartAnimation(&g_EnemyData.Enemysutandby, g_EnemyData.body.pos.x, g_EnemyData.body.pos.y, 1, 1, 468, 408, TRUE, 98, 175);
	StartAnimation(&g_EnemyData.Enemymove, g_EnemyData.body.pos.x, g_EnemyData.body.pos.y, 1, 2, 1774, 887, TRUE, 98, 175);
	StartAnimation(&g_EnemyData.Enemydie, g_EnemyData.body.pos.x, g_EnemyData.body.pos.y, 1, 1, 434, 116, TRUE, 98, 175);

	//反転
	g_EnemyData.Inversion = false;

	//サイズ
	g_EnemyData.body.width = ENEMY_WIDTH;
	g_EnemyData.body.height = ENEMY_HEIGHT;

	//接地
	g_EnemyData.body.Ground = false;
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

	if (g_EnemyData.body.move.x != 0.0f)
	{
		UpdateAnimation(&g_EnemyData.Enemymove);
	}
	else
	{
		UpdateAnimation(&g_EnemyData.Enemysutandby);
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

	if (g_EnemyData.InversionDie = true)
	{
		UpdateAnimation(&g_EnemyData.Enemydie);
	}
}

void DrawEnemy1()
{
	if (!g_EnemyData.active)
	{
		DrawAnimation(&g_EnemyData.Enemydie,
			g_EnemyData.body.pos.x + ENEMY_WIDTH / 2, g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2,
			FALSE, g_EnemyData.Inversion);
	}

	if (g_EnemyData.body.move.x != 0.0f)
	{

		DrawAnimation(&g_EnemyData.Enemymove,
			g_EnemyData.body.pos.x + ENEMY_WIDTH / 2, g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2,
			FALSE, g_EnemyData.Inversion);
	}
	else
	{
		DrawAnimation(&g_EnemyData.Enemysutandby,
			g_EnemyData.body.pos.x + ENEMY_WIDTH / 2, g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2,
			FALSE, g_EnemyData.Inversion);
	}
}

void FinEnemy1()
{
	DeleteGraph(g_EnemyData.handle);
}

void EnemyDead()
{
	g_EnemyData.active = false;
}

void PlayerHitEnemy()
{
	EnemyDead();
	//PlaySE();
}
