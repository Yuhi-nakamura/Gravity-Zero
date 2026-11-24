#include "DxLib.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyParameter.h"
#include "../Enemy/Enemy1.h"

#define GRAVITY_POWER (0.4f) //1フレームごとに加算する重力加速度
#define FALL_SPEED (10.0f) //落下速度上限

extern EnemyData g_EnemyData;

void InitGravity()
{
	PlayerData* player = GetPlayer();
	player->Inversion = false;
	player->body.move.y = 0.0f;
}

void StepGravity()
{
	PlayerData* player = GetPlayer();

	if (player->Inversion == false)
	{
		player->body.move.y += GRAVITY_POWER;
		if (player->body.move.y > FALL_SPEED)
		{
			player->body.move.y = FALL_SPEED;
		}

	}
	if (player->Inversion == true)
	{
		player->body.move.y -= GRAVITY_POWER;
		if (player->body.move.y < -FALL_SPEED)
		{
			player->body.move.y = -FALL_SPEED;
		}
	}
}

void ReverseGravity()
{
	PlayerData* player = GetPlayer();

	if (player->Inversion == false)
	{
		player->Inversion = true;
		player->body.move.y = 0.0f;
		player->body.Ground = false;
	}
	else if (player->Inversion == true)
	{
		player->Inversion = false;
		player->body.move.y = 0.0f;
		player->body.Ground = false;
	}
}

//Enemy用重力
void StepEnemyGravity()
{
	PlayerData* player = GetPlayer();

	if (player == nullptr)return;

	//通常
	if (player->Inversion == false)
	{
		g_EnemyData.body.move.y += GRAVITY_POWER;

		if (g_EnemyData.body.move.y > FALL_SPEED)
		{
			g_EnemyData.body.move.y = FALL_SPEED;
		}
	}

	//反転
	else
	{
		g_EnemyData.body.move.y -= GRAVITY_POWER;

		if (g_EnemyData.body.move.y < -FALL_SPEED)
		{
			g_EnemyData.body.move.y = -FALL_SPEED; 
		}
	}
}