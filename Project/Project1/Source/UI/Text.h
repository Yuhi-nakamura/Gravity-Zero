#pragma once

#define TEXT_MAX (256)

struct UITextData
{
	bool active;
	char text[TEXT_MAX];
	float posX;
	float posY;
};

//ä÷êî
void InitUIText();
void LoadUIText();
void StepUIText();
void UpdateUIText();
void DrawUIText();
void FinUIText();

//ê∂ê¨
UITextData* CreateUIText(float posX, float posY, const char* text);

void SetUIText(UITextData uiText, const char* text);

void ResetUIText();
