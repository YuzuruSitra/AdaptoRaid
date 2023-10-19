#include ".\threedvector.h"

//-----------------------------------------------------------------//
//  �f�t�H���g�R���X�g���N�^                                       //
//-----------------------------------------------------------------//
CThreedVector::CThreedVector(void)
{
  for(int i=0; i < 3; i++)
  {
    this->fvector[i] = 0.0;
  }
}

//-----------------------------------------------------------------//
//  �R���X�g���N�^(���W�l�z��w��)                                 //
//-----------------------------------------------------------------//
CThreedVector::CThreedVector(double *pval)
{
  for(int i=0; i < 3; i++)
  {
    this->fvector[i] = pval[i];
  }
}

//-----------------------------------------------------------------//
//  �R���X�g���N�^(���W�l�ʎw��)                                 //
//-----------------------------------------------------------------//
CThreedVector::CThreedVector(double val1, double val2, double val3)
{
  this->fvector[0] = val1;
  this->fvector[1] = val2;
  this->fvector[2] = val3;
}

//-----------------------------------------------------------------//
//  �R�s�[�R���X�g���N�^                                           //
//-----------------------------------------------------------------//
CThreedVector::CThreedVector(const CThreedVector &val)
{
  fvector[0] = val.fvector[0];
  fvector[1] = val.fvector[1];
  fvector[2] = val.fvector[2];
}

//-----------------------------------------------------------------//
//  �f�X�g���N�^                                                   //
//-----------------------------------------------------------------//
CThreedVector::~CThreedVector(void)
{
}

//-----------------------------------------------------------------//
//  X���W�l�ݒ�                                                    //
//-----------------------------------------------------------------//
void CThreedVector::setPointX(double val)
{
  this->fvector[0] = val;
}

//-----------------------------------------------------------------//
//  Y���W�l�ݒ�                                                    //
//-----------------------------------------------------------------//
void CThreedVector::setPointY(double val)
{
  this->fvector[1] = val;
}

//-----------------------------------------------------------------//
//  Z���W�l�ݒ�                                                    //
//-----------------------------------------------------------------//
void CThreedVector::setPointZ(double val)
{
  this->fvector[2] = val;
}

//-----------------------------------------------------------------//
//  �x�N�g�����W�l�ݒ�                                             //
//-----------------------------------------------------------------//
void CThreedVector::setPointAll(const double *pval)
{
  for(int i=0; i < 3; i++)
  {
    this->fvector[i] = pval[i];
  }
}

//-----------------------------------------------------------------//
//  X���W�l�擾                                                    //
//-----------------------------------------------------------------//
double CThreedVector::getPointX(void)
{
  return this->fvector[0];
}

//-----------------------------------------------------------------//
//  Y���W�l�擾                                                    //
//-----------------------------------------------------------------//
double CThreedVector::getPointY(void)
{
  return this->fvector[1];
}

//-----------------------------------------------------------------//
//  Z���W�l�擾                                                    //
//-----------------------------------------------------------------//
double CThreedVector::getPointZ(void)
{
  return this->fvector[2];
}

//-----------------------------------------------------------------//
//  �x�N�g�����W�l�擾                                             //
//-----------------------------------------------------------------//
double *CThreedVector::getPointAll(void)
{
  return this->fvector;
}

//-----------------------------------------------------------------//
//  �P�ʃx�N�g��X���W�l�擾                                        //
//-----------------------------------------------------------------//
double CThreedVector::getNormalizeX(void)
{
  culcNormalVector();      // �P�ʃx�N�g�����v�Z
  return this->fnormalvector[0];
}

//-----------------------------------------------------------------//
//  �P�ʃx�N�g��Y���W�l�擾                                        //
//-----------------------------------------------------------------//
double CThreedVector::getNormalizeY(void)
{
  culcNormalVector();      // �P�ʃx�N�g�����v�Z
  return this->fnormalvector[1];
}

//-----------------------------------------------------------------//
//  �P�ʃx�N�g��Z���W�l�擾                                        //
//-----------------------------------------------------------------//
double CThreedVector::getNormalizeZ(void)
{
  culcNormalVector();      // �P�ʃx�N�g�����v�Z
  return this->fnormalvector[2];
}

//-----------------------------------------------------------------//
//  �P�ʃx�N�g�����W�l�擾                                         //
//-----------------------------------------------------------------//
double *CThreedVector::getNormalizeALL(void)
{
  culcNormalVector();      // �P�ʃx�N�g�����v�Z
  return this->fnormalvector;
}

//-----------------------------------------------------------------//
//  �x�N�g���̒����擾                                             //
//-----------------------------------------------------------------//
double CThreedVector::getLength(void)
{
  culcLength();      // �x�N�g���̒������v�Z
  return this->fvectorlength;
}

//-----------------------------------------------------------------//
//  �x�N�g���̉��Z                                                 //
//-----------------------------------------------------------------//
CThreedVector CThreedVector::operator+(CThreedVector &val)
{
  CThreedVector temp;    // �ꎞ�I�u�W�F�N�g

  temp.setPointX(this->getPointX() + val.getPointX());
  temp.setPointY(this->getPointY() + val.getPointY());
  temp.setPointZ(this->getPointZ() + val.getPointZ());

  return temp;
}

//-----------------------------------------------------------------//
//  �x�N�g���̌��Z                                                 //
//-----------------------------------------------------------------//
CThreedVector CThreedVector::operator-(CThreedVector &val)
{
  CThreedVector temp;    // �ꎞ�I�u�W�F�N�g

  temp.setPointX(this->getPointX() - val.getPointX());
  temp.setPointY(this->getPointY() - val.getPointY());
  temp.setPointZ(this->getPointZ() - val.getPointZ());

  return temp;
}

