#ifndef __CObjLoader_h__
#define __CObjLoader_h__

#define _USE_MATH_DEFINES

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

#include "mtl.h"
#include "ThreedVector.h"
#include "TextureCoordinate.h"
#include "ObjData.h"

using namespace std;

namespace objloader
{

#define _USE_MATH_DEFINES                        // M_PI�p
#define SMOOTHING_ANGLE 90.0f                    // �X���[�W���O�p�x

/**
 *  @class    CObjLoader
 *  @brief    OBJ�f�[�^�A�N�Z�X�N���X@n
 <p>
        �{�N���X�ł�OBJ�f�[�^�̓Ǎ��݁A�`����s�����Ƃ��\�ł��B@n
        @n
        �g�p���@�́A�ȉ��̒ʂ�ł��B@n
          1.�{�N���X�̃C���X�^���X�𐶐����܂��B@n
          2.read�֐����g�p���āAOBJ�t�@�C����Ǎ��݂܂��B@n
          @n
            �ȉ��̊֐����g�p���āA�Ǎ��񂾃f�[�^��`�悵�܂��B@n
            2.1.draw�֐��ł́AOBJ�f�[�^��`�悵�܂��B@n
            2.2.drawNormal�֐��ł́AOBJ�f�[�^�̖@����`�悵�܂��B@n
            2.3.drawLine�֐��ł́AOBJ�f�[�^�����C���`�悵�܂��B@n
          @n
          3.write�֐����g�p���āA�@�����̂Ȃ�OBJ�t�@�C����Ǎ���@n
            �@������t������OBJ�t�@�C�����o�͂��܂��B@n
            �o�̓t�@�C���́A�uout_ + OBJ�t�@�C�����v�ŏo�͂���܂��B@n
          ���e�N�X�`���̌`����png�̂ݑΉ����Ă��܂��B
 </p>
 *  @version  1.0
 *  @date    2008/12/1
 *  @author    Masakazu Yoshida (yoshida@iltj.jp)
 *  @attention  Copyright (C) 2008, ILTJ Inc.
 *
 *  @mainpage
 *  <center>
 *  @n
 *    �{�@�\�́A���f�����O�\�t�g�ł���uMetasequoia�v�y�сuMaya�v����OBJ�`����@n
 *    �G�N�X�|�[�g���ꂽ���̂�Ǎ��݁AOpenGL�ɂĕ`�悵�܂��B@n
 *    OBJ�̃^�O�͎d�l���B���ł��邽�߁A�Œ���K�v�ł���^�O�݂̂ɑΉ����Ă��܂��B@n
 *
 *    �ȉ��ɁA�{�@�\�őΉ����Ă���^�O���̈ꗗ�������܂��B@n
 *
 *  <table border=1 cellspacing=0 cellpadding=4 width=700 align=center>
 *  <tr bgcolor="#dddddd">
 *    <td colspan=2><b>[ MTL�^�O ]</b></td><td><center><b>Metasequoia</b></center></td><td><center><b>MAYA</b></center></td>
 *  </tr>
 *  <tr>
 *    <td width=20%><b>newmtl</b></td><td width=60%>�}�e���A����`��</td><td width=10%><center>��</center></td><td width=10%><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>Ka</b></td><td>����(Ambient)�J���[</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>Kd</b></td><td>�g�U��(Diffuse)�J���[</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>Ks</b></td><td>���ʌ�(Specular)�J���[</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>Ns</b></td><td>���ʎw��(Shininness)</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>Tf</b></td><td>�s�����x</td><td><center>�~</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>d</b></td><td>�����x</td><td><center>�~</center></td><td><center>�~</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>illum</b></td><td>�C���~�l�[�V�����ݒ�(1:���ʌ�����, 2:���ʌ��Ȃ�)</td><td><center>�~</center></td><td><center>��</center></td>
 *  </tr>
 *  </tr>
 *  <tr>
 *    <td><b>map_Ka</b></td><td>���}�b�v</td><td><center>�~</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>map_Kd</b></td><td>�e�N�X�`���}�b�v</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>refl</b></td><td>���t���N�V�����}�b�v</td><td><center>�~</center></td><td><center>��</center></td>
 *  </tr>
 *  </table>
 *
 *  <table border=1 cellspacing=0 cellpadding=4 width=700 align=center>
 *  <tr bgcolor="#dddddd">
 *    <td colspan=2><b>[ OBJ�^�O ]</b></td><td><center><b>Metasequoia</b></center></td><td><center><b>MAYA</b></center></td>
 *  </tr>
 *  <tr>
 *    <td width=20%><b>mtlib</b></td><td width=60%>�}�e���A���t�@�C����</td><td width=10%><center>��</center></td><td width=10%><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>usemtl</b></td><td>�}�e���A����`��</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>v</b></td><td>���_���W</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>vt</b></td><td>���_��UV���W</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>vn</b></td><td>���_�̖@���x�N�g��</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>f</b></td><td>�ʂ̃C���f�b�N�X</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  <tr>
 *    <td><b>g</b></td><td>�O���[�v��</td><td><center>��</center></td><td><center>��</center></td>
 *  </tr>
 *  </table>
 *  @n
 *  
 *  </center>
 *
 */
class CObjLoader
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
    CObjLoader(void);

