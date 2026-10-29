#include "DxLib.h"
#include "FPS.h"

//平均を計算するタイミング
#define FPS_SAMPLE_NUM (60)

//ゲームのFPS
#define FPS (60)

int g_StartTime;    //計測開始
int g_Count;		//カウンター
float g_Fps;        //現在のFPS

void InitFPS()
{
	g_StartTime = GetNowCount();
	g_Count = 0;
	g_Fps = 0;
}

void UpdateFPS()
{
	//1フレーム目なら時刻を記録
	if (g_Count == 0)
	{
		g_StartTime = GetNowCount();
	}

	//サンプル数と同じ回数フレームが回ったら平均を計算
	if (g_Count == FPS_SAMPLE_NUM)
	{
		int time = GetNowCount();
		//かかった時間をサンプル数で割り平均とする
		g_Fps = 1000.0f / ((time - g_StartTime) / (float)FPS_SAMPLE_NUM);
		g_Count = 0;
		g_StartTime = time;
	}
	g_Count++;
}

void DrawFPS()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS 【%.1f】", g_Fps);
}

void FPSWait()
{
	//かかった時間
	int takeTime = GetNowCount() - g_StartTime;

	//待機時間
	int waitTime = g_Count * 1000 / FPS - takeTime;

	//待機
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}