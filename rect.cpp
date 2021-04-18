/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//画像のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "rect.h"

//########## グローバル変数 ##########

//########## 関数 ##########

/// <summary>
/// 領域の当たり判定をする関数
/// </summary>
/// <param name="a">領域A</param>
/// <param name="b">領域B</param>
/// <returns></returns>
BOOL RectCollCheck(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

/// <summary>
/// RECT型を一時的に渡す
/// </summary>
/// <param name="left">左</param>
/// <param name="top">上</param>
/// <param name="right">右</param>
/// <param name="bottom">下</param>
/// <returns>RECT型</returns>
RECT GetRect(int left, int top, int right, int bottom)
{
	//一時的にRECT型の変数を作って
	RECT rect = { left ,top ,right ,bottom };

	//RECT型を返す
	return rect;
}

/// <summary>
/// RECTを利用して四角を描画
/// </summary>
/// <param name="r">RECT構造体</param>
/// <param name="color">描画する色</param>
/// <param name="b">中を塗りつぶさないならFALSE/塗りつぶすならTRUE</param>
/// <returns></returns>
VOID DrawRect(RECT r, unsigned int color, bool b)
{
	//引数を基に描画
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}