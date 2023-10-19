#ifndef __CObjData_h__
#define __CObjData_h__

#include <cstring>
#include <vector>

#include "ObjData.h"
#include "ObjDetailData.h"

using namespace std;

namespace objloader
{

/**
 *  @struct  St_vf_detail_data
 *  @brief  ���W�C���f�b�N�X�\����
 *  @date  2008/12/1 ... �V�K�쐬
 */
struct St_vf_detail_data{
  long detail_data[3];                           // ���_���WNo�E�e�N�X�`�����WNo�E�@�����WNo�̂����ꂩ�Ŏg�p
};

/**
 *  @struct  St_face_data
 *  @brief  �ʃf�[�^�\����
 *  @date  2008/12/1 ... �V�K�쐬
 */
struct St_face_data{
  int           groupNo;                         // �O���[�vNo
  string        groupName;                       // �O���[�v��
  int           s_groupNo;                       // �X���[�W���O�O���[�vNo
  string        s_groupName;                     // �X���[�W���O�O���[�v��
  string        mtlnm;                           // �}�e���A����`��
  CThreedVector faceNormal;                      // �ʖ@��

  vector <CThreedVector>     vectorNormal;       // ���_�@��
  vector <St_vf_detail_data> vf_data;            // vf�ڍ׃f�[�^

  //*******************************************************************
  /*!
   *  @brief  �����f�[�^�̏o�͂��s���܂��B
   *  @param  ost ... �A�E�g�v�b�g�X�g���[��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void St_face_data::show(ostream &ost) const
  {
    ost << "======================================" << endl;
    for(unsigned int i = 0; i < vf_data.size(); i++)
    {
      ost << "--------------------------------------" << endl;
      if(groupNo)
      {
        ost << "�O���[�vNo�F" << groupNo << endl;
      }

      if(groupName.size())
      {
        ost << "�O���[�v���F" << groupName.c_str() << endl;
      }

      if(s_groupNo)
      {
        ost << "�X���[�W���O�O���[�vNo:" << s_groupNo << endl;
      }

      if(s_groupName.size())
      {
        ost << "�X���[�W���O�O���[�v��:" << s_groupName.c_str() << endl;
      }

      if(mtlnm.size())
      {
        ost << "�}�e���A�����F" << mtlnm.c_str() << endl;
      }

      ost << "���_���WNo�F" << vf_data[i].detail_data[0] << endl;

      ost << "�e�N�X�`�����WNo�F";

      if(vf_data[i].detail_data[1])
      {
        ost << "none" << endl;
      }
      else
      {
        ost << vf_data[i].detail_data[1] << endl;
      }

      ost << "�@�����WNo�F" << vf_data[i].detail_data[2] << endl;
    }
  }

  //*******************************************************************
  /*!
   *  @brief  �����f�[�^�̏��������s���܂��B
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void St_face_data::clear(void)
  {
    groupNo = 0;
    groupName.clear();
    mtlnm.clear();
    vf_data.clear();
  }
};

/** @class    CObjData
 *  @brief    OBJ��{�f�[�^�N���X
 *  @author    Masakazu Yoshida(yoshida@iltj.jp)
 *  @version  1.0
 *  @date    2008/12/1 ... �V�K�쐬
 *  @attention  Copyright (C) 2008, ILTJ Inc.
 */
class CObjData
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
  CObjData(void);

