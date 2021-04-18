/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//マウス処理のヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include"game.h"

//########## マクロ定義 ##########

//マウスのボタン
#define MOUSE_BUTTON_CODE	129		//0x0000～0x0080まで

//########## 構造体 ##########

//int型のPOINT構造体
struct iPOINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
};

//マウス構造体
struct MOUSE
{
	int InputValue = 0;	//GetMouseInputの値が入る
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;						//マウスの座標が入る
	iPOINT OldPoint;					//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE];	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE];		//マウスのボタン入力が入る
};

//########## 外部のグローバル変数 ##########

//マウス入力を取得
extern MOUSE mouse;

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern VOID MY_MOUSE_UPDATE(VOID);								//マウスの入力情報を更新する
extern BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_);					//ボタンを押しているか、マウスコードで判断する
extern BOOL MY_MOUSE_UP(int MOUSE_INPUT_);						//ボタンを押し上げたか、マウスコードで判断する
extern BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int milliTime);	//ボタンを押し続けているか、マウスコードで判断する
extern BOOL MY_MOUSE_CLICK(int MOUSE_INPUT_);					//マウスをクリックしたか、マウスコードで判断する
extern VOID MY_MOUSE_DRAW(VOID);								//マウスの情報を描画する