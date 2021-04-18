/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//音楽のヘッダファイル
//★注意！！フォルダ構造は以下の通りです。フォルダやファイルの準備をしてください
//ルートディレクトリ
// |-AUDIO
//    |-BGM
//       |-sampleBGM.mp3
//    |-SE
//       |-sampleSE.mp3

//★注意！
//PCのサウンドドライバが正しくないときは、(スピーカーで音がでない)
//読み込みエラーが発生する場合があります。スピーカー等から音がでるか確認！

//########## ヘッダーファイル読み込み ##########

//ゲームのメインヘッダファイル
#include "game.h"

//########## マクロ定義 ##########

//音楽系
#define BGM_TITLE_PATH		TEXT(".\\AUDIO\\BGM\\title.ogg")	
#define BGM_PLAY_PATH		TEXT(".\\AUDIO\\BGM\\play.ogg")	
#define BGM_END_CLEAR_PATH	TEXT(".\\AUDIO\\BGM\\battle.ogg")	
#define BGM_END_OVER_PATH	TEXT(".\\AUDIO\\BGM\\星の胎動.ogg")	
#define SE_SAMPLE_PATH		TEXT(".\\AUDIO\\SE\\coin.ogg")		

//関数形式マクロ
#define GetVolume(volume)	(255 * volume / 100)					//ボリュームの計算式

//エラーメッセージ
#define AUDIO_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//########## 構造体 ##########

//音楽構造体
struct AUDIO
{
	int handle = -1;		//画像ハンドル
	char path[PATH_MAX];	//パス
	int volume = -1;		//音量
	int playType = -1;		//再生形式
	int fadeInCnt = 0;				//フェードインカウンタ
	int fadeInCntMax = 0;			//フェードインカウンタMAX
	int fadeOutCnt = 0;				//フェードアウトカウンタ
	int fadeOutCntMax = 0;			//フェードアウトカウンタMAX
};

//########## 外部のグローバル変数 ##########

//音楽関連
extern AUDIO NowPlayBGM;	//現在流れいるBGM
extern AUDIO TitleBGM;		//タイトルのBGM
extern AUDIO PlayBGM;		//プレイのBGM
extern AUDIO EndClearBGM;	//エンドクリアのBGM
extern AUDIO EndOverBGM;	//エンドオーバーのBGM
extern AUDIO sampleSE;		//サンプルSE

//########## プロトタイプ宣言 ##########
//※extern は、外部に関数がありますよ！という目印でつけています。

extern BOOL MY_AUDIO_LOAD(VOID);		//音楽をまとめて読込
extern BOOL MY_AUDIO_LOAD_FILE(AUDIO* audio, const char* path, int volume, int playType);	//音楽を１つ読み込み
extern VOID FadeInOutResetAudio(VOID);	//フェードイン / フェードアウト処理をリセットする
extern VOID MY_AUDIO_DELETE(VOID);		//音楽をまとめて削除

extern VOID PlayAudio(AUDIO audio);			//音楽再生
extern VOID StopAudio(AUDIO* audio);		//音楽停止

extern int GetVolumeAudio(AUDIO audio);						//音楽のボリューム取得
extern VOID SetVolumeAudio(AUDIO* audio, int volume);		//音楽のボリューム設定
extern VOID ChangeVolumeAudio(AUDIO* audio, int volume);	//音楽のボリューム変更

extern VOID FadeInPlayAudio(AUDIO* audio, int milliTime);	//フェードイン処理
extern BOOL FadeOutPlayAudio(AUDIO* audio, int milliTime);	//フェードアウト処理
