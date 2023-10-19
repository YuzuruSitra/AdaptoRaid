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

//����������
void WarpTex::init(void)
{
	//GL�ݒ�̕ۑ�
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//�I�t�X�N���[�������_�����O�p�e�N�X�`������
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DC_MAX_TEX_SIZE_X, DC_MAX_TEX_SIZE_Y, 0,
		GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//GL�ݒ蕜��
	glPopAttrib();
}

//�c�݂̒��S�ݒ�
void WarpTex::setCenter(float cx, float cy)
{
	m_centerX = cx;
	m_centerY = cy;

	updateVertices();
}

//�c�݃p�����[�^�ݒ�
void WarpTex::setParams(float kR, float kG, float kB)
{
	m_kR = kR;
	m_kB = kB;
	m_kG = kG;

	updateVertices();
}

//���c�݂̓K�p�͈�
void WarpTex::setSize(float w, float h)
{
	m_width = w;
	m_height = h;

	updateVertices();
}

//�����݂̃r���[�|�[�g�̃T�C�Y���擾
void WarpTex::getViewportSize( void )
{
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	m_width = v[2];
	m_height = v[3];
}

//���_�X�V
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

//�f�o�b�O���[�h�؂�ւ�
void WarpTex::switchDebugMode(void)
{
	m_debugMode = !m_debugMode;
}

//�c�ݕ␳�����X�̘c�␳�֐������g��Ȃ���Update��Draw���g������
void WarpTex::runDC(void)
{
	//GL�ݒ�̕ۑ�
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//MatrixMode�擾
	GLint mode;
	glGetIntegerv(GL_MATRIX_MODE, &mode);

	//���e�s��擾
	GLfloat p[16];
	glGetFloatv(GL_PROJECTION_MATRIX, p);

	//���f���r���[�s��擾
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);

	//��ʂ̉𑜓x�擾
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	m_width = v[2];
	m_height = v[3];

	//���C�e�B���O����
	glDisable(GL_LIGHTING);

	//�f�v�X�e�X�g����
	glDisable(GL_DEPTH_TEST);

	//���e�s��w��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_width, 0, m_height, -1, 1);

	//���f���r���[�s��w��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�o�b�N�o�b�t�@���e�N�X�`���ɃR�s�[
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_width, m_height);

	//��ʃN���A���폜
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�c�ݕ␳�摜�`��
	renderUndistortedImage();

	glDisable(GL_TEXTURE_2D);

	//�f�o�b�O�\��
	if (m_debugMode) {
		Grid();
		Params();
	}
	//���f���r���[�s�񕜌�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(m);

	//���e�s�񕜌�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(p);

	//MatrixMode����
	glMatrixMode(mode);

	//GL�ݒ蕜��
	glPopAttrib();
}

//���摜�X�V
void WarpTex::Update(void)
{
	//�o�b�N�o�b�t�@���e�N�X�`���ɃR�s�[
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_width, m_height);
	/*��
	glCopyTexSubImage2D: �o�b�N�o�b�t�@�̈悩��e�N�X�`���ɉ摜���R�s�[����
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

//���摜�`��
void WarpTex::Draw(float x, float y, float s )
{
	//GL�ݒ�̕ۑ�
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//���e�s��w��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, m_width, 0, m_height, -1, 1);
	glOrtho( -m_width/2.0, m_width/2.0, -m_height/2.0, m_height/2.0, -1, 1);

	//���f���r���[�s��w��
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); //��
	glLoadIdentity();

	glTranslatef( x * m_width, y * m_width, 0.0);
	glScalef(s, s, 1.0);

	//�c�ݕ␳�摜�`��
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	renderUndistortedImage();

	glDisable(GL_TEXTURE_2D);

	//�f�o�b�O�\��
	if (m_debugMode) {
		Grid();
		Params();
	}
	glPopMatrix(); //��
}

//�c�ݕ␳�摜�`��
void WarpTex::renderUndistortedImage(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//���Z����

	glColor3f(1.0, 0.0, 0.0);
	renderEachImage(m_verticesR);

	glColor3f(0.0, 1.0, 0.0);
	renderEachImage(m_verticesG);

	glColor3f(0.0, 0.0, 1.0);
	renderEachImage(m_verticesB);

	glDisable(GL_BLEND);
}

//�e�摜�`��
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

//�f�o�b�O�\��
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
//�f�o�b�O�\��
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
//�f�o�b�O�p������`��i�x���j
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