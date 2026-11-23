#include "DxLib.h"
#include "Camera.h"
#include "../Input/Input.h"
#include "../Player/Player.h"
#include "../GameSetting/GameSetting.h"

#define DEBUG_CAMERA_SPEED (5.0f)
#define CAMERA_SCROLL_START_X (200.0f)

CameraData g_CameraData = { 0 };

void InitCamera()
{
	g_CameraData.posX = 0.0f;
	g_CameraData.posY = 0.0f;
}

void StepCamera()
{
	//プレイヤー取得
	PlayerData* player = GetPlayer();
	//画面中央にPlayerを表示
	g_CameraData.posX = player->body.pos.x
		+ player->body.width / 2 - SCREEN_WIDTH / 2;

	g_CameraData.posY = player->body.pos.y
		+ player->body.height / 2 - SCREEN_HEIGHT / 2;

}

void DrawCamera()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カメラの座標 = 【%f.%f】", g_CameraData.posX, g_CameraData.posY);

}

CameraData GetCamera()
{
	return g_CameraData;
}