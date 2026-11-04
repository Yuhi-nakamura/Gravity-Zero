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


//ゲームパッド関連
const static int TRIGGER_DEADZONE = 127;
const static int STICK_DEADZONE = 12000;

static int Input_Gamepad[XINPUT_ALL];

config_t config;

//入力関連初期化
void Input_Initialize()
{
	config.left = XINPUT_POV_LEFT;
	config.right = XINPUT_POV_RIGHT;
	config.confirm = XINPUT_A;
	config.menu = XINPUT_START;
	config.Inversion = XINPUT_B;
	config.Inversion = XINPUT_X;
	config.Inversion = XINPUT_Y;
}

//2つの引数を比較、大きいほうを1つ目の引数に代入
void Input_Merge(int* p, int k)
{
	//片方が離された瞬間(-1)でもう片方が入力なし(0)の場合
	if (*p == -1 && k == 0)
	{
		return;
	}
	else if (*p == 0 && k == -1)
	{
		*p = k;
		return;
	}
	//それ以外
	*p = *p > k ? *p : k;
}

//ゲームパッドの入力状態更新
void Input_UpdateGamepad()
{
	int i;
	XINPUT_STATE input; //現在のゲームパッドの入力状態を格納
	
	//入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	for (i = 0; i < XINPUT_ALL; i++)
	{
		if (i < XINPUT_LEFT_TRIGGER) //ボタン
		{
			if (input.Buttons[i] != 0) //i番に対応するボタンが押されていたら
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていれば
				{
					Input_Gamepad[i] = -1; //-1にする。-1はキーが離された時用の値
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_LEFT_TRIGGER) //Lトリガー
		{
			if (input.LeftTrigger > TRIGGER_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_RIGHT_TRIGGER) //Rトリガー
		{
			if (input.RightTrigger > TRIGGER_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBL_UP) //左スティック
		{
			if (input.ThumbLX > STICK_DEADZONE)
			{
				Input_Gamepad[i]++; // 加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBL_DOWN)
		{
			if (input.ThumbLY < -STICK_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBL_LEFT)
		{
			if (input.ThumbLX < -STICK_DEADZONE)
			{
				Input_Gamepad[i]++;
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBL_RIGHT)
		{
			if (input.ThumbLX > STICK_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBR_UP)//右スティック
		{
			if (input.ThumbRY > STICK_DEADZONE) //右スティックが上に一定以上倒されていたら
			{
				Input_Gamepad[i]++;         //加算       
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBR_DOWN)
		{
			if (input.ThumbRY < -STICK_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBR_LEFT)
		{
			if (input.ThumbRX < -STICK_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}
		else if (i == XINPUT_THUMBR_RIGHT)
		{
			if (input.ThumbRX > STICK_DEADZONE)
			{
				Input_Gamepad[i]++; //加算
			}
			else
			{
				if (Input_Gamepad[i] > 0) //前フレームで対応するキーが押されていたら
				{
					Input_Gamepad[i] = -1;//-1する
				}
				else
				{
					Input_Gamepad[i] = 0; //0にする
				}
			}
		}

		//キーボードとゲームパっドの入力を統合

	}
}
