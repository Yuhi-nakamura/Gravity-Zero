#include "DxLib.h"
#include "Text.h"
#include <string.h>

#define UI_TEXT_MAX (32)

//データ
UITextData g_UITextData[UI_TEXT_MAX] = { 0 };

//フォント
int g_FontHandle = 0;

void InitUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		uiText->active = false;
		uiText->posX = 0.0f;
		uiText->posY = 0.0f;
		memset(uiText->text, 0, sizeof(uiText->text));
	}
}

void LoadUIText()
{
	g_FontHandle = CreateFontToHandle("Nosutaru-dot M+H 10 Regular", 28, -1);
}

void StepUIText()
{

}

void UpdateUIText()
{

}

void DrawUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		if (!uiText->active)continue;

		//描画
		DrawStringToHandle((int)uiText->posX, (int)uiText->posY, uiText->text, GetColor(255, 255, 255), g_FontHandle);
	}
}

void FinUIText()
{

}

UITextData* CreateUIText(float posX, float posY, const char* text)
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		if (!uiText->active)
		{
			uiText->active = true;

			uiText->posX = posX;
			uiText->posY = posY;

			strcpy_s(uiText->text, text);

			return uiText;
		}
	}
	return nullptr;
}

void SetUIText(UITextData* uiText, const char* text)
{
	strcpy_s(uiText->text, text);
}

void ResetUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		uiText->active = false;
	}
}