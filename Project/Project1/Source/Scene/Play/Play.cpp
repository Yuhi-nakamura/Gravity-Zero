#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../Collision/Collision.h"
#include "../../Enemy/EnemyManager.h"

//背景スピード
#define BACK_GROUND_SPEED (4.0f)

void InitPlay()
{
	//プレイヤー初期化
	InitPlayer();

	//Enemy初期化
	InitEnemy();

	//マップ初期化
	InitMap();
}

void LoadPlay()
{
	LoadPlayer();

	LoadMap();
}

void StartPlay()
{
	StartPlayer();

	StartMap();
}

void StepPlay()
{
	StepPlayer();
}

void UpdatePlay()
{
	UpdatePlayer();
}

void DrawPlay()
{
	DrawMap();

	DrawPlayer();
}

void FinPlay()
{
	FinPlayer();

	FinMap();
}
