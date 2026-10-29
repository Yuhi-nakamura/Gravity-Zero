#pragma once

//BGM
enum BGM
{
	BGM_TITLE,
	BGM_PLAY,
	BGM_CLEAR,
	BGM_TYPE_MAX,
};

void LoadBGM();
void PlayBGN(BGM type);
void StopBGN(BGM type);
void FinBGM();

//SE
enum SE
{
	PLAYER_DEAD,
	ENEMY_1_DEAD,
	ENEMY_2_DEAD,
	SE_TYPE_MAX,
};

void LoadSE();
void PlaySE(SE type);
void FinSE();