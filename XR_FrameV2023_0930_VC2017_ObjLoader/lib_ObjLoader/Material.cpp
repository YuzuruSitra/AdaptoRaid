#include ".\material.h"

//-----------------------------------------------------------------//
// �f�t�H���g�R���X�g���N�^                                        //
//-----------------------------------------------------------------//
CMaterial::CMaterial(void)
{
}

//-----------------------------------------------------------------//
// �f�X�g���N�^                                                    //
//-----------------------------------------------------------------//
CMaterial::~CMaterial(void)
{
}

//-----------------------------------------------------------------//
// Diffuse(�g�U��)�ݒ���s���܂��B                                 //
//-----------------------------------------------------------------//
void CMaterial::setDiffuse(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  diffuse[0] = red;
  diffuse[1] = green;
  diffuse[2] = blue;
  diffuse[3] = alpha;

  glMaterialfv(val, GL_DIFFUSE, diffuse);
}

//-----------------------------------------------------------------//
// Ambient(����)�ݒ���s���܂��B                                 //
//-----------------------------------------------------------------//
void CMaterial::setAmbient(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  ambient[0] = red;
  ambient[1] = green;
  ambient[2] = blue;
  ambient[3] = alpha;

  //glColor3d(red, green, blue);
  glMaterialfv(val, GL_AMBIENT, ambient);
}

//-----------------------------------------------------------------//
// Specular(���ʌ�)�ݒ���s���܂��B                                //
//-----------------------------------------------------------------//
void CMaterial::setSpecular(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  specular[0] = red;
  specular[1] = green;
  specular[2] = blue;
  specular[3] = alpha;

  glMaterialfv(val, GL_SPECULAR, specular);
}

//-----------------------------------------------------------------//
// Emission(���ˌ�)�ݒ���s���܂��B                                //
//-----------------------------------------------------------------//
void CMaterial::setEmission(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  emission[0] = red;
  emission[1] = green;
  emission[2] = blue;
  emission[3] = alpha;

  glMaterialfv(val, GL_EMISSION, emission);
}

//-----------------------------------------------------------------//
// Shininess(���ʎw��)�ݒ���s���܂��B                             //
//-----------------------------------------------------------------//
void CMaterial::setShininess(int val1, GLfloat val2)
{
  glMaterialf(val1, GL_SHININESS, val2);
}

//-----------------------------------------------------------------//
// �����f�[�^�̏��������s���܂��B                                  //
//-----------------------------------------------------------------//
void CMaterial::clear(void)
{
  // DIFFUSE�ݒ�l
  diffuse[0] = GL_FRONT;
  diffuse[1] = 0.8f;
  diffuse[2] = 0.8f;
  diffuse[3] = 0.8f;
  diffuse[4] = 1.0f;
  setDiffuse((int)diffuse[0], diffuse[1], diffuse[2], diffuse[3], diffuse[4]);

  // AMBIENT�ݒ�l
  ambient[0] = GL_FRONT;
  ambient[1] = 0.2f;
  ambient[2] = 0.2f;
  ambient[3] = 0.2f;
  ambient[4] = 1.0f;
  setAmbient((int)ambient[0], ambient[1], ambient[2], ambient[3], ambient[4]);
  
  // SPECULAR�ݒ�l
  specular[0] = GL_FRONT;
  specular[1] = 0.0f;
  specular[2] = 0.0f;  
  specular[3] = 0.0f;
  specular[4] = 1.0f;
  setSpecular((int)specular[0], specular[1], specular[2], specular[3], specular[4]);

  // EMISSION�ݒ�l
  emission[0] = GL_FRONT;
  emission[1] = 0.0f;
  emission[2] = 0.0f;
  emission[3] = 0.0f;
  emission[4] = 1.0f;
  setEmission((int)emission[0], emission[1], emission[2], emission[3], emission[4]);

  // SHAININESS�ݒ�l
  shininess[0] = GL_FRONT;
  shininess[1] = 0.0f;
  setShininess((int)shininess[0], shininess[1]);

}
