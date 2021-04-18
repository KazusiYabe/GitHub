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
IMAGE sampleImage;	//サンプル画像
DIVIMAGE sampleDivImage;	//サンプル分割画像

//########## 関数 ##########

/// <summary>
/// 画像をまとめて読込
/// </summary>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_IMAGE_LOAD(VOID)
{
	//サンプル画像の読み込み(引数は関数の説明を読んでね！)
	if (MY_IMAGE_LOAD_FILE(&sampleImage, IMAGE_SAMPLE_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//サンプル分割画像の読み込み
	if (MY_IMAGE_LOAD_DIV_FILE(
		&sampleDivImage, IMAGE_SAMPLE_DIV_PATH,
		5, 2, (1200 / 5), (480 / 2),	//画像によって数値を変更すること（サンプルは、縦に５列、横に２行、幅240、高さ240という意味）
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
/// <param name = "width">画像の分割の幅</param>
/// <param name = "height">画像の分割の高さ</param>
/// 
/// <param name = "IsCenter">画像をXYの中心に描画したいときはTRUEにする</param>
/// <param name = "margin">画像の当たり判定の余白（当たり判定を狭めたりするときに使おう！）デフォルトはナシ！</param>
/// <returns>読み込めたらTRUE/読み込めなかったらFALSE</returns>
BOOL MY_IMAGE_LOAD_DIV_FILE(
	DIVIMAGE* image, const char* path,
	int retu, int gyo, int width, int height,
	int x, int y, BOOL IsCenter, RECT margin)
{
	//サンプル画像の読み込み
	LoadDivGraph(path, (retu * gyo), retu, gyo, width, height, &image->handle[0]);

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
	//サンプル画像を削除
	DeleteGraph(sampleImage.handle);
	for (int i = 0; i < sampleDivImage.DivMax; i++) { DeleteGraph(sampleDivImage.handle[i]); };

	//他の画像もココで削除すること

	return;
}