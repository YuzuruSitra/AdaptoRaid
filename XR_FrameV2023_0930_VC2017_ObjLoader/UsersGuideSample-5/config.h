#pragma once

//MREAL�̂Ƃ��g��
//MREAL�ł͂Ȃ��Ƃ��R�����g�ɂ���
#define MREALMODE

//�\�����
const bool fullscreen = false; //���t���X�N���[���t���O
//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
const bool no_cursor = false;  //���J�[�\����\���t���O
//�t���X�N���[����Ԃ̂Ƃ��J�[�\���͋����I�ɔ�\���ɂȂ�܂�

//HMD���[�h
const bool hmd = false; //��HMD���[�h�t���O
const bool distortion = true; //��HMD�c�␳�t���O

//��HMD���[�h���I�t�̂Ƃ����L�ݒ肪�@�\���܂�
const bool cylindrical = false; //���V�����h���J���t���O
const bool stereo = false;    //���X�e���I�t���O
//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
const bool swapeyes = false; //�����E�摜�̓���ւ� 
const float parallax = 0.0625; //�����E���ԋ���
const bool quadbuffer = false; //���t���V���b�^���K�l�Ή�
//���O���t�B�b�N�X�J�[�h�ɂ�NVIDIA Quadro���K�v�ł�
//�Ή����Ă��Ȃ�PC���ł́A�v���O�����������܂�

//�g���b�L���O�f�o�C�X
const bool use_tracker = false; //���g���b�J�[�t���O
const bool use_gyro = false; //���W���C���t���O

//�O���f�����́iusb�r�f�I�f�o�C�X�j
const bool usb_video = false; //��USB�r�f�I�f�o�C�X
