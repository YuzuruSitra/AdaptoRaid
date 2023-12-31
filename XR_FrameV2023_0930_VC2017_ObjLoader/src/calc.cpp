//New Vector版
#include "platform.h"

#include <math.h>
#include <stdlib.h> //rand

#include "sim.h"
#include "calc.h"
#include "ezUtil.h"

//float PI = 3.14159;
const float RADIAN = M_PI / 180.0;
const float DEGREE = 180.0 / M_PI;
/*
#define OBJ_X(obj) (obj->x)
#define OBJ_Y(obj) (obj->y)
#define OBJ_Z(obj) (obj->z)
#define OBJ_ROLL(obj)  (obj->roll)
#define OBJ_PITCH(obj) (obj->pitch)
#define OBJ_YAW(obj)   (obj->yaw)
*/
void vector_fromAngle2d(float angle, vector_t *v)
{
	v->x = cosf(RADIAN * angle);
	v->y = sinf(RADIAN * angle);
	v->z = 0.0;
}
void vector_add(vector_t *a, vector_t *b, vector_t *out)
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
}
void vector_mult(vector_t *in, float scale, vector_t *out)
{
	out->x = scale * in->x;
	out->y = scale * in->y;
	out->z = scale * in->z;
}

float vector_norm(vector_t *v)
{
	return VectorNorm(v);
}

void setObjPos( ObjDataT *obj, float *pos )
{
	/*
	obj->x = pos[0];
	obj->y = pos[1];
	obj->z = pos[2];
	*/
	OBJ_X(obj) = pos[0];
	OBJ_Y(obj) = pos[1];
	OBJ_Z(obj) = pos[2];
}

void setObjPos(ObjDataT *obj, vector_t *pos)
{
	OBJ_X(obj) = pos->x;
	OBJ_Y(obj) = pos->y;
	OBJ_Z(obj) = pos->z;
}

void setObjRot( ObjDataT *obj, float *rot )
{
	/*
	obj->roll =  rot[0];
	obj->pitch = rot[1];
	obj->yaw =   rot[2];
	*/
	OBJ_ROLL(obj) = rot[0];
	OBJ_PITCH(obj)= rot[1];
	OBJ_YAW(obj)  = rot[2];
}
void getObjPos( ObjDataT *obj, float *pos )
{
	/*
	pos[0] = obj->x;
	pos[1] = obj->y;
	pos[2] = obj->z;
	*/
	pos[0] = OBJ_X(obj);
	pos[1] = OBJ_Y(obj);
	pos[2] = OBJ_Z(obj);
}
void getObjRot( ObjDataT *obj, float *rot )
{
	/*
	rot[0] = obj->roll;
	rot[1] = obj->pitch;
	rot[2] = obj->yaw;
	*/
	rot[0] = OBJ_ROLL(obj);
	rot[1] = OBJ_PITCH(obj);
	rot[2] = OBJ_YAW(obj);
}

void setObjColor( ObjDataT *obj, float red, float green, float blue )
{
	/*
	obj->red = red;
	obj->green = green;
	obj->blue = blue;
	*/
	obj->color.red = red;
	obj->color.green = green;
	obj->color.blue = blue;
	obj->color.alpha = 1.0;
}
void setObjPos( ObjDataT *obj, float x, float y, float z )
{
	/*
	obj->x = x;
	obj->y = y;
	obj->z = z;
	*/
	OBJ_X(obj) = x;
	OBJ_Y(obj) = y;
	OBJ_Z(obj) = z;
}
void setObjRot( ObjDataT *obj, float roll, float pitch, float yaw )
{
	/*
	obj->roll = roll;
	obj->pitch = pitch;
	obj->yaw = yaw;
	*/
	OBJ_ROLL(obj) = roll;
	OBJ_PITCH(obj)= pitch;
	OBJ_YAW(obj) =  yaw;
}
void setObjSize(ObjDataT *obj, float x, float y, float z)
{
	obj->xsize = x;
	obj->ysize = y;
	obj->zsize = z;
}
void copyObj( ObjDataT *src, ObjDataT *dst )
{
	/*
	setObjPos( dst, src->x, src->y, src->z );
	setObjRot( dst, src->roll, src->pitch, src->yaw );
	*/
	setObjPos( dst, OBJ_X(src), OBJ_Y(src), OBJ_Z(src) );
	setObjRot( dst, OBJ_ROLL(src), OBJ_PITCH(src), OBJ_YAW(src) );
	
	setObjColor( dst, src->color.red, src->color.green, src->color.blue );
	dst->base = src->base;
	dst->radius = src->radius;
	dst->state = src->state;
	dst->visible = src->visible;
	dst->move = src->move;
	dst->turn = src->turn;
	dst->xsize = src->xsize;
	dst->ysize = src->ysize;
	dst->zsize = src->zsize;
	return;
}

