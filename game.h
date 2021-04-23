/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//ゲームのメインヘッダファイル

#pragma once

//########## ヘッダーファイル読み込み ##########
//エラー抑制
#define _CRT_SECURE_NO_WARNINGS

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "math.h"
#include "time.h"

//########## マクロ定義 ##########
#define PATH_MAX			255		//パスの長さ
#define STR_MAX				255		//文字の長さ
#define DEBUG_MODE			FALSE	//デバッグモード

#define GAME_WINDOW_MODE	TRUE	//ウィンドウモード
#define GAME_WIDTH			1280	//ゲームの幅	（16）
#define GAME_HEIGHT			720		//ゲームの高さ	（ 9）
#define WINDOW_WIDTH		GAME_WIDTH		//ウィンドウの幅
#define WINDOW_HEIGHT		GAME_HEIGHT		//ウィンドウの高さ
#define GAME_COLOR			32		//ゲームの色ビット
#define GAME_WINDOWBAR_KIND 0		//ウィンドウバーの種類
#define GAME_WINDOW_NAME	"HAMAMI-SlimeQuest-"	//ウィンドウのタイトル
#define GAME_ICON_ID		333		//ウィンドウアイコンのID

#define WAZA_EFFECT_MAX	15		//技のエフェクトの数

//########## 列挙型 ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};	//ゲームのシーン

//########## 外部のグローバル変数 ##########
//ゲーム関連
extern GAME_SCENE OldGameScene;			//ゲームのシーンを管理(以前)
extern GAME_SCENE GameScene;			//ゲームのシーンを管理
extern GAME_SCENE NextScene;			//切り替えるシーンを管理

//画面切り替え
extern BOOL IsFadeOut;	//フェードアウト
extern BOOL IsFadeIn;	//フェードイン

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern VOID MY_TITLE_INIT(VOID);	//ゲームタイトル初期化

extern VOID MY_TITLE(VOID);				//タイトル画面
extern VOID MY_TITLE_PROC(VOID);		//タイトル画面の処理
extern VOID MY_TITLE_DRAW(VOID);		//タイトル画面の描画

extern VOID MY_PLAY(VOID);				//プレイ画面
extern VOID MY_PLAY_PROC(VOID);			//プレイ画面の処理
extern VOID MY_PLAY_DRAW(VOID);			//プレイ画面の描画

extern VOID MY_END(VOID);				//エンド画面
extern VOID MY_END_PROC(VOID);			//エンド画面の処理
extern VOID MY_END_DRAW(VOID);			//エンド画面の描画

extern VOID MY_CHANGE(VOID);			//切り替え画面
extern VOID MY_CHANGE_PROC(VOID);		//切り替え画面の処理
extern VOID MY_CHANGE_DRAW(VOID);		//切り替え画面の描画

extern int GetRangeRand(int min, int max);	//任意の範囲で乱数を取得する
extern float DegToRad(int deg);				//度数法から弧度法に変換
extern int RadToDeg(float rad);				//弧度法から度数法に変換