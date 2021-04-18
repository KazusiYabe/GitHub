/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//ゲームパッド処理のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "FPS.h"
#include "gamepad.h"

//########## グローバル変数 ##########

//ゲームパッドのデータを管理
int padConnectNum = 0;			//パッドの接続数
GAMEPAD gamepad[PAD_MAX];		//GAMEPADデータを管理

//デバッグ用
DEBUG_GAMEPAD debug[PAD_MAX];	//ゲームパッドの動作デバッグ用

//########## 関数 ##########

/// <summary>
/// パッドの情報を初期化する
/// </summary>
/// <returns></returns>
VOID MY_PAD_INIT(VOID)
{
	//パッドの接続数を取得
	padConnectNum = GetJoypadNum();

	//パッド数は最大４まで（５以上は処理しない）
	if (DX_INPUT_PAD4 < padConnectNum) { padConnectNum = DX_INPUT_PAD4; }

	//パッドの数に応じて処理を行う
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		//振動して接続テスト(振動付きでないパッドは、当然振動しない・・・)
		//StartJoypadVibration(cnt, PAD_TEST_POWER, PAD_TEST_MSEC);

		//パッドのアナログスティックの無効範囲を設定する
		SetJoypadDeadZone(cnt, PAD_DEADZONE);

		//入力情報を初期化
		gamepad[cnt].InputState = -1;
		gamepad[cnt].NewAnalogX = 0;
		gamepad[cnt].NewAnalogY = 0;
		gamepad[cnt].OldAnalogX = 0;
		gamepad[cnt].OldAnalogY = 0;

		//ボタン情報を初期化
		for (int i = PADBTN_DOWN; i <= PADBTN_12; i++)
		{
			gamepad[cnt].AllButtonState[i] = 0;
			gamepad[cnt].OldButtonKeyState[i] = 0;
		}
	}

	if (DEBUG_MODE == TRUE)	//デバッグモードなら
	{
		//デバッグのときの円の色を設定する
		debug[DX_INPUT_PAD1].Color = GetColor(255, 0, 0);
		debug[DX_INPUT_PAD2].Color = GetColor(0, 255, 0);
		debug[DX_INPUT_PAD3].Color = GetColor(0, 0, 255);
		debug[DX_INPUT_PAD4].Color = GetColor(255, 255, 0);
	}

	return;
}

