/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2021
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//◎ゲームのメインソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "FPS.h"
#include "mouse.h"
#include "keyboard.h"
#include "gamepad.h"
#include "font.h"
#include "InputStr.h"
#include "image.h"
#include "audio.h"

#define PUSH_ENTER "-PUSH  ENTER-"

//########## グローバル変数 ##########

//シーン切り替え時で使用
int fadeTimeMill = 2000;	//行うミリ秒
int fadeTimeMax = (fadeTimeMill / 1000) * GAME_FPS;	//フレーム数に変換

//フェードアウト
int fadeOutCntInit = 0;
int fadeOutCnt = fadeOutCntInit;
int fadeOutCntMAX = fadeTimeMax;

//フェードイン
int fadeInCntInit = fadeTimeMax;
int fadeInCnt = fadeInCntInit;
int fadeInCntMAX = 0;

//スライムに勝ったか？
BOOL IsSlimeWin = FALSE;

//タイトル用点滅カウンタ
int titlePushCnt = 0;
int titlePushCntMAX = 60;
int titlePushPlus = 1;

//########## 関数のプロトタイプ宣言 ##########

VOID MY_TITLE_INIT(VOID);	//ゲームタイトル初期化
VOID DrawPushEnter(VOID);	//PUSH ENTERを描画

//########## ゲーム処理の関数 ##########

//ゲームタイトル初期化
VOID MY_TITLE_INIT(VOID)
{
	fadeOutCntInit = 0;
	fadeOutCnt = fadeOutCntInit;
	fadeOutCntMAX = fadeTimeMax;

	fadeInCntInit = fadeTimeMax;
	fadeInCnt = fadeInCntInit;
	fadeInCntMAX = 0;

	titlePushCnt = 0;
	titlePushCntMAX = 60;
	titlePushPlus = 1;

	IsSlimeWin = FALSE;

	return;
}

//PUSH ENTERを描画
VOID DrawPushEnter(VOID)
{
	//点滅する文字を描画
	if (titlePushCnt >= 0 && titlePushCnt < titlePushCntMAX) { titlePushCnt += titlePushPlus; }
	else { titlePushPlus = -titlePushPlus;  titlePushCnt += titlePushPlus; }	//符号反転

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)titlePushCnt / titlePushCntMAX) * 255);
	int witdh = GetDrawStringWidthToHandle(PUSH_ENTER, strlenDx(PUSH_ENTER), fontTitlePush.handle);
	DrawStringToHandle(GAME_WIDTH / 2 - witdh / 2, GAME_HEIGHT / 4 * 3, PUSH_ENTER, GetColor(255, 255, 255), fontTitlePush.handle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	return;
}

//タイトル画面
VOID MY_TITLE(VOID)
{
	MY_TITLE_PROC();	//タイトル画面の処理
	MY_TITLE_DRAW();	//タイトル画面の描画

	return;
}

//タイトル画面の処理
VOID MY_TITLE_PROC(VOID)
{
	//流すBGMが違うとき
	if (NowPlayBGM.handle != TitleBGM.handle) { NowPlayBGM = TitleBGM; }

	//フェードインしながら再生
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//エンターキーでシーン遷移
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		IsSlimeWin = FALSE;	//スライム勝敗初期化

		GameScene = GAME_SCENE_PLAY;	//プレイ画面へ
		IsFadeIn = FALSE;				//フェードインはしない！
		IsFadeOut = TRUE;				//フェードアウト開始！

		return;
	}

	return;
}

//タイトル画面の描画
VOID MY_TITLE_DRAW(VOID)
{
	//タイトル背景を描画
	DrawImage(titleBackImage);

	//ロゴを描画
	DrawImage(titleLogo);

	//PushEnterを描画
	DrawPushEnter();

	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//流すBGMが違うとき
	if (NowPlayBGM.handle != PlayBGM.handle) { NowPlayBGM = PlayBGM; }

	//フェードインしながら再生
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//エンターキーでシーン遷移
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_END;		//エンド画面へ
		IsFadeIn = FALSE;				//フェードインはしない！
		IsFadeOut = TRUE;				//フェードアウト開始！

		return;
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//プレイ背景を描画（場所は選べる４タイプ！）
	//草　原 ：playkusaImage
	//ﾀﾞﾝｼﾞｮﾝ：playdanjonImage
	//川　岸 ：playkawaImage
	//ボス戦 ：playbossImage
	DrawImage(playkusaImage);

	//スライムを描画
	DrawImage(slimeImage);

	DrawString(0, 0, "プレイ画面", GetColor(255, 255, 255));
	return;
}


