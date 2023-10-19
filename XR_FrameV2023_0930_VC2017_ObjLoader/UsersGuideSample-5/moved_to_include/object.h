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

	float red, green, blue; ///////���F

	float move; //�����x�km/�t���[���l
	float turn; //�����񑬓x�i�e���x�j�k�x/�t���[���l

	float radius; //���Փ˔���p�̔��a
	float xsize, ysize, zsize; //�{�b�N�X�T�C�Y

	struct _objdata_t *base; //���e�m�[�h

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
