#include "DxLib.h"
#include "Camera.h"
#include "../Input/Input.h"
#include "../Player/Player.h"

#define DEBUG_CAMERA_SPEED (5.0f)
#define CAMERA_SCROLL_START_X (200.0f)

CameraData g_CameraData = { 0 };

void InitCamera()
{

}

void StepCamera()
{
	//プレイヤー取得
	PlayerData* player = GetPlayer();
	//左右
	g_CameraData.posX = player->body.pos.x - 100.0f;

	//上下
	g_CameraData.posY = player->body.pos.y- 600.0f;

}

void DrawCamera()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カメラの座標 = 【%f.%f】", g_CameraData.posX, g_CameraData.posY);

}

CameraData GetCamera()
{
	return g_CameraData;
}