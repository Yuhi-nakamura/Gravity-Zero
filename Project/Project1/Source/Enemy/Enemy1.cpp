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
#include "../Camera/Camera.h"

//エネミー1関連設定(後で変更)
#define ENEMY_WIDTH (98.0f)
#define ENEMY_HEIGHT (175.0f)
#define ENEMY_RADIUS (20.0f)
#define ENEMY_MOVE_SPEED (3.0f)

//矩形判定のサイズ
#define ENEMY_COLLISION_WIDTH (98)
#define ENEMY_COLLISION_HEIGHT (175)

//デフォルト位置
#define ENEMY_DEFAULT_POS_X (450)
#define ENEMY_DEFAULT_POS_Y (300)


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
	g_EnemyData.dieTimer = 0;
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
	StartAnimation(&g_EnemyData.Enemymove, g_EnemyData.body.pos.x, g_EnemyData.body.pos.y, 4, 2, 887, 887, TRUE, 98, 175);
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

	//重力
	StepEnemyGravity();
}

void UpdateEnemy1()
{
	//移動前の値を保存
	float BeforeMoving = 0.0f;

	if (!g_EnemyData.active)
	{
		g_EnemyData.dieTimer++;

		// 約3秒経過したら画像を消す
		if (g_EnemyData.dieTimer >= 180)
		{
			g_EnemyData.handle = 0;
		}

		return;
	}
	
	float BeforeMoveY = g_EnemyData.body.move.y;

	BeforeMoving = g_EnemyData.body.move.x;

	MoveWithMapCollisin(&g_EnemyData.body);

	// 上昇中に天井へぶつかったらしぬ
	if (BeforeMoveY < 0.0f && g_EnemyData.body.Ground == true)
	{
		EnemyDead();
		return;
	}

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
	if(g_EnemyData.body.move.x == 0.0f)
	{
		UpdateAnimation(&g_EnemyData.Enemysutandby);
	}
	
	
	PlayerData* player = GetPlayer();

	if (player != nullptr)
	{
		g_EnemyData.Inversion = player->Inversion;

		if (player->active)
		{
			if (CheckSquareSquarebody(&g_EnemyData.body, &player->body))
			{
				EnemyHit();
			}
		}
		
		/*if (player->Inversion == true)
		{
			g_EnemyData.Inversion = true;
		}*/
	}
	

	if (g_EnemyData.InversionDie == true)
	{
		UpdateAnimation(&g_EnemyData.Enemydie);
	}
}

void DrawEnemy1()
{
	CameraData camera = GetCamera();

	if (!g_EnemyData.active)
	{
		// 3秒経過したら死亡画像を描画しない
		if (g_EnemyData.dieTimer < 180)
		{
			DrawAnimation(&g_EnemyData.Enemydie,
				g_EnemyData.body.pos.x + ENEMY_WIDTH / 2 - camera.posX,
				g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2 - camera.posY,
				FALSE, g_EnemyData.Inversion);
		}
		return;
	}

	if (g_EnemyData.body.move.x != 0.0f)
	{

		DrawAnimation(&g_EnemyData.Enemymove,
			g_EnemyData.body.pos.x + ENEMY_WIDTH / 2 - camera.posX, g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2 - camera.posY,
			g_EnemyData.direction > 0, g_EnemyData.Inversion);
	}
	if(g_EnemyData.body.move.x == 0.0f)
	{
		DrawAnimation(&g_EnemyData.Enemysutandby,
			g_EnemyData.body.pos.x + ENEMY_WIDTH / 2 - camera.posX, g_EnemyData.body.pos.y + ENEMY_HEIGHT / 2 - camera.posY,
			g_EnemyData.direction > 0, g_EnemyData.Inversion);
	}
}

void FinEnemy1()
{
	DeleteGraph(g_EnemyData.handle);
}

void EnemyDead()
{
	g_EnemyData.active = false;
	g_EnemyData.dieTimer = 0;
}

void PlayerHitEnemy()
{
	EnemyDead();
	//PlaySE();
}
