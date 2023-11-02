#include "platform.h"

#include "ezUtil.h"
#include "sim.h"
#include "light.h"
#include "mymodel.h" //★
#include "depth.h"

extern SimDataT simdata;
extern ezDepth *kinect;

//-------- prototypes for user functions

void applyMaterialColor( float r, float g, float b );
void drawString(float x, float y, float z, float xscl, float yscl,
	const char *string);
/**/
/*---------------------------------------------------------------------------*/
void drawString(float x, float y, float z, float xscl, float yscl,
	const char *string)
{
	bool lighting = glIsEnabled(GL_LIGHTING);
	if (lighting) glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(xscl*0.001, yscl*0.001, 1.0);
	while (*string) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);
	}
	glPopMatrix();
	if( lighting ) glEnable(GL_LIGHTING);
	return;
}
/*--------------------------------------------------------- setMaterialColor
 * applyMaterialColor:
 *--------*/
void applyMaterialColor( float r, float g, float b )
{
    float diffuse[4];
    float specular[] = { 0.8, 0.8, 0.8, 1.0 };

	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = 1.0;

    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 32.0 );

    return;
}
/*----------------------------------------------------------- drawSolidCube
 * drawSolidCube:
 *--------*/
void drawSolidCube( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );   //オブジェクト基準位置調整
		glRotatef( 0.0, 0.0, 1.0, 0.0 ); //オブジェクト基準姿勢調整：ヨー角
		glRotatef( 0.0, 1.0, 0.0, 0.0 ); //オブジェクト基準姿勢調整：ピッチ角
		glRotatef( 0.0, 0.0, 0.0, 1.0 ); //オブジェクト基準姿勢調整：ロール角
		glutSolidCube( 1.0 );
	}
	glPopMatrix();
    return;
}
/*--------------------------------------------------------- drawSolidSphere
 * drawSolidSphere:
 *--------*/
void drawSolidSphere( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );    //オブジェクト基準位置調整
		glRotatef( 0.0, 0.0, 1.0, 0.0 );  //オブジェクト基準姿勢調整：ヨー角
		glRotatef( 90.0, 1.0, 0.0, 0.0 ); //オブジェクト基準姿勢調整：ピッチ角
		glRotatef( 0.0, 0.0, 0.0, 1.0 );  //オブジェクト基準姿勢調整：ロール角
		glutSolidSphere( 0.125, 18, 16 );   //半径，経度方向分割数，緯度方向分割数
	}
	glPopMatrix();
    return;
}
//----------------------------------------------- drawPlayer
void drawPlayer( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );    //オブジェクト基準位置調整
		glRotatef( 0.0, 0.0, 1.0, 0.0 );  //オブジェクト基準姿勢調整：ヨー角
		glRotatef( 180.0, 1.0, 0.0, 0.0 ); //オブジェクト基準姿勢調整：ピッチ角
		glRotatef( 0.0, 0.0, 0.0, 1.0 );  //オブジェクト基準姿勢調整：ロール角
		glutSolidCone( 0.5, 1.0, 6, 4 );   //半径，経度方向分割数，緯度方向分割数
	}
	glPopMatrix();
}

void drawExtVideo(void)
{
	glPushMatrix();
	simdata.extvideo->draw( -0.5, -0.5, 0.0, 0.32, 0.24, 1.0, 0.0);
	glPopMatrix();
}

void drawMovie(void)
{
	glPushMatrix();
	glScalef(simdata.movie_screen.xsize, simdata.movie_screen.ysize, simdata.movie_screen.zsize);
	glTranslatef(-0.5, 0.5, 0.0);
	simdata.movie->frame->draw();
	glPopMatrix();
}
void drawHandR( void )
{
	glPushMatrix();
	applyObjColor( &simdata.handR );
	applyObjTransform( &simdata.handR );
	drawHandRmodel();//mymodels.cppで作った描画関数
	//衝突判定範囲がわかりやすいようワイヤ球描画
	glutWireSphere( simdata.handR.radius, 8, 6 );
	////drawMovie();
	glPopMatrix();
}
void drawHandL( void )
{
	glPushMatrix();
	applyObjColor( &simdata.handL );
	applyObjTransform( &simdata.handL );
	drawHandLmodel();//mymodels.cppで作った描画関数
	//衝突判定範囲がわかりやすいようワイヤ球描画
	glutWireSphere( simdata.handL.radius, 8, 6 );
	if( usb_video ) drawExtVideo();
	glPopMatrix();
}


/*---------------------------------------------------------------- Lighting
 * Lighing
 */
void Lighting( void )
{
	static float lmodelAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static float lmodelLocalviewer[] = { 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelAmbient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodelLocalviewer);

	//▼メインライトON: R, G, B
	MainLight( GL_LIGHT0, 0.8, 0.8, 0.8 );

	//▼サブライトON: R, G, B
	SubLight( GL_LIGHT1, 0.2, 0.2, 0.2 );
}
void setFog( void )
{
	//▼フォグON: R, G, B, 密度, 開始距離, 終了距離
	Fog( GL_EXP, 
		simdata.air_color[0],
		simdata.air_color[1],
		simdata.air_color[2], 
		simdata.air_color[3], 
		simdata.clip_near, simdata.clip_far );
}
/*-------------------------------------------------------------- HeadLight
 * HeadLight
 */
