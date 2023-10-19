#include ".\objloader.h"

using namespace objloader;

//-----------------------------------------------------------------//
// �f�t�H���g�R���X�g���N�^                                        //
//-----------------------------------------------------------------//
CObjLoader::CObjLoader(void)
{
  debug_cnt = 0;
}

//-----------------------------------------------------------------//
// �f�X�g���N�^                                                    //
//-----------------------------------------------------------------//
CObjLoader::~CObjLoader(void)
{
}

//-----------------------------------------------------------------//
// OBJ�t�@�C����Ǎ��݂܂��B                                       //
//-----------------------------------------------------------------//
bool CObjLoader::read(string objfnm)
{
  isMakeDispList = true;                         // �f�B�X�v���C���X�g�쐬����

  return (readTrans(objfnm));                    // OBJ�t�@�C���Ǎ���
}

//-----------------------------------------------------------------//
// read()�œǍ��ݍς݂�OBJ���f����`�悵�܂��B                     //
//-----------------------------------------------------------------//
void CObjLoader::draw(double enlarge)
{
  glPushMatrix();
  {
    // �g��䗦��1.0�{�ȊO�ł���ꍇ
    if(enlarge != 1.0)
    {
      // �g��䗦�Ń��f���̑傫���𒲐�
      glScaled(enlarge, enlarge, enlarge);
    }
    // �f�B�X�v���C���X�g���Ăяo��
    glCallList(displaylistNo);
  }
  glPopMatrix();
}

//-----------------------------------------------------------------//
// read()�œǍ��ݍς݂�OBJ���f���̖@����`�悵�܂��B               //
//-----------------------------------------------------------------//
void CObjLoader::drawNormal(double enlarge)
{
  glPushMatrix();
  {
    // �g��䗦��1.0�{�ȊO�ł���ꍇ
    if(enlarge != 1.0)
    {
      glScaled(enlarge, enlarge, enlarge);   // ���f���̊g��
    }
    // �@���`��p�f�B�X�v���C���X�g���Ăяo��
    glCallList(lineDisplaylistNo);
  }
  glPopMatrix();
}

//-----------------------------------------------------------------//
// read()�œǍ��ݍς݂�OBJ���f�������C���`�悵�܂��B               //
//-----------------------------------------------------------------//
void CObjLoader::drawLine(double enlarge)
{
  glDisable(GL_LIGHTING);                        // ���C�e�B���OOFF
  {
    glPolygonMode(GL_FRONT, GL_LINE);            // ���C���`��ݒ�ON
    {
      glPushMatrix();
      {
        // �g��䗦��1.0�{�ȊO�ł���ꍇ
        if(enlarge != 1.0)
        {
          glScaled(enlarge, enlarge, enlarge);   // ���f���̊g��
        }
        glCallList(displaylistNo);               // �@���`��p�f�B�X�v���C���X�g���Ăяo��
      }
      glPopMatrix();
    }
    glPolygonMode(GL_FRONT, GL_FILL);            // ���C���`��ݒ�OFF
  }
  glEnable(GL_LIGHTING);                         // ���C�e�B���OON
}

//-----------------------------------------------------------------//
// �@���Ȃ���OBJ���f�����A�@����t������OBJ�t�@�C���ɏo�͂��܂��B  //
//-----------------------------------------------------------------//
bool CObjLoader::write(string inFileNm, string outFileNm)
{
  bool ret = true;                               // �߂�l
  isMakeDispList = false;                        // �f�B�X�v���C���X�g�쐬�Ȃ�

  // OBJ�t�@�C���̓Ǎ���
  if(!readTrans(inFileNm))
  {
    ret = false;                                 // �ُ�I���ɐݒ�
  }
  // OBJ�t�@�C���̏o��
  else if(!writeTrans(outFileNm))
  {
    ret = false;                                 // �ُ�I���ɐݒ�
  }
  clear();                                       // �����f�[�^������

  return ret;                                    // �Ăяo�����ɕԂ�
}

