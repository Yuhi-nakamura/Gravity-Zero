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
void UpdataInput();
void DrawInput();
void FinInput();

bool IsInputKey(InputKey key);
bool IsTrigerKey(InputKey key);