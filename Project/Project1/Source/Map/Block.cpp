#include "Block.h"

BlockData g_Block[BLOCK_MAX] = { 0 };
int g_Blockhandle[BLOCK_TYPE_MAX] = { 0 };

void InitBlock()
{
	BlockData* block = g_Block;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		block->active = false;
		block->pos = VGet(0.0f, 0.0f, 0.0f);
		block->type = BLOCK_TYPE_NONE;
	}
}

void LoadBlock()
{
	g_Blockhandle[NORMAL_BLOCK] = LoadGraph("Data/Map/NormalBlock.png");

	if (g_Blockhandle[NORMAL_BLOCK] == -1)
	{
		MessageBox(NULL, "NormalBlock.pngを読み込めません",
			"エラー", MB_OK);
	}
}

void StartBlock()
{

}

void StepBlock()
{

}

void DrawBlock()
{
	BlockData* block = g_Block;

	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		if (block->active)
		{
			DrawGraph((int)block->pos.x, (int)block->pos.y,
				block->handle, TRUE);
		}
	}
}
void FinBlock()
{

}

BlockData* CreateBlock(MapChipType type, VECTOR pos)
{
	//未使用ブロックえお探す
	BlockData* block = g_Block;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		if (!block->active)
		{
			block->active = true;
			block->handle = g_Blockhandle[type];
			block->pos = pos;
			block->type = type;
			block->width = MAP_CHIP_WIDTH;
			block->height = MAP_CHIP_HEIGHT;
			return block;
		}
	}
	return nullptr;
}

BlockData* GetBlocks()
{
	return g_Block;
}