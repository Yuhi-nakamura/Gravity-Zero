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

void StepEnemy2()
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

void StartEnemy2()
{

}

void UpdataEnemy2()
{

}

void DrawEnemy2()
{

}

void FinEnemy2()
{

}