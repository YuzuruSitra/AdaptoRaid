#ifndef __CMtl_h__
#define __CMtl_h__

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <GL/glut.h>
#include <GL/glext.h>

#include "pngImage.h"
#include "material.h"

using namespace std;

//#undef _WIN32
/*
#ifdef _WIN32
//typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC)    (GLenum target);
PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
*/

/**
 *  @struct  St_mtl_data
 *  @brief  MTL�f�[�^�\����
 *  @date  2008/12/1 ... �V�K�쐬
 */
struct St_mtl_data
{
  string mtlnm;                                  // �}�e���A����`��
  string mtlfilenm;                              // �}�e���A���t�@�C����

  bool  isAmbient;                               // �����ݒ�̗L��(true=�L, false=��)
  float  ambient[3];                             // ����

  bool  isDiffuse;                               // �g�U���ݒ�̗L��(true=�L, false=��)
  float  diffuse[3];                             // �g�U��

  bool  isSpecular;                              // ���ʐݒ�̗L��(true=�L, false=��)
  float  specular[3];                            // ���ʌ�

  bool  isTransparency;                          // �A���t�@�l�̗L��(true=�L, false=��)
  float  transparency;                           // �A���t�@�l

  bool  isShininess;                             // ���ʌW���ݒ�̗L��(true=�L, false=��)
  int    shininess;                              // ���ʌW��

  bool  isIllumination;                          // �C���~�l�[�V�����ݒ�̗L��(true=�L, false=��)
  int    illumination;                           // �C���~�l�[�V����(1=���ʌ������A2=���ʌ��L��)

  GLuint  tNo;                                   // �e�N�X�`��No

  bool  isTexture;                               // �e�N�X�`���ݒ�̗L��(true=�L, false=��)

  bool  isSphereTexture;                         // �X�t�B�A�}�b�s���O�p�e�N�X�`���ݒ�̗L��(true=�L, false=��)
  string  texturefnm;                            // �e�N�X�`���t�@�C����(�e�N�X�`���}�b�s���O�A�X�t�B�A�}�b�s���O�p)
  int    textureCnt;                             // �L���[�u�}�b�s���O�p�J�E���^
  int    textureIndex[6];                        // �L���[�u�}�b�s���O�p�C���f�b�N�X

  vector <string> v_texturefnm;                  // �e�N�X�`���t�@�C����(�L���[�u�}�b�s���O�p)
  bool  isCubeTexture;                           // �L���[�u�}�b�s���O�p�e�N�X�`���ݒ�̗L��(true=�L, false=��)

  //*******************************************************************
  /*!
   *  @brief  �����f�[�^�̏��������s���܂��B
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void init(void)
  {
    mtlnm.clear();                               // �}�e���A����`��
    mtlfilenm.clear();                           // �}�e���A���t�@�C����

    isAmbient = false;                           // �����ݒ�̗L��
    ambient[0] = 0.0f;                           // ����
    ambient[1] = 0.0f;
    ambient[2] = 0.0f;

    isDiffuse = false;                           // �g�U���ݒ�̗L��
    diffuse[0] = 0.0f;                           // �g�U��
    diffuse[1] = 0.0f;
    diffuse[2] = 0.0f;

    isSpecular = false;                          // ���ʐݒ�̗L��
    specular[0] = 0.0f;                          // ���ʌ�
    specular[1] = 0.0f;
    specular[2] = 0.0f;

    isTransparency = false;                      // �A���t�@�l�̗L��
    transparency = 1.0f;                         // �A���t�@�l�̗L��

    isShininess = false;                         // ���ʌW���ݒ�̗L��

    shininess = 0;                               // ���ʌW��

    isIllumination = false;                      // �C���~�l�[�V�����ݒ�̗L��
    illumination = 1;                            // �C���~�l�[�V����

    tNo = 0;                                     // �e�N�X�`��No

    isTexture = false;                           // �e�N�X�`���ݒ�̗L��
    isSphereTexture = false;                     // �X�t�B�A�}�b�s���O�p�e�N�X�`���ݒ�̗L��

    texturefnm.clear();                          // �e�N�X�`���t�@�C����(�e�N�X�`���}�b�s���O�A�X�t�B�A�}�b�s���O�p)

    textureCnt = 0;                              // �L���[�u�}�b�s���O�p�J�E���^

    textureIndex[0] = 1;                         // �L���[�u�}�b�s���O�p�C���f�b�N�X
    textureIndex[1] = 3;
    textureIndex[2] = 5;
    textureIndex[3] = 2;
    textureIndex[4] = 4;
    textureIndex[5] = 0;

    v_texturefnm.clear();                        // �e�N�X�`���t�@�C����(�L���[�u�}�b�s���O�p)
    isCubeTexture = false;                       // �L���[�u�}�b�s���O�p�e�N�X�`���ݒ�̗L��
  }
};

/** @class  CMtl
  * @brief  OBJ�p�}�e���A���N���X
  * @author  Masakazu Yoshida(yoshida@iltj.jp)
  * @version  1.0
  * @date  2008/12/1 ... �V�K�쐬
  * @attention  Copyright (C) 2008, ILTJ Inc.
�@*/
class CMtl
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
  CMtl(void);

