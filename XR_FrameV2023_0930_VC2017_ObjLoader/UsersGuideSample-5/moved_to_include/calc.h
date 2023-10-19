#ifndef __CALC_H__
#define __CALC_H__

#include <math.h>

//���x�N�g��
typedef struct {
	float x, y, z;
} vector_t;
//���I�C���[�p�ɂ���]�̕\��
typedef struct {
	float roll, pitch, yaw;
} euler_t;
//���F
typedef struct{
	float red, blue, green, alpha;
} color_t;
//���}�g���N�X
typedef float matrix_t[16];

#include "object.h"

///////////////////////////////
//���I���G���e�[�V�����\����
typedef struct {
	float x, y, z, angle;
} OrientationT;
//��MREAL�^�[�Q�b�g�\����
typedef struct {
	vector_t pos;
	OrientationT ori;
	int state;
	bool detected;
} TargetT;

//��MREAL�}�[�J�\����
typedef struct {
	vector_t pos;
	OrientationT ori;
	int state; //�O�t���[�������detected��Ԃ̕ω�
	bool detected;
	int markerID;
	int targetID;
} MarkerT;

//---- vector���Z�֐�
void vector_fromAngle2d(float angle, vector_t *v);
void vector_add(vector_t *a, vector_t *b, vector_t *out);
void vector_mult(vector_t *in, float scale, vector_t *out);
float vector_norm(vector_t *v);

void setObjPos( ObjDataT *obj, float *pos );
void setObjRot( ObjDataT *obj, float *rot );
void getObjPos( ObjDataT *obj, float *pos );
void getObjRot( ObjDataT *obj, float *rot );
void copyObj( ObjDataT *src, ObjDataT *dst );
void initObj(ObjDataT *obj);

void setObjColor( ObjDataT *obj, float red, float green, float blue );
void setObjPos( ObjDataT *obj, float x, float y, float z );
void setObjRot( ObjDataT *obj, float roll, float pitch, float yaw );

void DirectionAtoB( ObjDataT *a, ObjDataT *b, vector_t *dir );
float VectorNorm( vector_t *v );
float DistanceAtoB( ObjDataT *a, ObjDataT *b );
float VectorToPolar( vector_t *v,  euler_t *angle );
void PolarToVector( euler_t *angle, vector_t *v);
float EulerAtoB( ObjDataT *a, ObjDataT *b, euler_t *angle );

void MoveObject( ObjDataT *obj );

float uniformRandom( float min, float max);
float gaussianRandom( float rmin, float rmax );
int diceRandom(int min, int max);

void setObjLocal( ObjDataT *target, ObjDataT *base );
void setObjWorld( ObjDataT *target );
void moveLocalToWorld( ObjDataT *target );
void moveWorldToLocal( ObjDataT *target, ObjDataT *base );

void getWorld(ObjDataT *target, ObjDataT *world);

bool HitTest( ObjDataT *a, ObjDataT *b );
//a�F �Փ˔���̑���
//b�F �Փ˔���̎��
//�߂�l�F �Փ˂����ꍇ��true���Ԃ�
bool HitTestBox( ObjDataT *box, ObjDataT *ball );
bool isHit( ObjDataT *a, ObjDataT *b );

//���[�J�����W�n���烏�[���h���W�n�ւ̕ϊ�
void TransformLocalToWorld( ObjDataT *base, ObjDataT *local, ObjDataT *world );
//���[���h���W�n���烍�[�J�����W�n�ւ̕ϊ�
void TransformWorldToLocal( ObjDataT *base, ObjDataT *world, ObjDataT *local );

//---- �^�[�Q�b�g�����p�֐�
void TargetToObjData(TargetT *src, ObjDataT *obj);
void TransformLocalToWorldX(TargetT *base, ObjDataT *local, ObjDataT *world);

void applyObjTransform(ObjDataT *obj);
void applyObjInverse(ObjDataT *obj);
void applyObjColor(ObjDataT *obj);
void applyMaterialColor(float red, float green, float blue);

#endif
