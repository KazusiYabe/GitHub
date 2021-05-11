//キーボードのソースファイル

//ヘッダファイル読み込み
#include "keyboard.h"

//グローバル変数
KEYBOARD keyboard;

//関数

/// <summary>
/// キーの入力状態を更新する
/// </summary>
VOID ALLKeyUpdate(VOID)
{
	//直前のキー入力を取っておく
	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		keyboard.OldAllKeyState[i] = keyboard.AllKeyState[i];
	}

	//すべてのキーの入力状態を得る
	GetHitKeyStateAll(keyboard.TempKeyState);

	//押されているキーの時間を更新する
	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		keyboard.AllKeyState[i]++;
	}
	
	else
	{
		keyboard.AllkeyState[i] = 0;
	}

	return;
}

/// <summary>
/// キーをクリックしたか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT">キーコード</param>
/// <returns>押していたらTRUE</returns>
BOOL KeyDown(int KEY_INPUT_)
{
	if (
		keyboard.OldAllKeyState[KEY_INPUT_] != 0   //以前は押していた
		&& keyboard.AllKeyState[KEY_INPUT_] == 0   //現在は押していない
		)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/// <summary>
/// キーを押し続けているか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT_">キーコード</param>
/// <param name="MilliTime">キーを押し続けているミリ秒</param>
/// <returns></returns>
BOOL KeyDownKeep(int KEY_INPUT_, int MilliTime)
{
	//1秒は1000ミリ秒
	float MilliSec = 1000.0f;

	//押し続けている時間は、ミリ秒xFPS値

	int UpdateTime = (MilliTime / MilliSec) * 60;

	if (keyboard.AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;   //押し続けている
	}
	else
	{
		return FALSE;  //押し続けていない
	}
}