#pragma once
//-------- common window parameters
typedef struct {
    int xo;
    int yo;
    int width;
    int height;
    float aspect;
	char *title;
} WindowDataT;

//-------- common mouse data
typedef struct {
	float xo, yo; // click position
	float xp, yp; // previous position
    float x,  y;  // current position
	float dx, dy; // movement
	float xAbs, yAbs; // absolute position
	float xRel, yRel; // relative position
	bool left;    // left button
	bool middle;  // middle button
 	bool right;   // right button - false:UP, true:DOWN
} MouseDataT;

//-------- common keyboard data
typedef struct {
	float x, y;
	bool charKey[128];//alpha-numeric printable ascii characters
	bool arrowLeft, arrowUp, arrowRight, arrowDown;
	bool spaceKey;
    bool funcKey[12]; //0:F1 - 11:F12
	bool pageUp, pageDown;
	bool home, end;
	bool insert;
} KeyDataT;

//-------- config data
typedef struct{
	//�\�����
	bool fullscreen; //���t���X�N���[���t���O
	//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
	bool no_cursor;  //���J�[�\�������t���O
	//���J�[�\�������̓t���X�N���[���̂Ƃ��̂ݐݒ�ł��܂�

	//HMD���[�h
	bool hmd; //��HMD���[�h�t���O
	bool distortion; //��HMD�c�␳�t���O

	//��HMD���[�h���I�t�̂Ƃ����L�ݒ肪�@�\���܂�
	bool cylindrical; //���V�����h���J���t���O
	bool stereo;    //���X�e���I�t���O
	//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
	bool swapeyes; //�����E�摜�̓���ւ� 
	float parallax; //�����E���ԋ���
	bool quadbuffer; //���t���V���b�^���K�l�Ή�
	//���O���t�B�b�N�X�J�[�h�ɂ�NVIDIA Quadro���K�v�ł�
	//�Ή����Ă��Ȃ�PC���ł́A�v���O�����������܂�

	//�g���b�L���O�f�o�C�X
	bool use_tracker; //���g���b�J�[�t���O
	bool use_gyro; //���W���C���t���O
} ConfigDataT;

class ezConfig: public ConfigDataT{
public:
	ezConfig(){

		//�\�����
		fullscreen = true; //���t���X�N���[���t���O
		//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
		no_cursor = false;  //���J�[�\�������t���O
		//���J�[�\�������̓t���X�N���[���̂Ƃ��̂ݐݒ�ł��܂�

		//HMD���[�h
		hmd = false; //��HMD���[�h�t���O
		distortion = true; //��HMD�c�␳�t���O

		//��HMD���[�h���I�t�̂Ƃ����L�ݒ肪�@�\���܂�
		cylindrical = false; //���V�����h���J���t���O
		stereo = true;    //���X�e���I�t���O
		//���X�e���I���[�h�̂Ƃ��ɂ͋����I�Ƀt���X�N���[���ɂȂ�܂�
		swapeyes = false; //�����E�摜�̓���ւ� 
		parallax = 0.0625; //�����E���ԋ���
		quadbuffer = false; //���t���V���b�^���K�l�Ή�
		//���O���t�B�b�N�X�J�[�h�ɂ�NVIDIA Quadro���K�v�ł�
		//�Ή����Ă��Ȃ�PC���ł́A�v���O�����������܂�

		//�g���b�L���O�f�o�C�X
		use_tracker = false; //���g���b�J�[�t���O
		use_gyro = true; //���W���C���t���O
	}
	~ezConfig(){
	};
private:

};
