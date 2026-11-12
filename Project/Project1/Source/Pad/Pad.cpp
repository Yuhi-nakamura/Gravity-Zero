#include "DxLib.h"
#include "Pad.h"

namespace Pad
{
	//前のパッド
	int lastPad = 0;

	//現在のパッド
	int nowPad = 0;
}

namespace Pad
{
	//左スティックX軸、Y軸
	int stickX = 0;
	int stickY = 0;

	void Update()
	{
		//前のフレームのパッド情報
		lastPad = nowPad;

		//現在のパッド情報
		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		//左スティックの入力情報
		GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_PAD1);
	}

	//左スティックのX軸を取得
	int GetStickX()
	{
		return stickX;
	}

	//左スティックのY軸を取得
	int GetStickY()
	{
		return stickY;
	}

	bool Pad::IsPress(int Key)
	{
		//現在のフレームで押されている
		return (nowPad & Key);
	}

	bool Pad::IsTrigger(int Key)
	{
		bool isNow = (nowPad & Key);//現在のフレーム
		bool isLast = (lastPad & Key); //前のフレーム

		//現在のフレームに押されていて前回のフレームに押されていない
		if (isNow && !isLast)
		{
			return true;
		}
		return false;
	}

	bool Pad::IsRelease(int Key)
	{
		bool isNow = (nowPad & Key);
		bool isLast = (lastPad & Key);

		//現在のフレームに押されてなくて前回のフレームに押されていた
		if (!isNow && isLast)
		{
			return true;
		}
		return false;
	}
}