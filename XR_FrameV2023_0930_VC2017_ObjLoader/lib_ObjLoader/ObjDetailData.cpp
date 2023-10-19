#include ".\objdetaildata.h"

using namespace objloader;

//-----------------------------------------------------------------//
//  �f�t�H���g�R���X�g���N�^                                       //
//-----------------------------------------------------------------//
CObjDetailData::CObjDetailData(void)
{
//  textureU = NULL;
//  textureV = NULL;
  st_texture.u = 0;
  st_texture.v = 0;
}

//-----------------------------------------------------------------//
//  �f�X�g���N�^                                                   //
//-----------------------------------------------------------------//
CObjDetailData::~CObjDetailData(void)
{
}

//-----------------------------------------------------------------//
// ���_���W�l�̎擾(�z��)���s���܂��B                              //
//-----------------------------------------------------------------//
double *CObjDetailData::getVertexCoordinates(void)
{
  return vertexCoordinate.getPointAll();
}

//-----------------------------------------------------------------//
// ���_X���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getVertexCoordinateX(void)
{
  return vertexCoordinate[0];
}

//-----------------------------------------------------------------//
// ���_Y���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getVertexCoordinateY(void)
{
  return vertexCoordinate[1];
}

//-----------------------------------------------------------------//
// ���_Z���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getVertexCoordinateZ(void)
{
  return vertexCoordinate[2];
}

//-----------------------------------------------------------------//
// �e�N�X�`��U���W�l�̎擾���s���܂��B                             //
//-----------------------------------------------------------------//
double CObjDetailData::getTextureCoordinateU(void)
{
//  return textureU;
  return st_texture.u;
}

//-----------------------------------------------------------------//
// �e�N�X�`��V���W�l�̎擾���s���܂��B                             //
//-----------------------------------------------------------------//
double CObjDetailData::getTextureCoordinateV(void)
{
//  return textureV;
  return st_texture.v;
}

//-----------------------------------------------------------------//
// �@�����W�l�̎擾(�z��)���s���܂��B                              //
//-----------------------------------------------------------------//
double *CObjDetailData::getNormalCoordinates(void)
{
  return normalCoordinate.getPointAll();
}

//-----------------------------------------------------------------//
// �@��X���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getNormalCoordinateX(void)
{
  return normalCoordinate[0];
}

//-----------------------------------------------------------------//
// �@��Y���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getNormalCoordinateY(void)
{
  return normalCoordinate[1];
}

//-----------------------------------------------------------------//
// �@��Z���W�l�̎擾���s���܂��B                                   //
//-----------------------------------------------------------------//
double CObjDetailData::getNormalCoordinateZ(void)
{
  return normalCoordinate[2];
}

//-----------------------------------------------------------------//
// ���_���W�l�̐ݒ�(�z��w��)���s���܂��B                          //
//-----------------------------------------------------------------//
void CObjDetailData::setVertexCoordinate(const double *pval)
{
  vertexCoordinate.setPointAll(pval);
}

//-----------------------------------------------------------------//
// ���_���W�l�̐ݒ�(�ʎw��)���s���܂��B                          //
//-----------------------------------------------------------------//
void CObjDetailData::setVertexCoordinate(double val_x
                                       , double val_y
                                       , double val_z)
{
  vertexCoordinate.setPointX(val_x);
  vertexCoordinate.setPointY(val_y);
  vertexCoordinate.setPointZ(val_z);
}

//-----------------------------------------------------------------//
// ���_���W�l�̐ݒ�(3D�x�N�g���N���X�I�u�W�F�N�g�w��)���s���܂��B  //
//-----------------------------------------------------------------//
void CObjDetailData::setVertexCoordinate(const CThreedVector *pval)
{
  vertexCoordinate = *pval;
}

//-----------------------------------------------------------------//
// �e�N�X�`�����W�l�̐ݒ�(�z��w��)���s���܂��B                    //
//-----------------------------------------------------------------//
void CObjDetailData::setTextureCoordinate(const double *pval)
{
//  textureU = *pval;
//  textureV = *(pval + 1);
  st_texture.u = *pval;
  st_texture.v = *(pval + 1);
}

//-----------------------------------------------------------------//
// �e�N�X�`�����W�l�̐ݒ�(�ʎw��)���s���܂��B                    //
//-----------------------------------------------------------------//
void CObjDetailData::setTextureCoordinate(double val_u, double val_v)
{
//  textureU = val_u;
//  textureV = val_v;
  st_texture.u = val_u;
  st_texture.v = val_v;
}

//-----------------------------------------------------------------//
// �e�N�X�`��U���W�l�̐ݒ���s���܂��B                             //
//-----------------------------------------------------------------//
void CObjDetailData::setTextureCoordinateU(double val)
{
//  textureU = val;
  st_texture.u = val;
}

//-----------------------------------------------------------------//
// �e�N�X�`��V���W�l�̐ݒ���s���܂��B                             //
//-----------------------------------------------------------------//
void CObjDetailData::setTextureCoordinateV(double val)
{
//  textureV = val;
  st_texture.v = val;
}

//-----------------------------------------------------------------//
// �@�����W�l�̐ݒ�(�z��w��)���s���܂��B                          //
//-----------------------------------------------------------------//
void CObjDetailData::setNormalCoordinate(const double *pval)
{
  CThreedVector temp((double *)pval);
  normalCoordinate = temp.getNormalizeALL();
}

//-----------------------------------------------------------------//
// �@�����W�l�̐ݒ�(�ʎw��)���s���܂��B                          //
//-----------------------------------------------------------------//
void CObjDetailData::setNormalCoordinate(double val_x
                                       , double val_y
                                       , double val_z)
{
  CThreedVector temp(val_x, val_y, val_z);
  normalCoordinate = temp.getNormalizeALL();
}

//-----------------------------------------------------------------//
// �@�����W�l�̐ݒ�(3D�x�N�g���N���X�I�u�W�F�N�g)���s���܂��B      //
//-----------------------------------------------------------------//
void CObjDetailData::setNormalCoordinate(const CThreedVector *pval)
{
  CThreedVector temp(*pval);
  normalCoordinate = temp.getNormalizeALL();
}
