#ifndef __CALC_H__
#define __CALC_H__

typedef struct{
	float x, y, z;
} vector_t;

typedef struct{
	float roll, pitch, yaw;
} euler_t;

typedef float matrix_t[16];

typedef struct {
	float x, y, z, angle;
} OrientationT;

typedef struct {
	vector_t pos;
	OrientationT ori;
	int state;
	bool detected;
} TargetT;

typedef struct {
	vector_t pos;
	OrientationT ori;
	int state; //�O�t���[�������detected��Ԃ̕ω�
	bool detected;
	int markerID;
	int targetID;
} MarkerT;

typedef struct{
	vector_t pos;
	euler_t rot;
	int state;
	bool visible;
	float radius;
	float move;
	float turn;
} ObjDataT;

// set components
void vector_set( vector_t *v, float x, float y, float z );
void vector_get( const vector_t *src, float *dst );
void vector_copyFrom( vector_t *dst, const vector_t *src );
// diffence
void vector_Diff( vector_t *out, const vector_t *p0, const vector_t *p1 );
void vector_Add( vector_t *out, const vector_t *p0, const vector_t *p1 );

//r=�ړ��� pitch.yaw=�ړ����� v=float�^�C�v�̔z��x,y,z�����炤����
void PolarToVector( float r, float pitch, float yaw, float *v);
float EulerAtoB( ObjDataT *a, ObjDataT *b, euler_t *angle );

//��l���z�̗����֐�
float uniformRandom( float rmin, float rmax );
//���K���z�̗����֐�
float gaussianRandom( float rmin, float rmax );

bool HitTest( ObjDataT *a, ObjDataT *b );
//a�F �Փ˔���̑���
//b�F �Փ˔���̎��
//�߂�l�F �Փ˂����ꍇ��true���Ԃ�

float DistanceAtoB( vector_t *a, vector_t *b );
//�߂�l�F ������a��b�Ƃ̊Ԃ̋�����Ԃ�

void MoveObject( ObjDataT *obj );

void TransformLocalToWorld(ObjDataT *base, ObjDataT *local, ObjDataT *world);

//���g������
void TransformLocalToWorldX(TargetT *base, ObjDataT *local, ObjDataT *world);

//���~��������
void TransformLocalToWorld2(TargetT *base, ObjDataT *local, ObjDataT *world);

void TransformWorldToLocal(ObjDataT *base, ObjDataT *world, ObjDataT *local);

void TargetToObjData(TargetT *src, ObjDataT *obj);

#endif
