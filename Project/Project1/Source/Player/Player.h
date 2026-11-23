#pragma once
#include "../Collision/CollisionParameter.h"
#include "../Animetion/Animetion.h"

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
	AnimationData standby; //待機
	AnimationData Dash; // ダッシュ
	AnimationData InversionAnime; //反転中
	int invincibletimer; //死亡後無敵時間
	bool invincible; //死亡後無敵
	int respawnTimer; //リスポーン待ち

	bool TurnX; //左右反転
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

//リスポーン
bool ReSpawnPlayer();

//死亡
void PlayerDead();

//Enemyと接触
void EnemyHit();