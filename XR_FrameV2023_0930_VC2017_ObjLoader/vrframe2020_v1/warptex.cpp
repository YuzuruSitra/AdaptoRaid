#include <stdarg.h>
#include "WarpTex.h"

WarpTex::WarpTex(void)
{
	m_width = 0;
	m_height = 0;
	m_centerX = 0;
	m_centerY = 0;
	m_kR = 0;
	m_kG = 0;
	m_kB = 0;
	m_debugMode = true;
}

WarpTex::~WarpTex(void)
{
}

#include <stdio.h>

//初期化処理
void WarpTex::init(void)
{
	//GL設定の保存
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//オフスクリーンレンダリング用テクスチャ生成
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DC_MAX_TEX_SIZE_X, DC_MAX_TEX_SIZE_Y, 0,
		GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//GL設定復元
	glPopAttrib();
}

//歪みの中心設定
void WarpTex::setCenter(float cx, float cy)
{
	m_centerX = cx;
	m_centerY = cy;

	updateVertices();
}

//歪みパラメータ設定
void WarpTex::setParams(float kR, float kG, float kB)
{
	m_kR = kR;
	m_kB = kB;
	m_kG = kG;

	updateVertices();
}

//★歪みの適用範囲
void WarpTex::setSize(float w, float h)
{
	m_width = w;
	m_height = h;

	updateVertices();
}

//☆現在のビューポートのサイズを取得
void WarpTex::getViewportSize( void )
{
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	m_width = v[2];
	m_height = v[3];
}

//頂点更新
void WarpTex::updateVertices(void)
{
	float dw = m_width / (float)DC_MESH_NUM_X;
	float dh = m_height / (float)DC_MESH_NUM_Y;
	float x, y;
	for (int i = 0; i<DC_MESH_NUM_X + 1; i++) {
		x = dw*i - m_width/2.0;
		for (int j = 0; j<DC_MESH_NUM_Y + 1; j++) {
			y = dh*j - m_height/2.0;
			float u = x - m_centerX;
			float v = y - m_centerY;
			
			m_verticesR[i][j].x = x + m_kR / (float)m_width*u*(u*u + v*v);
			m_verticesR[i][j].y = y + m_kR / (float)m_width*v*(u*u + v*v);
			m_verticesG[i][j].x = x + m_kG / (float)m_width*u*(u*u + v*v);
			m_verticesG[i][j].y = y + m_kG / (float)m_width*v*(u*u + v*v);
			m_verticesB[i][j].x = x + m_kB / (float)m_width*u*(u*u + v*v);
			m_verticesB[i][j].y = y + m_kB / (float)m_width*v*(u*u + v*v);

			/*
			m_verticesR[i][j].x = u + m_kR / (float)m_width*u*(u*u + v*v);
			m_verticesR[i][j].y = v + m_kR / (float)m_width*v*(u*u + v*v);
			m_verticesG[i][j].x = u + m_kG / (float)m_width*u*(u*u + v*v);
			m_verticesG[i][j].y = v + m_kG / (float)m_width*v*(u*u + v*v);
			m_verticesB[i][j].x = u + m_kB / (float)m_width*u*(u*u + v*v);
			m_verticesB[i][j].y = v + m_kB / (float)m_width*v*(u*u + v*v);
			*/
		}
	}
}

//デバッグモード切り替え
void WarpTex::switchDebugMode(void)
{
	m_debugMode = !m_debugMode;
}

//歪み補正◆元々の歪補正関数だが使わない＞UpdateとDrawを使うこと
void WarpTex::runDC(void)
{
	//GL設定の保存
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//MatrixMode取得
	GLint mode;
	glGetIntegerv(GL_MATRIX_MODE, &mode);

	//投影行列取得
	GLfloat p[16];
	glGetFloatv(GL_PROJECTION_MATRIX, p);

	//モデルビュー行列取得
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);

	//画面の解像度取得
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	m_width = v[2];
	m_height = v[3];

	//ライティング無効
	glDisable(GL_LIGHTING);

	//デプステスト無効
	glDisable(GL_DEPTH_TEST);

	//投影行列指定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_width, 0, m_height, -1, 1);

	//モデルビュー行列指定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//バックバッファをテクスチャにコピー
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_width, m_height);

	//画面クリア★削除
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//歪み補正画像描画
	renderUndistortedImage();

	glDisable(GL_TEXTURE_2D);

	//デバッグ表示
	if (m_debugMode) {
		Grid();
		Params();
	}
	//モデルビュー行列復元
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(m);

	//投影行列復元
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(p);

	//MatrixMode復元
	glMatrixMode(mode);

	//GL設定復元
	glPopAttrib();
}

//★画像更新
void WarpTex::Update(void)
{
	//バックバッファをテクスチャにコピー
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_width, m_height);
	/*★
	glCopyTexSubImage2D: バックバッファ領域からテクスチャに画像をコピーする
	void glCopyTexSubImage2D(	GLenum target,
	GLint level,
	GLint xoffset,
	GLint yoffset,
	GLint x,
	GLint y,
	GLsizei width,
	GLsizei height);
	x,y - Specify the window coordinates of the lower left corner of the rectangular region of pixels to be copied.
	width,height - Specify the width and height of the texture subimage.
	*/
	glDisable(GL_TEXTURE_2D);
}

