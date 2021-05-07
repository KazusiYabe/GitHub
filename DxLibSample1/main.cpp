//ヘッダーファイルの読み込み
#include "DxLib.h"  //DxLibを使う時は必要

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
	//四角の位置を決める
	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;

	//四角の大きさを決める
	int width = 32;
	int height = 32;

	int radius = 100;

	int Speed = 5;
	int XSpeed = Speed;
	int YSpeed = Speed;
	SetDrawScreen(DX_SCREEN_BACK);

	//無限ループ
	while (1)
	{
		if (CheckHitKeyAll() != 0)
		{
			break;  //無限ループを抜ける
		}

		//メッセージを受け取り続ける
		if (ProcessMessage() != 0)
		{
			break;  //無限ループを抜ける
		}


		//画面を消去する
		if (ClearDrawScreen() != 0) { break; }


		//四角を描画
		//DrawBox(
		//	X, Y, X + width, Y + height,
		//	GetColor(255, 0, 0),   //色を取得
		//	TRUE                   //塗りつぶし?
		//);


		//円を描画
		DrawCircle(
			X, Y,  radius,
			GetColor(0, 255, 0),
			FALSE, 5
		);

		X += XSpeed;

		Y += YSpeed;

		if (X - radius < 0 || X+ width > GAME_WIDTH)
		{
			XSpeed = -XSpeed;//移動する向きを反転

			if (XSpeed > 0) {XSpeed += 2; }
			else if (XSpeed < 0) { XSpeed -= 2; }
		}
		ScreenFlip();
	}

	if (Y - radius < 0 || Y + height > GAME_HEIGHT)
	
	{
		YSpeed = -YSpeed;//移動する向きを反転

		if (YSpeed > 0) { YSpeed += 2; }
		else if (YSpeed < 0) { YSpeed -= 2; }
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}