/// <summary>
/// パッドの入力情報を更新する
/// </summary>
/// <returns></returns>
VOID MY_PAD_UPDATE(VOID)
{
	//パッドの数に応じて処理を行う
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		//前回のアナログレバーの傾き具合を保存
		gamepad[cnt].OldAnalogX = gamepad[cnt].NewAnalogX;
		gamepad[cnt].OldAnalogY = gamepad[cnt].NewAnalogY;

		//前回のボタン入力を保存
		for (int i = PADBTN_DOWN; i <= PADBTN_12; i++)
		{
			gamepad[cnt].OldButtonKeyState[i] = gamepad[cnt].AllButtonState[i];
		}

		//アナログレバーの傾き具合を取得
		GetJoypadAnalogInput(&(gamepad[cnt].NewAnalogX), &(gamepad[cnt].NewAnalogY), cnt);

		//パッドの状態を入力
		gamepad[cnt].InputState = GetJoypadInputState(cnt);

		//下ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_DOWN) == PAD_INPUT_DOWN) { gamepad[cnt].AllButtonState[PADBTN_DOWN]++; }		//押している
		if ((gamepad[cnt].InputState & MOUSE_INPUT_LEFT) != PAD_INPUT_DOWN) { gamepad[cnt].AllButtonState[PADBTN_DOWN] = 0; }	//押していない

		//左ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_LEFT) == PAD_INPUT_LEFT) { gamepad[cnt].AllButtonState[PADBTN_LEFT]++; }		//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_LEFT) != PAD_INPUT_LEFT) { gamepad[cnt].AllButtonState[PADBTN_LEFT] = 0; }	//押していない

		//右ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_RIGHT) == PAD_INPUT_RIGHT) { gamepad[cnt].AllButtonState[PADBTN_RIGHT]++; }	//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_RIGHT) != PAD_INPUT_RIGHT) { gamepad[cnt].AllButtonState[PADBTN_RIGHT] = 0; }	//押していない

		//上ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_UP) == PAD_INPUT_UP) { gamepad[cnt].AllButtonState[PADBTN_UP]++; }			//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_UP) != PAD_INPUT_UP) { gamepad[cnt].AllButtonState[PADBTN_UP] = 0; }			//押していない

		//1ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_1) == PAD_INPUT_1) { gamepad[cnt].AllButtonState[PADBTN_1]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_1) != PAD_INPUT_1) { gamepad[cnt].AllButtonState[PADBTN_1] = 0; }				//押していない

		//2ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_2) == PAD_INPUT_2) { gamepad[cnt].AllButtonState[PADBTN_2]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_2) != PAD_INPUT_2) { gamepad[cnt].AllButtonState[PADBTN_2] = 0; }				//押していない

		//3ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_3) == PAD_INPUT_3) { gamepad[cnt].AllButtonState[PADBTN_3]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_3) != PAD_INPUT_3) { gamepad[cnt].AllButtonState[PADBTN_3] = 0; }				//押していない

		//4ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_4) == PAD_INPUT_4) { gamepad[cnt].AllButtonState[PADBTN_4]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_4) != PAD_INPUT_4) { gamepad[cnt].AllButtonState[PADBTN_4] = 0; }				//押していない

		//5ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_5) == PAD_INPUT_5) { gamepad[cnt].AllButtonState[PADBTN_5]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_5) != PAD_INPUT_5) { gamepad[cnt].AllButtonState[PADBTN_5] = 0; }				//押していない

		//6ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_6) == PAD_INPUT_6) { gamepad[cnt].AllButtonState[PADBTN_6]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_6) != PAD_INPUT_6) { gamepad[cnt].AllButtonState[PADBTN_6] = 0; }				//押していない

		//7ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_7) == PAD_INPUT_7) { gamepad[cnt].AllButtonState[PADBTN_7]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_7) != PAD_INPUT_7) { gamepad[cnt].AllButtonState[PADBTN_7] = 0; }				//押していない

		//8ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_8) == PAD_INPUT_8) { gamepad[cnt].AllButtonState[PADBTN_8]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_8) != PAD_INPUT_8) { gamepad[cnt].AllButtonState[PADBTN_8] = 0; }				//押していない

		//9ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_9) == PAD_INPUT_9) { gamepad[cnt].AllButtonState[PADBTN_9]++; }				//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_9) != PAD_INPUT_9) { gamepad[cnt].AllButtonState[PADBTN_9] = 0; }				//押していない

		//10ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_10) == PAD_INPUT_10) { gamepad[cnt].AllButtonState[PADBTN_10]++; }			//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_10) != PAD_INPUT_10) { gamepad[cnt].AllButtonState[PADBTN_10] = 0; }			//押していない

		//11ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_11) == PAD_INPUT_11) { gamepad[cnt].AllButtonState[PADBTN_11]++; }			//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_11) != PAD_INPUT_11) { gamepad[cnt].AllButtonState[PADBTN_11] = 0; }			//押していない

		//12ボタンを押しているかチェック
		if ((gamepad[cnt].InputState & PAD_INPUT_12) == PAD_INPUT_12) { gamepad[cnt].AllButtonState[PADBTN_12]++; }			//押している
		if ((gamepad[cnt].InputState & PAD_INPUT_12) != PAD_INPUT_12) { gamepad[cnt].AllButtonState[PADBTN_12] = 0; }			//押していない

		if (DEBUG_MODE == TRUE)	//デバッグモードなら
		{
			//数値を反映して移動させる
			debug[cnt].ptLeft.x += gamepad[cnt].NewAnalogX / 100;
			debug[cnt].ptLeft.y += gamepad[cnt].NewAnalogY / 100;

			//左上に戻る
			if (MY_PAD_CLICK(cnt, PADBTN_3) == TRUE)
			{
				debug[cnt].ptLeft.x = 0;
				debug[cnt].ptLeft.y = 0;
			}
		}

	}

	return;
}

/// <summary>
/// ボタンを押しているか、パッドコードで判断する
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>押していたらTRUE</returns>
BOOL MY_PAD_DOWN(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	
	//パッドコードのボタンを押している時
	if (gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] != 0)
	{
		return TRUE;	//ボタンを押している
	}
	else
	{
		return FALSE;	//ボタンを押していない
	}
}

