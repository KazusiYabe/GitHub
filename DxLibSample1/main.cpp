//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"  //DxLib���g�����͕K�v

#include "keyboard.h"
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
	
	SetDrawScreen(DX_SCREEN_BACK);

	//�������[�v
	while (1)
	{
		//���b�Z�[�W���󂯎�葱����
		if (ProcessMessage() != 0){break;  //�������[�v�𔲂���}
		if (ClearDrawScreen() != 0) { break; }  //��ʂ���������

		//�L�[�{�[�h���͂̍X�V
		AllKeyUpdate();
		
		//�L�[����
		if (KeyDown(KEY_INPUT_UP) == TRUE)
		{
			Y--;  //��Ɉړ�
		}
		if (KeyDown(KEY_INPUT_DOWN) == TRUE)
		{
			Y++;  //���Ɉړ�
		}
		if (KeyDown(KEY_INPUT_LEFT) == TRUE)
		{
			X--;  //���Ɉړ�
		}
		if (KeyDown(KEY_INPUT_RIGHT) == TRUE)
		{
			X++;  //�E�Ɉړ�
		}

		DrawCircle(X, Y, radius, GetColor(255, 255, 0), TRUE);

		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}