void initObj(ObjDataT *obj)
{
	setObjPos(obj, 0.0, 0.0, 0.0);
	setObjRot(obj, 0.0, 0.0, 0.0);
	setObjColor(obj, 0.0, 0.0, 0.0);
	setObjWorld(obj);
}

//▼オブジェクトaからオブジェクトbへの方向ベクトルを求める関数
//オブジェクト間の方向ベクトル
void DirectionAtoB( ObjDataT *a, ObjDataT *b, vector_t *dir )
{
	/*
	dir->x = b->x - a->x;
	dir->y = b->y - a->y;
	dir->z = b->z - a->z;
	*/
	
	dir->x = OBJ_X(b) - OBJ_X(a);
	dir->y = OBJ_Y(b) - OBJ_Y(a);
	dir->z = OBJ_Z(b) - OBJ_Z(a);
}
//▼ベクトルの大きさを計算する関数
//ベクトルの大きさ
float VectorNorm( vector_t *v )
{
	return sqrtf( v->x * v->x + v->y * v->y + v->z * v->z );
}
//▼距離を求める関数（「衝突判定」で作った関数の別バージョン）
//オブジェクト間距離
float DistanceAtoB( ObjDataT *a, ObjDataT *b )
{
	vector_t v;
 	DirectionAtoB( a, b, &v );
	return VectorNorm( &v );
}
//▼方向ベクトルから方位角と仰角を求める関数
float VectorToPolar( vector_t *v,  euler_t *angle )
{
	float d = sqrtf( v->x * v->x + v->z * v->z );
	angle->pitch = DEGREE * atan2f( v->y, d );
	angle->yaw = DEGREE * atan2f( - v->x, - v->z );
	return VectorNorm( v );
}
//▼方位角と仰角から単位方向ベクトルを求める関数
void PolarToVector( euler_t *angle, vector_t *v)
{
    float rad, l;

	rad = angle->pitch * RADIAN;
	v->y = sinf( rad );
	l = cosf( rad );

	rad = angle->yaw * RADIAN;
	v->x = - l * sinf( rad );
	v->z = - l * cosf( rad );

	return;
}
//▼オブジェクト間の角度（aからbを見込む方位角と仰角）
float EulerAtoB( ObjDataT *a, ObjDataT *b, euler_t *angle )
{
	vector_t dir;
	DirectionAtoB( a, b, &dir );
	VectorToPolar( &dir, angle );
	return VectorNorm( &dir );
}
//▼備考：構造体へのポインタを引数としている
void MoveObject( ObjDataT *obj )
{
	/*
	obj->yaw += obj->turn;
	obj->x -= obj->move * sinf( obj->yaw * RADIAN );
	obj->z -= obj->move * cosf( obj->yaw * RADIAN );
	obj->y += obj->move * sinf( obj->pitch * RADIAN ); ///// y方向の移動も考慮する場合
	*/
	
	OBJ_YAW(obj) += obj->turn;
	OBJ_X(obj) -= obj->move * sinf( OBJ_YAW(obj) * RADIAN );
	OBJ_Z(obj) -= obj->move * cosf( OBJ_YAW(obj) * RADIAN );
	OBJ_Y(obj) += obj->move * sinf( OBJ_PITCH(obj) * RADIAN ); ///// y方向の移動も考慮する場合
}
//▼物体同士の距離に基づいて衝突したかをチェックする関数
bool HitTest( ObjDataT *a, ObjDataT *b )
{
	if( DistanceAtoB( a, b ) < a->radius + b->radius ) return true;
	else return false;
}
//▼箱型オブジェクト（領域）と球状オブジェクト（領域）の衝突判定
bool HitTestBox(ObjDataT *box, ObjDataT *ball)
{
	//球体レベルの衝突判定でfalseなら衝突判定falseで終了
	//前提として、box全体を包む球体の半径としてradiusが設定されていること

	float boxradius, x, y, z;
	x = box->xsize / 2.0;
	y = box->ysize / 2.0;
	z = box->zsize / 2.0;
	boxradius = sqrtf(x * x + y * y + z * z);

	if( DistanceAtoB( box, ball ) > boxradius + ball->radius ){
		return false;
	}

	//箱の座標範囲
	/*
	float xmin = box->x - box->xsize / 2.0;
	float xmax = box->x + box->xsize / 2.0;
	float ymin = box->y - box->ysize / 2.0;
	float ymax = box->y + box->ysize / 2.0;
	float zmin = box->z - box->zsize / 2.0;
	float zmax = box->z + box->zsize / 2.0;
	*/
	
	float xmin = OBJ_X(box) - box->xsize / 2.0;
	float xmax = OBJ_X(box) + box->xsize / 2.0;
	float ymin = OBJ_Y(box) - box->ysize / 2.0;
	float ymax = OBJ_Y(box) + box->ysize / 2.0;
	float zmin = OBJ_Z(box) - box->zsize / 2.0;
	float zmax = OBJ_Z(box) + box->zsize / 2.0;

	//X座標の衝突判定
	//if( xmax < ball->x - ball->radius || xmin > ball->x + ball->radius){
	if( xmax < OBJ_X(ball) - ball->radius || xmin > OBJ_X(ball) + ball->radius){		
		return false;
	}
	//Y座標の衝突判定
	//if( ymax < ball->y - ball->radius || ymin > ball->y + ball->radius){
	if( ymax < OBJ_Y(ball) - ball->radius || ymin > OBJ_Y(ball) + ball->radius){		
		return false;
	}
	//Z座標の衝突判定
	//if( zmax < ball->z - ball->radius || zmin > ball->z + ball->radius){
	if( zmax < OBJ_Z(ball) - ball->radius || zmin > OBJ_Z(ball) + ball->radius){
		return false;
	}
	return true;
}

