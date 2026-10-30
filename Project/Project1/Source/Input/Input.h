#pragma once

//入力ボタン定義
enum InputKey
{
	KEY_Q		=(1 << 0),
	KEY_A		=(1 << 1),
	KEY_Z		=(1 << 2),
	KEY_E		=(1 << 3),
	KEY_D		=(1 << 4),
	KEY_C		=(1 << 5),
	KEY_SPACE	=(1 << 6),
};

//関数のプロトタイプ宣言
void  InitInput();
void UpdateInput();
void DrawInput();
void FinInput();

bool IsInputKey(InputKey key);
bool IsTriggerKey(InputKey key);

//ゲームパッド
//各ボタン、スティックの定義
typedef enum
{
	XINPUT_POV_UP = 0,
	XINPUT_POV_DOWN,
	XINPUT_POV_LEFT,
	XINPUT_POV_RIGHT,
	XINPUT_START,
	XINPUT_BACK,
	XINPUT_LEFT_THUMB,
	XINPUT_RIGHT_THUMB,
	XINPUT_LEFT_SHOULDER,
	XINPUT_RIGHT_SHOULDER,
	XINPUT_A = 12,
	XINPUT_B,
	XINPUT_X,
	XINPUT_Y,
	XINPUT_LEFT_TRIGGER,
	XINPUT_RIGHT_TRIGGER,
	XINPUT_THUMBL_LEFT,
	XINPUT_THUMBL_RIGHT,
	XINPUT_THUMBL_UP,
	XINPUT_THUMBL_DOWN,
	XINPUT_THUMBL_LEFT,
	XINPUT_THUMBL_RIGHT,

	XINPUT_ALL
} exInput;

//ゲーム内操作
typedef struct
{
	int left;
	int right;
	int confirm; //決定
	bool Inversion; //反転
	int menu;
}config_t;

extern config_t config;

void Input_Initialize();
void Input_Merge(int* p, int k);

void Input_UddateGamepad();
bool Input_GetGamepadDown(int KeyCode);
int Input_GetGamepad(int KeyCode);
bool Input_GetGamepadUp(int KeyCode);
void Input_ALLUpdate();