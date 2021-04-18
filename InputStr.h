/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//キー文字入力処理のヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include"game.h"

//########## マクロ定義 ##########

//キー文字入力系
#define INPUTSTR_MAX	33	//半角で32文字まで(全角で16文字まで)

//########## 構造体 ##########

//キー文字入力構造体
struct INPUTSTR
{
	int StrMax = INPUTSTR_MAX - 1;		//入力文字最大数(-1はヌル文字分)
	BOOL CancelValidFlag = FALSE;		//入力中にESCでキャンセルできるか？ TRUEでキャンセルできる
	BOOL SingleCharOnlyFlag = FALSE;	//半角文字のみの入力させるか？　　　TRUEで半角文字のみ
	BOOL NumCharOnlyFlag = FALSE;		//数値文字のみの入力の入力させるか？TRUEで数値文字のみ
	int handle = -1;					//キー入力ハンドル
	char StrBuf[INPUTSTR_MAX];			//入力した文字列が入る
	BOOL CanInputStr = FALSE;			//現在入力できるか？
	char drawSampleString[INPUTSTR_MAX];	//入力サンプル文字列（入力枠描画用）
};

//########## 外部のグローバル変数 ##########

//キー文字入力関連
extern INPUTSTR inputstr;			//キー文字入力管理
extern FONT sampleInputStrFont;		//入力中のサンプルフォント

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern VOID MY_INPUT_STR_CREATE(VOID);			//キー文字入力ハンドルを作る
extern VOID MY_INPUT_STR_UPDATE(GAME_SCENE old, GAME_SCENE now);		//キー入力の入力情報を更新する
extern VOID MY_INPUT_STR_PROC(VOID);			//キー文字入力を行う
extern VOID MY_INPUT_STR_DRAW(int x, int y, FONT font, unsigned int c);	//キー入力中の文字列を描画する
extern VOID MY_INPUT_STR_DELETE(VOID);			//キー文字入力ハンドルを削除する