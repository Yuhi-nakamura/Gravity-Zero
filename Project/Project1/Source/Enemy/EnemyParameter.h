#pragma once
#include "../Collision/CollisionParameter.h"

//エネミーデータ
struct EnemyData
{
	bool active; //生存フラグ
	int handle; //画像
	Body body; //当たり判定
	bool Inversion; //反転
};