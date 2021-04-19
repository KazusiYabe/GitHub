/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�摜�̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "image.h"
#include "rect.h"

//########## �O���[�o���ϐ� ##########

//�摜�Ǘ�
IMAGE dragonImage;			//�h���S���摜
IMAGE slimeImage;			//�X���C���摜
IMAGE titleBackImage;		//�^�C�g���w�i�摜

IMAGE playkusaImage;		//�v���C�w�i�摜(����)
IMAGE playdanjonImage;		//�v���C�w�i�摜(�_���W����)
IMAGE playkawaImage;		//�v���C�w�i�摜(���)
IMAGE playbossImage;		//�v���C�w�i�摜(�{�X)

IMAGE endClearImage;		//�G���h�w�i�摜(�N���A)
IMAGE endOverImage;			//�G���h�w�i�摜(�I�[�o�[)

IMAGE endClearLogo;			//�G���h���S�摜(�N���A)
IMAGE endOverLogo;			//�G���h���S�摜(�I�[�o�[)

IMAGE titleLogo;			//�^�C�g�����S�摜

IMAGE wakuImage;			//�����X�^�[�g�摜
IMAGE messageImage;				//���b�Z�[�W�g�摜

DIVIMAGE sampleDivImage;	//�T���v�������摜

//########## �֐� ##########

/// <summary>
/// �摜���܂Ƃ߂ēǍ�
/// </summary>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_IMAGE_LOAD(VOID)
{
	//�h���S���摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&dragonImage, IMAGE_DRAGON_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�X���C���摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&slimeImage, IMAGE_SLIME_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//�^�C�g���w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&titleBackImage, IMAGE_TITLE_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//�v���C�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&playkusaImage, IMAGE_PLAY_KUSA_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�v���C�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&playdanjonImage, IMAGE_PLAY_DANJON_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�v���C�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&playkawaImage, IMAGE_PLAY_KAWA_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�v���C�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&playbossImage, IMAGE_PLAY_BOSS_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//�G���h�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&endClearImage, IMAGE_END_CLEAR_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�G���h�w�i�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&endOverImage, IMAGE_END_OVER_BACK_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//�G���h���S�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&endClearLogo, IMAGE_END_CLEAR_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 4 * 3, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�G���h���S�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&endOverLogo, IMAGE_END_OVER_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }

	//�^�C�g�����S�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&titleLogo, IMAGE_TITLE_LOGO_PATH, GAME_WIDTH / 2, GAME_HEIGHT / 3 * 1, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�����X�^�[�g�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&wakuImage, IMAGE_WAKU_PATH, GAME_WIDTH / 2, 100, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }
	//�����X�^�[�g�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_FILE(&messageImage, IMAGE_MESSAGE_PATH, GAME_WIDTH / 2, GAME_HEIGHT - 100, TRUE, GetRect(0, 0, 0, 0)) == FALSE) { return FALSE; }


	//�T���v�������摜�̓ǂݍ���
	if (MY_IMAGE_LOAD_DIV_FILE(
		&sampleDivImage, IMAGE_SAMPLE_DIV_PATH,
		5, 2, (1200 / 5), (480 / 2),	//�摜�ɂ���Đ��l��ύX���邱�Ɓi�T���v���́A�c�ɂT��A���ɂQ�s�A��240�A����240�Ƃ����Ӗ��j
		GAME_WIDTH / 2, GAME_HEIGHT / 2, TRUE, GetRect(0, 0, 0, 0)) == FALSE) {
		return FALSE;
	}


	//���̉摜���R�R�œǂݍ��ނ���

	return TRUE;
}

