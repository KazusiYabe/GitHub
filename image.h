/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//画像のヘッダファイル
//★注意！！フォルダ構造は以下の通りです。フォルダやファイルの準備をしてください
//ルートディレクトリ
// |-IMAGE
//    |-sample.png

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include "game.h"

//########## マクロ定義 ##########

//画像系
#define IMAGE_DRAGON_PATH			TEXT(".\\IMAGE\\dragon.png")	//ドラゴンのパス
#define IMAGE_SLIME_PATH			TEXT(".\\IMAGE\\slime.png")		//スライムのパス

#define IMAGE_TITLE_BACK_PATH		TEXT(".\\IMAGE\\titleBack.png")	//タイトルの背景のパス

#define IMAGE_PLAY_KUSA_BACK_PATH		TEXT(".\\IMAGE\\grass.png")	//プレイ背景のパス
#define IMAGE_PLAY_DANJON_BACK_PATH		TEXT(".\\IMAGE\\maou.png")	//プレイ背景のパス
#define IMAGE_PLAY_KAWA_BACK_PATH		TEXT(".\\IMAGE\\river.png")	//プレイ背景のパス
#define IMAGE_PLAY_BOSS_BACK_PATH		TEXT(".\\IMAGE\\boss.png")	//プレイ背景のパス

#define IMAGE_END_CLEAR_BACK_PATH		TEXT(".\\IMAGE\\clearimage.png")	//エンド背景のパス
#define IMAGE_END_OVER_BACK_PATH		TEXT(".\\IMAGE\\gameover.png")		//エンド背景のパス

#define IMAGE_END_CLEAR_LOGO_PATH		TEXT(".\\IMAGE\\gameclear_logo.png")		//エンドロゴ
#define IMAGE_END_OVER_LOGO_PATH		TEXT(".\\IMAGE\\gameover_logo.png")			//エンドロゴ

#define IMAGE_TITLE_LOGO_PATH			TEXT(".\\IMAGE\\titleLogo.png")				//タイトルのロゴ

#define IMAGE_WAKU_PATH					TEXT(".\\IMAGE\\waku.png")					//モンスターの枠
#define IMAGE_MESSAGE_PATH				TEXT(".\\IMAGE\\message.png")				//メッセージ枠

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//分割画像系
#define IMAGE_DIV_CHARA_MAX			(4*3)		//ハンドルの最大数(キャラなど、4方向＋3アニメ)
#define IMAGE_DIV_CHARA2_MAX		(8*3)		//ハンドルの最大数(キャラなど、8方向＋3アニメ)
#define IMAGE_DIV_MAP_MAX			(32*32)		//ハンドルの最大数(マップなど、32×32)

#define IMAGE_DIV_MAX				256			//ハンドルの最大数(任意)

#define EFFECT_MAX	12

#define IMAGE_WAZA0_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\hikkaku.png")	
#define IMAGE_WAZA1_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\slash.png")
#define IMAGE_WAZA2_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\kamituku.png")	
#define IMAGE_WAZA3_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\slash2.png")	

#define IMAGE_WAZA4_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\ice.png")	
#define IMAGE_WAZA5_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\raigeki.png")	
#define IMAGE_WAZA6_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\kaenbeam.png")
#define IMAGE_WAZA7_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\ken.png")	

#define IMAGE_WAZA8_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\pipo-btleffect043.png")
#define IMAGE_WAZA9_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\pipo-btleffect044.png")	
#define IMAGE_WAZA10_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\pipo-btleffect045.png")
#define IMAGE_WAZA11_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\kaihuku.png")	

//########## 構造体 ##########

//位置と当たり判定
struct POSTION
{
	int x = -1;				//X位置
	int y = -1;				//Y位置
	int width = -1;			//幅
	int height = -1;		//高さ

	RECT coll;				//当たり判定
	RECT margin;			//当たり判定(余白)
};

//画像構造体
struct IMAGE
{
	int handle = -1;		//画像ハンドル
	char path[PATH_MAX];	//パス

	POSTION pos;			//位置と幅高さ、当たり判定

	BOOL IsDraw = FALSE;	//描画できるか？
	BOOL IsCenter = FALSE;	//XY位置を中心に描画するか？	
};

//連続する画像の構造体
struct DIVIMAGE
{
	int DivMax = IMAGE_DIV_MAX;		//分割数
	int handle[IMAGE_DIV_MAX];		//画像ハンドル
	int nowIndex = 0;				//現在のハンドル配列のインデックス
	char path[PATH_MAX];			//パス

	POSTION pos;					//位置と幅高さ、当たり判定

	BOOL IsDraw = FALSE;			//描画できるか？
	BOOL IsCenter = FALSE;			//XY位置を中心に描画するか？

	int AnimCnt = 0;				//アニメーションカウンタ
	int AnimCntMAX = 4;				//アニメーションカウンタMAX
	BOOL IsAnimLoop = FALSE;		//アニメーションをループさせるか？
};

//########## 外部のグローバル変数 ##########

//画像関連
extern IMAGE dragonImage;			//ドラゴン画像
extern IMAGE slimeImage;			//スライムの画像
extern IMAGE tekiImage;				//敵の画像

extern IMAGE titleBackImage;	//タイトル背景画像

extern IMAGE playkusaImage;		//プレイ背景画像(草原)
extern IMAGE playdanjonImage;	//プレイ背景画像(ダンジョン)
extern IMAGE playkawaImage;		//プレイ背景画像(川岸)
extern IMAGE playbossImage;		//プレイ背景画像(ボス)

extern IMAGE endClearImage;		//エンド背景画像(クリア)
extern IMAGE endOverImage;		//エンド背景画像(オーバー)

extern IMAGE endClearLogo;		//エンドロゴ画像(クリア)
extern IMAGE endOverLogo;		//エンドロゴ画像(オーバー)

extern IMAGE titleLogo;			//タイトルロゴ画像
extern IMAGE wakuImage;			//モンスター枠画像
extern IMAGE messageImage;			//メッセージ枠画像

extern DIVIMAGE effectImage[EFFECT_MAX];	//エフェクト分割画像

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern BOOL MY_IMAGE_LOAD(VOID);		//画像をまとめて読込
extern BOOL MY_IMAGE_LOAD_FILE(IMAGE* image, const char* path, int x, int y, BOOL IsCenter, RECT margin);	//画像を１つ読み込み

extern BOOL MY_IMAGE_LOAD_DIV_FILE(
	DIVIMAGE* image, const char* path,
	int retu, int gyo, int width, int height,
	int x, int y, BOOL IsCenter, RECT margin);	//画像を分割して読み込み

extern VOID ImageCollUpdate(POSTION* pos);	//画像の当たり判定の位置を更新する
extern VOID DrawImage(IMAGE image);			//画像描画
extern VOID DrawDivImage(DIVIMAGE* image);	//分割画像描画
extern VOID MY_IMAGE_DELETE(VOID);			//画像をまとめて削除