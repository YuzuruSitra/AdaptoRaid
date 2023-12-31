#ifndef __OBJECT_H__
#define __OBJECT_H__

#define VECTORMODE

//-------- object data
typedef struct _objdata_t{

#ifdef VECTORMODE
	vector_t pos;
	euler_t rot;
#else
    float x, y, z; ///// ◆レイアウト位置
	float roll, pitch, yaw; /////◆姿勢
#endif

	int state; /////◆状態
	bool visible; ///◆可視属性

	//float red, green, blue; ///////◆色
	color_t color;

	float move; //◆速度〔m/フレーム〕
	float turn; //◆旋回速度（各速度）〔度/フレーム〕

	float radius; //◆衝突判定用の半径
	float xsize, ysize, zsize; //ボックスサイズ

	float enemyMoveTime; // 敵の移動タイミング制御用
	float enemyGoRight; // 敵の左右制御用
	int enemyLastReachPoint; // 最後に到達した地点
	int enemyLine; // 敵の所属している列
	int enemyRow; // 敵の所属している行

	struct _objdata_t *base; //★親ノード

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