/// <summary>
/// �摜���P�ǂݍ���
/// </summary>
/// <param name = "image">�ݒ肵�����摜�\����</param>
/// <param name = "path">�摜�̃t�@�C���p�X</param>
/// <param name = "x">X�ʒu</param>
/// <param name = "y">Y�ʒu</param>
/// <param name = "IsCenter">�摜��XY�̒��S�ɕ`�悵�����Ƃ���TRUE�ɂ���</param>
/// <param name = "margin">�摜�̓����蔻��̗]���i�����蔻������߂��肷��Ƃ��Ɏg�����I�j�f�t�H���g�̓i�V�I</param>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_IMAGE_LOAD_FILE(IMAGE* image, const char* path, int x, int y, BOOL IsCenter, RECT margin)
{
	//�T���v���摜�̓ǂݍ���
	image->handle = LoadGraph(path);
	if (image->handle == -1)
	{
		//�ǂݍ��݃G���[
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(image->handle, &image->pos.width, &image->pos.height);

	//XY�ʒu�𒆐S�ɂ������Ƃ�
	if (IsCenter == TRUE)
	{
		//�����񂹂ɂ��Đݒ�
		image->pos.x = x - image->pos.width / 2;
		image->pos.y = y - image->pos.height / 2;
		image->IsCenter = TRUE;
	}
	else
	{
		//���̂܂܈ʒu��ݒ�
		image->pos.x = x;
		image->pos.y = y;
		image->IsCenter = FALSE;
	}

	//�`�悷��
	image->IsDraw = TRUE;

	//�����蔻��̗]����ݒ�
	image->pos.margin = margin;

	//�摜�̓����蔻��̈ʒu���X�V����
	ImageCollUpdate(&image->pos);

	return TRUE;
}

/// <summary>
/// �摜�𕪊����ēǂݍ���
/// </summary>
/// <param name = "image">�ݒ肵�����摜�\����</param>
/// <param name = "path">�摜�̃t�@�C���p�X</param>
/// <param name = "x">X�ʒu</param>
/// <param name = "y">Y�ʒu</param>
/// 
/// <param name = "retu">��̕�����</param>
/// <param name = "gyo">�s�̕�����</param>
/// <param name = "width">�摜�̕����̕�</param>
/// <param name = "height">�摜�̕����̍���</param>
/// 
/// <param name = "IsCenter">�摜��XY�̒��S�ɕ`�悵�����Ƃ���TRUE�ɂ���</param>
/// <param name = "margin">�摜�̓����蔻��̗]���i�����蔻������߂��肷��Ƃ��Ɏg�����I�j�f�t�H���g�̓i�V�I</param>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_IMAGE_LOAD_DIV_FILE(
	DIVIMAGE* image, const char* path,
	int retu, int gyo, int width, int height,
	int x, int y, BOOL IsCenter, RECT margin)
{
	//�T���v���摜�̓ǂݍ���
	LoadDivGraph(path, (retu * gyo), retu, gyo, width, height, &image->handle[0]);

	image->DivMax = retu * gyo;	//���ۂɓǂݍ��񂾐���MAX�l�ɐݒ�

	if (image->handle[0] == -1)
	{
		//�ǂݍ��݃G���[
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//���ƍ������擾
	GetGraphSize(image->handle[0], &image->pos.width, &image->pos.height);

	//XY�ʒu�𒆐S�ɂ������Ƃ�
	if (IsCenter == TRUE)
	{
		//�����񂹂ɂ��Đݒ�
		image->pos.x = x - image->pos.width / 2;
		image->pos.y = y - image->pos.height / 2;
		image->IsCenter = TRUE;
	}
	else
	{
		//���̂܂܈ʒu��ݒ�
		image->pos.x = x;
		image->pos.y = y;
		image->IsCenter = FALSE;
	}

	//�`�悷��
	image->IsDraw = FALSE;

	//�����蔻��̗]����ݒ�
	image->pos.margin = margin;

	//�摜�̓����蔻��̈ʒu���X�V����
	ImageCollUpdate(&image->pos);

	return TRUE;
}

/// <summary>
/// �摜�̓����蔻��̈ʒu���X�V����
/// </summary>
/// <param name="pos">�ݒ肵�����摜�̈ʒu�ⓖ���蔻��</param>
/// <returns></returns>
VOID ImageCollUpdate(POSTION* pos)
{
	pos->coll.left = (pos->x) + pos->margin.left;						//�����蔻�荶�iX�ʒu�j
	pos->coll.top = (pos->y) + pos->margin.top;							//�����蔻���iY�ʒu�j
	pos->coll.right = (pos->x + pos->width) + pos->margin.right;		//�����蔻��E�iX�ʒu+���j
	pos->coll.bottom = (pos->y + pos->height) + pos->margin.bottom;		//�����蔻��E�iY�ʒu+�����j
	return;
}

/// <summary>
/// �摜�`��
/// </summary>
/// <param name="image">�`�悷��摜�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawImage(IMAGE image)
{
	//�摜���`��ł���Ƃ���
	if (image.IsDraw == TRUE)
	{
		DrawGraph(image.pos.x, image.pos.y, image.handle, TRUE);
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (DEBUG_MODE == TRUE)
	{
		//�����蔻���`��
		DrawRect(image.pos.coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// �����摜�̕`��
/// </summary>
/// <param name="image">�`�悷��摜�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawDivImage(DIVIMAGE* image)
{
	//�摜���`��ł���Ƃ���
	if (image->IsDraw == TRUE)
	{
		DrawGraph(image->pos.x, image->pos.y, image->handle[image->nowIndex], TRUE);

		//�A�j���[�V�����̃J�E���g�A�b�v
		if (image->AnimCnt < image->AnimCntMAX) { image->AnimCnt++; }
		else
		{
			//���ׂẴA�j���[�V������`�悵�I�������
			if (image->nowIndex == image->DivMax - 1)
			{
				//�A�j���[�V�������J��Ԃ��Ȃ��Ȃ��
				if (image->IsAnimLoop == FALSE)
				{
					image->IsDraw = FALSE;	//�`����~�߂�
				}
				image->AnimCnt = 0;		//�J�E���^0�N���A
				image->nowIndex = 0;	//�擪�ɖ߂�
			}
			//���̕����摜������Ƃ���
			else if (image->nowIndex < image->DivMax)
			{
				image->nowIndex++; //���̉摜��
			}
			image->AnimCnt = 0;	//�J�E���^0�N���A
		}
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (DEBUG_MODE == TRUE)
	{
		//�����蔻���`��
		DrawRect(image->pos.coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// �摜���܂Ƃ߂č폜
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

	for (int i = 0; i < sampleDivImage.DivMax; i++) { DeleteGraph(sampleDivImage.handle[i]); };

	//���̉摜���R�R�ō폜���邱��

	return;
}