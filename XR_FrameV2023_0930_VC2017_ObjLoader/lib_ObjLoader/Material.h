#ifndef __CMaterial_h__
#define __CMaterial_h__

#include <GL/glut.h>

/** @class  CMaterial
 *  @brief  �}�e���A���N���X
 *  @author  Masakazu Yoshida(yoshida@iltj.jp)
 *  @version  1.0
 *  @date  2008/12/1 ... �V�K�쐬
 *  @attention  Copyright (C) 2008, ILTJ Inc.
 */
class CMaterial
{
/*--------------*/
/* ���J�����o   */
/*--------------*/
public:
//*******************************************************************
/*!
 *  @brief  �f�t�H���g�R���X�g���N�^
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  CMaterial(void);

//*******************************************************************
/*!
 *  @brief  �f�X�g���N�^
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  ~CMaterial(void);

//*******************************************************************
/*!
 *  @brief  Diffuse(�g�U��)�ݒ���s���܂��B
 *  @param  val ... [In] �\��[GL_FRONT:�\, GL_BACK:��]
 *  @param  red ... [In] �ԐF����
 *  @param  green ... [In] �ΐF����
 *  @param  blue ... [In] �F����
 *  @param  alpha ... [In] �A���t�@�l
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void setDiffuse(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

//*******************************************************************
/*!
 *  @brief  Ambient(����)�ݒ���s���܂��B
 *  @param  val ... [In] �\��[GL_FRONT:�\, GL_BACK:��]
 *  @param  red ... [In] �ԐF����
 *  @param  green ... [In] �ΐF����
 *  @param  blue ... [In] �F����
 *  @param  alpha ... [In] �A���t�@�l
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void setAmbient(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

//*******************************************************************
/*!
 *  @brief  Specular(���ʌ�)�ݒ���s���܂��B
 *  @param  val ... [In] �\��[GL_FRONT:�\, GL_BACK:��]
 *  @param  red ... [In] �ԐF����
 *  @param  green ... [In] �ΐF����
 *  @param  blue ... [In] �F����
 *  @param  alpha ... [In] �A���t�@�l
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void setSpecular(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

//*******************************************************************
/*!
 *  @brief  Emission(���ˌ�)�ݒ���s���܂��B
 *  @param  val ... [In] �\��[GL_FRONT:�\, GL_BACK:��]
 *  @param  red ... [In] �ԐF����
 *  @param  green ... [In] �ΐF����
 *  @param  blue ... [In] �F����
 *  @param  alpha ... [In] �A���t�@�l
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void setEmission(int val, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

//*******************************************************************
/*!
 *  @brief  Shininess(���ʎw��)�ݒ���s���܂��B
 *  @param  val1 ... [In] �\�� [GL_FRONT=�\, GL_BACK=��]
 *  @param  val2 ... [In] ���ʎw��
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void setShininess(int val1, GLfloat val2);

//*******************************************************************
/*!
 *  @brief  �����f�[�^�̏��������s���܂��B
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
  void clear(void);

/*--------------*/
/* ����J�����o */
/*--------------*/
private:
  GLfloat diffuse[5];                            // DIFFUSE�ݒ�l
  GLfloat ambient[5];                            // AMBIENT�ݒ�l
  GLfloat specular[5];                           // SPECULAR�ݒ�l
  GLfloat emission[5];                           // EMISSION�ݒ�l
  GLfloat shininess[2];                          // SHAININESS�ݒ�l
};

#endif