  //*******************************************************************
  /*!
   *  @brief  �f�X�g���N�^
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  ~CObjData(void);

  //*******************************************************************
  /*!
   *  @brief  �O���[�vNo���擾���܂��B
   *  @return  int ... �O���[�vNo
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  int getGroupNo(void);

  //*******************************************************************
  /*!
   *  @brief  �O���[�v�����擾���܂��B
   *  @return  std::string ... �O���[�v��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  string getGroupName(void);

  //*******************************************************************
  /*!
   *  @brief  �}�e���A����`�����擾���܂��B
   *  @return  std::string ... �}�e���A����`��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  string getMtlName(void);
  
  //*******************************************************************
  /*!
   *  @brief  �ʖ@�����擾�擾���܂��B
   *  @return  CThreedVector * ... 3D�x�N�g���N���X�I�u�W�F�N�g
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  CThreedVector *getFaceNormal(void);

  //*******************************************************************
  /*!
   *  @brief  �@���t���O���擾���܂��B
   *  @retval  true  ... �@���ݒ肠��
   *  @retval  false ... �@���ݒ�Ȃ�
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool getNormalFlg(void);

  //*******************************************************************
  /*!
   *  @brief  �e�N�X�`���t���O���擾���܂��B
   *  @retval  true  ... �e�N�X�`���ݒ肠��
   *  @retval  false ... �e�N�X�`���ݒ�Ȃ�
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  bool getTextureFlg(void);

  //*******************************************************************
  /*!
   *  @brief  ���_�@�����擾���܂��B
   *  @param  val ... [In] �C���f�b�N�X
   *  @return  CThreedVector * ... 3D�x�N�g���N���X�I�u�W�F�N�g
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  CThreedVector *getVertexNormal(unsigned int val);

  //*******************************************************************
  /*!
   *  @brief  OBJ�ڍ׃f�[�^���擾���܂��B
   *  @param  val ... [In] �C���f�b�N�X
   *  @return  CObjDetailData * ... OBJ�ڍ׃f�[�^�N���X�I�u�W�F�N�g
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  CObjDetailData *getObjDetailData(unsigned int val);

  //*******************************************************************
  /*!
   *  @brief  �O���[�vNo��ݒ肵�܂��B
   *  @param  val ... [In] �O���[�vNo
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setGroupNo(int val);

  //*******************************************************************
  /*!
   *  @brief  �O���[�v����ݒ肵�܂��B
   *  @param  val ... [In] �O���[�v��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setGroupName(string val);

  //*******************************************************************
  /*!
   *  @brief  �}�e���A����`����ݒ肵�܂��B
   *  @param  val ... [In] �}�e���A����`��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setMtlName(string val);

  //*******************************************************************
  /*!
   *  @brief  �ʖ@����ݒ肵�܂��B
   *  @param  pval ... [In] �ʖ@��(3D�x�N�g���N���X�I�u�W�F�N�g)
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setFaceNormal(const CThreedVector *pval);

  //*******************************************************************
  /*!
   *  @brief  �@���t���O��ݒ肵�܂��B
   *  @param  val ... [In] �@���t���O
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setNormalFlg(bool val);

  //*******************************************************************
  /*!
   *  @brief  �e�N�X�`���t���O��ݒ肵�܂��B
   *  @param  val ... [In] �e�N�X�`���t���O
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setTextureFlg(bool val);

  //*******************************************************************
  /*!
   *  @brief  �@�����W�C���f�b�N�X��ݒ肵�܂��B
   *  @param arrayindex ... [In] �i�[��C���f�b�N�X
   *  @param index ... [In] �@�����W�C���f�b�N�X
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void setNormalIndex(int arrayindex, long index);

  //*******************************************************************
  /*!
   *  @brief  ���_�@����ݒ肵�܂��B
   *  @param  pval ... [In] ���_�@��(3D�x�N�g���N���X�I�u�W�F�N�g)
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void addVertexNormal(const CThreedVector &pval);

  //*******************************************************************
  /*!
   *  @brief  OBJ�ڍ׃f�[�^��ǉ����܂��B
   *  @param  pval ... [In] OBJ�ڍ׃f�[�^�N���X�I�u�W�F�N�g
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void addObjDetailData(const CObjDetailData &pval);

  //*******************************************************************
  /*!
   *  @brief  OBJ�C���f�b�N�X�f�[�^��ǉ����܂��B
   *  @param  pval ... [In] ���W�C���f�b�N�X�\����
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void addIndex(const St_vf_detail_data & pval);

  //*******************************************************************
  /*!
   *  @brief  OBJ�f�[�^�̏��������s���܂��B
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void clear(void);

  //*******************************************************************
  /*!
   *  @brief  OBJ�ڍ׃f�[�^�����擾���܂��B
   *  @return  unsigned int ... �ێ����Ă���OBJ�ڍ׃f�[�^��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  unsigned int getObjDetailDataSize(void);

  //*******************************************************************
  /*!
   *  @brief  OBJ�C���f�b�N�X�f�[�^�����擾���܂��B
   *  @return  unsigned int ... �ێ����Ă���OBJ�C���f�b�N�X�f�[�^��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  unsigned int getIndexSize(void);

  //*******************************************************************
  /*!
   *  @brief  OBJ�C���f�b�N�X�f�[�^���擾���܂��B
   *  @param  index ... �擾�f�[�^�̃C���f�b�N�X
   *  @return  St_vf_detail_data ... �ێ����Ă���OBJ�C���f�b�N�X�f�[�^
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  St_vf_detail_data getIndex(int index);

  //*******************************************************************
  /*!
   *  @brief  �@�����W�f�[�^���擾���܂��B
   *  @param  index ... �擾�f�[�^�̃C���f�b�N�X
   *  @return  CThreedVector ... �@�����W�f�[�^
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  CThreedVector getVertexNormal(int index);

  //*******************************************************************
  /*!
   *  @brief  �����f�[�^���o�͂��܂��B
   *  @param  os ... [In] �A�E�g�v�b�g�X�g���[��
   *  @date  2008/12/1 ... �V�K�쐬
   */
  //********************************************************************
  void show(ostream &os);

/*--------------*/
/* ����J�����o */
/*--------------*/
private:
  int           groupNo;                         // �O���[�vNO
  string        groupName;                       // �O���[�v��
  string        mtlName;                         // mtl��`��

  CThreedVector faceNormal;                      // �ʖ@��

  bool          normalFlg;                       // �@���t���O(true:obj�ݒ肠��, false:�Ȃ�)
  bool          textureFlg;                      // �e�N�X�`���t���O(true:obj�ݒ肠��, false:�Ȃ�)

  vector <CThreedVector>     vertexNormal;       // ���_�@��
  vector <CObjDetailData>    objDetailData;      // OBJ�ڍ׃f�[�^
  vector <St_vf_detail_data> v_index;            // �C���f�b�N�X�f�[�^
};
}
#endif
