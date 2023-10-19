#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "vector.h"
#include "euler.h"
#include "color.h"

//-------- object data
typedef struct _objdata_t {

	//float x, y, z; ///// �����C�A�E�g�ʒu
	vector_t pos;
	vector_t prePos;
	//float roll, pitch, yaw; /////���p��
	euler_t rot;
	int state; /////�����
	bool visible; ///��������

	color_t color; ///////���F

	float move; //�����x�km/�t���[���l
	float turn; //�����񑬓x�i�e���x�j�k�x/�t���[���l

	float radius; //���Փ˔���p�̔��a
	float xsize, ysize, zsize; //�{�b�N�X�T�C�Y

	struct _objdata_t *base; //���e�m�[�h

	_objdata_t() {
		pos = vector_t(0, 0, 0);
		prePos = vector_t(0,0,0);
		rot = euler_t();
		state = 0;
		visible = true;
		
		color.red = 1;
		color.green = 1;
		color.blue = 1;
		
		move = 0;
		turn = 0;

		radius = 1;
		xsize = 1;
		ysize = 1;
		zsize = 1;

		base = nullptr;
	}

} ObjDataT;

#endif
