//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"  //DxLib���g�����͕K�v

//�}�N����`
#define GAME_TITLE "�Q�[���^�C�g��"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_COLOR 32

#define GAME_ICON_ID  333

#define GAME_WINDOW_BAR 0
// �v���O������ �� ����n�܂�܂�
//Windows�̃v���O�������@ = (WinAPI)�œ����Ă���
//DxLib�́ADirectx �Ƃ����A�Q�[���v���O�������ȒP�Ɏg����d�g��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);   //Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);
	SetMainWindowText(GAME_TITLE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	SetBackgroundColor(255, 255, 255);
	SetWindowIconID(GAME_ICON_ID);
	SetWindowStyleMode(GAME_WINDOW_BAR);     //�E�B���h�E�o�[�̏��
	SetWaitVSyncFlag(TRUE);                  //�f�B�X�v���C�̐���������L���ɂ���
	SetAlwaysRunFlag(TRUE);

	
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	//�l�p�̈ʒu�����߂�
	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;

	//�l�p�̑傫�������߂�
	int width = 32;
	int height = 32;

	int radius = 100;

	int Speed = 5;
	int XSpeed = Speed;
	int YSpeed = Speed;
	SetDrawScreen(DX_SCREEN_BACK);

	//�������[�v
	while (1)
	{
		if (CheckHitKeyAll() != 0)
		{
			break;  //�������[�v�𔲂���
		}

		//���b�Z�[�W���󂯎�葱����
		if (ProcessMessage() != 0)
		{
			break;  //�������[�v�𔲂���
		}


		//��ʂ���������
		if (ClearDrawScreen() != 0) { break; }


		//�l�p��`��
		//DrawBox(
		//	X, Y, X + width, Y + height,
		//	GetColor(255, 0, 0),   //�F���擾
		//	TRUE                   //�h��Ԃ�?
		//);


		//�~��`��
		DrawCircle(
			X, Y,  radius,
			GetColor(0, 255, 0),
			FALSE, 5
		);

		X += XSpeed;

		Y += YSpeed;

		if (X - radius < 0 || X+ width > GAME_WIDTH)
		{
			XSpeed = -XSpeed;//�ړ���������𔽓]

			if (XSpeed > 0) {XSpeed += 2; }
			else if (XSpeed < 0) { XSpeed -= 2; }
		}
		ScreenFlip();
	}

	if (Y - radius < 0 || Y + height > GAME_HEIGHT)
	
	{
		YSpeed = -YSpeed;//�ړ���������𔽓]

		if (YSpeed > 0) { YSpeed += 2; }
		else if (YSpeed < 0) { YSpeed -= 2; }
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}