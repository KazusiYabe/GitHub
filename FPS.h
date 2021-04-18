/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//FPS処理のヘッダファイル

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include"game.h"

//########## マクロ定義 ##########
#define GAME_FPS			60		//FPSの数値	
#define GAME_VSYNC_OFF		TRUE	//垂直同期しない：TRUE / する：FALSE

//########## 構造体 ##########

//FPS構造体
struct FPS
{
	BOOL IsInitFlg = FALSE;			//最初の測定開始時刻を取得するフラグ
	LONGLONG StartTime = 0;			//測定開始時刻
	LONGLONG NowTime = 0;			//現在の時刻
	LONGLONG OldTime = 0;			//以前の時刻
	float DeltaTime = 0.000001f;	//経過時間
	int Count = 1;					//カウンタ(1～GAME_FPS)
	float DrawValue = 0.0f;			//計算結果
	int SampleRate = GAME_FPS;		//平均を取るサンプル数
};

//########## 外部のグローバル変数 ##########

//FPS関連
extern FPS fps;	//FPSをデータを管理

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern VOID MY_FPS_UPDATE(VOID);		//FPS値を計測、更新する
extern VOID MY_FPS_DRAW(VOID);			//FPS値を描画する
extern VOID MY_FPS_WAIT(VOID);			//FPS値を計測し、待つ