//ヘッダーファイルの読み込み
#include "DxLib.h"  //DxLibを使う時は必要

//マクロ定義
#define GAME_TITLE "ゲームタイトル"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_COLOR 32

#define GAME_ICON_ID  333
// プログラムは は から始まります
//Windowsのプログラム方法 = (WinAPI)で動いている
//DxLibは、Directx という、ゲームプログラムを簡単に使える仕組み
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText(GAME_TITLE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	SetBackgroundColor(255, 255, 255);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

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
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}