/// <summary>
/// パッドを押し上げたか、パッドコード判断する
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>押し上げたらTRUE</returns>
BOOL MY_PAD_UP(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	if (gamepad[DX_INPUT_PAD].OldButtonKeyState[PADBTN_] >= 1	//直前は押していて
		&& gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] == 0)	//今は押していないとき
	{
		return TRUE;	//ボタンを押し上げている
	}
	else
	{
		return FALSE;	//ボタンを押し上げていない
	}
}

/// <summary>
/// パッドを押し続けているか、パッドコード判断する
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <param name="DownSecond">パッドを押し続けている時間(秒)</param>
/// <returns>押し続けていたらTRUE</returns>
BOOL MY_PADDOWN_KEEP(int DX_INPUT_PAD, PAD_BUTTON PADBTN_, int milliTime)
{
	float MilliSec = 1000.0f;	//１秒は1000ミリ秒

	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = (milliTime / MilliSec) * GAME_FPS;

	if (gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

/// <summary>
/// パッドをクリックしたか、パッドコードで判断する
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>クリックしたらTRUE</returns>
BOOL MY_PAD_CLICK(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	if (gamepad[DX_INPUT_PAD].OldButtonKeyState[PADBTN_] == 0		//直前は押していなくて
		&& gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] >= 1)	//今は押しているとき
	{
		return TRUE;	//パッドをクリックした（押し続けても、１回のみ発生）
	}
	else
	{
		return FALSE;	//パッドをクリックしていないか、押し続けている
	}
}

/// <summary>
/// パッドの情報を描画する
/// </summary>
/// <returns></returns>
VOID MY_PAD_DRAW(VOID)
{
	//パッドの数に応じて処理を行う
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		if (DEBUG_MODE == TRUE)	//デバッグモードなら
		{
			//円を描画
			DrawCircle(debug[cnt].ptLeft.x, debug[cnt].ptLeft.y, debug[cnt].RoundLeft, debug[cnt].Color, TRUE);
		}
	}

	if (DEBUG_MODE == TRUE)	//デバッグモードなら
	{
		//文字列を描画
		if (padConnectNum <= 0)
		{
			DrawFormatString(0, GAME_HEIGHT - 180, GetColor(255, 255, 255), "ゲームパッド未接続");
		}
		else
		{
			DrawFormatString(0, GAME_HEIGHT - 180, GetColor(255, 255, 255), "ゲームパッド接続数:%1d", padConnectNum);
		}

		//パッドの数に応じて処理を行う
		for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
		{
			//パッドの情報を描画
			DrawFormatString(0, GAME_HEIGHT - (160 - cnt * 20), GetColor(255, 255, 255),
				"[AX:%5d][AY:%5d][U:%3d][R:%3d][D:%3d][L:%3d][1:%3d][2:%3d][3:%3d][4:%3d][5:%3d][6:%3d][7:%3d][8:%3d][9:%3d][10:%3d][11:%3d][12:%3d]",
				gamepad[cnt].NewAnalogX,
				gamepad[cnt].NewAnalogY,
				gamepad[cnt].AllButtonState[PADBTN_UP],
				gamepad[cnt].AllButtonState[PADBTN_RIGHT],
				gamepad[cnt].AllButtonState[PADBTN_DOWN],
				gamepad[cnt].AllButtonState[PADBTN_LEFT],
				gamepad[cnt].AllButtonState[PADBTN_1],
				gamepad[cnt].AllButtonState[PADBTN_2],
				gamepad[cnt].AllButtonState[PADBTN_3],
				gamepad[cnt].AllButtonState[PADBTN_4],
				gamepad[cnt].AllButtonState[PADBTN_5],
				gamepad[cnt].AllButtonState[PADBTN_6],
				gamepad[cnt].AllButtonState[PADBTN_7],
				gamepad[cnt].AllButtonState[PADBTN_8],
				gamepad[cnt].AllButtonState[PADBTN_9],
				gamepad[cnt].AllButtonState[PADBTN_10],
				gamepad[cnt].AllButtonState[PADBTN_11],
				gamepad[cnt].AllButtonState[PADBTN_12]
			);

		}

	}

	return;
}