//-----------------------------------------------------------------//
// ���f���`��̃f�B�X�v���C���X�g���쐬���܂��B                    //
//-----------------------------------------------------------------//
void CObjLoader::makeDisplayList(bool isDelete)
{
  float colors_line[] = {0.8f, 0.8f, 0.0f};      // �@���F
  float colorCl[] = {1.0, 1.0, 1.0, 1.0};        // �����l
  bool mtlFlg = false;
  bool drawFlg = false;

  pre_MaterialName = "";                         // �O��̃}�e���A������������

  displaylistNo = glGenLists(1);                 // �f�B�X�v���C���X�gNO�擾

  // �f�B�X�v���C���X�g�֓o�^
  glNewList(displaylistNo, GL_COMPILE);
  {
    // �`���`�̃��R�[�h�������[�v
    for(unsigned int i = 0; i < objData.size(); i++)
    {
      draw_face(objData[i]);                     // �ʂ̕`��
    }
    cmtl.clearMtl();                             // OBJ�p�}�e���A���ݒ�̏�����
  }
  glEndList();


  lineDisplaylistNo = glGenLists(1);             // �f�B�X�v���C���X�gNO�擾

  // �@���`��p�f�B�X�v���C���X�g�֓o�^
  glNewList(lineDisplaylistNo, GL_COMPILE);
  {
    glDisable(GL_LIGHTING);                      // ���C�e�B���OOFF
    {
      glColor3fv(colors_line);                   // �@���`��F��ݒ�

      glPushMatrix();
      {
        // �@���̃��C���`��
        glBegin(GL_LINES);
        {
          // �`���`�̃��R�[�h�������[�v
          for(unsigned int i = 0; i < objData.size(); i++)
          {
            draw_normal(objData[i]);                 // �@���̕`��
          }
        }
        glEnd();
      }
      glPopMatrix();

      glColor3fv(colorCl);                       // �}�e���A���ݒ菉����
    }
    glEnable(GL_LIGHTING);                       // ���C�e�B���OOFF
  }
  glEndList();

  // �������̈�J������̏ꍇ
  if(isDelete)
  {
    this->clear();                               // �������̈�J��
  }
}

//-----------------------------------------------------------------//
//  �I�u�W�F�N�g�̖ʂ̕`��(1�̖ʃf�[�^��`��)���s���܂��B        //
//-----------------------------------------------------------------//
void CObjLoader::draw_face(CObjData &val)
{
  int tempCnt;                                   // �J�E���^�ꎞ�ێ��p
  vector <int> v_index;                          // ���_�`��C���f�b�N�X

  v_index.push_back(0);                          // 1�ڂ̒��_�C���f�b�N�X
  v_index.push_back(1);                          // 2�ڂ̒��_�C���f�b�N�X
  v_index.push_back(2);                          // 3�ڂ̒��_�C���f�b�N�X

  // ���_����3�ł���ꍇ
  if(val.getObjDetailDataSize() == 3)
  {
    ;
  }
  // ���_����4�ł���ꍇ
  else if(val.getObjDetailDataSize() == 4)
  {
    // f�w��Ńp�����[�^��4�ł���ꍇ
    // ���_�̏��������́u0 �� 1 �� 3 �� 2�v�ƂȂ�
    v_index[2] = 3;
    v_index.push_back(2);
  }
  // ��L�ȊO
  else
  {
    v_index.clear();                             // �C���f�b�N�X�̃N���A
  }

  // �}�e���A����`�����ݒ肳��Ă���ꍇ
  if(val.getMtlName().length() > 0
    && pre_MaterialName.compare(val.getMtlName()) != 0)
  {
    // OBJ�p�}�e���A����`�̏�����
    cmtl.clearMtl();

    // OBJ�p�}�e���A����`�̓K�p
    cmtl.applyMtl(val.getMtlName());

    // �}�e���A���������ɐݒ�
    pre_MaterialName = val.getMtlName().c_str();
  }

  // �O�p�`�X�g���b�v�`��
  glBegin(GL_TRIANGLE_STRIP);
  {
  // ���_�̌������[�v
  for(unsigned int i = 0; i < v_index.size(); i++)
  {
    // �@�����W�̐ݒ�l�����݂���ꍇ
    if(val.getNormalFlg())
    {
      // �@�����W�̐ݒ�
      glNormal3dv(val.getObjDetailData(v_index[i])->getNormalCoordinates());
    }
    // �@�����W�̐ݒ�l�����݂��Ȃ��ꍇ
    else
    {
      // ���_�@���̌v�Z
      culcVertexNormal(val, v_index[i]);
    }
    
    // �e�N�X�`���ݒ�l�����݂���ꍇ
    if(val.getTextureFlg())
    {
      // �e�N�X�`�����W�̐ݒ�
      glTexCoord2f(val.getObjDetailData(v_index[i])->getTextureCoordinateU()
            , val.getObjDetailData(v_index[i])->getTextureCoordinateV());
    }
    // �e�N�X�`���ݒ�l�����݂��Ȃ��ꍇ
    else
    {
      // �X�L�b�v
      ;
    }
    // ���_���W�̐ݒ�
    glVertex3dv(val.getObjDetailData(v_index[i])->getVertexCoordinates());
  }
  }
  glEnd();
}