    //*******************************************************************
    /*!
     *  @brief  �f�X�g���N�^
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    ~CObjLoader(void);

    //*******************************************************************
    /*!
     *  @brief  �����ł���OBJ�t�@�C�������g�p���āAOBJ�t�@�C����Ǎ��݂܂��B
     *  @param  objfnm ... [In] OBJ�t�@�C����
     *  @retval  true  ... ����I��
     *  @retval  false ... �ُ�I��
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    bool read(string objfnm);

    //*******************************************************************
    /*!
     *  @brief  read()�œǍ��ݍς݂�OBJ���f����`�悵�܂��B
     *  @attention  ���O��read()���Ăяo���Ă���K�v������܂��B
     *  @param  enlarge ... [In] �g��䗦
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void draw(double enlarge);

    //*******************************************************************
    /*!
     *  @brief  read()�œǍ��ݍς݂�OBJ���f���̖@����`�悵�܂��B
     *  @attention  ���O��read()���Ăяo���Ă���K�v������܂��B
     *  @param  enlarge ... [In] �g��䗦
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void drawNormal(double enlarge);

    //*******************************************************************
    /*!
     *  @brief  read()�œǍ��ݍς݂�OBJ���f�������C���`�悵�܂��B
     *  @attention  ���O��read()���Ăяo���Ă���K�v������܂��B
     *  @param  enlarge ... [In] �g��䗦
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void drawLine(double enlarge);

    //*******************************************************************
    /*!
     *  @brief  �@���Ȃ���OBJ���f�����A�@����t������OBJ�t�@�C���ɏo�͂��܂��B@n
     *          �P�D�����ł���OBJ�t�@�C�������g�p���āAOBJ�t�@�C����Ǎ��݂܂��B@n
     *          �Q�D�Ǎ���OBJ�ɖ@������t�����āAOBJ�t�@�C�����o�͂��܂��B
     *  @attention  �}�e���A���t�@�C���̏o�͍͂s���܂���B
     *  @param  inFileNm  ... [In] ����OBJ�t�@�C����
     *  @param  outFileNm  ... [Out] �o��OBJ�t�@�C����
     *  @retval true  ... ����I��
     *  @retval false ... �ُ�I��
     *  @date 2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    bool write(string inFileNm, string outFileNm);

  /*--------------*/
  /* ����J�����o */
  /*--------------*/
  private:
    CMtl cmtl;                                     // OBJ�p�}�e���A���N���X
    bool logFlg;                                   // ���O�t���O(true:debug�o��, false:release�o��)

