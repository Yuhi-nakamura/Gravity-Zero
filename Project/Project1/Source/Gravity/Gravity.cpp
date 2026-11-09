#include "DxLib.h"
#include "../Player/Player.h"

#define GRAVITY_POWER (0.4f) //1フレームごとに加算する重力加速度
#define FALL_SPEED (8.0f) //落下速度上限

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