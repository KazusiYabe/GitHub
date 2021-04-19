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
#include "rect.h"

#define PUSH_ENTER "-PUSH  ENTER-"
#define WAZA_MAX	12
#define WAZA_SELECT_MAX	4

//########## 構造体 ##########
struct CHARACTOR_DATA
{
	char Name[STR_MAX] = "";
	int HP = 0;			//体力
	int HPMAX = 0;		//体力(MAX)
	float ATK = 1.0;	//攻撃力
	int MP = 0;			//ＭＰ
};//モンスターのデータ

struct WAZA_RECORD
{
	int No = -1;
	char Name[STR_MAX] = "";
	int ATK = 0;
	int MP = -1;		//使うMPの量
	int HealHP = -1;	//HP回復量
	int HealMP = -1;	//MP回復量
};	//技レコード用

enum COMMAND
{
	encounter,	//遭遇
	input,		//入力
	waza,		//技
	process,	//処理
	damage		//ダメージを食らう
};

enum BUTTLECOMMAND
{
	attack,
	magic,
	recovery
};

enum WAZACOMMAND
{
	wazaSelect0,
	wazaSelect1,
	wazaSelect2,
	wazaSelect3
};


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

//モンスターデータ
CHARACTOR_DATA dragonData;
CHARACTOR_DATA slimeData;
CHARACTOR_DATA tekiData;

CHARACTOR_DATA playerData;

//技テーブルデータ
WAZA_RECORD wazaTable[WAZA_MAX]{
	{0,"ヒッカキ"		,1,		0,		0,		0},
	{1,"キリツケ"		,1,		0,		0,		0},
	{2,"ハサミ"			,2,		0,		0,		0},
	{3,"スラッシュ"		,3,		0,		0,		0},
	{4,"アイシクル"		,5,		10,		0,		0},
	{5,"雷撃"			,5,		10,		0,		0},
	{6,"カエンビーーム"	,20,	20,		0,		0},
	{7,"トリプルソード"	,30,	30,		0,		0},
	{8,"いやしの風"		,0,		5,		5,		0},
	{9,"いやしの雨"		,0,		5,		0,		5},
	{10,"アースヒール"	,0,		30,		30,		30},
	{11,"聖なる光"		,0,		50,	   100,	   100}
};

//ステータスの表示系
int statusHeight = 40;
int HpBarMaxWidth = 650;
RECT HpBar;
RECT HpBarWaku;

//コマンド系
int NowCommand = encounter;
int buttleCmd = attack;
int wazaSelectCmd = 0;		//選択した技の場所
int wazaNo = 0;				//選択した技No.

BOOL ProcCmdFlg = FALSE;	//技の説明が終わった？
BOOL EffectEndFlg = FALSE;	//エフェクトが終わった？

BOOL IsNotEnoughMP = FALSE;		//MPは足りる？

int damageCnt = 0;
int damageCntMAX = 60;
BOOL damageProcFlg = FALSE;	//ダメージ処理を行ったか？

