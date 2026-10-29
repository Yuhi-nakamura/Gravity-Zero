#include "Sound.h"
#include "DxLib.h"

int g_BGMHandle[BGM_TYPE_MAX] = { 0 };
int g_SEHandle[SE_TYPE_MAX] = { 0 };

void LoadBGM()
{
	g_BGMHandle[BGM_TITLE] = LoadSoundMem("");
	g_BGMHandle[BGM_PLAY] = LoadSoundMem("");
	g_BGMHandle[BGM_CLEAR] = LoadSoundMem("");
}

void PlayBGM(BGM type)
{
	PlaySoundMem(g_BGMHandle[type], DX_PLAYTYPE_LOOP);
}

void StopBGM(BGM type)
{
	StopSoundMem(g_BGMHandle[type]);
}

void FinBGM()
{
	for (int i = 0; i < BGM_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_BGMHandle[i]);
	}
}

void LoadSE()
{
	g_SEHandle[PLAYER_DEAD] = LoadSoundMem("");
	g_SEHandle[ENEMY_1_DEAD] = LoadSoundMem("");
	g_SEHandle[ENEMY_2_DEAD] = LoadSoundMem("");
}

void PlaySE(SE type)
{
	PlaySoundMem(g_SEHandle[type], DX_PLAYTYPE_BACK);
}

void FinSE()
{
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_SEHandle[i]);
	}
}