//-----------------------------------------------------------------//
//  �X�J���[�̏�Z                                                 //
//-----------------------------------------------------------------//
CThreedVector CThreedVector::operator*(double val)
{
  CThreedVector temp;    // �ꎞ�I�u�W�F�N�g

  temp.setPointX(this->getPointX() * val);
  temp.setPointY(this->getPointY() * val);
  temp.setPointZ(this->getPointZ() * val);

  return temp;
}

//-----------------------------------------------------------------//
//  �X�J���[�̏��Z                                                 //
//-----------------------------------------------------------------//
CThreedVector CThreedVector::operator/(double val)
{
  CThreedVector temp;    // �ꎞ�I�u�W�F�N�g

  // 0���Z�Ή�
  if(val == 0.0f)
  {
    cout << "�X�J���[�ʂ̌��Z��0���w�肳��܂����B" << endl;
    return NULL;
  }

  temp.setPointX(this->getPointX() / val);
  temp.setPointY(this->getPointY() / val);
  temp.setPointZ(this->getPointZ() / val);

  return temp;
}

//-----------------------------------------------------------------//
//  �x�N�g���̑��                                                 //
//-----------------------------------------------------------------//
CThreedVector &CThreedVector::operator=(const CThreedVector &val)
{
  this->fvector[0] = val.fvector[0];
  this->fvector[1] = val.fvector[1];
  this->fvector[2] = val.fvector[2];

  return *this;
}

//-----------------------------------------------------------------//
//  �x�N�g���̔�r(==)                                             //
//-----------------------------------------------------------------//
bool CThreedVector::operator==(CThreedVector &val)
{
  return (this->fvector[0] == val.fvector[0]
      && this->fvector[1] == val.fvector[1]
      && this->fvector[2] == val.fvector[2]);
}

//-----------------------------------------------------------------//
//  �x�N�g���̔�r(!=)                                             //
//-----------------------------------------------------------------//
bool CThreedVector::operator!=(CThreedVector &val)
{
  return (this->fvector[0] != val.fvector[0]
      && this->fvector[1] != val.fvector[1]
      && this->fvector[2] != val.fvector[2]);
}

//-----------------------------------------------------------------//
//  �s��v�f�̎擾                                                 //
//-----------------------------------------------------------------//
double & CThreedVector::operator[](int id)
{
  // 0��菬�����A15���傫���ꍇ�̓G���[
  if(id > 4 || 0 > id)
  {
    cout << "�����̎w�肪�s��(0��菬�����A����4���傫��)�ł��B" << endl;
    exit(1);
  }

  return this->fvector[id];
}

//-----------------------------------------------------------------//
//  ���ώ擾                                                       //
//-----------------------------------------------------------------//
double CThreedVector::getDotProduct(CThreedVector &val)
{
  return this->getPointX() * val.getPointX()
      + this->getPointY() * val.getPointY()
      + this->getPointZ() * val.getPointZ();
}

//-----------------------------------------------------------------//
//  �O�ώ擾                                                       //
//-----------------------------------------------------------------//
CThreedVector CThreedVector::getCrossProduct(CThreedVector &val)
{
  CThreedVector temp;    // �ꎞ�I�u�W�F�N�g
  
  temp.setPointX((this->getPointY() * val.getPointZ()) - (this->getPointZ() * val.getPointY()));
  temp.setPointY((this->getPointZ() * val.getPointX()) - (this->getPointX() * val.getPointZ()));
  temp.setPointZ((this->getPointX() * val.getPointY()) - (this->getPointY() * val.getPointX()));

  return temp;
}

//-----------------------------------------------------------------//
//  �p�x�擾                                                       //
//-----------------------------------------------------------------//
double CThreedVector::getAngle(CThreedVector &val)
{
  double angle;      // �p�x

  // acos(���� / |A|*|B|)
  angle = acos(this->getDotProduct(val) / (this->fvectorlength * val.fvectorlength));
  // ���W�A������p�x�ɕϊ�
  angle = (angle * 180.0f) / (double)M_PI;

  return angle;
}

//-----------------------------------------------------------------//
//  �x�N�g���̒������v�Z                                           //
//-----------------------------------------------------------------//
void CThreedVector::culcLength(void)
{
  this->fvectorlength = sqrt(pow(this->fvector[0], 2)
                + pow(this->fvector[1], 2)
                + pow(this->fvector[2], 2));
}

//-----------------------------------------------------------------//
//  �P�ʃx�N�g�����v�Z                                             //
//-----------------------------------------------------------------//
void CThreedVector::culcNormalVector(void)
{
  culcLength();

  for(int i = 0; i < 3; i++)
  {
    // �x�N�g���̒�����0�ł���ꍇ
    if(this->fvectorlength == 0)
    {
      this->fnormalvector[i] = 0;
    }
    else
    {
      this->fnormalvector[i] = this->fvector[i] / this->fvectorlength;
    }
  }
}

//-----------------------------------------------------------------//
//  �����f�[�^�o��                                                 //
//-----------------------------------------------------------------//
void CThreedVector::show(ostream &ost)
{
  ost << "=======================================" << endl;
  ost << "������{��񁄁�" << endl;
  ost << "�x�N�g�� X:" << this->getPointX() << endl;
  ost << "�x�N�g�� Y:" << this->getPointY() << endl;
  ost << "�x�N�g�� Z:" << this->getPointZ() << endl;
  ost << "�x�N�g���̒���:" << this->getLength() << endl;
  ost << "�P�ʃx�N�g�� X:" << this->getNormalizeX() << endl;
  ost << "�P�ʃx�N�g�� Y:" << this->getNormalizeY() << endl;
  ost << "�P�ʃx�N�g�� Z:" << this->getNormalizeZ() << endl;
}
