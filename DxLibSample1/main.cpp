//ヘッダーファイルの読み込み
#include "DxLib.h"  //DxLibを使う時は必要

#include "keyboard.h"
//マクロ定義
#define GAME_TITLE "ゲームタイトル"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_COLOR 32

#define GAME_ICON_ID  333

#define GAME_WINDOW_BAR 0
// プログラムは は から始まります
//Windowsのプログラム方法 = (WinAPI)で動いている
//DxLibは、Directx という、ゲームプログラムを簡単に使える仕組み
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);   //Log.txtを出力しない
	ChangeWindowMode(TRUE);
	SetMainWindowText(GAME_TITLE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	SetBackgroundColor(255, 255, 255);
	SetWindowIconID(GAME_ICON_ID);
	SetWindowStyleMode(GAME_WINDOW_BAR);     //ウィンドウバーの状態
	SetWaitVSyncFlag(TRUE);                  //ディスプレイの垂直同期を有効にする
	SetAlwaysRunFlag(TRUE);

	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	
	SetDrawScreen(DX_SCREEN_BACK);

	//無限ループ
	while (1)
	{
		//メッセージを受け取り続ける
		if (ProcessMessage() != 0){break;  //無限ループを抜ける}
		if (ClearDrawScreen() != 0) { break; }  //画面を消去する

		//キーボード入力の更新
		AllKeyUpdate();
		
		//キー入力
		if (KeyDown(KEY_INPUT_UP) == TRUE)
		{
			Y--;  //上に移動
		}
		if (KeyDown(KEY_INPUT_DOWN) == TRUE)
		{
			Y++;  //下に移動
		}
		if (KeyDown(KEY_INPUT_LEFT) == TRUE)
		{
			X--;  //左に移動
		}
		if (KeyDown(KEY_INPUT_RIGHT) == TRUE)
		{
			X++;  //右に移動
		}

		DrawCircle(X, Y, radius, GetColor(255, 255, 0), TRUE);

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}