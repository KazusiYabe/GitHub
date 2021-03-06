/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//画像のソースファイル

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "image.h"
#include "rect.h"

//########## グローバル変数 ##########

//画像管理
IMAGE dragonImage;			//ドラゴン画像
IMAGE slimeImage;			//スライム画像
IMAGE tekiImage;			//敵の画像
IMAGE titleBackImage;		//タイトル背景画像

IMAGE playkusaImage;		//プレイ背景画像(草原)
IMAGE playdanjonImage;		//プレイ背景画像(ダンジョン)
IMAGE playkawaImage;		//プレイ背景画像(川岸)
IMAGE playbossImage;		//プレイ背景画像(ボス)

IMAGE endClearImage;		//エンド背景画像(クリア)
IMAGE endOverImage;			//エンド背景画像(オーバー)

IMAGE endClearLogo;			//エンドロゴ画像(クリア)
IMAGE endOverLogo;			//エンドロゴ画像(オーバー)

IMAGE titleLogo;			//タイトルロゴ画像

IMAGE wakuImage;			//モンスター枠画像
IMAGE messageImage;				//メッセージ枠画像

DIVIMAGE effectImage[WAZA_EFFECT_MAX];	//エフェクト分割画像

//########## 関数 ##########

/// <summary>
/// 画像をまとめて読込
/// </summary>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_IMAGE_LOAD(VOID)
{
	//ドラゴン画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&dragonImage, IMAGE_DRAGON_PATH, 0, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//スライム画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&slimeImage, IMAGE_SLIME_PATH, 0, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//タイトル背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&titleBackImage, IMAGE_TITLE_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//プレイ背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&playkusaImage, IMAGE_PLAY_KUSA_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//プレイ背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&playdanjonImage, IMAGE_PLAY_DANJON_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//プレイ背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&playkawaImage, IMAGE_PLAY_KAWA_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//プレイ背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&playbossImage, IMAGE_PLAY_BOSS_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//エンド背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&endClearImage, IMAGE_END_CLEAR_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//エンド背景画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&endOverImage, IMAGE_END_OVER_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//エンドロゴ画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&endClearLogo, IMAGE_END_CLEAR_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 4 * 1, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//エンドロゴ画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&endOverLogo, IMAGE_END_OVER_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 4 * 1, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//タイトルロゴ画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&titleLogo, IMAGE_TITLE_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 3 * 1, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//モンスター枠画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&wakuImage, IMAGE_WAKU_PATH, GAME_WIDTH / 2, 100, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//プレイヤー枠画像の読み込み
	if (MY_IMAGE_LOAD_FILE(&messageImage, IMAGE_MESSAGE_PATH, 450, GAME_HEIGHT - 100, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }


	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[0], IMAGE_WAZA0_DIV_PATH,
		5, 2,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[1], IMAGE_WAZA1_DIV_PATH,
		9, 1,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[2], IMAGE_WAZA2_DIV_PATH,
		5, 2, 	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[3], IMAGE_WAZA3_DIV_PATH,
		5, 2,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[4], IMAGE_WAZA4_DIV_PATH,
		5, 2, //画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[5], IMAGE_WAZA5_DIV_PATH,
		5, 2, 	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[6], IMAGE_WAZA6_DIV_PATH,
		2, 10, //画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[7], IMAGE_WAZA7_DIV_PATH,
		1, 16,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[8], IMAGE_WAZA8_DIV_PATH,
		9, 1, 	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[9], IMAGE_WAZA9_DIV_PATH,
		10, 1, 	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[10], IMAGE_WAZA10_DIV_PATH,
		10, 1,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[11], IMAGE_WAZA11_DIV_PATH,
		5, 2,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[12], IMAGE_WAZA12_DIV_PATH,
		1, 15, //画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[13], IMAGE_WAZA13_DIV_PATH,
		3, 10,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//エフェクト画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&effectImage[14], IMAGE_WAZA14_DIV_PATH,
		5, 4,	//画像によって数値を変更すること
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}

	//他の画像もココで読み込むこと

	return TRUE;
}