//★画像描画
void WarpTex::Draw(float x, float y, float s )
{
	//GL設定の保存
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//投影行列指定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, m_width, 0, m_height, -1, 1);
	glOrtho( -m_width/2.0, m_width/2.0, -m_height/2.0, m_height/2.0, -1, 1);

	//モデルビュー行列指定
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); //★
	glLoadIdentity();

	glTranslatef( x * m_width, y * m_width, 0.0);
	glScalef(s, s, 1.0);

	//歪み補正画像描画
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	renderUndistortedImage();

	glDisable(GL_TEXTURE_2D);

	//デバッグ表示
	if (m_debugMode) {
		Grid();
		Params();
	}
	glPopMatrix(); //★
}

//歪み補正画像描画
void WarpTex::renderUndistortedImage(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//加算合成

	glColor3f(1.0, 0.0, 0.0);
	renderEachImage(m_verticesR);

	glColor3f(0.0, 1.0, 0.0);
	renderEachImage(m_verticesG);

	glColor3f(0.0, 0.0, 1.0);
	renderEachImage(m_verticesB);

	glDisable(GL_BLEND);
}

//各画像描画
void WarpTex::renderEachImage(vertex2f vertices[DC_MESH_NUM_X + 1][DC_MESH_NUM_Y + 1])
{
	float dw = m_width / (float)DC_MAX_TEX_SIZE_X / (float)DC_MESH_NUM_X;
	float dh = m_height / (float)DC_MAX_TEX_SIZE_Y / (float)DC_MESH_NUM_Y;
	for (int j = 0; j<DC_MESH_NUM_Y; j++) {
		for (int i = 0; i<DC_MESH_NUM_X; i++) {
			glBegin(GL_QUADS);
			glTexCoord2f(dw*i, dh*j);
			glVertex2f(vertices[i][j].x, vertices[i][j].y);
			glTexCoord2f(dw*i, dh*(j + 1));
			glVertex2f(vertices[i][j + 1].x, vertices[i][j + 1].y);
			glTexCoord2f(dw*(i + 1), dh*(j + 1));
			glVertex2f(vertices[i + 1][j + 1].x, vertices[i + 1][j + 1].y);
			glTexCoord2f(dw*(i + 1), dh*j);
			glVertex2f(vertices[i + 1][j].x, vertices[i + 1][j].y);
			glEnd();
		}
	}
}

//デバッグ表示
void WarpTex::Grid(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);

	glColor3d(1.0, 0.0, 0.0);
	for (int j = 0; j<DC_MESH_NUM_Y; j++) {
		for (int i = 0; i<DC_MESH_NUM_X; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(m_verticesR[i][j].x, m_verticesR[i][j].y);
			glVertex2f(m_verticesR[i][j + 1].x, m_verticesR[i][j + 1].y);
			glVertex2f(m_verticesR[i + 1][j + 1].x, m_verticesR[i + 1][j + 1].y);
			glVertex2f(m_verticesR[i + 1][j].x, m_verticesR[i + 1][j].y);
			glEnd();
		}
	}

	glColor3d(0.0, 1.0, 0.0);
	for (int j = 0; j<DC_MESH_NUM_Y; j++) {
		for (int i = 0; i<DC_MESH_NUM_X; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(m_verticesG[i][j].x, m_verticesG[i][j].y);
			glVertex2f(m_verticesG[i][j + 1].x, m_verticesG[i][j + 1].y);
			glVertex2f(m_verticesG[i + 1][j + 1].x, m_verticesG[i + 1][j + 1].y);
			glVertex2f(m_verticesG[i + 1][j].x, m_verticesG[i + 1][j].y);
			glEnd();
		}
	}

	glColor3d(0.0, 0.0, 1.0);
	for (int j = 0; j<DC_MESH_NUM_Y; j++) {
		for (int i = 0; i<DC_MESH_NUM_X; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(m_verticesB[i][j].x, m_verticesB[i][j].y);
			glVertex2f(m_verticesB[i][j + 1].x, m_verticesB[i][j + 1].y);
			glVertex2f(m_verticesB[i + 1][j + 1].x, m_verticesB[i + 1][j + 1].y);
			glVertex2f(m_verticesB[i + 1][j].x, m_verticesB[i + 1][j].y);
			glEnd();
		}
	}
	glDisable(GL_BLEND);

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2f( -m_width/4.0, 0.0);
	glVertex2f( m_width/4.0, 0.0);
	glVertex2f( 0.0, -m_height/4.0);
	glVertex2f( 0.0, m_height/4.0);
	glEnd();
	glLineWidth(1.0);
}
//デバッグ表示
void WarpTex::Params(void)
{
	glColor3d(0.0, 1.0, 0.5);
	float w = -m_width / 2;
	//float w = 0.0;
	float h = m_height / 2;
	//float h = m_height;
	renderString(w + 10, h - 20, "width:  %d", m_width);
	renderString(w + 10, h - 40, "height: %d", m_height);
	renderString(w + 10, h - 60, "center x: %f", m_centerX);
	renderString(w + 10, h - 80, "center y: %f", m_centerY);
	renderString(w + 10, h - 100, "kR: %f", m_kR);
	renderString(w + 10, h - 120, "kG: %f", m_kG);
	renderString(w + 10, h - 140, "kB: %f", m_kB);
}
//デバッグ用文字列描画（遅い）
void WarpTex::renderString(float x, float y, const char *_Format, ...)
{
	char str[128];
	va_list ap;
	va_start(ap, _Format);
	vsprintf(str, _Format, ap);
	va_end(ap);
	glRasterPos2f(x, y);
	char *ptr = str;
	while (*ptr) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ptr);
		++ptr;
	}
}