bool isHit( ObjDataT *a, ObjDataT *b )
{
	ObjDataT a_world, b_world;

	copyObj( a, &a_world );
	copyObj( b, &b_world );
	moveLocalToWorld( &a_world );
	moveLocalToWorld( &b_world );

	return HitTest( &a_world, &b_world );
}

bool isHitBox( ObjDataT *box, ObjDataT *ball )
{
	ObjDataT ball_world;
	ObjDataT box_world;

	copyObj( box, &box_world );
	copyObj( ball, &ball_world );
	//moveLocalToWorld( &box_world );
	moveLocalToWorld( &ball_world );
	moveWorldToLocal( &ball_world, box );

	return HitTestBox( box, &ball_world );
}
//====================================================================================================
//▼乱数生成関数
//最小値minと最大値maxの間の値をランダムに返す
float uniformRandom( float min, float max ){
    double r;
    r = (double)rand()/(double)RAND_MAX;
    r = r * ( max - min ) + min;
    return r;
}
//▼簡易ガウスノイズ関数
float gaussianRandom( float rmin, float rmax ){
    int i;
	float r = 0.0;
	const int n = 12;
	for( i = 0; i < n; i++ ){
		r += uniformRandom( rmin, rmax );
	}
	return r / n;
}

//▼整数型ランダム関数
int diceRandom(int min, int max)
{
	int n;
	n = (int)uniformRandom((float)min, (float)max+1.0);
	if (n > max) n = max;
	return n;
}

