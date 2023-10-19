#pragma once
#include <GL/glut.h>

#define DC_MAX_TEX_SIZE_X 2048
#define DC_MAX_TEX_SIZE_Y 2048

#define DC_MESH_NUM_X 20
#define DC_MESH_NUM_Y 15

class WarpTex
{
public:
	WarpTex(void);
	~WarpTex(void);

	void init(void);
	void setCenter(float cx, float cy);
	void setParams(float kR, float kG, float kB);
	void switchDebugMode(void);

	void runDC(void);

	void setSize(float w, float h);
	void getViewportSize(void);
	void Update(void);
	void Draw(float x = 0.0, float y = 0.0, float s = 1.0 );

private:
	typedef struct _vertex2f {
		float x;
		float y;
	}vertex2f;

	void updateVertices(void);

	void Grid(void);
	void Params(void);

	void renderUndistortedImage(void);
	void renderEachImage(vertex2f vertices[DC_MESH_NUM_X + 1][DC_MESH_NUM_Y + 1]);

	void renderString(float x, float y, const char *_Format, ...);

	int m_width;
	int m_height;
	float m_centerX;
	float m_centerY;
	float m_kR;
	float m_kG;
	float m_kB;
	bool m_debugMode;

	GLuint m_texture;
	vertex2f m_verticesR[DC_MESH_NUM_X + 1][DC_MESH_NUM_Y + 1];
	vertex2f m_verticesG[DC_MESH_NUM_X + 1][DC_MESH_NUM_Y + 1];
	vertex2f m_verticesB[DC_MESH_NUM_X + 1][DC_MESH_NUM_Y + 1];
};
