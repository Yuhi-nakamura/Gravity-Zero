#include "Input.h"
#include "DxLib.h"

//入力ビットフラグ
int g_InputState = 0;
//前回の入力ビット
int g_PrevInputState = 0;

void InitInput()
{
	g_InputState = 0;
	g_PrevInputState = 0;
}

void UpdateInput()
{
	//前回の入力を覚えておく
	g_PrevInputState = g_InputState;

	//入力状態をクリア
	g_InputState = 0;

	//入力状態をビットフラグで設定
	if (CheckHitKey(KEY_INPUT_Q))
	{
		g_InputState |= KEY_Q;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		g_InputState |= KEY_A;
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		g_InputState |= KEY_Z;
	}
	if (CheckHitKey(KEY_INPUT_E))
	{
		g_InputState |= KEY_E;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		g_InputState |= KEY_D;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		g_InputState |= KEY_C;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		g_InputState |= KEY_SPACE;
	}
}

void DrawInput()
{

}

void FinInput()
{

}

bool IsInputKey(InputKey key)
{
	return g_InputState & key;
}

bool IsTriggerKey(InputKey key)
{
	return (g_InputState & key) && !(g_PrevInputState & key);
}