//-------------座標系階層構造操作関数
// setObjLocal
void setObjLocal( ObjDataT *target, ObjDataT *base )
{
	target->base = base;
	return;
}
// setObjWorld
void setObjWorld( ObjDataT *target )
{
	target->base = NULL;
	return;
}
//--------------- 
//ローカルからワールドへ
void moveLocalToWorld( ObjDataT *target )
{
	ObjDataT *base;
	base = target->base;
	while( base != NULL ){
		TransformLocalToWorld( base, target, target );
		base = base->base;
		setObjLocal( target, base );
	}
	setObjWorld( target );
	return;
}
//ワールドからローカルへ
void moveWorldToLocal( ObjDataT *target, ObjDataT *base )
{
	ObjDataT *b, world;

	b = base->base;
	if( b != NULL ){ //baseがワールドでなければワールドへ
		copyObj(base, &world);
		moveLocalToWorld( &world );
	}
	else {
		//good
		copyObj(base, &world);
		//bad
		//initObj(&world);
	}
	TransformWorldToLocal( &world, target, target );
	setObjLocal( target, base );
	return;
}

void getWorld(ObjDataT *target, ObjDataT *world)
{
	copyObj(target, world);
	moveLocalToWorld(world);
}

//----------------------------------- LocalToWorld
void TransformLocalToWorld( ObjDataT *base, ObjDataT *local, ObjDataT *world )
{
	//ObjDataT hand, target;
	float base_pos[3], base_rot[3], local_pos[3], local_rot[3];
	float world_pos[3], world_rot[3];

	/*
	base_pos[0] = base->x;
	base_pos[1] = base->y;
	base_pos[2] = base->z;
	base_rot[0] = base->roll;
	base_rot[1] = base->pitch;
	base_rot[2] = base->yaw;
	*/
	getObjPos( base, base_pos );
	getObjRot( base, base_rot );
	
	/*
	local_pos[0] = local->x;
	local_pos[1] = local->y;
	local_pos[2] = local->z;
	local_rot[0] = local->roll;
	local_rot[1] = local->pitch;
	local_rot[2] = local->yaw;
	*/
	getObjPos( local, local_pos );
	getObjRot( local, local_rot );
	
	ezUtil_Mult( base_pos, base_rot, local_pos, local_rot, world_pos, world_rot );

	/*
	world->x = world_pos[0];
	world->y = world_pos[1];
	world->z = world_pos[2];
	*/
	setObjPos( world, world_pos ); ////////0627
	
	/*
	world->roll = world_rot[0];
	world->pitch = world_rot[1];
	world->yaw = world_rot[2];
	*/
	setObjRot( world, world_rot ); ////////0627
}

void TransformWorldToLocal( ObjDataT *base, ObjDataT *target, ObjDataT *local )
{

	float matrix[16];

	glPushMatrix();
	glLoadIdentity();
	
	/*
	glRotatef( - base->roll, 0.0, 0.0, 0.0 );
	glRotatef( - base->pitch, 1.0, 0.0, 0.0 );
	glRotatef( - base->yaw, 0.0, 1.0, 0.0 );
	glTranslatef( - base->x,
			- base->y,
			- base->z );
	*/
	applyObjInverse( base );
	applyObjTransform( target );
	/*
	glTranslatef( target->x, target->y, target->z );
	glRotatef( target->yaw, 0.0, 1.0, 0.0 );
	glRotatef( target->pitch, 1.0, 0.0, 0.0 );
	glRotatef( target->roll, 0.0, 0.0, 1.0 );
	*/
	glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
	glPopMatrix();

	float rot[3],pos[3];
	ezUtil_getRot( matrix, rot );
	ezUtil_getPos( matrix, pos );
	/*
	local->x = pos[0];
	local->y = pos[1];
	local->z = pos[2];
	local->roll = rot[0];
	local->pitch = rot[1];
	local->yaw = rot[2];
	*/
	setObjPos( local, pos );
	setObjRot( local, rot );

	return;
}
//-----------------------------------------------
void TargetToObjData(TargetT *src, ObjDataT *dst)
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(src->pos.x,
		src->pos.y,
		src->pos.z);

	glRotatef(src->ori.angle,
		src->ori.x,
		src->ori.y,
		src->ori.z);

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	float rot[3], pos[3];
	ezUtil_getRot(matrix, rot);
	ezUtil_getPos(matrix, pos);
	/*
	dst->x = pos[0];
	dst->y = pos[1];
	dst->z = pos[2];
	*/
	setObjPos( dst, pos );
	/*
	dst->roll = rot[0];
	dst->pitch = rot[1];
	dst->yaw = rot[2];
	*/
	setObjRot( dst, rot );

	return;
}
//--------
void TransformLocalToWorldX(  TargetT *base, ObjDataT *local, ObjDataT *world )
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
    glTranslatef( base->pos.x,
			base->pos.y,
			base->pos.z );

	glRotatef( base->ori.angle,
			base->ori.x,
			base->ori.y,
			base->ori.z );

	/*
	glTranslatef( local->x, local->y, local->z );
	glRotatef( local->yaw, 0.0, 1.0, 0.0 );
	glRotatef( local->pitch, 1.0, 0.0, 0.0 );
	glRotatef( local->roll, 0.0, 0.0, 1.0 );
	*/
	applyObjTransform( local );
	
	glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
	glPopMatrix();

	float rot[3],pos[3];
	ezUtil_getRot( matrix, rot );
	ezUtil_getPos( matrix, pos );
	/*
	world->x = pos[0];
	world->y = pos[1];
	world->z = pos[2];
	world->roll = rot[0];
	world->pitch = rot[1];
	world->yaw = rot[2];
	*/
	setObjPos( world, pos );
	setObjRot( world, rot );

	return;
}

