#include "DxLib.h"
#include "Animetion.h"

void InitAnimation(AnimationData* animData)
{
	animData->active = false;
	animData->handle = 0;
	animData->nowFrame = 0;
	animData->frameNum = 0;
	animData->frameWidth = 0;
	animData->frameHeight = 0;
	animData->timer = 0;
	animData->posX = 0.0f;
	animData->posY = 0.0f;
	animData->drawHeight = 0;
	animData->drawWidth = 0;
	animData->sheetWidth = 0;
}

void StartAnimation(AnimationData* animData, float posX, float posY, int interval, int frameNum, int width, int height, bool isLoop,int DrawWidth,int DrawHeight)
{
	//アクティブ
	animData->active = true;

	//座標
	animData->posX = posX;
	animData->posY = posY;

	//インターバル
	animData->interval = interval;

	//タイマー
	animData->timer = animData->interval;

	//0コマ目に
	animData->nowFrame = 0;

	//コマ数
	animData->frameNum = frameNum;

	//サイズ
	animData->frameHeight = height;
	animData->frameWidth = width;
	animData->sheetWidth = width * frameNum;

	//ループ
	animData->Loop = isLoop;

	//描画サイズ
	animData->drawWidth = DrawWidth;
	animData->drawHeight = DrawHeight;

}

void UpdateAnimation(AnimationData* animData)
{
	if (!animData->active)return;

	//次のコマ
	if (animData->timer <= 0)
	{
		//次のコマ
		animData->nowFrame++;

		//タイマーリセット
		animData->timer = animData->interval;

		//全コマ表示が終わったら非表示
		if (animData->nowFrame >= animData->frameNum)
		{
			//ループ
			if (animData->Loop)
			{
				//0コマ目に
				animData->nowFrame = 0;
			}
			else
			{
				//終了
				animData->active = false;
			}

			return;
		}
	}

	animData->timer--;
}

void DrawAnimation(AnimationData* animData, bool isTurnX, bool isTurnY)
{
	DrawAnimation(animData, animData->posX, animData->posY,isTurnX,isTurnY);
}

void DrawAnimation(AnimationData* animData, float posX, float posY, bool isTurnX, bool isTurnY)
{
	if (!animData->active)return;

	//コマの切り取り位置計算
	int frameX = (animData->sheetWidth * animData->nowFrame) / animData->frameNum;
	int nextFrameX = (animData->sheetWidth * (animData->nowFrame + 1)) / animData->frameNum;
	int frameWidth = nextFrameX - frameX;

	//表示するコマ
	//DrawRectRotaGraph(
	//	(int)posX, (int)posY,
	//	frameX, 0,
	//	frameWidth, animData->frameHeight,
	//	(double)animData->drawWidth / frameWidth,
	//	isTurnY ? DX_PI : 0.0,
	//	animData->handle, TRUE, isTurnX);

	DrawRectRotaGraph3(
		(int)posX, (int)posY,
		frameX, 0,
		frameWidth, animData->frameHeight,
		frameWidth / 2, animData->frameHeight / 2,
		(double)animData->drawWidth / frameWidth,
		(double)animData->drawHeight / animData->frameHeight,
		0.0,
		animData->handle, TRUE,
		isTurnX, isTurnY);
}