void HeadLight( void )
{
	/*
	glPushMatrix();
	glTranslatef( simdata.body.x, simdata.body.y, simdata.body.z );
	glRotatef( simdata.body.yaw, 0.0, 1.0, 0.0 );
	glRotatef( simdata.body.pitch, 1.0, 0.0, 0.0 );
	glRotatef( simdata.body.roll, 0.0, 0.0, 1.0 );
	*/

	glPushMatrix();
	//glLoadIdentity();
	//applyObjTransform( &simdata.player ); ////////0627
	applyObjTransform( &simdata.head ); ////////0627

	PointLight( GL_LIGHT2, 0.75, 0.75, 0.75, simdata.clip_far * 2.0 );
	//▼ヘッドライトON: R, G, B, 照度半減距離[m]
	//SpotLight( GL_LIGHT2, 1.0, 1.0, 1.0, simdata.clip_far, 25.0, 32 );

	glPopMatrix();
}
/*---------------------------------------------------------------- PreDraw
 * PreDraw:
 *--------*/
void PreDraw(void)
{
}
/*--------------------------------------------------------------- PostDraw
* PostDraw: 3Dのシーンに重ねて2Dの情報を表示する関数
*--------*/
void PostDraw(void)
{
	//文字を描画するコード一式など
	//ライティングなし
	//2Dの情報画面
	//2Dの投影変換を設定する（並行投影）
	glMatrixMode(GL_PROJECTION);//投影変換マトリクス編集モード
	glLoadIdentity();//初期化
	glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0); //画面全体を0.0～1.0の範囲に設定
	glMatrixMode(GL_MODELVIEW);//モデリング変換マトリクスモード
	glLoadIdentity();//初期化

	//お好きに描画
	//char time_message[32];
	//sprintf(time_message, "time = %d", simdata.time );
	//glColor3f( 1.0, 1.0, 1.0 );
	//drawString(0.1, 0.1, 0.0, 0.25, 0.5, time_message );

	//char head_xyz[128];
	//sprintf(head_xyz, "POS: %8.3f\t%8.3f\t%8.3f", 
	//	simdata.head.pos.x,
	//	simdata.head.pos.y,
	//	simdata.head.pos.z);
	//glColor3f( 1.0, 1.0, 1.0 );
	//drawString(0.1, 0.2, 0.0, 0.25, 0.5, head_xyz );

	//sprintf(head_xyz, "ROT: %8.3f\t%8.3f\t%8.3f", 
	//	simdata.head.rot.roll,
	//	simdata.head.rot.pitch,
	//	simdata.head.rot.yaw);
	//glColor3f( 1.0, 1.0, 1.0 );
	//drawString(0.1, 0.3, 0.0, 0.25, 0.5, head_xyz );
}

