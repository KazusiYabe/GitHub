/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2021
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//########## ドキュメントコメントの書き方 ##########
/*
* 何これ？→インテリセンスにドキュメントコメントを表示させることができる
* (ホントはC#でよく使うんだけどね...)
* (技術的には、XMLという書き方を使用しています)(HTMLと似てるかも？)
* やり方→///をつけると、Visual Studioが自動補完してくれる
* 　　　　特に、関数名を書いてから、関数名の上に///を書くと、とても楽。
*
* タグ		説明
* <summary>	メソッドの説明を記述する
* <param>	引数の説明を記述する
* <returns>	戻り値の説明を記述する
*
*/

//◎メインソースファイル
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

//ゲーム関連
GAME_SCENE OldGameScene;		//ゲームのシーンを管理(以前)
GAME_SCENE GameScene;			//ゲームのシーンを管理
GAME_SCENE NextScene;			//切り替えるシーンを管理

//画面切り替え
BOOL IsFadeOut = FALSE;	//フェードアウト
BOOL IsFadeIn = FALSE;	//フェードイン

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txtを出力しない
	ChangeWindowMode(GAME_WINDOW_MODE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//ウィンドウの解像度を設定
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			//ウィンドウの大きさを設定
	SetWindowIconID(GAME_ICON_ID);						//アイコンファイルを読込
	SetMainWindowText(GAME_WINDOW_NAME);				//ウィンドウのタイトルの文字
	SetWindowStyleMode(GAME_WINDOWBAR_KIND);			//タイトルバーの種類はデフォルトにする
	SetBackgroundColor(0, 0, 0);						//デフォルトの背景の色
	SetWaitVSyncFlag(GAME_VSYNC_OFF);					//垂直同期の設定
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する

	//ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) { return -1; }

	//Draw系関数は裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	//パッドの入力を初期化
	MY_PAD_INIT();

	//フォントの読込
	if (MY_FONT_LOAD() == FALSE) { return -1; DxLib_End(); }

	//画像の読み込み
	if (MY_IMAGE_LOAD() == FALSE) { return -1; DxLib_End(); }

	//音楽の読み込み
	if (MY_AUDIO_LOAD() == FALSE) { return -1; DxLib_End(); }

	//ゲームの初期化
	GameScene = GAME_SCENE_TITLE;	//ゲームシーンはタイトル画面から

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		//押しているキー状態を取得
		MY_ALL_KEYDOWN_UPDATE();

		//マウスの状態を取得
		MY_MOUSE_UPDATE();

		//パッドの入力情報を更新する
		MY_PAD_UPDATE();

		//FPSの更新処理
		MY_FPS_UPDATE();

		//以前のシーンを取得
		if (GameScene != GAME_SCENE_CHANGE)	//シーン切り替え以外なら
		{
			OldGameScene = GameScene;
		}

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			MY_TITLE();		//タイトル画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();		//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();		//エンド画面
			break;
		case GAME_SCENE_CHANGE:
			MY_CHANGE();	//切り替え画面
			break;
		}

		//シーン切り替え
		if (OldGameScene != GameScene)
		{
			if (GameScene != GAME_SCENE_CHANGE)	//シーン切り替え以外なら
			{
				NextScene = GameScene;			//次のシーンを保存
				GameScene = GAME_SCENE_CHANGE;	//画面切り替えに遷移
			}
		}

		//キー入力の更新処理
		MY_INPUT_STR_UPDATE(OldGameScene, GameScene);

		//現在のマウスの情報を描画
		MY_MOUSE_DRAW();

		//現在のパッドの情報を描画する
		MY_PAD_DRAW();

		//現在のFPS値を描画
		MY_FPS_DRAW();

		//裏画面を再描画
		ScreenFlip();

		//FPSが早すぎるときは、処理を待つ
		MY_FPS_WAIT();
	}

	MY_IMAGE_DELETE();	//画像の削除
	MY_AUDIO_DELETE();	//音楽の削除
	MY_FONT_DELETE();	//フォントの削除

	//ＤＸライブラリ使用の終了処理
	DxLib_End();

	return 0;
}

//########## 共通で利用する関数 ##########

//任意の範囲で乱数を取得する
int GetRangeRand(int min, int max)
{
	//乱数の種を作成
	static BOOL IsSeed = FALSE;	//static:関数の処理が終了しても値を保持
	if (IsSeed == FALSE) { srand((unsigned int)time(NULL)); IsSeed = TRUE; }	//乱数の種を生成

	//生成したい数値の幅 = 生成したい上限値 - 生成したい下限値
	//rand() % ( 生成したい数値の幅 + 1 ) + 生成したい下限値
	return rand() % (max - min + 1) + min;
}

//度数法から弧度法に変換
float DegToRad(int deg)
{
	//角度 * 円周率 / 180
	return deg * DX_PI / 180;
}

//弧度法から度数法に変換
int RadToDeg(float rad)
{
	//ラジアン * 180 / 円周率
	return rad * 180.0f / DX_PI;
}
