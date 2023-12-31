#ifndef __CALC_H__
#define __CALC_H__

#include <math.h>

#if 0
#include "vector.h"
#include "euler.h"
#include "color.h"
#include "matrix.h"
#else
//▼ベクトル
typedef struct _vector_t{
	float x, y, z;
	_vector_t( float _x = 0.0, float _y = 0.0, float _z = 0.0 ) { x = _x; y = _y; z = _z; }
} vector_t;
//▼オイラー角による回転の表現
typedef struct _euler_t{
	float roll, pitch, yaw;
	_euler_t() { roll = 0.0; pitch = 0.0; yaw = 0.0; }
} euler_t;
//▼色
typedef struct _color_t{
	float red, green, blue, alpha;
	_color_t() { red = 0.75; green = 0.75; blue = 0.75; alpha = 1.0; }
} color_t;
//▼マトリクス
typedef float matrix_t[16];
#endif

#include "object.h"

///////////////////////////////
//▼オリエンテーション構造体
typedef struct {
	float x, y, z, angle;
} OrientationT;
//▼MREALターゲット構造体
typedef struct {
	vector_t pos;
	OrientationT ori;
	int state;
	bool detected;
} TargetT;

//▼MREALマーカ構造体
typedef struct {
	vector_t pos;
	OrientationT ori;
	int state; //前フレームからのdetected状態の変化
	bool detected;
	int markerID;
	int targetID;
} MarkerT;

//---- vector演算関数
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

void setObjPos(ObjDataT *obj, vector_t *pos);
void getObjPos(ObjDataT *obj, vector_t *pos);
void setObjSize(ObjDataT *obj, float x, float y, float z);

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

void moveToWorld( ObjDataT *target );
void moveToLocal( ObjDataT *target, ObjDataT *base );

void getWorld(ObjDataT *target, ObjDataT *world);

bool HitTest( ObjDataT *a, ObjDataT *b );
//a： 衝突判定の相手
//b： 衝突判定の主体
//戻り値： 衝突した場合にtrueが返る
bool HitTestBox( ObjDataT *box, ObjDataT *ball );
bool isHit( ObjDataT *a, ObjDataT *b );
bool isHitBox(ObjDataT *box, ObjDataT *ball);

//ローカル座標系からワールド座標系への変換
void TransformLocalToWorld( ObjDataT *base, ObjDataT *local, ObjDataT *world );
//ワールド座標系からローカル座標系への変換
void TransformWorldToLocal( ObjDataT *base, ObjDataT *world, ObjDataT *local );

//---- ターゲット処理用関数
void TargetToObjData(TargetT *src, ObjDataT *obj);
void TransformLocalToWorldX(TargetT *base, ObjDataT *local, ObjDataT *world);

//---- ベクトル処理

void DirectionLocalToWorld(ObjDataT * target, vector_t * localDir, vector_t * worldDir);

void LocalForward(ObjDataT *target, vector_t *forward);

void LocalUP(ObjDataT * target, vector_t *up);


//---- オブジェクトの属性を設定・適用する関数
//▼オブジェクトの位置と姿勢の幾何変換を行う関数
void applyObjTransform(ObjDataT *obj);
void applyObjInverse(ObjDataT *obj);
//▼オブジェクトのカラーを指定する関数
void applyObjColor(ObjDataT *obj);
void applyMaterialColor(float red, float green, float blue);

void Pointing( ObjDataT *xy, ObjDataT *z, vector_t *p );

void getMatrix( ObjDataT *obj, matrix_t *mat );
void getOrigin( ObjDataT *obj, vector_t *o );
void getXaxis( ObjDataT *obj, vector_t *x );
void getYaxis( ObjDataT *obj, vector_t *y );
void getZaxis( ObjDataT *obj, vector_t *z );

void Intersection( vector_t *n, vector_t *p, vector_t *u, vector_t *q, vector_t *x );

#endif