//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	if (IsSlimeWin == TRUE)
	{
		//流すBGMが違うとき
		if (NowPlayBGM.handle != EndClearBGM.handle) { NowPlayBGM = EndClearBGM; }
	}
	else
	{
		//流すBGMが違うとき
		if (NowPlayBGM.handle != EndOverBGM.handle) { NowPlayBGM = EndOverBGM; }
	}

	//フェードインしながら再生
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//エンターキーでシーン遷移
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_TITLE;	//タイトル画面へ
		IsFadeIn = FALSE;				//フェードインはしない！
		IsFadeOut = TRUE;				//フェードアウト開始！

		//ゲーム初期化
		MY_TITLE_INIT();

		return;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	if (IsSlimeWin == TRUE)
	{
		//背景を描画
		DrawImage(endClearImage);

		//ロゴを描画
		DrawImage(endClearLogo);
	}
	else
	{
		//背景を描画
		DrawImage(endOverImage);

		//ロゴを描画
		DrawImage(endOverLogo);
	}

	//PushEnterを描画
	DrawPushEnter();

	DrawString(0, 0, "エンド画面", GetColor(255, 255, 255));
	return;
}

//切り替え画面
VOID MY_CHANGE(VOID)
{
	MY_CHANGE_PROC();	//切り替え画面の処理
	MY_CHANGE_DRAW();	//切り替え画面の描画
	return;
}

//切り替え画面の処理
VOID MY_CHANGE_PROC(VOID)
{
	//フェードイン
	if (IsFadeIn == TRUE)
	{
		if (fadeInCnt > fadeInCntMAX)
		{
			fadeInCnt--;

			//フェードインしながら再生（ミリ秒）
			FadeInPlayAudio(&NowPlayBGM, fadeTimeMill);
		}
		else
		{
			fadeInCnt = fadeInCntInit;	//カウンタを初期化

			//フェードアウトさせる
			IsFadeIn = FALSE;
			IsFadeOut = TRUE;
		}
	}

	//フェードアウト
	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt < fadeOutCntMAX) {
			fadeOutCnt++;

			//フェードアウトしながら再生（ミリ秒）
			FadeOutPlayAudio(&NowPlayBGM, fadeTimeMill);

		}
		else
		{
			fadeOutCnt = fadeOutCntInit;	//カウンタを初期化

			IsFadeIn = FALSE;
			IsFadeOut = FALSE;
		}
	}

	//切り替え処理終了
	if (IsFadeIn == FALSE && IsFadeOut == FALSE)
	{
		//フェードアウトが終わったとき
		StopAudio(&NowPlayBGM);					//BGM停止

		GameScene = NextScene;					//ゲームシーンを切り替える
		OldGameScene = GameScene;				//ゲームシーン(直前)も切り替える
	}

	return;
}

//切り替え画面の描画
VOID MY_CHANGE_DRAW(VOID)
{
	//以前の画面を描画
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		MY_TITLE_DRAW();	//タイトル画面
		break;
	case GAME_SCENE_PLAY:
		MY_PLAY_DRAW();		//プレイ画面
		break;
	case GAME_SCENE_END:
		MY_END_DRAW();		//エンド画面
		break;
	}

	//画面をだんだん透明にする(フェードイン)
	if (IsFadeIn == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeTimeMax) * 255); }

	//画面をだんだん透明にする(フェードアウト)
	if (IsFadeOut == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeTimeMax) * 255); }

	//画面を黒い四角でフェードアウト
	if (IsFadeIn == TRUE || IsFadeOut == TRUE) { DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE); }

	//半透明終了
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "切り替え画面", GetColor(255, 255, 255));
	return;
}