#if 0
void LocalForward(ObjDataT * target, vector_t * forward)
{
	vector_t forWardDir( 0,0,1);
	DirectionLocalToWorld(target, &forWardDir, forward);
}

void LocalUP(ObjDataT * target, vector_t * up)
{
	vector_t upDir(0,1,0 );
	DirectionLocalToWorld(target, &upDir, up);
}


void DirectionLocalToWorld(ObjDataT * target, vector_t * localDir, vector_t * worldDir) {
	
	//*
	float pos_origin[3];
	float pos_dir[3];

	matrix_t matrix[2];
	glPushMatrix(); {
		glLoadIdentity();

		applyObjTransform(target);
		glTranslatef(0,0,0);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix[0]);

		glTranslatef(localDir->x, localDir->y, localDir->z);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix[1]);
	}glPopMatrix();
	ezUtil_getPos(matrix[0], pos_origin);
	ezUtil_getPos(matrix[1], pos_dir);


	worldDir->x = pos_origin[0] - pos_dir[0];
	worldDir->y = pos_origin[1] - pos_dir[1];
	worldDir->z = pos_origin[2] - pos_dir[2];
	/*/
	ObjDataT dir;
	moveWorldToLocal(&dir, target);
	setObjPos(&dir,
		localDir->x,
		localDir->y,
		localDir->z);
	moveLocalToWorld(&dir);

	worldDir->x = dir.pos.x;
	worldDir->y = dir.pos.y;
	worldDir->z = dir.pos.z;
	//*/
	*worldDir = VectorNormalized(*worldDir);
}
#endif

//▼オブジェクトの位置と姿勢の幾何変換を行う関数
//プログラミング上のトピックス
//関数の引数として「構造体のポインタ」を与えるには？（アロー演算子）
//「構造体のポインタ」を使って構造体の中身「メンバー変数」を使うには？

/*----------------------------------------------*/
void applyObjTransform( ObjDataT *obj )
{
	if( obj->base != NULL ){
		applyObjTransform( obj->base );
	}
	/*
	glTranslatef( obj->x, obj->y, obj->z ); //位置
	glRotatef( obj->yaw,	0.0, 1.0, 0.0 );//ヨー（方位角）ｙ軸
	glRotatef( obj->pitch,	1.0, 0.0, 0.0 );//ピッチ（仰角）ｘ軸
	glRotatef( obj->roll,	0.0, 0.0, 1.0 );//ロール（傾き）ｚ軸
	*/
	
	glTranslatef( OBJ_X(obj), OBJ_Y(obj), OBJ_Z(obj) ); //位置
	glRotatef( OBJ_YAW(obj),	0.0, 1.0, 0.0 );//ヨー（方位角）ｙ軸
	glRotatef( OBJ_PITCH(obj),	1.0, 0.0, 0.0 );//ピッチ（仰角）ｘ軸
	glRotatef( OBJ_ROLL(obj),	0.0, 0.0, 1.0 );//ロール（傾き）ｚ軸
	return;
}

