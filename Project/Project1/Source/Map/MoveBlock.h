#pragma once
#include "../Collision/CollisionParameter.h"
#include "MapParameter.h"
#include "DxLib.h"

struct MoveBlockData
{
	bool active;
	int handle;
	MapChipType type;
	float width;
	float height;
	Body body; //“–‚½‚è”»’èƒ{ƒfƒB
	int direction; //•ûŒü

};

//ŠÖ”
void InitMoveBlock();
void LoadMoveBlock();
void StartMoveBlock();
void StepMoveBlock();
void UpdateMoveBlock();
void DrawMoveBlock();
void FinMoveBlock();