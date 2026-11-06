#pragma once

//”wŒiƒŒƒCƒ„[
enum BackGroundLayer
{
	BACK_GROUND_LAYER_1,
	BACK_GROUND_LAYER_2,
	BACK_GROUND_LAYER_3,
	BACK_GROUND_LAYER_MAX,
};

//ŠÖ”
void InitBackGround();
void LoadBackGround(const char* path, BackGroundLayer layer);
void StepBackGround();
void UpdateBackGround();
void DrawBackGround();
void FinBackGround();

//”wŒi‚ÌˆÚ“®—Êİ’è
void SetBackGroundMove(float moveX, float moveY, BackGroundLayer layer);