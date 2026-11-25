#pragma once
#include "DxLib.h"
#include "../Collision/CollisionParameter.h"

#define BLOCK_MAX 2048
#define MAP_CHIP_X_NUM (64)
#define MAP_CHIP_Y_NUM (30)
#define MAP_CHIP_WIDTH (50.0f)
#define MAP_CHIP_HEIGHT (50.0f)

enum MapChipType
{
	BLOCK_TYPE_NONE,
	NORMAL_BLOCK,
	MOVE_BLOCK, //ìÆÇ≠è∞
	THORN_BLOCK, //ûô
	BLOCK_TYPE_MAX,
};

struct BlockData
{
	bool active;
	int handle;
	MapChipType type;
	VECTOR pos;
	float width;
	float height;
	Body body; //ìñÇΩÇËîªíËÉ{ÉfÉB
};

struct MapChipData
{
	int mapChip;
	BlockData* data;
	//bool isCollision;
};
