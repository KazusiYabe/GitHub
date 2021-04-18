#pragma once
/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//RECTのヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include "game.h"

//########## マクロ定義 ##########


//########## 構造体 ##########

//########## 外部のグローバル変数 ##########


//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern BOOL RectCollCheck(RECT a, RECT b);						//四角領域の当たり判定をチェックする
extern RECT GetRect(int left, int top, int right, int bottom);	//RECT型を一時的に渡す
extern void DrawRect(RECT r, unsigned int color, bool b);		//RECTを利用して四角を描画