//-----------------------------------------------------------------//
// �I�u�W�F�N�g�̖ʂ̖@���`��(1�̖ʃf�[�^��`��)���s���܂��B     //
//-----------------------------------------------------------------//
void CObjLoader::draw_normal(CObjData &val)
{
  CThreedVector stPoint, endPoint;               // �n�_�A�I�_

    // ���_�̌������[�v
    for(unsigned int i = 0; i < val.getObjDetailDataSize(); i++)
    {
                                                 // ���_���W���擾
      stPoint.setPointAll(val.getObjDetailData(i)->getVertexCoordinates());

      glVertex3dv(stPoint.getPointAll());        // ���_���W�̕`��

      // �ʖ@�����W�̐ݒ�l�����݂���ꍇ
      if(val.getNormalFlg())
      {
                                                 // �ʖ@�����擾
        endPoint.setPointAll(val.getObjDetailData(i)->getNormalCoordinates());

        endPoint = stPoint + endPoint;           // ���_���W�{�ʖ@��
        glVertex3dv(endPoint.getPointAll());     // �@�����W�̕`��
      }
      // �@�����W�̐ݒ�l�����݂��Ȃ��ꍇ
      else
      {
        // ���_�@�����擾
        endPoint.setPointAll(val.getVertexNormal(i)->getNormalizeALL());

        endPoint = stPoint + endPoint;           // ���_���W�{���_�@��
        glVertex3dv(endPoint.getPointAll());     // ���_�@�����W�̕`��
      }
    }
}

//-----------------------------------------------------------------//
//  �ʖ@���̌v�Z���s���܂��B                                       //
//-----------------------------------------------------------------//
void CObjLoader::culcFaceNormal(CObjData &val)
{
  vector < CThreedVector > vArrayNo;             // �ʖ@�����X�g
  CThreedVector ctv_1, ctv_2, temp;              // �ėp�x�N�g��

  // �@����񂪊��ɑ��݂���ꍇ�A�������s��Ȃ�
  if(val.getNormalFlg())
  {
    return;                                      // �Ăяo�����ɖ߂�
  }

  // ���_�̐��������[�v
  for(unsigned int i = 0; i < val.getObjDetailDataSize(); i++)
  {
    // �x�N�g���̎擾(obj�ɐݒ肵�Ă���@�������擾)
    vArrayNo.push_back(val.getObjDetailData(i)->getVertexCoordinates());
  }
  // �����������K�v�ł��A�ʖ@���Ƃ��Ă͓��������Ȃ̂ŁA���_1�`3���g�p
  ctv_1 = vArrayNo[1] - vArrayNo[0];
  ctv_2 = vArrayNo[2] - vArrayNo[0];

  temp = ctv_1.getCrossProduct(ctv_2);           // �O�ς��擾
  val.setFaceNormal(&temp);                      // �O�ς�ʖ@���ɐݒ�
}

