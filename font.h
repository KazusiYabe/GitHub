/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//フォント処理のヘッダファイル
//★注意！！フォルダ構造は以下の通りです。フォルダやファイルの準備をしてください
//ルートディレクトリ
// |-FONT
//    |-TanukiMagic.ttf
//    |-Jiyucho.ttf

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include "game.h"

//########## マクロ定義 ##########

//フォント系
#define FONT_TANUKI_PATH		TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANUKI_NAME		TEXT("たぬき油性マジック")			//フォントの名前

#define FONT_JIYU_PATH			TEXT(".\\FONT\\Jiyucho.ttf")		//フォントの場所
#define FONT_JIYU_NAME			TEXT("じゆうちょうフォント")		//フォントの名前

#define DEF_FONT_NAME	FONT_JIYU_NAME				//デフォルトのフォント名
#define DEF_FONT_SIZE	20							//デフォルトのサイズ
#define DEF_FONT_THINCK	1							//デフォルトの太さ
#define DEF_FONT_TYPE	 DX_FONTTYPE_ANTIALIASING	//デフォルトのタイプ

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//########## 構造体 ##########

//フォント構造体
struct FONT
{
	int handle;		//フォントハンドル
	int Size;		//フォントのサイズ
	int Thinck;		//フォントの太さ
	int Type = DX_FONTTYPE_ANTIALIASING;	//フォントのタイプ
	char Name[STR_MAX] = FONT_TANUKI_NAME;	//フォントの名前
};

//########## 外部のグローバル変数 ##########

//フォント関連
extern FONT fontdef;		//デフォルトのフォント
extern FONT fontSample;		//サンプルのフォント

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern BOOL MY_FONT_LOAD(VOID);		//フォントの読込
extern VOID MY_FONT_SET(FONT* f, const char* name, int size, int thinck, int type);	//フォントに設定する
extern VOID MY_FONT_DRAWSET(FONT f);	//フォントを全体に反映させる
extern VOID MY_FONT_DELETE(VOID);		//フォントの削除