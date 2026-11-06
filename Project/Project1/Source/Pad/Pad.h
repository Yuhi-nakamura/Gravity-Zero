#pragma once

/// <summary>
/// ゲームパッドの入力を管理
/// </summary>

namespace Pad
{
	//更新処理
	void Update();

	/// <summary>
	/// 押されているか
	/// </summary>
	/// <param name="Key">入力キー</param>
	/// <returns></returns>
	bool IsPress(int Key);

	/// <summary>
	/// 押された瞬間
	/// </summary>
	/// <param name="Key">入力樹ー</param>
	/// <returns></returns>
	bool IsTrigger(int Key);

	//離した瞬間
	bool IsRelease(int Key);
}