//-----------------------------------------------------------------//
//  ���_�@���̌v�Z���s���܂��B                                     //
//-----------------------------------------------------------------//
void CObjLoader::culcVertexNormal(CObjData &val, int cntval)
{
  vector <CThreedVector> faceNormal;             // �אږʖ@���o�b�t�@
  CThreedVector ctv_1                            // �ꎞ�x�N�g���̈�
              , ctv_2                            // �ꎞ�x�N�g���̈�
              , ctv_faceNormal                   // �ʖ@���x�N�g��
              , ctv_vertexNormal;                // ���_�@���x�N�g��

  // �v�Z�Ώۂ̃x�N�g�����W���R�s�[
  ctv_2.setPointAll(val.getObjDetailData(cntval)->getVertexCoordinates());

  // ���g�̖ʖ@����ǉ�
  faceNormal.push_back(*val.getFaceNormal());

  // ���ʐ������[�v
  for(unsigned int i = 0; i < objData.size(); i++)
  {
    // �����O���[�v�ł���ꍇ
    if(!strcmp(val.getGroupName().c_str(), objData[i].getGroupName().c_str()))
    {
      // 1�̖ʂ̑����_�������[�v
      for(unsigned int j = 0; j < objData[i].getObjDetailDataSize(); j++)
      {
        ctv_1.setPointAll(objData[i].getObjDetailData(j)->getVertexCoordinates());

        // ���_���W�������ł���ꍇ
        if(ctv_1 == ctv_2)
        {
          // �ʖ@���̒l�������łȂ��ꍇ
          if(objData[i].getFaceNormal() != val.getFaceNormal())
          {

            // �ʖ@����ǉ�
            faceNormal.push_back(*objData[i].getFaceNormal());
            break;
          }
        }
        // ���_���W���قȂ�ꍇ
        else
        {
          // �X�L�b�v
          ;
        }
      }
    }
  }

  // �אڂ����ʖ@�������[�v
  for(unsigned int i = 0; i < faceNormal.size(); i++)
  {
    // �ʖ@�������Z
    ctv_faceNormal = ctv_faceNormal + faceNormal[i];
  }

  // �P�ʃx�N�g����(���_�@��)
  CThreedVector ctv_dot(ctv_faceNormal.getNormalizeALL());

  // �X���[�W���O�p�Ƃ̔�r�ɂ��A�ʖ@���E���_�@���̂ǂ�����g�p���邩����
  // ���όv�Z(���g�̖@���Ɨאڂ���ʂ̖@��)
  double dot = val.getFaceNormal()->getDotProduct(ctv_dot);

  // �X���[�W���O�p�x�̃��W�A��
  double angle = cos(SMOOTHING_ANGLE * M_PI / 180.0f);

  // �X���[�W���O�p�Ɠ����A�܂��͑傫���ꍇ
  if(dot >= angle)
  {
    // ���_�@����ݒ�
    glNormal3dv(ctv_faceNormal.getNormalizeALL());

    // ���_�@����ۑ�
    val.addVertexNormal(ctv_faceNormal);
  }
  // �X���[�W���O�p��菬�����ꍇ
  else if(dot < angle)
  {
    // �ʖ@����ݒ�
    glNormal3dv(val.getFaceNormal()->getPointAll());
    val.addVertexNormal(*val.getFaceNormal());
  }
  // �@�����W�p�C���f�b�N�X��ݒ�
  val.setNormalIndex(cntval, vf_cnt);

  // �@�����W�p�C���f�b�N�X��+1
  vf_cnt++;
}

//-----------------------------------------------------------------//
//  �����f�[�^�������������s���܂��B                               //
//-----------------------------------------------------------------//
void CObjLoader::clear(void)
{
  debug_cnt = 0;                                 // �f�o�b�O�p�J�E���^
  vf_cnt = 1;                                    // ���_�@���p�C���f�b�N�X�J�E���^

  v_v.clear();                                   // ���_���W�p vector
  v_vn.clear();                                  // �@�����W vector
  v_vt.clear();                                  // �e�N�X�`�����W vector
  v_f.clear();                                   // �ʂ̃f�[�^ vector

  objData.clear();                               // OBJ��{�f�[�^
  v_mtlfn.clear();                               // �}�e���A���t�@�C���� vector
}

