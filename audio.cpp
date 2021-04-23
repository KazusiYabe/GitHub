/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//音楽のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "FPS.h"
#include "audio.h"

//########## グローバル変数 ##########

//音楽管理
AUDIO NowPlayBGM;	//現在流れいるBGM
AUDIO TitleBGM;		//タイトルのBGM
AUDIO PlayBGM;		//プレイのBGM
AUDIO EndClearBGM;	//エンドクリアのBGM
AUDIO EndOverBGM;	//エンドオーバーのBGM

AUDIO sampleSE;			//サンプルSE
AUDIO selectSE;			//選択SE
AUDIO selectEnterSE;	//選択SE

AUDIO wazaSE[WAZA_EFFECT_MAX];	//技のエフェクトのSE

AUDIO dragonSE;	//ドラゴンの鳴き声
AUDIO slimeSE;	//スライムの鳴き声
AUDIO playerSE;	//プレイヤの鳴き声

//########## 関数 ##########

/// <summary>
/// 音楽をまとめて読込
/// </summary>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_AUDIO_LOAD(VOID)
{
	//BGMの読み込み
	if (MY_AUDIO_LOAD_FILE(&TitleBGM, BGM_TITLE_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&PlayBGM, BGM_PLAY_PATH, 25, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&EndClearBGM, BGM_END_CLEAR_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&EndOverBGM, BGM_END_OVER_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }

	//サンプル音楽の読み込み(引数は関数の説明を読んでね！)
	if (MY_AUDIO_LOAD_FILE(&sampleSE, SE_SAMPLE_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&selectSE, SE_SELECT_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&selectEnterSE, SE_SELECT_ENTER_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }

	//他の音楽もココで読み込むこと
	if (MY_AUDIO_LOAD_FILE(&wazaSE[0], SE_WAZA0_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[1], SE_WAZA1_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[2], SE_WAZA2_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[3], SE_WAZA3_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[4], SE_WAZA4_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[5], SE_WAZA5_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[6], SE_WAZA6_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[7], SE_WAZA7_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[8], SE_WAZA8_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[9], SE_WAZA9_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[10], SE_WAZA10_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[11], SE_WAZA11_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[12], SE_WAZA12_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[13], SE_WAZA13_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[14], SE_WAZA14_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }

	if (MY_AUDIO_LOAD_FILE(&dragonSE, SE_DRAGON_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&slimeSE, SE_SLIME_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&playerSE, SE_PLAYER_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	
	return TRUE;
}

/// <summary>
/// 音楽をまとめて削除
/// </summary>
/// <returns></returns>
VOID MY_AUDIO_DELETE(VOID)
{
	//サンプル音楽を削除
	DeleteSoundMem(TitleBGM.handle);
	DeleteSoundMem(PlayBGM.handle);
	DeleteSoundMem(EndClearBGM.handle);
	DeleteSoundMem(EndOverBGM.handle);

	DeleteSoundMem(sampleSE.handle);
	DeleteSoundMem(selectSE.handle);
	DeleteSoundMem(selectEnterSE.handle);

	DeleteSoundMem(dragonSE.handle);
	DeleteSoundMem(slimeSE.handle);
	DeleteSoundMem(playerSE.handle);

	//他の音楽もココで削除すること
	for (int cnt = 0; cnt < WAZA_EFFECT_MAX; cnt++)
	{
		DeleteSoundMem(wazaSE[cnt].handle);
	}

	return;
}

/// <summary>
/// 音楽を１つ読み込む
/// </summary>
/// <param name = "audio">設定したい音楽構造体</param>
/// <param name = "path">音楽のファイルパス</param>
/// <param name = "volume">ボリューム(0%～100%)</param>
/// <param name = "playType">再生形式 DX_PLAYTYPE_BACK / DX_PLAYTYPE_LOOPなど</param>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_AUDIO_LOAD_FILE(AUDIO* audio, const char* path, int volume, int playType)
{
	//サンプル音楽の読み込み
	audio->handle = LoadSoundMem(path);
	if (audio->handle == -1)
	{
		//読み込みエラー
		MessageBox(GetMainWindowHandle(), path, AUDIO_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//音量を設定
	SetVolumeAudio(audio, GetVolume(volume));

	//再生形式を設定
	audio->playType = playType;

	//その他設定
	audio->fadeInCnt = 0;
	audio->fadeInCntMax = 0;
	audio->fadeOutCnt = 0;
	audio->fadeOutCntMax = 0;

	return TRUE;
}

/// <summary>
/// 音楽再生
/// </summary>
/// <param name="audio">再生する音楽構造体</param>
/// <returns></returns>
VOID PlayAudio(AUDIO audio)
{
	//ループ再生でなければ、そのまま再生する
	if (audio.playType == DX_PLAYTYPE_BACK)
	{
		PlaySoundMem(audio.handle, audio.playType);//音楽の再生
	}
	//ループ再生のときは、音楽が再生されていなければ、再生する
	else if (audio.playType == DX_PLAYTYPE_LOOP)
	{
		if (CheckSoundMem(audio.handle) == 0)
		{
			PlaySoundMem(audio.handle, audio.playType);//音楽の再生
		}
	}

	return;
}

/// <summary>
/// 音楽のボリューム取得
/// </summary>
/// <param name="audio">取得する音楽構造体</param>
/// <param name = "volume">ボリューム(0%～100%)</param>
/// <returns></returns>
int GetVolumeAudio(AUDIO audio)
{
	//音量を取得
	return audio.volume;
}

/// <summary>
/// 音楽のボリューム設定
/// </summary>
/// <param name="audio">設定する音楽構造体</param>
/// <param name = "volume">ボリューム(0%～100%)</param>
/// <returns></returns>
VOID SetVolumeAudio(AUDIO* audio, int volume)
{
	//音量を設定
	audio->volume = volume;
	ChangeVolumeSoundMem(audio->volume, audio->handle);

	return;
}

/// <summary>
/// 音楽のボリューム変更
/// </summary>
/// <param name="audio">変更する音楽構造体</param>
/// <param name = "volume">ボリューム(0%～100%)</param>
/// <returns></returns>
VOID ChangeVolumeAudio(AUDIO* audio, int volume)
{
	//音量を設定（構造体のボリュームは変更しない）
	ChangeVolumeSoundMem(volume, audio->handle);

	return;
}

/// <summary>
/// 音楽停止
/// </summary>
/// <param name="audio">停止する音楽構造体</param>
/// <returns></returns>
VOID StopAudio(AUDIO* audio)
{
	//音楽の停止
	StopSoundMem(audio->handle);

	//フェード系カウンタ初期化
	audio->fadeInCnt = 0;
	audio->fadeOutCnt = 0;

	return;
}

/// <summary>
/// フェードイン処理
/// </summary>
/// <param name="audio">フェードインする音楽構造体</param>
/// <param name="milliTime">フェードインする時間(ミリ秒)</param>
/// <returns></returns>
VOID FadeInPlayAudio(AUDIO* audio, int milliTime)
{
	//最初のフェードイン処理のとき
	if (audio->fadeInCnt == 0)
	{
		float MilliSec = 1000.0f;	//１秒は1000ミリ秒

		//流し続ける時間=秒数×FPS値
		//例）60FPSのゲームで、1秒間流し続けるなら、1秒×60FPS
		int UpdateTime = (milliTime / MilliSec) * GAME_FPS;	//この時間がMAX

		//フェードインのカウンタ設定
		audio->fadeInCnt = 0;
		audio->fadeInCntMax = UpdateTime;

		ChangeVolumeAudio(audio, 0);	//音量を0にして

		//音楽再生
		if (CheckSoundMem(audio->handle) == 0) {
			PlayAudio(*(audio));
		}
	}

	//フェードインしているとき(フェードインのMAX値以下ならば)
	if (audio->fadeInCnt >= 0 && audio->fadeInCnt <= audio->fadeInCntMax)
	{
		//カウンタを上げる
		audio->fadeInCnt++;

		//現在のカウント時間÷MAX時間で、音量の全体割合を計算→％から×100して音量へ
		float CalcVolume = (float)audio->fadeInCnt / (float)audio->fadeInCntMax * 100;

		//読み込み時に設定した音量は超えないように注意すること！
		if (CalcVolume >= GetVolumeAudio(*(audio))) {
			CalcVolume = GetVolumeAudio(*(audio));
		}

		//音量を上げる
		ChangeVolumeAudio(audio, GetVolume(CalcVolume));
	}

	return;
}

/// <summary>
/// フェードアウト処理
/// </summary>
/// <param name="audio">フェードアウトする音楽構造体</param>
/// <param name="milliTime">フェードアウトする時間(ミリ秒)</param>
/// <returns>フェードアウト中はFALSE / フェードアウト終了はTRUE</returns>
BOOL FadeOutPlayAudio(AUDIO* audio, int milliTime)
{
	//最初のフェードアウト処理のとき
	if (audio->fadeOutCnt == 0)
	{
		float MilliSec = 1000.0f;	//１秒は1000ミリ秒

		//流し続ける時間=秒数×FPS値
		//例）60FPSのゲームで、1秒間流し続けるなら、1秒×60FPS
		int UpdateTime = (milliTime / MilliSec) * GAME_FPS;	//この時間がMAX

		//フェードアウトのカウンタ設定
		audio->fadeOutCnt = 0;
		audio->fadeOutCntMax = UpdateTime;

		ChangeVolumeAudio(audio, GetVolume(GetVolumeAudio(*(audio))));	//音量をMAXにして

		//音楽再生
		if (CheckSoundMem(audio->handle) == 0) {
			PlayAudio(*(audio));
		}
	}

	//フェードアウトしているとき(フェードアウトのMAX値以下ならば)
	if (audio->fadeOutCnt >= 0 && audio->fadeOutCnt <= audio->fadeOutCntMax)
	{
		//カウンタを上げる
		audio->fadeOutCnt++;

		//(MAX時間-現在のカウント時間)÷MAX時間で、音量の全体割合を計算→％から×100して音量へ
		float CalcVolume = ((float)audio->fadeOutCntMax - (float)audio->fadeOutCnt) / (float)audio->fadeOutCntMax * 100;

		//読み込み時に設定した音量は超えないように注意すること！
		if (CalcVolume >= GetVolumeAudio(*(audio))) { CalcVolume = GetVolumeAudio(*(audio)); }

		//音量を下げる
		ChangeVolumeAudio(audio, GetVolume(CalcVolume));

		//フェードアウト中
		return FALSE;
	}
	else
	{
		return TRUE;
	}

	return FALSE;
}