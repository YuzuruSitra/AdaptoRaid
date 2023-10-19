#include ".\objdata.h"

using namespace objloader;

//-----------------------------------------------------------------//
// �f�t�H���g�R���X�g���N�^                                        //
//-----------------------------------------------------------------//
CObjData::CObjData(void)
{
}

//-----------------------------------------------------------------//
//  �f�X�g���N�^                                                   //
//-----------------------------------------------------------------//
CObjData::~CObjData(void)
{
}

//-----------------------------------------------------------------//
// �O���[�vNo���擾���܂��B                                        //
//-----------------------------------------------------------------//
int CObjData::getGroupNo(void)
{
  return groupNo;
}

//-----------------------------------------------------------------//
// �O���[�v�����擾���܂��B                                        //
//-----------------------------------------------------------------//
string CObjData::getGroupName(void)
{
  return groupName;
}

//-----------------------------------------------------------------//
// �}�e���A����`�����擾���܂��B                                  //
//-----------------------------------------------------------------//
string CObjData::getMtlName(void)
{
  return mtlName;
}

//-----------------------------------------------------------------//
// �ʖ@�����擾�擾���܂��B                                        //
//-----------------------------------------------------------------//
CThreedVector *CObjData::getFaceNormal(void)
{
  return &faceNormal;
}

//-----------------------------------------------------------------//
// �@���t���O���擾���܂��B                                        //
//-----------------------------------------------------------------//
bool CObjData::getNormalFlg(void)
{
  return normalFlg;
}

//-----------------------------------------------------------------//
// �e�N�X�`���t���O���擾���܂��B                                  //
//-----------------------------------------------------------------//
bool CObjData::getTextureFlg(void)
{
  return textureFlg;
}

//-----------------------------------------------------------------//
// ���_�@�����擾���܂��B                                          //
//-----------------------------------------------------------------//
CThreedVector *CObjData::getVertexNormal(unsigned int val)
{
  // �������A0�ȏォ�Avector�T�C�Y�����ł���ꍇ
  if(0 <= val && val < vertexNormal.size())
  {
    return &vertexNormal[val];
  }
  // ��L�ȊO�̏ꍇ
  else
  {
    return NULL;
  }
}

//-----------------------------------------------------------------//
// OBJ�ڍ׃f�[�^���擾���܂��B                                     //
//-----------------------------------------------------------------//
CObjDetailData *CObjData::getObjDetailData(unsigned int val)
{
  // �������A0�ȏォ�Avector�T�C�Y�����ł���ꍇ
  if(0 <= val && val < objDetailData.size())
  {
    return &objDetailData[val];
  }
  // ��L�ȊO�̏ꍇ
  else
  {
    return NULL;
  }
}

//-----------------------------------------------------------------//
// �O���[�vNo��ݒ肵�܂��B                                        //
//-----------------------------------------------------------------//
void CObjData::setGroupNo(int val)
{
  groupNo = val;
}

//-----------------------------------------------------------------//
// �O���[�v����ݒ肵�܂��B                                        //
//-----------------------------------------------------------------//
void CObjData::setGroupName(string val)
{
  groupName = val;
}

//-----------------------------------------------------------------//
// �}�e���A����`����ݒ肵�܂��B                                  //
//-----------------------------------------------------------------//
void CObjData::setMtlName(string val)
{
  mtlName = val;
}

//-----------------------------------------------------------------//
// �ʖ@����ݒ肵�܂��B                                            //
//-----------------------------------------------------------------//
void CObjData::setFaceNormal(const CThreedVector *pval)
{
  faceNormal = *pval;
}

//-----------------------------------------------------------------//
// �@���t���O��ݒ肵�܂��B                                        //
//-----------------------------------------------------------------//
void CObjData::setNormalFlg(bool val)
{
  normalFlg = val;
}

//-----------------------------------------------------------------//
// �e�N�X�`���t���O��ݒ肵�܂��B                                  //
//-----------------------------------------------------------------//
void CObjData::setTextureFlg(bool val)
{
  textureFlg = val;
}

//-----------------------------------------------------------------//
// �@�����W�C���f�b�N�X��ݒ肵�܂��B                              //
//-----------------------------------------------------------------//
void CObjData::setNormalIndex(int arrayindex, long index)
{
  v_index[arrayindex].detail_data[2] = index;
}