    int  debug_cnt;                                // �f�o�b�O�p�J�E���^
    long vf_cnt;                                   // ���_�@���p�C���f�b�N�X�J�E���^
    string pre_MaterialName;                       // �O��̃}�e���A����
    bool isMakeDispList;                           // OBJ�Ǎ��ݎ��Ƀf�B�X�v���C���X�g�쐬�L��(true:����, false:�Ȃ�)

    vector< CThreedVector > v_v;                   // ���_���W�p vector
    vector< CThreedVector > v_vn;                  // �@�����W vector
    vector< St_TextureCoordinate > v_vt;           // �e�N�X�`�����W vector
    vector< St_face_data > v_f;                    // �ʂ̃f�[�^ vector

    vector< CObjData > objData;                    // OBJ��{�f�[�^

    GLuint displaylistNo;                          // �f�B�X�v���C���X�gNO
    GLuint lineDisplaylistNo;                      // �@���`��p�f�B�X�v���C���X�gNO

    vector< string > v_mtlfn;                      // �}�e���A���t�@�C���� vector

    //*******************************************************************
    /*!
     *  @brief  ���f���`��̃f�B�X�v���C���X�g���쐬���܂��B
     *  @param  isDelete ... [In] true:�������̈�J������ / false:�������̈�J���Ȃ�
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void makeDisplayList(bool isDelete);

    //*******************************************************************
    /*!
     *  @brief  �I�u�W�F�N�g�̖ʂ̕`��(1�̖ʃf�[�^��`��)���s���܂��B
     *  @param  val ... [In] �ʃf�[�^�\����
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void draw_face(CObjData &val);

    //*******************************************************************
    /*!
     *  @brief  �I�u�W�F�N�g�̖ʂ̖@���`��(1�̖ʃf�[�^��`��)���s���܂��B
     *  @param  val ... [In] �ʃf�[�^�\����
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void draw_normal(CObjData &val);

    //*******************************************************************
    /*!
     *  @brief  �ʖ@���̌v�Z���s���܂��B
     *  @param  val ... [In,Out] �ʃf�[�^�\����
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void culcFaceNormal(CObjData &val);
    
    //*******************************************************************
    /*!
     *  @brief  ���_�@���̌v�Z���s���܂��B
     *  @param  val ... [In, Out] OBJ��{�f�[�^�I�u�W�F�N�g
     *  @param  cntval ... [In] ���݂̒��_�C���f�b�N�X
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void culcVertexNormal(CObjData &val, int cntval);

    //*******************************************************************
    /*!
     *  @brief  �����f�[�^�������������s���܂��B
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    void clear(void);

    //*******************************************************************
    /*!
     *  @brief  �����ł���OBJ�t�@�C�������g�p���āAOBJ�t�@�C����Ǎ��݂܂��B
     *  @attention  public�ł���read()�̓C���^�[�t�F�[�X�ł���A�{�֐��Ŏ��������s���Ă��܂��B@n
     *              �Eread()�o�R�ŏ������s���ꍇ�́A�f�B�X�v���C���X�g�̍쐬���s���܂��B@n
     *              �Eread()���o�R���Ȃ��ŏ������s���ꍇ�́A�f�B�X�v���C���X�g�̍쐬���s���܂���B
     *  @param  objfnm ... [In] OBJ�t�@�C����
     *  @retval  true  ... ����I��
     *  @retval  false ... �ُ�I��
     *  @date  2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    bool readTrans(string objfnm);

    //*******************************************************************
    /*!
     *  @brief  read()�œǍ��ݍς݂�OBJ���f����OBJ�t�@�C���ɏo�͂��܂��B
     *  @attention  �}�e���A���t�@�C���̏o�͍͂s���܂���B@n
     *              �܂��A���O��read()���Ăяo���Ă���K�v������܂��B
     *  @param  filenm  ... [In] �o��OBJ�t�@�C����
     *  @retval true  ... ����I��
     *  @retval false ... �ُ�I��
     *  @date 2008/12/1 ... �V�K�쐬
     */
    //********************************************************************
    bool writeTrans(string filenm);

  };
}

#endif
