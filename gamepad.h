/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//ゲームパッド処理のヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include"game.h"

//########## マクロ定義 ##########

//ゲームパッド
#define PAD_MAX		(4+1)	//最大接続数(0番目はダミー)
#define PAD_BUTTON_MAX 16	//ボタンの数

#define PAD_TEST_POWER	100//接続テスト振動パワー(0～1000)
#define PAD_TEST_MSEC	500	//接続テスト振動時間(ミリ秒)

#define PAD_DEADZONE 0.10f	//ジョイパッドの入力方向の無効範囲を設定(デフォルトは0.35/0.0～1.0の間)

//########## 列挙型 ##########
enum PAD_BUTTON
{
	PADBTN_DOWN,
	PADBTN_LEFT,
	PADBTN_RIGHT,
	PADBTN_UP,
	PADBTN_1,
	PADBTN_2,
	PADBTN_3,
	PADBTN_4,
	PADBTN_5,
	PADBTN_6,
	PADBTN_7,
	PADBTN_8,
	PADBTN_9,
	PADBTN_10,
	PADBTN_11,
	PADBTN_12,
};	//パッドのボタンの種類

//########## 構造体 ##########

//ゲームパッド構造体
struct GAMEPAD
{
	int InputState = -1;	//接続状態

	int NewAnalogX = 0;		//アナログレバーの傾き具合X位置(更新)
	int NewAnalogY = 0;		//アナログレバーの傾き具合Y位置(更新)
	int OldAnalogX = 0;		//アナログレバーの傾き具合X位置(直前)
	int OldAnalogY = 0;		//アナログレバーの傾き具合Y位置(直前)

	int AllButtonState[PAD_BUTTON_MAX];			//すべてのボタンの状態
	int OldButtonKeyState[PAD_BUTTON_MAX];		//すべてのボタンの状態(直前)
};

//ゲームパッド動作確認用
struct DEBUG_GAMEPAD
{
	int RoundLeft = 20;		//半径
	POINT ptLeft = { 0,0 };	//位置
	unsigned int Color;		//色
};

//########## 外部のグローバル変数 ##########

//パッド関連
extern int padConnectNum ;			//パッドの接続数
extern GAMEPAD gamepad[PAD_MAX];	//GAMEPADデータを管理

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。
extern VOID MY_PAD_INIT(VOID);													//パッドの情報を初期化する
extern VOID MY_PAD_UPDATE(VOID);												//パッドの入力情報を更新する
extern BOOL MY_PAD_DOWN(int DX_INPUT_PAD, PAD_BUTTON PAD_);						//ボタンを押しているか、マウスコードで判断する
extern BOOL MY_PAD_UP(int DX_INPUT_PAD, PAD_BUTTON PAD_);						//ボタンを押し上げたか、マウスコードで判断する
extern BOOL MY_PADDOWN_KEEP(int DX_INPUT_PAD, PAD_BUTTON PAD_, int milliTime);	//ボタンを押し続けているか、マウスコードで判断する
extern BOOL MY_PAD_CLICK(int DX_INPUT_PAD, PAD_BUTTON PAD_);					//マウスをクリックしたか、マウスコードで判断する
extern VOID MY_PAD_DRAW(VOID);													//パッドの情報を描画する