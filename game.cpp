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

//########## グローバル変数 ##########

//シーン切り替え時で使用
int fadeTimeMill = 500;	//行うミリ秒

//フェードアウト
int fadeOutCntInit = (fadeTimeMill / fadeTimeMill) * GAME_FPS;	//フレーム数に変換
int fadeOutCnt = fadeOutCntInit;
int fadeOutCntMAX = 0;

//フェードイン
int fadeInCntInit = 0;
int fadeInCnt = fadeInCntInit;
int fadeInCntMAX = (fadeTimeMill / fadeTimeMill) * GAME_FPS;	//フレーム数に変換

//########## ゲーム処理の関数 ##########

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
	//流すBGMが違うとき
	if (NowPlayBGM.handle != EndClearBGM.handle) { NowPlayBGM = EndClearBGM; }

	//フェードインしながら再生
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//エンターキーでシーン遷移
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_TITLE;	//タイトル画面へ
		IsFadeIn = FALSE;				//フェードインはしない！
		IsFadeOut = TRUE;				//フェードアウト開始！

		return;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{

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
		if (fadeInCnt < fadeInCntMAX)
		{
			fadeInCnt++; //カウントアップ

			//フェードインしながら再生（ミリ秒）
			FadeInPlayAudio(&NowPlayBGM, fadeTimeMill);
		}
		else
		{
			//フェードインが終わったとき
			StopAudio(&NowPlayBGM);		//BGM停止
			fadeInCnt = fadeInCntInit;	//カウンタを初期化

			//フェードアウトさせる
			IsFadeIn = FALSE;
			IsFadeOut = TRUE;
		}
	}

	//フェードアウト
	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt > fadeOutCntMAX) {
			fadeOutCnt--;	//カウントダウン

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
		StopAudio(&TitleBGM);					//BGM停止

		GameScene = NextScene;					//ゲームシーンを切り替える
		OldGameScene = GameScene;				//ゲームシーン(直前)も切り替える
	}

	return;
}

//切り替え画面の描画
VOID MY_CHANGE_DRAW(VOID)
{
	//画面をだんだん透明にする(フェードイン)
	if (IsFadeIn == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeInCntMAX) * 255); }

	//画面をだんだん透明にする(フェードアウト)
	if (IsFadeOut == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeInCntMAX) * 255); }

	//画面を黒い四角でフェードアウト
	if (IsFadeIn == TRUE || IsFadeOut == TRUE) { DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 255, 255), TRUE); }

	//半透明終了
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

	DrawString(0, 0, "切り替え画面", GetColor(255, 255, 255));
	return;
}