//-----------------------------------------------------------------//
// �����ł���OBJ�t�@�C�������g�p���āAOBJ�t�@�C����Ǎ��݂܂��B    //
//-----------------------------------------------------------------//
bool CObjLoader::readTrans(string objfnm)
{
  bool ret = false;                              // �߂�l

  ifstream ifs;                                  // ���̓t�@�C���p�X�g���[��

  char line_buff[255];                           // ���C���o�b�t�@
  char *psrc;                                    // �����񌟍��p�|�C���^
  char *ptemp;                                   // �ėp�|�C���^
  char *token;                                   // �����񕪊��p�|�C���^

  string mtl_buff;                               // �}�e���A����`���o�b�t�@
  string group_buff;                             // �O���[�v���o�b�t�@

  vector<double> v_temp;                         // �ꎞ�̈�

  CThreedVector vectorCtv;                       // �x�N�g���ꎞ�̈�
  CThreedVector normalCtv;                       // �@���x�N�g���ꎞ�̈�

  St_TextureCoordinate textureCoordinate_temp;   // �e�N�X�`�����W�ꎞ�̈�

  int groupNoCnt = 0;                            // �O���[�vNO�J�E���^

  CObjData objData_temp;                         // �ꎞOBJ�f�[�^
  CObjDetailData objDetailData_temp;             // �ꎞOBJ�ڍ׃f�[�^

  bool vn_flg = false;                           // VN�ݒ�t���O(true:���݂���, false:���݂��Ȃ�)

  clear();                                       // ����������

  ifs.open(objfnm.c_str(), ios::in);             // obj�t�@�C���I�[�v��

  // �t�@�C���I�[�v���`�F�b�N
  if(!ifs.is_open())
  {
    cout << "�Ǎ��݃t�@�C���̃I�[�v���Ɏ��s���܂����Bfile: " << objfnm.c_str() << endl;
    return ret;
  }

  // OBJ�i�[�f�B���N�g���p�X���擾
  string::size_type copysize = objfnm.rfind("/");
  string objdir = objfnm.substr(0, copysize+1);

  ifs.unsetf(ios::skipws);                       // �u�����N���X�L�b�v�����Ȃ�
  string mtlpath;                                // mtl�i�[�f�B���N�g���p�X

  // EOF�����o�����܂Ń��[�v
  while(!ifs.eof())
  {
    ifs.getline(line_buff, 255 - 1);             // �P�s�Ǎ���
    psrc = line_buff;

    // �擪���u#�v�ł���ꍇ(�R�����g����)
    if(*psrc == '#')
    {
      ;  // �X�L�b�v
    }
    else if(*psrc == 'v')
    {
      // �@�����W�̎w��ł���ꍇ
      if(*(psrc + 1) == 'n')
      {
        // �u�����N����؂蕶���Ƃ��Č���
        token = strtok((psrc + 3), " ");
        for(int i = 0; token != NULL; i++, token = strtok(NULL, " "))
        {
          normalCtv[i] = atof(token);            // �@�����W��ݒ�
        }
        // �P�ʃx�N�g���ōč쐬
        CThreedVector Ctvtmp(normalCtv.getNormalizeALL());
        v_vn.push_back(Ctvtmp);                  // �@���x�N�g����ǉ�
        vn_flg = true;                           // VN��`�L���t���O��ON
      }
      // �e�N�X�`�����W�̎w��ł���ꍇ
      else if(*(psrc + 1) == 't')
      {
        // �u�����N����؂蕶���Ƃ��Č���
        token = strtok((psrc + 3), " ");
        for(int i = 0; token != NULL; i++, token = strtok(NULL, " "))
        {
          // U���W�l�ł���ꍇ
          if(i == 0)
          {
            textureCoordinate_temp.u = atof(token);// �e�N�X�`��U���W��ݒ�
          }
          // V���W�l�ł���ꍇ
          else if(i == 1)
          {
            textureCoordinate_temp.v = atof(token);// �e�N�X�`��V���W��ݒ�
          }
          // ��L�ȊO�ł���ꍇ
          else
          {
            ;
          }
        }
        v_vt.push_back(textureCoordinate_temp);  // �e�N�X�`�����W vector�ɒǉ�

      }
      // ���_���W�̎w��ł���ꍇ
      else
      {
        // �u�����N����؂蕶���Ƃ��Č���
        token = strtok((psrc + 2), " ");

        // �g�[�N�������݂���ꍇ
        if(token != NULL)
        {
          // �g�[�N�����Ȃ��Ȃ�܂Ń��[�v
          for(int i = 0; token != NULL; i++, token = strtok(NULL, " "))
          {
            vectorCtv[i] = atof(token);          // ���_���W��ݒ�
          }
        }
        v_v.push_back(vectorCtv);                // ���_���W�f�[�^��ǉ�
      }
    }
    // �`���`
    else if(*psrc == 'f')
    {
      vector< vector<int> > v_i;                 // �ʂ��Ǘ�
      vector<int> v_i_temp;                      // ���_���W���Ǘ�
      vector<char*> v_c;                         // �����񕪊��p�ꎞ�̈�
      St_vf_detail_data vf_data;                 // �C���f�b�N�X�Ǘ��p�ꎞ�̈�

      int cnt = 0;                               // �����J�E���^
      bool flg = false;                          // �e�N�X�`�����W�w��L��(true:��, false:�L)

      // �u�����N����؂蕶���Ƃ��Č���
      token = strtok((psrc + 2), " ");

      // ���_�����؂蕪��
      while(token != NULL)
      {
        v_c.push_back(token);
        token = strtok(NULL, " ");
      }

      // �g�[�N�����Ȃ��Ȃ�܂Ń��[�v
      for(unsigned int i = 0; i< v_c.size(); i++)
      {
        // �e�N�X�`�����W�w�肪�Ȃ��ꍇ(f (v)//(vn))
        if(strstr(v_c[i], "//"))
        {
          // �e�N�X�`�����W�w��Ȃ�
          flg = true;
        }
        // �u/�v����؂蕶���Ƃ��ĕ�������
        token = strtok(v_c[i], "/");
        for(int i = 0; token != NULL; i++, token = strtok(NULL, "/"))
        {
          vf_data.detail_data[i] = atol(token);  // ���_���WNo�A�e�N�X�`�����WNo�A�@�����WNo�̂����ꂩ��ݒ�

          cnt++;                                 // �g�[�N�������C���N�������g
        }

        // �e�N�X�`�����W�w�肪�Ȃ��A���̓g�[�N�����R��菭�Ȃ��ꍇ
        if(flg || cnt < 3)
        {
          // �e�N�X�`�����W�w�肪�Ȃ��ꍇ
          if(flg)
          {
                                                 // �g�p����̈��ύX
            vf_data.detail_data[2] = vf_data.detail_data[1];

            vf_data.detail_data[1] = 0;          // �g�p���Ȃ��̈��0��ݒ�
            flg = false;                         // �t���O�̏�����
          }
          // �g�[�N�����R��菭�Ȃ��ꍇ
          else
          {
            // �R�ڂ̗v�f��0�ɐݒ�
            vf_data.detail_data[2] = 0;          // �g�p���Ȃ��̈��0��ݒ�
          }

          // ���_���W�̎w�肵���Ȃ��ꍇ(f (v))
          if(cnt == 1)
          {
            vf_data.detail_data[2] = 0;          // �g�p���Ȃ��̈��0��ݒ�
          }
        }
        // ���W�C���f�b�N�X���ݒ�
        objData_temp.addIndex(vf_data);

        // ���_���ݒ�
        objDetailData_temp.setVertexCoordinate(v_v[vf_data.detail_data[0] - 1].getPointAll());

        // �e�N�X�`����񂪑��݂���ꍇ
        if(vf_data.detail_data[1])
        {
          // �e�N�X�`�����̐ݒ�
          objData_temp.setTextureFlg(true);
          objDetailData_temp.setTextureCoordinateU(v_vt[vf_data.detail_data[1] - 1].u);
          objDetailData_temp.setTextureCoordinateV(v_vt[vf_data.detail_data[1] - 1].v);
        }
        // �e�N�X�`����񂪑��݂��Ȃ��ꍇ
        else
        {
          // �e�N�X�`�����𖳂��ɐݒ�
          objData_temp.setTextureFlg(false);
        }

        // �@����񂪑��݂���ꍇ
        if(vn_flg && vf_data.detail_data[2])
        {
          // �@�����̐ݒ�
          CThreedVector temp(v_vn[vf_data.detail_data[2] - 1].getPointAll());

          objData_temp.setNormalFlg(true);
          objData_temp.setFaceNormal(&temp);
          objDetailData_temp.setNormalCoordinate(v_vn[vf_data.detail_data[2] - 1].getPointAll());
        }
        // �@����񂪑��݂��Ȃ��ꍇ
        else
        {
          // �@�����𖳂��ɐݒ�
          objData_temp.setNormalFlg(false);
        }

        // OBJ��{���ɒǉ�
        objData_temp.addObjDetailData(objDetailData_temp);

        cnt = 0;
      }

      objData_temp.setGroupNo(groupNoCnt);       // �O���[�vNo�ݒ�
      objData_temp.setGroupName(group_buff);     // �O���[�v���ݒ�
      objData_temp.setMtlName(mtl_buff);         // �}�e���A����`���ݒ�
      culcFaceNormal(objData_temp);              // �ʖ@���̌v�Z

      objData.push_back(objData_temp);           // OBJ��{���ɒǉ�
      objData_temp.clear();                      // OBJ�f�[�^�̏�����
    }
    // �O���[�s���O��`
    else if(*psrc == 'g')
    {
      bool findflg = false;                      // ����HIT�t���O

      // ���[�h�ςݖʐ������[�v
      for(unsigned int gcnt = 0; gcnt < objData.size(); gcnt++)
      {
        // �O���[�v���������ł���ꍇ
        if(strcmp(objData[gcnt].getGroupName().c_str(), psrc + 2) == 0)
        {
          group_buff = psrc + 2;                 // �����_�ł̃O���[�v����ݒ�
          findflg = true;                        // ����HIT�t���OON
          break;
        }
      }

      // ������HIT���Ȃ������ꍇ
      if(!findflg)
      {
        group_buff = psrc + 2;                   // �����_�ł̃O���[�v����ݒ�
      }
    }
    // mtl�t�@�C���f�[�^��荞�ݎw��ł���ꍇ
    else if(ptemp = strstr(psrc, "mtllib"))
    {
      // OBJ�i�[�f�B���N�g���p�X���擾
      string::size_type copysize = objfnm.rfind("/");
      mtlpath = objfnm.substr(0, copysize+1);

      mtlpath.append(ptemp + 7);
      if(!cmtl.loadMtl(mtlpath))                 // mtl�t�@�C���Ǎ���
      {
        return false;
      }
      v_mtlfn.push_back(ptemp + 7);              // �}�e���A���t�@�C������ǉ�
    }
    // �}�e���A����`�ݒ�̎w��ł���ꍇ
    else if(ptemp = strstr(psrc, "usemtl"))
    {
      mtl_buff = ptemp + 7;
    }
    else
    {
      ;                                          // �X�L�b�v
    }
  }
  ifs.close();                                   // obj�t�@�C���N���[�Y

  makeDisplayList(isMakeDispList);               // �f�B�X�v���C���X�g�֓o�^

  ret = true;

  return ret;
}