// 砲台(プレイヤー)の描画
void drawFort(void)
{
	glTranslatef(0.0, 0.0, 0.0);   //オブジェクト基準位置調整
	glRotatef(0.0, 0.0, 1.0, 0.0); //オブジェクト基準姿勢調整：ヨー角
	glRotatef(0.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
	glRotatef(0.0, 0.0, 0.0, 1.0); //オブジェクト基準姿勢調整：ロール角
	glutSolidCube(1.0);
	glutWireCube(simdata.fort.radius);
}

void drawFortTop(void)
{
	glTranslatef(0.0, 0.0, 0.0);   //オブジェクト基準位置調整
	glRotatef(0.0, 0.0, 1.0, 0.0); //オブジェクト基準姿勢調整：ヨー角
	glRotatef(0.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
	glRotatef(0.0, 0.0, 0.0, 1.0); //オブジェクト基準姿勢調整：ロール角
	glutSolidCube(1.0);
	glutWireCube(simdata.fortTop.radius);
}

// 砲台の弾の描画
void drawFortBullets(void)
{
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (!simdata.fortBullets[i].visible) continue;

		glPushMatrix();
		{
			applyObjTransform(&simdata.fortBullets[i]);
			applyObjColor(&simdata.fortBullets[i]);

			glScalef(simdata.fortBullets[i].xsize, simdata.fortBullets[i].ysize, simdata.fortBullets[i].zsize);
			glTranslatef(0.0, 0.0, 0.0);    //オブジェクト基準位置調整
			glRotatef(0.0, 0.0, 1.0, 0.0);  //オブジェクト基準姿勢調整：ヨー角
			glRotatef(180.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
			glRotatef(0.0, 0.0, 0.0, 1.0);  //オブジェクト基準姿勢調整：ロール角

			glutSolidCube(1);
			glutWireCube(simdata.fortBullets[i].radius);
		}
		glPopMatrix();
	}
}


// 侵略者の描画
void drawEnemies(void)
{
	for (int i = 0; i < N_ENEMIES; i++)
	{
		if (!simdata.enemies[i].visible) continue;
		
		glPushMatrix();
		{
			applyObjTransform(&simdata.enemies[i]);
			applyObjColor(&simdata.enemies[i]);

			glScalef(simdata.enemies[i].xsize, simdata.enemies[i].ysize, simdata.enemies[i].zsize);
			glTranslatef(0.0, 0.0, 0.0);    //オブジェクト基準位置調整
			glRotatef(0.0, 0.0, 1.0, 0.0);  //オブジェクト基準姿勢調整：ヨー角
			glRotatef(180.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
			glRotatef(0.0, 0.0, 0.0, 1.0);  //オブジェクト基準姿勢調整：ロール角

			glutSolidCube(1);
			glutWireCube(simdata.enemies[i].radius);
		}
		glPopMatrix();
	}
}

// 侵略者の弾の描画
void drawEnemyBullets(void)
{
	for (int i = 0; i < N_ENEMY_BULLETS; i++)
	{
		if (!simdata.enemyBullets[i].visible) continue;

		glPushMatrix();
		{
			applyObjTransform(&simdata.enemyBullets[i]);
			applyObjColor(&simdata.enemyBullets[i]);

			glScalef(simdata.enemyBullets[i].xsize, simdata.enemyBullets[i].ysize, simdata.enemyBullets[i].zsize);
			glTranslatef(0.0, 0.0, 0.0);    //オブジェクト基準位置調整
			glRotatef(0.0, 0.0, 1.0, 0.0);  //オブジェクト基準姿勢調整：ヨー角
			glRotatef(180.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
			glRotatef(0.0, 0.0, 0.0, 1.0);  //オブジェクト基準姿勢調整：ロール角

			glutSolidCube(1);
			glutWireCube(simdata.enemyBullets[i].radius);
		}
		glPopMatrix();
	}
}

// シールドの描画
void drawShields(void)
{
	for (int i = 0; i < SHIELDS; i++)
	{
		if (!simdata.shields[i].visible) continue;

		glPushMatrix();
		{
			applyObjTransform(&simdata.shields[i]);
			applyObjColor(&simdata.shields[i]);

			glScalef(simdata.shields[i].xsize, simdata.shields[i].ysize, simdata.shields[i].zsize);
			glTranslatef(0.0, 0.0, 0.0);    //オブジェクト基準位置調整
			glRotatef(0.0, 0.0, 1.0, 0.0);  //オブジェクト基準姿勢調整：ヨー角
			glRotatef(180.0, 1.0, 0.0, 0.0); //オブジェクト基準姿勢調整：ピッチ角
			glRotatef(0.0, 0.0, 0.0, 1.0);  //オブジェクト基準姿勢調整：ロール角

			glutSolidCube(1);
			glutWireCube(simdata.shields[i].radius);
		}
		glPopMatrix();
	}
}

/**/
/*---------------------------------------------------------------- DrawScene
 * DrawScene:
 *--------*/
void DrawScene( void )
{
	glDisable( GL_LIGHTING );
	glColor3f( 0.5, 0.5, 0.5 );
	ezUtil_drawGrid( 100, 100.0 );
	ezUtil_drawAxes( 100.0 );

	//kinect->drawPoints( true );

	//simdata.camL->draw();

	glEnable( GL_LIGHTING );

	// glPushMatrix();
	// applyObjTransform( &simdata.player );
	// drawHandL();
	// drawHandR();

	// glPopMatrix();

	// 心臓の読み込み
	//glPushMatrix();
	//{
	//	applyObjTransform( &simdata.sphere ); //ポインタにはアドレス「＆」をつけて、引数にする
	//	applyObjColor( &simdata.sphere );
	//	//drawSolidSphere();
	//	//drawFish(); //mymodels.cpp
	//	drawHeartModel();
	//}
	//glPopMatrix();


	// fortの描画
	glPushMatrix();
	{
		applyObjTransform( &simdata.fort );
		applyObjColor( &simdata.fort );
		glScalef( simdata.fort.xsize, simdata.fort.ysize, simdata.fort.zsize );
		drawFort();
	}
	glPopMatrix();

	glPushMatrix();
	{
		applyObjTransform(&simdata.fortTop);
		applyObjColor(&simdata.fortTop);
		glScalef(simdata.fortTop.xsize, simdata.fortTop.ysize, simdata.fortTop.zsize);
		drawFortTop();
	}
	glPopMatrix();

	drawFortBullets();

	drawEnemies();
	drawEnemyBullets();

	drawShields();

	/*
	//// プレイヤを描画する
	glPushMatrix();
	{
		applyObjTransform( &simdata.player );
		applyObjColor( &simdata.player );
		//drawPlayer();
	}
	glPopMatrix();
	*/

    return;
}
