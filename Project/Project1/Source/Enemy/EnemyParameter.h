#pragma once
#include "../Collision/CollisionParameter.h"

//エネミーデータ
struct EnemyData
{
	bool active; //生存フラグ
	int handle; //画像
	Body body; //当たり判定
	bool Inversion; //反転

	int direction; //向き
	bool InversionDie; //着地後死亡判定
	int stopTimer; //ぶつかった後の停止時間
	MoveState movestate; //行動状態
};

enum MoveState
{
	MOVE,
	STOP,
	DIE,
	MOVE_MAX,
};