#pragma once

//Imageの種類
enum UIImageType
{
	//playシーンで使う
	UI_IMAGE_KEY,

	//種類最大数
	UI_IMAGE_TYPE_MAX,
};

//データ
struct UIImageData
{
	bool active;
	int handle;
	float posX;
	float posY;
};

//関数
void InitUIImage();
void LoadUIImage();
void StepUIImage();
void UpdateUIImage();
void DrawUIImage();
void FinUIImage();

//生成
void CreateUImage(UIImageType type, float posX, float posY);

//未使用にする,切り替え時など
void ResetUIImage();