#include "DxLib.h"
#include "Image.h"

#define IMAGE_MAX 32

//Imageデータ
UIImageData g_UIImageData[IMAGE_MAX] = { 0 };

//画像保存
int g_UIImageHnadle[UI_IMAGE_TYPE_MAX] = { 0 };

void InitUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < IMAGE_MAX; i++, ui++)
	{
		ui->active = false;
		ui->handle = 0;
		ui->posX = 0.0f;
		ui->posY = 0.0f;
	}
}

void LoadUIImage()
{
	//Playシーン
	g_UIImageHnadle[UI_IMAGE_KEY] = LoadGraph("Data/UI/KEY.png");
}

void StepUIImage()
{

}

void UpdateUIImage()
{

}

void DrawUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < IMAGE_MAX; i++, ui++)
	{
		if (!ui->active)return;
		DrawGraph((int)ui->posX, (int)ui->posY, ui->handle, TRUE);
	}
}

void FinUIImage()
{
	for (int i = 0; i < UI_IMAGE_TYPE_MAX; i++)
	{
		DeleteGraph(g_UIImageHnadle[i]);
	}
}

void CreateUIImage(UIImageType type, float posX, float posY)
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < IMAGE_MAX; i++, ui++)
	{
		//未使用のUIを探す
		if (!ui->active)
		{
			//アクティブ
			ui->active = true;

			//画像
			ui->handle = g_UIImageHnadle[type];

			//座標
			ui->posX = posX;
			ui->posY = posY;

			break;
		}
	}
}

void ResetUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < IMAGE_MAX; i++, ui++)
	{
		ui->active = false;
	}
}