  //*******************************************************************
  /*!
   *  @brief  �f�X�g���N�^
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  ~CMtl(void);

  //*******************************************************************
  /*!
   *  @brief  �}�e���A���t�@�C���̃��[�h���s���܂��B
   *  @param  mtlfnm ... [In] �}�e���A���t�@�C����
   *  @retval  true  ... ����I��
   *  @retval  false ... �Ϗ��I��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool loadMtl(string mtlfnm);

  //*******************************************************************
  /*!
   *  @brief  �}�e���A���ݒ�̓K�p���s���܂��B
   *  @param  mtlnm ... [In] �}�e���A����`��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void applyMtl(string mtlnm);

  //*******************************************************************
  /*!
   *  @brief  �}�e���A���ݒ�̏��������s���܂��B
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void clearMtl(void);

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
  bool texturebind_flg;                          // �e�N�X�`���}�b�s���O�o�C���h�t���O
  bool spherebind_flg;                           // �X�t�B�A�}�b�s���O�o�C���h�t���O
  bool cubebind_flg;                             // �L���[�u�}�b�s���O�o�C���h�t���O

  // mtl��`�ێ��̈�
  vector <St_mtl_data> v_mtl;

  // �e�N�X�`����(ID)�ێ��̈�
  vector <GLuint> v_tNo;

  // �}�e���A��
  CMaterial material;

  //*******************************************************************
  /*!
   *  @brief  �����f�[�^�̏o�͂��s���܂��B
   *  @param  val ... [In] mtl�f�[�^�\����
   *  @param  os ... [In] �A�E�g�v�b�g�X�g���[��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void show(const St_mtl_data &val, ostream &os);
  
  //*******************************************************************
  /*!
   *  @brief  �e�N�X�`���̃��[�h���s���܂��B
   *  @param  pval ... [In] mtl�f�[�^�\����
   *  @retval  true  ... ����I��
   *  @retval  false ... �ُ�I��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool loadTexture(const St_mtl_data *pval);

  //*******************************************************************
  /*!
   *  @brief  �X�t�B�A�}�b�s���O�p�e�N�X�`���̃��[�h���s���܂��B
   *  @param  pval ... [In] mtl�f�[�^�\����
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool loadSphereTexture(const St_mtl_data *pval);

  //*******************************************************************
  /*!
   *  @brief  �L���[�u�}�b�s���O�p�e�N�X�`���̃��[�h���s���܂��B
   *  @param  pval ... [In] mtl�f�[�^�\����
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool loadCubeTexture(const St_mtl_data *pval);
};

#endif