void applyObjInverse( ObjDataT *obj )
{
	/*
	glRotatef( - obj->roll,	0.0, 0.0, 1.0 );//ロール（傾き）ｚ軸
	glRotatef( - obj->pitch,1.0, 0.0, 0.0 );//ピッチ（仰角）ｘ軸
	glRotatef( - obj->yaw,	0.0, 1.0, 0.0 );//ヨー（方位角）ｙ軸
	glTranslatef( - obj->x, - obj->y, - obj->z ); //位置
	*/
	
	glRotatef( - OBJ_ROLL(obj),	0.0, 0.0, 1.0 );//ロール（傾き）ｚ軸
	glRotatef( - OBJ_PITCH(obj),1.0, 0.0, 0.0 );//ピッチ（仰角）ｘ軸
	glRotatef( - OBJ_YAW(obj),	0.0, 1.0, 0.0 );//ヨー（方位角）ｙ軸
	glTranslatef( - OBJ_X(obj), - OBJ_Y(obj), - OBJ_Z(obj) ); //位置
	if( obj->base != NULL ){
		applyObjInverse( obj->base );
	}	
	return;
}
//▼オブジェクトのカラーを適用する関数
void applyObjColor( ObjDataT *obj )
{
	applyMaterialColor( obj->color.red, obj->color.green, obj->color.blue );
}

//-----------------------------------------------
void Pointing( ObjDataT *xy, ObjDataT *z, vector_t *o )
{
	ObjDataT xy_copy;
	ObjDataT z_copy;

	vector_t n;
	vector_t p;
	vector_t u;
	vector_t q;

	n.x = 0.0;
	n.y = 0.0;
	n.z = 1.0;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;

	copyObj( xy, &xy_copy );
	copyObj( z,  &z_copy );
	moveWorldToLocal( &z_copy, &xy_copy );
	getZaxis( &z_copy, &u );
	getObjPos( &z_copy, &q );
	Intersection( &n, &p, &u, &q, o );

	return;
}
//-----------------------------------------------
void Intersection( vector_t *n, vector_t *p, vector_t *u, vector_t *q, vector_t *o )
{
	float t;
	float a, b, c, i, j, k;

	a = n->x;
	b = n->y;
	c = n->z;
	i = u->x;
	j = u->y;
	k = u->z;

	t = a*(p->x-q->x) + b*(p->y-q->y) + c*(p->z-q->z) / (a*i+b*j+c*k);
	o->x = q->x + i*t;
	o->y = q->y + j*t;
	o->z = q->z + k*t;

	return;
}
//-------------------------------------
void getMatrix( ObjDataT *obj, matrix_t mat )
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( obj->pos.x, obj->pos.y, obj->pos.z );
	glRotatef( obj->rot.yaw, 0.0, 1.0, 0.0 );
	glRotatef( obj->rot.pitch, 1.0, 0.0, 0.0 );
	glRotatef( obj->rot.roll, 0.0, 0.0, 1.0 );
	glGetFloatv( GL_MODELVIEW_MATRIX, mat );
	glPopMatrix();
}
void getObjPos( ObjDataT *obj, vector_t *pos )
{
	pos->x = obj->pos.x;
	pos->y = obj->pos.y;
	pos->z = obj->pos.z;
}
void getXaxis( ObjDataT *obj, vector_t *x )
{
	matrix_t mat;
	getMatrix( obj, mat );
	x->x = mat[ 0];
	x->y = mat[ 1];
	x->z = mat[ 2];
}
void getYaxis( ObjDataT *obj, vector_t *y )
{
	matrix_t mat;
	getMatrix( obj, mat );
	y->x = mat[ 4];
	y->y = mat[ 5];
	y->z = mat[ 6];
}
void getZaxis( ObjDataT *obj, vector_t *z )
{
	matrix_t mat;
	getMatrix( obj, mat );
	z->x = mat[ 8];
	z->y = mat[ 9];
	z->z = mat[10];
}
/*---------------------------------------------*/