//########## 関数のプロトタイプ宣言 ##########

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

	//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
	//モンスターのデータを初期化する

	//ドラゴン
	strcpy_sDx(dragonData.Name, STR_MAX, "緑神竜グレガリゴン");
	dragonData.HPMAX = 100;
	dragonData.HP = dragonData.HPMAX;
	dragonData.ATK = 3.0;
	dragonData.MP = 50;

	//スライム
	strcpy_sDx(slimeData.Name, STR_MAX, "ハマミースライム");
	slimeData.HPMAX = 10;
	slimeData.HP = slimeData.HPMAX;
	slimeData.ATK = 1.0;
	slimeData.MP = 5;

	//プレイヤー
	strcpy_sDx(playerData.Name, STR_MAX, "冒険者ブレイブ");
	playerData.HPMAX = 20;
	playerData.HP = slimeData.HPMAX;
	playerData.ATK = 1.0;
	playerData.MP = 10;

	//スライムのデータを固定
	tekiData = slimeData;

	//ステータス系
	HpBar = GetRect(wakuImage.pos.x + 60, statusHeight + 60, wakuImage.pos.x + 60 + HpBarMaxWidth, statusHeight + 60 + 60);
	HpBarWaku = HpBar;

	//コマンド系
	NowCommand = encounter;
	buttleCmd = attack;
	wazaSelectCmd = 0;
	wazaNo = 0;

	GameScene = GAME_SCENE_TITLE;	//ゲームシーンはタイトル画面から

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

	////エンターキーでシーン遷移
	//if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	//{
	//	GameScene = GAME_SCENE_END;		//エンド画面へ
	//	IsFadeIn = FALSE;				//フェードインはしない！
	//	IsFadeOut = TRUE;				//フェードアウト開始！

	//	return;
	//}

	//コマンド系の処理
	switch (NowCommand)
	{
	case encounter:
		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = input;//次のコマンドへ
		}
		break;
	case input:
		if (MY_KEY_CLICK(KEY_INPUT_UP) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd > attack) { buttleCmd--; }
			else { buttleCmd = attack; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_DOWN) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd < recovery) { buttleCmd++; }
			else { buttleCmd = recovery; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_LEFT) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd > attack) { buttleCmd--; }
			else { buttleCmd = attack; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RIGHT) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd < recovery) { buttleCmd++; }
			else { buttleCmd = recovery; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = waza;	//次のコマンドへ
			IsNotEnoughMP = FALSE;	//MPは足りる？
		}

		break;

	case waza:

		if (MY_KEY_CLICK(KEY_INPUT_BACK) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = input;	//前のコマンドへ
		}

		if (MY_KEY_CLICK(KEY_INPUT_UP) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaSelectCmd >= wazaSelect2) { wazaSelectCmd -= 2; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_DOWN) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaSelectCmd <= wazaSelect1) { wazaSelectCmd += 2; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_LEFT) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaSelectCmd == wazaSelect1 || wazaSelectCmd == wazaSelect3) { wazaSelectCmd--; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RIGHT) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaSelectCmd == wazaSelect0 || wazaSelectCmd == wazaSelect2) { wazaSelectCmd++; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			wazaNo = (buttleCmd * WAZA_SELECT_MAX) + wazaSelectCmd;	//技Noを決定

			if (playerData.MP < wazaTable[wazaNo].MP)
			{
				IsNotEnoughMP = TRUE;	//MPが足りない！
			}

			PlayAudio(selectSE);
			ProcCmdFlg = FALSE;		//技の説明をする
			NowCommand = process;	//次のコマンドへ

		}

		break;

	case process:

		//MPが足りないときは選択し直す
		if (IsNotEnoughMP == TRUE)
		{
			EffectEndFlg = FALSE;
			if (MY_KEY_CLICK(KEY_INPUT_BACK) == TRUE)
			{
				PlayAudio(selectSE);
				NowCommand = waza;		//前のコマンドへ
				IsNotEnoughMP = FALSE;
				break;
			}
		}

		//MPが足りていれば
		if (IsNotEnoughMP == FALSE)
		{
			if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
			{
				ProcCmdFlg = TRUE;
				EffectEndFlg = FALSE;
			}
		}

		//エフェクトがおわったら
		if (EffectEndFlg == TRUE)
		{
			damageProcFlg = FALSE;	//ダメージ処理
			damageCnt = 0;
			NowCommand = damage;	//次のコマンドへ
		}

		break;
	case damage:

		if (damageProcFlg == FALSE)
		{
			if (buttleCmd == attack || buttleCmd == magic)
			{
				tekiData.HP -= (int)ceil(playerData.ATK * wazaTable[wazaNo].ATK);	//HPを減らす
				if (tekiData.HP < 0) { tekiData.HP = 0; }
				playerData.MP -= wazaTable[wazaNo].MP;	//MPを減らす
				if (tekiData.MP < 0) { tekiData.MP = 0; }
			}
			else if (buttleCmd == recovery)
			{
				playerData.HP += wazaTable[wazaNo].HealHP;	//HPを増やす
				playerData.MP += wazaTable[wazaNo].HealMP;	//MPを増やす
			}
			damageProcFlg = TRUE;
		}

		//自動で次のコマンドへ
		if (damageCnt < damageCntMAX) { damageCnt++; }
		else
		{
			//敵のHPが0以下になったとき
			if (tekiData.HP <= 0)
			{
				GameScene = GAME_SCENE_END;		//エンド画面へ
				IsSlimeWin = TRUE;				//敵に勝った！
				IsFadeIn = FALSE;				//フェードインはしない！
				IsFadeOut = TRUE;				//フェードアウト開始！
			}

			//自分のHPは0以下になったとき
			if (playerData.HP <= 0)
			{
				GameScene = GAME_SCENE_END;		//エンド画面へ
				IsSlimeWin = FALSE;				//敵に負けた
				IsFadeIn = FALSE;				//フェードインはしない！
				IsFadeOut = TRUE;				//フェードアウト開始！
			}

			NowCommand = input;
		}

		break;
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
	DrawImage(playbossImage);

	//スライムを描画
	//ドラゴン：dragonImage
	//スライム：slimeImage
	DrawImage(dragonImage);

	//モンスターのステータス
	DrawImage(wakuImage);
	DrawStringToHandle(wakuImage.pos.x + 60, statusHeight, tekiData.Name, GetColor(255, 255, 255), fontMonster.handle);

	//HPによってバーを縮める
	HpBar.right = HpBar.left + ((float)tekiData.HP / tekiData.HPMAX) * HpBarMaxWidth;
	if (HpBar.right < HpBar.left) { HpBar.right = HpBar.left; }	//HPバーを超えないように

	//HPバーの色を変える
	if (tekiData.HP < tekiData.HPMAX / 8) { DrawRect(HpBar, GetColor(204, 75, 49), TRUE); }
	else if (tekiData.HP < tekiData.HPMAX / 4) { DrawRect(HpBar, GetColor(204, 178, 49), TRUE); }
	else { DrawRect(HpBar, GetColor(49, 204, 49), TRUE); }
	DrawRect(HpBarWaku, GetColor(255, 255, 255), FALSE);
	//HPの数値を表示
	DrawFormatStringToHandle(wakuImage.pos.x + 80, statusHeight + 60, GetColor(255, 255, 255), fontMonster.handle, "HP：%5d/%5d", tekiData.HP, tekiData.HPMAX);

	//メッセージ枠描画
	DrawImage(messageImage);
	//プレイヤー名前描画
	DrawStringToHandle(messageImage.pos.x + 5, messageImage.pos.y + 10, playerData.Name, GetColor(255, 255, 255), fontPlayer.handle);

	unsigned int selectColor = GetColor(245, 245, 245);
	unsigned int notselectColor = GetColor(102, 102, 102);

	unsigned int kougekiColor = notselectColor;
	unsigned int mahouColor = notselectColor;
	unsigned int kaihukuColor = notselectColor;

	unsigned int waza1Color = notselectColor;
	unsigned int waza2Color = notselectColor;
	unsigned int waza3Color = notselectColor;
	unsigned int waza4Color = notselectColor;

	char ProcText[STR_MAX];

	//コマンド系の処理
	switch (NowCommand)
	{
	case encounter:
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "なんと！モンスターに遭遇してしまった！！", GetColor(255, 255, 255), fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 90, "どうやら戦うしかないようだ・・・！▼", GetColor(255, 255, 255), fontCommand.handle);
		break;
	case input:

		if (buttleCmd == attack) { kougekiColor = selectColor; }
		else if (buttleCmd == magic) { mahouColor = selectColor; }
		else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "コウゲキ", kougekiColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "マホウ", mahouColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "カイフク", kaihukuColor, fontCommand.handle);

		break;

	case waza:

		//入力のコマンドはそのまま描画中
		if (buttleCmd == attack) { kougekiColor = selectColor; }
		else if (buttleCmd == magic) { mahouColor = selectColor; }
		else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "コウゲキ", kougekiColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "マホウ", mahouColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "カイフク", kaihukuColor, fontCommand.handle);

		if (wazaSelectCmd == 0) { waza1Color = selectColor; }
		else if (wazaSelectCmd == 1) { waza2Color = selectColor; }
		else if (wazaSelectCmd == 2) { waza3Color = selectColor; }
		else if (wazaSelectCmd == 3) { waza4Color = selectColor; }

		//技を描画
		if (buttleCmd == attack)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[0].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[1].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[2].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[3].Name, waza4Color, fontCommand.handle);
		}
		else if (buttleCmd == magic)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[4].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[5].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[6].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[7].Name, waza4Color, fontCommand.handle);
		}
		else if (buttleCmd == recovery)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[8].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[9].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[10].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[11].Name, waza4Color, fontCommand.handle);
		}


		break;

	case process:

		if (IsNotEnoughMP == FALSE)
		{
			if (buttleCmd == attack)
			{
				sprintfDx(ProcText, "%sは%s攻撃した！", playerData.Name, wazaTable[wazaNo].Name);
			}
			else if (buttleCmd == magic)
			{
				sprintfDx(ProcText, "%sは%sを唱えた！", playerData.Name, wazaTable[wazaNo].Name);
			}
			else if (buttleCmd == recovery)
			{
				sprintfDx(ProcText, "%sは%sを祈った！", playerData.Name, wazaTable[wazaNo].Name);
			}


			EffectEndFlg = TRUE;
			//エフェクト描画
			if (EffectEndFlg == TRUE)
			{

			}

		}
		else
		{
			sprintfDx(ProcText, "MPが足りない...技を選び直さねば...");
		}
		DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

		break;
	case damage:

		if (buttleCmd == attack || buttleCmd == magic)
		{
			sprintfDx(ProcText, "%sに[%3d]アタックした！！", tekiData.Name, (int)ceil(playerData.ATK * wazaTable[wazaNo].ATK));
		}
		else if (buttleCmd == recovery)
		{
			sprintfDx(ProcText, "%sは[HP%3d/MP%3d]回復した", playerData.Name, wazaTable[wazaNo].HealHP, wazaTable[wazaNo].HealMP);
		}
		DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

		break;
	}

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

		//ゲーム初期化
		if (GameScene == GAME_SCENE_TITLE) { MY_TITLE_INIT(); }

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