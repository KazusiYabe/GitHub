/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//キー文字入力処理のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "font.h"
#include "InputStr.h"

//########## グローバル変数 ##########

//キー文字入力のデータを管理
INPUTSTR inputstr;

//入力中のサンプルフォント
FONT sampleInputStrFont;

//########## 関数 ##########

/// <summary>
/// キー入力ハンドルを作る
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_CREATE(VOID)
{
	//キー入力中でなければ
	if (inputstr.CanInputStr == FALSE)
	{
		// キー入力ハンドルを作る
		inputstr.handle = MakeKeyInput(
			inputstr.StrMax,				//入力最大文字列？
			inputstr.CancelValidFlag,		//ESCでキャンセルできるようにする？
			inputstr.SingleCharOnlyFlag,	//半角入力のみOKにする？
			inputstr.NumCharOnlyFlag		//数字入力のみOKにする？
		);

		//入力バッファ初期化
		for (int i = 0; i < INPUTSTR_MAX; i++) { inputstr.StrBuf[i] = '\0'; }

		//描画用サンプル文字列生成
		for (int i = 0; i < INPUTSTR_MAX - 1; i++) { strcat(&inputstr.drawSampleString[i], "a"); }
		inputstr.drawSampleString[INPUTSTR_MAX - 1] = '\0';

		//作成したキー入力ハンドルを有効にする(キー入力開始)
		SetActiveKeyInput(inputstr.handle);

		//キー文字入力開始
		inputstr.CanInputStr = TRUE;

		//サンプルのフォントを作成する
		MY_FONT_SET(&sampleInputStrFont, "ＭＳ ゴシック", 30, 1, DX_FONTTYPE_ANTIALIASING);
		sampleInputStrFont.handle = CreateFontToHandle(sampleInputStrFont.Name, sampleInputStrFont.Size, sampleInputStrFont.Thinck, sampleInputStrFont.Type);
	}

	return;
}

/// <summary>
/// キー入力の入力情報を更新する
/// </summary>
/// <param name="old">以前のゲームシーン</param>
/// <param name="now">現在のゲームシーン</param>
/// <returns></returns>
VOID MY_INPUT_STR_UPDATE(GAME_SCENE old, GAME_SCENE now)
{
	//シーンを切り替えるとき
	if (old != now)
	{
		//キー文字入力ハンドル強制削除
		MY_INPUT_STR_DELETE();
	}

	return;
}

/// <summary>
/// キー入力を行う
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_PROC(VOID)
{
	//キー入力中であれば
	if (inputstr.CanInputStr == TRUE)
	{
		//入力が完了したら
		if (CheckKeyInput(inputstr.handle) > 0)
		{
			//入力された文字列を取得する
			GetKeyInputString(inputstr.StrBuf, inputstr.handle);

			//キー入力ハンドル削除
			MY_INPUT_STR_DELETE();

			//入力できなくする
			inputstr.CanInputStr = FALSE;
		}
	}

	return;
}

/// <summary>
/// キー入力中の文字列を描画する
/// </summary>
/// <param name="x">文字列を描画するX開始位置</param>
/// <param name="y">文字列を描画するY開始位置</param>
/// <param name="font">描画するフォント</param>
/// <param name="c">描画する文字色</param>
/// <returns></returns>
VOID MY_INPUT_STR_DRAW(int x, int y, FONT font, unsigned int c)
{
	//キー文字入力ができるとき
	if (inputstr.CanInputStr == TRUE)
	{
		//入力の枠線を描画する
		int fontWidth = GetDrawStringWidthToHandle(inputstr.drawSampleString, strlen(inputstr.drawSampleString), font.handle);	//幅を取得
		int fontHeight = GetFontSizeToHandle(font.handle);							//高さを取得
		DrawBox(x - 1, y - 1, x + fontWidth + 1, y + fontHeight + 1, GetColor(255, 255, 255), FALSE);

		//入力文字列を描画する
		FONT oldFont;	//以前のフォント

		//デフォルトフォントの情報を取得
		GetFontStateToHandle(oldFont.Name, &oldFont.Size, &oldFont.Thinck, GetDefaultFontHandle(), &oldFont.Type);

		//描画するフォントをセットする
		MY_FONT_DRAWSET(font);

		//入力中の文字列の色を変える
		SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, c);

		//入力中の文字を描画
		DrawKeyInputString(x, y, inputstr.handle);

		//描画する以前のフォントをセットする
		MY_FONT_DRAWSET(oldFont);
	}

	return;
}

/// <summary>
/// キー入力ハンドルを削除する
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_DELETE(VOID)
{
	//キー入力ハンドルを削除する
	DeleteKeyInput(inputstr.handle);

	//入力できなくする
	inputstr.CanInputStr = FALSE;

	//サンプルのフォントを削除する
	DeleteFontToHandle(sampleInputStrFont.handle);

	return;
}
