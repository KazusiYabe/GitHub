/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//キーボード処理のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "keyboard.h"
#include "FPS.h"

//########## グローバル変数 ##########

//キー入力を取得
KEYBOARD keyboard;

//########## 関数 ##########

/// <summary>
/// キーの入力状態を更新する関数
/// </summary>
/// <returns></returns>
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//一時的に現在のキーの入力状態を格納する
	char TempKey[KEY_KIND_MAX];

	//直前のキー入力をとっておく
	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		keyboard.OldAllKeyState[i] = keyboard.AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			keyboard.AllKeyState[i]++;	//押されている
		}
		else
		{
			keyboard.AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

/// <summary>
/// キーを押しているか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>押していたらTRUE</returns>
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (keyboard.AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

/// <summary>
/// キーを押し上げたか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>押し上げたらTRUE</returns>
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& keyboard.AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

/// <summary>
/// キーをクリックしたか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>クリックしたらTRUE</returns>
BOOL MY_KEY_CLICK(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] == 0		//直前は押していなくて
		&& keyboard.AllKeyState[KEY_INPUT_] >= 1)	//今は押しているとき
	{
		return TRUE;	//キーをクリックした（押し続けても、１回のみ発生）
	}
	else
	{
		return FALSE;	//キーをクリックしていないか、押し続けている
	}
}

/// <summary>
/// キーを押し続けているか、キーコードで判断する
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <param name="milliTime">キーを押し続けている時間(ミリ秒)</param>
/// <returns>押し続けていたらTRUE</returns>
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int milliTime)
{
	float MilliSec = 1000.0f;	//１秒は1000ミリ秒

	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = (milliTime / MilliSec) * GAME_FPS;

	if (keyboard.AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}