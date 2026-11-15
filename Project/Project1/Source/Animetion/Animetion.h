#pragma once

struct AnimationData
{
	bool active;
	bool Loop;
	float posX;
	float posY;
	int handle;
	int nowFrame;
	int frameNum;
	int frameWidth; //切り出しサイズ
	int frameHeight; //切り出しサイズ
	int timer;
	int interval;
	int drawWidth; //描画サイズ
	int drawHeight; //描画サイズ
};

void InitAnimation(AnimationData* animData);
void UpdateAnimation(AnimationData* animData);
void DrawAnimation(AnimationData* animData, bool isTurnX = false, bool isTurnY = false);
void DrawAnimation(AnimationData* animData, float posX, float posY, bool isTurnX = false, bool isTurnY = false);
void StartAnimation(AnimationData* animData, float posX, float posY,
	int interval, int frameNum, int width, int height, bool isLoop,
	int DrawWidth, int DrawHeight);