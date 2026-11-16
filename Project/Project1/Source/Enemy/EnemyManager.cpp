#include "EnemyManager.h"
#include "Enemy1.h"

int g_EnemyTimer = 0;

void InitEnemy()
{
	g_EnemyTimer = 0;
	
	//各エネミー初期化
	InitEnemy1();
}

void LoadEnemy()
{
	//各エネミーロード
	LoadEnemy1();
}

void StartEnemy()
{
	//各エネミースタート
	StartEnemy1();
}

void StepEnemy()
{
	//各エネミーステップ
	StepEnemy1();
}

void UpdateEnemy()
{
	//各エネミー更新
	UpdateEnemy1();
}

void DrawEnemy() 
{
	//各エネミー描画
	DrawEnemy1();
}

void FinEnemy()
{
	//各エネミー終了
	FinEnemy1();
}

void EnemySpawn()
{

}