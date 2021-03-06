/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//フォント処理のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "font.h"

//########## グローバル変数 ##########

//フォントデータを管理
FONT fontdef;			//デフォルトのフォント
FONT fontTitlePush;		//タイトルのフォント
FONT fontMonster;		//モンスターのフォント
FONT fontPlayer;		//プレイヤーの名前のフォント
FONT fontCommand;		//コマンドのフォント

//########## 関数 ##########

/// <summary>
/// フォントの読込
/// </summary>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_FONT_LOAD(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_TANUKI_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_TANUKI_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_JIYU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//デフォルトフォントの情報を初期化
	MY_FONT_SET(
		&fontdef,			//設定するフォント
		DEF_FONT_NAME,		//フォントの名前をコピー
		DEF_FONT_SIZE,		//フォントのサイズ
		DEF_FONT_THINCK,	//フォントの太さ
		DEF_FONT_TYPE		//フォントのタイプ
	);

	//デフォルトフォントを全体に反映
	MY_FONT_DRAWSET(fontdef);

	//デフォルトフォントのハンドル作成
	fontdef.handle = CreateFontToHandle(
		fontdef.Name,	//フォント名を設定
		fontdef.Size, 	//フォントのサイズを設定
		fontdef.Thinck, //フォントの太さを設定
		fontdef.Type	//フォントのタイプを設定
	);

	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_DELTA_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_DELTA_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//フォントを作成
	MY_FONT_SET(&fontTitlePush, FONT_DELTA_NAME, 80, 1, DEF_FONT_TYPE);
	fontTitlePush.handle = CreateFontToHandle(
		fontTitlePush.Name,		//フォント名を設定
		fontTitlePush.Size, 	//フォントのサイズを設定
		fontTitlePush.Thinck,	//フォントの太さを設定
		fontTitlePush.Type		//フォントのタイプを設定
	);

	//フォントを作成
	MY_FONT_SET(&fontMonster, FONT_DELTA_NAME, 50, 1, DEF_FONT_TYPE);
	fontMonster.handle = CreateFontToHandle(
		fontMonster.Name,		//フォント名を設定
		fontMonster.Size, 	//フォントのサイズを設定
		fontMonster.Thinck,	//フォントの太さを設定
		fontMonster.Type		//フォントのタイプを設定
	);

	//フォントを作成
	MY_FONT_SET(&fontPlayer, FONT_TANUKI_NAME, 25, 1, DEF_FONT_TYPE);
	fontPlayer.handle = CreateFontToHandle(
		fontPlayer.Name,		//フォント名を設定
		fontPlayer.Size, 	//フォントのサイズを設定
		fontPlayer.Thinck,	//フォントの太さを設定
		fontPlayer.Type		//フォントのタイプを設定
	);

	//フォントを作成
	MY_FONT_SET(&fontCommand, FONT_DELTA_NAME, 35, 1, DEF_FONT_TYPE);
	fontCommand.handle = CreateFontToHandle(
		fontCommand.Name,		//フォント名を設定
		fontCommand.Size, 	//フォントのサイズを設定
		fontCommand.Thinck,	//フォントの太さを設定
		fontCommand.Type		//フォントのタイプを設定
	);

	return TRUE;
}

/// <summary>
/// 引数のフォント構造体へ設定する
/// </summary>
/// <param name="f">設定するフォント構造体</param>
/// <param name="name">フォント名</param>
/// <param name="size">フォントのサイズ</param>
/// <param name="thinck">フォントの太さ</param>
/// <param name="type">フォントのタイプ</param>
/// <returns></returns>
VOID MY_FONT_SET(FONT* f, const char* name, int size, int thinck, int type)
{
	strcpy_sDx(f->Name, STR_MAX, name);	//フォントの名前をコピー
	f->Size = size;						//フォントのサイズ
	f->Thinck = thinck;					//フォントの太さ
	f->Type = type;						//フォントのタイプ
	return;
}

/// <summary>
/// フォントを画面全体に反映させる
/// </summary>
/// <param name="f">設定するフォント構造体</param>
/// <returns></returns>
VOID MY_FONT_DRAWSET(FONT f)
{
	ChangeFont(f.Name);				//フォント名を設定
	SetFontSize(f.Size);			//フォントのサイズを設定
	SetFontThickness(f.Thinck);		//フォントの太さを設定
	ChangeFontType(f.Type);			//フォントのタイプを設定

	return;
}

/// <summary>
/// フォントの削除
/// </summary>
/// <returns></returns>
VOID MY_FONT_DELETE(VOID)
{
	//デフォルトフォント削除
	DeleteFontToHandle(fontdef.handle);
	DeleteFontToHandle(fontTitlePush.handle);
	DeleteFontToHandle(fontPlayer.handle);
	DeleteFontToHandle(fontCommand.handle);

	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_TANUKI_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_DELTA_NAME, FR_PRIVATE, NULL);

	return;
}