//-----------------------------------------------------------------//
// ���_�@����ݒ肵�܂��B                                          //
//-----------------------------------------------------------------//
void CObjData::addVertexNormal(const CThreedVector &pval)
{
  vertexNormal.push_back(pval);
}

//-----------------------------------------------------------------//
// OBJ�ڍ׃f�[�^��ǉ����܂��B                                     //
//-----------------------------------------------------------------//
void CObjData::addObjDetailData(const CObjDetailData &pval)
{
  objDetailData.push_back(pval);
}

//-----------------------------------------------------------------//
// OBJ�C���f�b�N�X�f�[�^��ǉ����܂��B                             //
//-----------------------------------------------------------------//
void CObjData::addIndex(const St_vf_detail_data & pval)
{
  v_index.push_back(pval);
}

//-----------------------------------------------------------------//
// OBJ�f�[�^�̏��������s���܂��B                                   //
//-----------------------------------------------------------------//
void CObjData::clear(void)
{
  groupNo = 0;
  groupName = "";
  mtlName = "";
  normalFlg = false;
  textureFlg = false;
  vertexNormal.clear();
  objDetailData.clear();
  v_index.clear();
}

//-----------------------------------------------------------------//
// OBJ�ڍ׃f�[�^�����擾���܂��B                                   //
//-----------------------------------------------------------------//
unsigned int CObjData::getObjDetailDataSize(void)
{
  return (unsigned int)objDetailData.size();
}

//-----------------------------------------------------------------//
// OBJ�C���f�b�N�X�f�[�^�����擾���܂��B                           //
//-----------------------------------------------------------------//
unsigned int CObjData::getIndexSize(void)
{
  return (unsigned int)v_index.size();
}

//-----------------------------------------------------------------//
// OBJ�C���f�b�N�X�f�[�^���擾���܂��B                             //
//-----------------------------------------------------------------//
St_vf_detail_data CObjData::getIndex(int index)
{
  St_vf_detail_data tmp;
  tmp.detail_data[0] = -1;
  tmp.detail_data[1] = -1;
  tmp.detail_data[2] = -1;

  // �C���f�b�N�X�w�肪�͈͊O�ł���ꍇ
  if(index < 0 || (int)v_index.size() <= index)
  {
    return tmp;
  }

  return v_index[index];
}

//-----------------------------------------------------------------//
// �����f�[�^���o�͂��܂��B                                        //
//-----------------------------------------------------------------//
void CObjData::show(ostream &os)
{
  os << "==============================================" << endl;
  os << "groupNo:" << groupNo << endl;

  os << "groupName:" << groupName.c_str() << endl;

  os << "mtlName:" << mtlName.c_str() << endl;

  os << "faceNormal: x = " << faceNormal.getPointX()
        << ", y = " << faceNormal.getPointY()
        << ", z = " << faceNormal.getPointZ() << endl;

  os << "normalFlg:" << normalFlg << endl;

  os << "textureFlg:" << textureFlg << endl;

  os << "----------------------------------------------" << endl;
  for(unsigned int i = 0; i < vertexNormal.size(); i++)
  {
    os << "vertexNormal[" << i << "]: x = " << vertexNormal[i].getPointX()
          << ", y = " << vertexNormal[i].getPointY()
          << ", z = " << vertexNormal[i].getPointZ() << endl;
  }

  os << "----------------------------------------------" << endl;
  for(unsigned int i = 0; i < objDetailData.size(); i++)
  {
    os << "objDetailData[" << i << "] Vertex: x = " << objDetailData[i].getVertexCoordinateX()
                      << ", y = " << objDetailData[i].getVertexCoordinateY()
                      << ", z = " << objDetailData[i].getVertexCoordinateZ() << endl;

    os << "objDetailData[" << i << "] Normal: x = " << objDetailData[i].getNormalCoordinateX()
                      << ", y = " << objDetailData[i].getNormalCoordinateY()
                      << ", z = " << objDetailData[i].getNormalCoordinateZ() << endl;

    os << "objDetailData[" << i << "] texture: U = " << objDetailData[i].getTextureCoordinateU()
                      << ", V = " << objDetailData[i].getTextureCoordinateV() << endl;
  }
}
