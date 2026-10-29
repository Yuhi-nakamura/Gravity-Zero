#pragma once
#include "../Collision/CollisionParameter.h"

enum PlayerAnimetionType
{
	PLAYER_ANIM_IDLE,
	PLAYER_ANIM_RUN,
	PLAYER_ANIM_MAX,
	PLAYER_ANIM_NOME = -1
};

//プレイヤーデータ
struct PlayerData
{
	bool active;	//生存フラグ
	int handle;		//画像
	Body body;	//当たり判定
	bool Inversion; //反転
};

//関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

//取得関数
PlayerData* GetPlayer();