/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//FPS処理のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "FPS.h"

//########## グローバル変数 ##########

//FPSのデータを管理
FPS fps;

//########## 関数 ##########

/// <summary>
/// FPS値を計測し、値を更新する関数
/// </summary>
/// <returns></returns>
VOID MY_FPS_UPDATE(VOID)
{
	//一番最初の処理のときだけ、測定開始時刻を取得する
	if (fps.IsInitFlg == FALSE)
	{
		//測定開始時刻をマイクロ秒単位で取得
		fps.StartTime = GetNowHiPerformanceCount();

		fps.IsInitFlg = TRUE;	//フラグを立てておく
	}

	//現在の時刻をマイクロ秒単位で取得
	fps.NowTime = GetNowHiPerformanceCount();

	// 前回取得した時間からの経過時間を秒に変換してセット
	fps.DeltaTime = (fps.NowTime - fps.OldTime) / 1000000.0f;

	// 今回取得した時間を保存
	fps.OldTime = fps.NowTime;

	//1フレーム目～FPS設定値までは、カウントアップ
	if (fps.Count < fps.SampleRate)
	{
		//カウンタを増やす
		fps.Count++;
	}
	else
	{
		//FPS設定値フレーム目なら平均を計算

		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		fps.DrawValue = 1000000.0f / ((fps.NowTime - fps.StartTime) / (float)fps.SampleRate);

		//測定開始時刻をマイクロ秒単位で取得
		fps.StartTime = GetNowHiPerformanceCount();

		//カウンタ初期化
		fps.Count = 1;
	}

	return;
}

/// <summary>
/// FPS値を描画する関数
/// </summary>
/// <returns></returns>
VOID MY_FPS_DRAW(VOID)
{
	if (DEBUG_MODE == TRUE)	//デバッグモードなら
	{
		//文字列を描画
		DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", fps.DrawValue);
	}

	return;
}

/// <summary>
/// FPS値を計測し、待つ関数
/// </summary>
/// <returns></returns>
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = fps.NowTime - fps.StartTime;					//測定開始時刻から現在のかかった時間(マイクロ秒)
	int waitTime = 1000000.0f / GAME_FPS * fps.Count - resultTime;	//待つべき時間(マイクロ秒)

	waitTime /= 1000.0f;		//マイクロ秒をミリ秒に変換

	if (waitTime > 0)			//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//早かったら処理を待つ(ProcessMessage関数は裏で実行される)
	}
	return;
}