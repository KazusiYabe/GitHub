#pragma once

//ヘッダーファイルを読み込み
#include "DxLib.h"

//キーボードのヘッダーファイル

//マクロ定義
#define KEY_KIND_MAX   256

//構造体

struct KEYBOARD
{
	char TempKeyState[KEY_KIND_MAX];
	int AllKeyState[KEY_KIND_MAX];
	int OldAllKeyState[KEY_KIND_MAX];
};

//外部のグローバル変数
extern KEYBOARD keyboard;

//プロトタイプ宣言
extern void AllKeyDownUpdate(void);
extern BOOL KeyDown(int KEY_INPUT_);
extern BOOL KeyUp(int KEY_INPUT_);
extern BOOL KeyClick(int KEY_INPUT_);
extern BOOL KeyDownKeep(int KEY_INPUT_,int millSec);
