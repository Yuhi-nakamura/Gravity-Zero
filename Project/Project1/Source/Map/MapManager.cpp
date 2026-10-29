#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Collision/Collision.h"

void InitMap()
{

}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	DrawBlock();
}

void FinMap()
{

}

//マップとの当たり判定と移動処理
void MoveWithMapCollisin(Body* body)
{
	//X軸
	body->pos.x += body->pos.x;

	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			//マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);

			//マップチップが0のときは何もない
			if (mapChipData.mapChip == 0)continue;

			//ブロック取得、当たり判定
			BlockData* block = mapChipData.data;

			//当たり判定
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height, block->pos.x, block->pos.y, block->width, block->height))
			{
				//左
				if (body->move.x > 0.0f)
				{
					//押し出し
					body->pos.x -= (body->pos.x + body->width) - block->pos.x;
				}
				//右
				else if (body->move.x < 0.0f)
				{
					//押し出し
					body->pos.x += (block->pos.x + block->width) - body->pos.x;
				}

				//移動量を0にする
				body->move.x = 0.0f;
			}
		}
	}

	//Y軸
	body->pos.y += body->move.y;

	// マップチップと当たり判定、押し出し
	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);
			// マップチップが0のときはなにもない
			if (mapChipData.mapChip == 0) continue;

			// ブロック取得、当たり判定
			BlockData* block = mapChipData.data;
			// 当たり判定
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height,
				block->pos.x, block->pos.y, block->width, block->height))
			{
				// 上
				if (body->move.y > 0.0f)
				{
					//押し出す
					body->pos.y -= (body->pos.y + body->height) - block->pos.y;

					// 空中フラグを折る
					body->isAir = false;
				}
				// 下
				else if (body->move.y < 0.0f)
				{
					//押し出す
					body->pos.y += (block->pos.y + block->height) - body->pos.y;

				}

				// 移動量を0にする
				body->move.y = 0.0f;
			}

		}
	}
}

