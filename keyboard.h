/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//キーボード処理のヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include"game.h"

//########## マクロ定義 ##########

//キーボードの種類
#define KEY_KIND_MAX		256

//########## 構造体 ##########

//キーボード構造体
struct KEYBOARD
{
	char AllKeyState[KEY_KIND_MAX];			//すべてのキーの状態が入る
	char OldAllKeyState[KEY_KIND_MAX];		//すべてのキーの状態(直前)が入る
};

//########## 外部のグローバル変数 ##########

//キーボードの入力を取得
extern KEYBOARD keyboard;

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern VOID MY_ALL_KEYDOWN_UPDATE(VOID);					//キーの入力状態を更新する
extern BOOL MY_KEY_DOWN(int KEY_INPUT_);					//キーを押しているか、キーコードで判断する
extern BOOL MY_KEY_UP(int KEY_INPUT_);						//キーを押し上げたか、キーコードで判断する
extern BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int milliTime);	//キーを押し続けているか、キーコードで判断する
extern BOOL MY_KEY_CLICK(int KEY_INPUT_);					//キーをクリックしたか、キーコードで判断する