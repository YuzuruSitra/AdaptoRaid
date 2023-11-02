#ifndef __OBJECT_H__
#define __OBJECT_H__

#define VECTORMODE

//-------- object data
typedef struct _objdata_t{

#ifdef VECTORMODE
	vector_t pos;
	euler_t rot;
#else
    float x, y, z; ///// �����C�A�E�g�ʒu
	float roll, pitch, yaw; /////���p��
#endif

	int state; /////�����
	bool visible; ///��������

	//float red, green, blue; ///////���F
	color_t color;

	float move; //�����x�km/�t���[���l
	float turn; //�����񑬓x�i�e���x�j�k�x/�t���[���l

	float radius; //���Փ˔���p�̔��a
	float xsize, ysize, zsize; //�{�b�N�X�T�C�Y

	float enemyMoveTime; // �G�̈ړ��^�C�~���O����p
	float enemyGoRight; // �G�̍��E����p
	int enemyLastReachPoint; // �Ō�ɓ��B�����n�_
	int enemyLine; // �G�̏������Ă����
	int enemyRow; // �G�̏������Ă���s

	struct _objdata_t *base; //���e�m�[�h

	_objdata_t() {
		pos = vector_t();
		rot = euler_t();
		state = 0;
		visible = true;

		color = color_t();
		/*
		red = 0.75;
		green = 0.75;
		blue = 0.75;
		*/
		move = 0;
		turn = 0;

		radius = 1;
		xsize = 1;
		ysize = 1;
		zsize = 1;

		base = nullptr;
	}

} ObjDataT;

#ifdef VECTORMODE
#define OBJ_X(obj) ((obj)->pos.x)
#define OBJ_Y(obj) ((obj)->pos.y)
#define OBJ_Z(obj) ((obj)->pos.z)
#define OBJ_ROLL(obj)  ((obj)->rot.roll)
#define OBJ_PITCH(obj) ((obj)->rot.pitch)
#define OBJ_YAW(obj)   ((obj)->rot.yaw)
#else
#define OBJ_X(obj) ((obj)->x)
#define OBJ_Y(obj) ((obj)->y)
#define OBJ_Z(obj) ((obj)->z)
#define OBJ_ROLL(obj)  ((obj)->roll)
#define OBJ_PITCH(obj) ((obj)->pitch)
#define OBJ_YAW(obj)   ((obj)->yaw)
#endif

#endif