/// <summary>
/// 画像を１つ読み込む
/// </summary>
/// <param name = "image">設定したい画像構造体</param>
/// <param name = "path">画像のファイルパス</param>
/// <param name = "x">X位置</param>
/// <param name = "y">Y位置</param>
/// <param name = "IsCenter">画像をXYの中心に描画したいときはTRUEにする</param>
/// <param name = "margin">画像の当たり判定の余白（当たり判定を狭めたりするときに使おう！）デフォルトはナシ！</param>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_IMAGE_LOAD_FILE(IMAGE* image, const char* path, int x, int y, BOOL IsCenter, RECT margin)
{
	//サンプル画像の読み込み
	image->handle = LoadGraph(path);
	if (image->handle == -1)
	{
		//読み込みエラー
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(image->handle, &image->pos.width, &image->pos.height);

	//XY位置を中心にしたいとき
	if (IsCenter == TRUE)
	{
		//中央寄せにして設定
		image->pos.x = x - image->pos.width / 2;
		image->pos.y = y - image->pos.height / 2;
		image->IsCenter = TRUE;
	}
	else
	{
		//そのまま位置を設定
		image->pos.x = x;
		image->pos.y = y;
		image->IsCenter = FALSE;
	}

	//描画する
	image->IsDraw = TRUE;

	//当たり判定の余白を設定
	image->pos.margin = margin;

	//画像の当たり判定の位置を更新する
	ImageCollUpdate(&image->pos);

	return TRUE;
}

/// <summary>
/// 画像を分割して読み込む
/// </summary>
/// <param name = "image">設定したい画像構造体</param>
/// <param name = "path">画像のファイルパス</param>
/// <param name = "x">X位置</param>
/// <param name = "y">Y位置</param>
/// 
/// <param name = "retu">列の分割数</param>
/// <param name = "gyo">行の分割数</param>
/// 
/// <param name = "IsCenter">画像をXYの中心に描画したいときはTRUEにする</param>
/// <param name = "margin">画像の当たり判定の余白（当たり判定を狭めたりするときに使おう！）デフォルトはナシ！</param>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_IMAGE_LOAD_DIV_FILE(
	DIVIMAGE* image, const char* path,
	int retu, int gyo,
	int x, int y, BOOL IsCenter, RECT margin)
{
	//画像全体のサイズを取得
	int width = 0;
	int height = 0;

	//一時的に画像をすべて読み込む
	image->handle[0] = LoadGraph(path);
	//画像サイズを取得
	GetGraphSize(image->handle[0], &width, &height);
	//画像を破棄
	DeleteGraph(image->handle[0]);

	//分割画像の読み込み
	LoadDivGraph(path, (retu * gyo), retu, gyo, width / retu, height / gyo, &image->handle[0]);

	image->DivMax = retu * gyo;	//実際に読み込んだ数をMAX値に設定

	if (image->handle[0] == -1)
	{
		//読み込みエラー
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//幅と高さを取得
	GetGraphSize(image->handle[0], &image->pos.width, &image->pos.height);

	//XY位置を中心にしたいとき
	if (IsCenter == TRUE)
	{
		//中央寄せにして設定
		image->pos.x = x - image->pos.width / 2;
		image->pos.y = y - image->pos.height / 2;
		image->IsCenter = TRUE;
	}
	else
	{
		//そのまま位置を設定
		image->pos.x = x;
		image->pos.y = y;
		image->IsCenter = FALSE;
	}

	//描画する
	image->IsDraw = FALSE;

	//当たり判定の余白を設定
	image->pos.margin = margin;

	//画像の当たり判定の位置を更新する
	ImageCollUpdate(&image->pos);

	return TRUE;
}

/// <summary>
/// 画像の当たり判定の位置を更新する
/// </summary>
/// <param name="pos">設定したい画像の位置や当たり判定</param>
/// <returns></returns>
VOID ImageCollUpdate(POSTION* pos)
{
	pos->coll.left = (pos->x) + pos->margin.left;						//当たり判定左（X位置）
	pos->coll.top = (pos->y) + pos->margin.top;							//当たり判定上（Y位置）
	pos->coll.right = (pos->x + pos->width) + pos->margin.right;		//当たり判定右（X位置+幅）
	pos->coll.bottom = (pos->y + pos->height) + pos->margin.bottom;		//当たり判定右（Y位置+高さ）
	return;
}

/// <summary>
/// 画像描画
/// </summary>
/// <param name="image">描画する画像構造体</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawImage(IMAGE image)
{
	//画像が描画できるときは
	if (image.IsDraw == TRUE)
	{
		DrawGraph(image.pos.x, image.pos.y, image.handle, TRUE);
	}

	//デバッグモードのときは
	if (DEBUG_MODE == TRUE)
	{
		//当たり判定を描画
		DrawRect(image.pos.coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// 分割画像の描画
/// </summary>
/// <param name="image">描画する画像構造体</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawDivImage(DIVIMAGE* image)
{
	//画像が描画できるときは
	if (image->IsDraw == TRUE)
	{
		DrawGraph(image->pos.x, image->pos.y, image->handle[image->nowIndex], TRUE);

		//アニメーションのカウントアップ
		if (image->AnimCnt < image->AnimCntMAX) { image->AnimCnt++; }
		else
		{
			//すべてのアニメーションを描画し終わったら
			if (image->nowIndex == image->DivMax - 1)
			{
				//アニメーションを繰り返さないならば
				if (image->IsAnimLoop == FALSE)
				{
					image->IsDraw = FALSE;	//描画を止める
				}
				image->AnimCnt = 0;		//カウンタ0クリア
				image->nowIndex = 0;	//先頭に戻す
			}
			//次の分割画像があるときは
			else if (image->nowIndex < image->DivMax)
			{
				image->nowIndex++; //次の画像へ
			}
			image->AnimCnt = 0;	//カウンタ0クリア
		}
	}

	//デバッグモードのときは
	if (DEBUG_MODE == TRUE)
	{
		//当たり判定を描画
		DrawRect(image->pos.coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// 画像をまとめて削除
/// </summary>
/// <returns></returns>
VOID MY_IMAGE_DELETE(VOID)
{
	DeleteGraph(slimeImage.handle);
	DeleteGraph(dragonImage.handle);
	DeleteGraph(titleBackImage.handle);

	DeleteGraph(playkusaImage.handle);
	DeleteGraph(playdanjonImage.handle);
	DeleteGraph(playkawaImage.handle);
	DeleteGraph(playbossImage.handle);

	DeleteGraph(endClearImage.handle);
	DeleteGraph(endOverImage.handle);

	DeleteGraph(endClearLogo.handle);
	DeleteGraph(endOverLogo.handle);

	DeleteGraph(titleLogo.handle);
	DeleteGraph(wakuImage.handle);
	DeleteGraph(messageImage.handle);

	for (int cnt = 0; cnt < WAZA_EFFECT_MAX; cnt++)
	{
		for (int i = 0; i < effectImage[cnt].DivMax; i++) { DeleteGraph(effectImage[0].handle[i]); };
	}

	//他の画像もココで削除すること

	return;
}