//-----------------------------------------------------------------//
// read()�œǍ��ݍς݂�OBJ���f����OBJ�t�@�C���ɏo�͂��܂��B        //
//-----------------------------------------------------------------//
bool CObjLoader::writeTrans(string filenm)
{
  bool ret = false;                              // �߂�l
  unsigned int i = 0;

  ofstream ofs(filenm.c_str(), ios::out);        // obj�t�@�C���I�[�v��

  // �t�@�C���I�[�v���`�F�b�N
  if(!ofs.is_open())
  {
    cout << "�o�̓t�@�C���̃I�[�v���Ɏ��s���܂����Bfile: " << filenm.c_str() << endl;
    return ret;
  }

  ofs << "# Create by OBJ Loader." << endl;
  ofs << endl;

  // �g�p����}�e���A���t�@�C���̐錾
  for(i = 0; i < v_mtlfn.size(); i++)
  {
    ofs << "mtllib " << v_mtlfn[i].c_str() << endl;
  }
  ofs << "# " << i << " material files." << endl;
  ofs << endl;

  // ���_���W�̗�
  for(i = 0; i < v_v.size(); i++)
  {
    ofs << "v " << v_v[i].getPointX() << " "
                << v_v[i].getPointY() << " "
                << v_v[i].getPointZ() << endl;
  }
  ofs << "# " << i << " vertices." << endl;
  ofs << endl;

  // �e�N�X�`�����W�̗�
  for(i = 0; i < v_vt.size(); i++)
  {
    //ofs << "vt " << v_vt[i].getU() << " "
    //             << v_vt[i].getV() << endl;
    ofs << "vt " << v_vt[i].u << " "
                 << v_vt[i].v << endl;
  }
  ofs << "# " << i << " texture vertices." << endl;
  ofs << endl;

  // �@�����W�̗�
  // �@���L�q���Ȃ��ꍇ
  if(v_vn.size() == 0)
  {
    CThreedVector *tmp;                           // �ꎞ�o�b�t�@

    // OBJ�̖ʐ������[�v
    for(i = 0; i < objData.size(); i++)
    {
      // �ʂ̒��_�������[�v
      for(unsigned int j = 0; j < objData[i].getObjDetailDataSize(); j++)
      {
        // �v�Z�ςݖ@�����W�擾
        tmp = objData[i].getVertexNormal(j);
        // �@�����W�̏o��
        ofs << "vn " << tmp->getPointX() << " "
                     << tmp->getPointY() << " "
                     << tmp->getPointZ() << endl;
      }
    }
  }
  // �@���L�q������ꍇ
  else
  {
    // ��`�ς݂̖@���������[�v
    for(i = 0; i < v_vn.size(); i++)
    {
      // �@�����W�̏o��
      ofs << "vn " << v_vn[i].getPointX() << " "
                  << v_vn[i].getPointY() << " "
                  << v_vn[i].getPointZ() << endl;
    }
  }
  ofs << "# " << i << " normal vertices." << endl;
  ofs << endl;

  string groupNametmp("");                       // �O���[�v�t�@�C�����ꎞ�o�b�t�@
  string mtlNametmp("");                         // MTL�t�@�C�����ꎞ�o�b�t�@

  // OBJ�̖ʐ������[�v
  for(i = 0; i < objData.size(); i++)
  {
    // �O��̃O���[�v���ƈقȂ�ꍇ
    if(strcmp(groupNametmp.c_str(), objData[i].getGroupName().c_str()) != 0)
    {
      ofs << "g " << objData[i].getGroupName().c_str() << endl;
      groupNametmp = objData[i].getGroupName().c_str();
    }
    // �O��̃}�e���A�����ƈقȂ�ꍇ
    if(strcmp(mtlNametmp.c_str(), objData[i].getMtlName().c_str()) != 0)
    {
      ofs << "usemtl " << objData[i].getMtlName().c_str() << endl;
      mtlNametmp = objData[i].getMtlName().c_str();
    }

    ofs << "f";

    // �ʂ̒��_�������[�v
    for(unsigned int j = 0; j < objData[i].getIndexSize(); j++)
    {
      ofs << " ";
      // ���_���W�C���f�b�N�X���o��
      if(objData[i].getIndex(j).detail_data[0] != -1)
      {
        ofs << objData[i].getIndex(j).detail_data[0];
      }
      ofs << "/";

      // �e�N�X�`�����W�C���f�b�N�X�����݂���ꍇ
      if(objData[i].getIndex(j).detail_data[1] != -1)
      {
        // �e�N�X�`�����W�C���f�b�N�X���o��
        ofs << objData[i].getIndex(j).detail_data[1];
      }

      // �@�����W�C���f�b�N�X�����݂���ꍇ
      if(objData[i].getIndex(j).detail_data[2] != -1)
      {
        // �@�����W�C���f�b�N�X���o��
        ofs << "/";
        ofs << objData[i].getIndex(j).detail_data[2];
      }
    }
    ofs << endl;
  }
  ofs << "# " << i << " elements." << endl;
  ofs.close();

  ret = true;

  return ret;
}
