#include ".\mtl.h"

/////////////////////////////
#ifdef _WIN32
PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
/////////////////////////////

//-----------------------------------------------------------------//
// �f�t�H���g�R���X�g���N�^                                        //
//-----------------------------------------------------------------//
CMtl::CMtl(void)
{
	//////////////////////////
#ifdef _WIN32
  glActiveTexture =
		(PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
#endif
	//////////////////////////
  texturebind_flg = false;                       // �e�N�X�`���o�C���h�t���O������
  spherebind_flg = false;                        // �X�t�B�A�e�N�X�`���o�C���h�t���O������
  cubebind_flg = false;                          // �L���[�u�e�N�X�`���o�C���h�t���O������
}

//-----------------------------------------------------------------//
// �f�X�g���N�^                                                    //
//-----------------------------------------------------------------//
CMtl::~CMtl(void)
{
}

//-----------------------------------------------------------------//
// �}�e���A���t�@�C���̃��[�h���s���܂��B                          //
//-----------------------------------------------------------------//
bool CMtl::loadMtl(string mtlfnm)
{
  St_mtl_data *pst;                              // mtl�f�[�^�\���̈ꎞ�̈�
  int token_cnt = 0;                             // �g�[�N���p�J�E���^
  GLuint tNo_temp;                               // �e�N�X�`����(ID)�ꎞ�̈�
  char line_buff[255];                           // ���R�[�h�Ǎ��ݗp�o�b�t�@
  char bufftemp[255];                            // �ꎞ�̈�o�b�t�@
  char *psrc;                                    // �����񌟍��p�|�C���^
  char *token;                                   // �����񕪊��p�|�C���^
  ifstream ifs;                                  // �Ǎ��݃t�@�C���p�X�g���[��
  bool newflg = false;                           // ���񔻒�t���O

  // �Ǎ��݃t�@�C���I�[�v��
  ifs.open(mtlfnm.c_str(), ios::in);

  // �I�[�v���G���[�`�F�b�N
  if(!ifs.is_open())
  {
    cout << "�Ǎ��݃t�@�C���̃I�[�v���Ɏ��s���܂����B file: " << mtlfnm.c_str() << endl;
    return false;
  }

  // OBJ�i�[�f�B���N�g���p�X���擾
  string::size_type copysize = mtlfnm.rfind("/");
  string mtldir = mtlfnm.substr(0, copysize+1);

  ifs.unsetf(ios::skipws);                       // �u�����N���X�L�b�v�����Ȃ�

  string texpath;                                // �e�N�X�`���i�[�f�B���N�g���p�X

  // mtl�t�@�C���Ǎ���
  while(!ifs.eof())
  {
    // 1���R�[�h�Ǎ���
    ifs.getline(line_buff, 255 - 1);
    token_cnt = 0;

    // �擪���u#�v�ł���ꍇ
    if(line_buff[0] == '#')
    {
      ;                // �X�L�b�v
    }
    // �}�e���A����`��
    else if(psrc = strstr(line_buff, "newmtl"))
    {
      // 1��ڂ̏����ł���ꍇ
      if(!newflg)
      {
        newflg = true;
      }
      // ��L�ȊO�ł���ꍇ
      else
      {
        // mtl��`�ɒǉ�
        v_mtl.push_back(*pst);
        // �̈�J��
        delete pst;
      }
      pst = new St_mtl_data;
      pst->init();

      strcpy(bufftemp, (psrc + 7));
      pst->mtlnm = bufftemp;                     // �}�e���A����`���ݒ�
      pst->mtlfilenm = mtlfnm;                   // �}�e���A���t�@�C������ݒ�
    }
    // �e�N�X�`���}�b�s���O
    else if(psrc = strstr(line_buff, "map_Kd"))
    {
      pst->isTexture = true;                     // �e�N�X�`���}�b�s���OON

      texpath = mtldir;                          // �e�N�X�`���p�X��ݒ�
      texpath.append(psrc + 7);                  // �e�N�X�`������ǉ�
      pst->texturefnm = texpath;                 // �e�N�X�`���t�@�C�����ݒ�

      glGenTextures(1, &tNo_temp);               // �e�N�X�`����(ID)�擾
      pst->tNo = tNo_temp;                       // �e�N�X�`����(ID)�ݒ�

      // �e�N�X�`���t�@�C�����[�h
      if(!loadTexture(pst))
      {
        return false;
      }
    }

    // ��(�X�t�B�A)�}�b�s���O
    else if(psrc = strstr(line_buff, "map_Ka"))
    {
      pst->isSphereTexture = true;

      texpath = mtldir;                          // �e�N�X�`���p�X��ݒ�
      texpath.append(psrc + 7);                  // �e�N�X�`������ǉ�
      pst->texturefnm = texpath;                 // �e�N�X�`���t�@�C�����ݒ�

      glGenTextures(1, &tNo_temp);               // �e�N�X�`����(ID)�擾
      pst->tNo = tNo_temp;                       // �e�N�X�`����(ID)�ݒ�

      // �e�N�X�`���t�@�C�����[�h
      loadSphereTexture(pst);
    }
    // ���t���N�V����(�L���[�u)�}�b�s���O
    else if(psrc = strstr(line_buff, "refl"))
    {
      texpath.clear();                           // �e�N�X�`���i�[�f�B���N�g���p�X�̏�����
      // 6�̃e�N�X�`���t�@�C������ݒ�
      if(psrc = strstr(line_buff, "cube_top"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 9);                // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(top)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else if(psrc = strstr(line_buff, "cube_bottom"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 12);               // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(bottom)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else if(psrc = strstr(line_buff, "cube_front"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 11);               // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(front)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else if(psrc = strstr(line_buff, "cube_back"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 10);               // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(back)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else if(psrc = strstr(line_buff, "cube_left"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 10);               // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(left)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else if(psrc = strstr(line_buff, "cube_right"))
      {
        texpath = mtldir;                        // �e�N�X�`���p�X��ݒ�
        texpath.append(psrc + 11);               // �e�N�X�`������ǉ�
        pst->v_texturefnm.push_back(texpath);    // �e�N�X�`���t�@�C����(right)��ݒ�
        pst->textureCnt++;                       // �Ǎ��ݍς݃e�N�X�`����+1
      }
      else
      {
        cout << "���m�� refl ����`����܂����B rec:" << line_buff << endl;
        return false;
      }

      // 6�̃e�N�X�`����񂪑������ꍇ
      if(pst->textureCnt == 6)
      {
        pst->isCubeTexture = true;
        // �e�N�X�`����ǂ݁AglTexImage2D�ɐݒ�
        loadCubeTexture(pst);
      }
    }

    // �C���~�l�[�V����
    else if(psrc = strstr(line_buff, "illum"))
    {
      strcpy(bufftemp, (psrc + 6));
      pst->isIllumination = true;
      pst->illumination = atoi(bufftemp);        // �C���~�l�[�V�����l�ݒ�
    }
    // ����
    else if(psrc = strstr(line_buff, "Ka"))
    {
      pst->isAmbient = true;
      token = strtok((psrc + 3), " ");
      while(token != NULL)
      {
        // �����l�ݒ�(x, y, z)
        pst->ambient[token_cnt] = atof(token);
        token = strtok(NULL, " ");
        token_cnt++;
      }
    }
    // �g�U��
    else if(psrc = strstr(line_buff, "Kd"))
    {
      pst->isDiffuse = true;
      token = strtok((psrc + 3), " ");
      while(token != NULL)
      {
        // �g�U���l�ݒ�(x, y, z)
        pst->diffuse[token_cnt] = atof(token);
        token = strtok(NULL, " ");
        token_cnt++;
      }
    }
    // ���ʌ�
    else if(psrc = strstr(line_buff, "Ks"))
    {
      pst->isSpecular = true;                    // ���ʌ��w�肠��ɐݒ�
      token = strtok((psrc + 3), " ");

      // �g�[�N�����Ȃ��Ȃ�܂Ń��[�v
      while(token != NULL)
      {
        // ���ʌ��l�ݒ�(x, y, z)
        pst->specular[token_cnt] = atof(token);
        token = strtok(NULL, " ");
        token_cnt++;
      }
    }
    // ���ʌW��
    else if(psrc = strstr(line_buff, "Ns"))
    {
      pst->isShininess = true;
      strcpy(bufftemp, (psrc + 3));
      pst->shininess = atoi(bufftemp);           // ���ʌW���ݒ�
    }
    // �A���t�@�l(�����x�P��w��)
    else if(line_buff[0] == 'd')
    {
      // �A���t�@�l�̃R�s�[
      strcpy(bufftemp, &line_buff[2]);

      // �w��l��1.0f���傫���ꍇ
      if(1.0f < atof(bufftemp))
      {
        pst->isTransparency = true;
        pst->transparency = 1.0f;                // �A���t�@�l�ő�l��ݒ�
      }
      // �w��l��0.0f��菬�����ꍇ
      else if(0.0f > atof(bufftemp))
      {
        pst->isTransparency = true;
        pst->transparency = 0.0f;                // �A���t�@�l�ŏ��l��ݒ�
      }
      // ��L�ȊO�̏ꍇ
      else
      {
        pst->isTransparency = true;
        pst->transparency = atof(bufftemp);      // �A���t�@�l�ݒ�
      }
    }

    // �A���t�@�l(�����xRGB�w��)
    else if(psrc = strstr(line_buff, "Tf"))
    {
      float tmpTransparency = 0.0f;
      int tmpTokenCnt = 0;
      char *tmpToken;

      tmpToken = strtok((psrc + 3), " ");

      // �g�[�N�����Ȃ��Ȃ�܂Ń��[�v
      while(tmpToken != NULL)
      {
        // �A���t�@�l�𑫂�����
        tmpTransparency += atof(tmpToken);

        tmpToken = strtok(NULL, " ");
        tmpTokenCnt++;
      }
      pst->isTransparency = true;

      // �擾�����l�̕��ϒl��ݒ�
      tmpTransparency = tmpTransparency / tmpTokenCnt;
      
      // �l��1���傫���ꍇ
      if(1.0f < tmpTransparency)
      {
        tmpTransparency = 1.0f;
      }
      // �l��0��菬�����ꍇ
      else if(1.0 > tmpTransparency)
      {
        tmpTransparency = 0.0f;
      }

      // �l�̐ݒ�
      pst->transparency = tmpTransparency;
    }

    // ��L�ȊO
    else
    {
      ;  // �X�L�b�v
    }
  }
  ifs.close();

  // mtl��`�ɒǉ�
  v_mtl.push_back(*pst);

  // �̈�J��
  delete pst;

  return true;
}

//-----------------------------------------------------------------//
// �}�e���A���ݒ�̓K�p���s���܂��B                                //
//-----------------------------------------------------------------//
void CMtl::applyMtl(string mtlnm)
{
  // �}�e���A����`�̌������[�v
  for(unsigned int i = 0; i < v_mtl.size(); i++)
  {
    // �w�肵���}�e���A����`�ł���ꍇ
    if(!v_mtl[i].mtlnm.compare(mtlnm))
    {
      if(v_mtl[i].isAmbient)
      {
        // �����ݒ�
        material.setAmbient(GL_FRONT
                  , v_mtl[i].ambient[0]
                  , v_mtl[i].ambient[1]
                  , v_mtl[i].ambient[2]
                  , v_mtl[i].transparency);
      }
      if(v_mtl[i].isDiffuse)
      {
        // �g�U���ݒ�
        material.setDiffuse(GL_FRONT
                  , v_mtl[i].diffuse[0]
                  , v_mtl[i].diffuse[1]
                  , v_mtl[i].diffuse[2]
                  , v_mtl[i].transparency);
      }
      if(v_mtl[i].isSpecular)
      {
        // ���ʌ��ݒ�
        material.setSpecular(GL_FRONT
                  , v_mtl[i].specular[0]
                  , v_mtl[i].specular[1]
                  , v_mtl[i].specular[2]
                  , v_mtl[i].transparency);
      }
      if(v_mtl[i].isShininess)
      {
        // ���ʌW���ݒ�
        material.setShininess(GL_FRONT
                  , (float)v_mtl[i].shininess);
      }

      if(v_mtl[i].isIllumination)
      {
        // �C���~�l�[�V�����ݒ�OFF�ł���ꍇ
        if(v_mtl[i].illumination == 1)
        {
          material.setSpecular(GL_FRONT
                    , 0.0f
                    , 0.0f
                    , 0.0f
                    , 0.0f);
        }
        // �C���~�l�[�V�����ݒ�ON�ł���ꍇ
        else if(v_mtl[i].illumination == 2)
        {
          ; // ��L�̋��ʌ��ݒ�ŁA���ɐݒ�ςׁ݂̈A�X�L�b�v
        }
      }

      // �����x�ݒ肪����ꍇ
      if(v_mtl[i].isTransparency)
      {
        // �����x�ݒ�
        glColor4d(1.0, 1.0, 1.0, v_mtl[i].transparency);
      }
      // �����x�ݒ肪�Ȃ��ꍇ
      else
      {
        // �s�����ɐݒ�
        glColor4d(1.0, 1.0, 1.0, 1.0);
      }

      // �e�N�X�`���}�b�s���O�ݒ肪����ꍇ
      if(v_mtl[i].isTexture)
      {
        // �e�N�X�`���̃o�C���h
        glBindTexture(GL_TEXTURE_2D, v_mtl[i].tNo);

        glEnable(GL_TEXTURE_2D);

        // �����x�ݒ肪����A1.0��菬�����w��ł���ꍇ
        if(v_mtl[i].transparency < 1.0)
        {
          // �e�N�X�`����
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        }
        // �����x�ݒ肪�Ȃ��ꍇ
        else
        {
          // �e�N�X�`����
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }

        texturebind_flg = true;
      }
      // �e�N�X�`���ݒ肪�Ȃ��ꍇ
      else
      {
        if(texturebind_flg)
        {
          texturebind_flg = false;
        }
      }

      // �X�t�B�A�}�b�s���O�ݒ肪����ꍇ
      if(v_mtl[i].isSphereTexture)
      {
        // �X�t�B�A�}�b�s���O�o�C���h
        glBindTexture(GL_TEXTURE_2D, v_mtl[i].tNo);

#ifdef _WIN32
        glActiveTexture(GL_TEXTURE1);
#endif

        glEnable(GL_TEXTURE_2D);

        /* �e�N�X�`�����g��E�k��������@�̎w�� */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        /* �e�N�X�`���̌J��Ԃ����@�̎w�� */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        /* �e�N�X�`���� */
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // �X�t�B�A�}�b�s���O�p�e�N�X�`�����W�𐶐�
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

        // �e�N�X�`�����W�̎���������L���ɂ���
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        spherebind_flg = true;
      }

      // �L���[�u�}�b�s���O�ݒ肪����ꍇ
      if(v_mtl[i].isCubeTexture)
      {
        // �L���[�u�}�b�s���O�o�C���h
        glBindTexture(GL_TEXTURE_CUBE_MAP, v_mtl[i].tNo);

#ifdef _WIN32
        glActiveTexture(GL_TEXTURE2);
#endif

        glEnable(GL_TEXTURE_CUBE_MAP);

        /* �e�N�X�`�����g��E�k��������@�̎w�� */
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        /* �e�N�X�`���̌J��Ԃ����@�̎w�� */
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);

        /* �e�N�X�`���� */
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // �X�t�B�A�}�b�s���O�p�e�N�X�`�����W�𐶐�
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
        glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

        // �e�N�X�`�����W�̎���������L���ɂ���
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);

        cubebind_flg = true;
      }

      break;
    }
  }
}

//-----------------------------------------------------------------//
// �}�e���A���ݒ�̏��������s���܂��B                              //
//-----------------------------------------------------------------//
void CMtl::clearMtl(void)
{

#ifdef _WIN32
  // �e�N�X�`�����j�b�g1�ɐ؂�ւ�
  glActiveTexture(GL_TEXTURE1);
  glDisable(GL_TEXTURE_GEN_T);                   // �e�N�X�`��T���W�̎��������𖳌��ɂ���
  glDisable(GL_TEXTURE_GEN_S);                   // �e�N�X�`��S���W�̎��������𖳌��ɂ���
  glDisable(GL_TEXTURE_2D);                      // �e�N�X�`���}�b�s���OOFF

  // �e�N�X�`�����j�b�g2�ɐ؂�ւ�
  glActiveTexture(GL_TEXTURE2);
#endif
  glDisable(GL_TEXTURE_GEN_T);                   // �e�N�X�`��T���W�̎��������𖳌��ɂ���
  glDisable(GL_TEXTURE_GEN_S);                   // �e�N�X�`��S���W�̎��������𖳌��ɂ���
  glDisable(GL_TEXTURE_GEN_R);                   // �e�N�X�`��R���W�̎��������𖳌��ɂ���
  glDisable(GL_TEXTURE_CUBE_MAP);                // �L���[�u�}�b�s���OOFF
  glDisable(GL_TEXTURE_2D);                      // �X�t�B�A�}�b�s���OOFF

#ifdef _WIN32
  // �e�N�X�`�����j�b�g0�ɐ؂�ւ�
  glActiveTexture(GL_TEXTURE0);
#endif
  glDisable(GL_TEXTURE_2D);                      // �e�N�X�`���}�b�s���O�}�b�s���OOFF

  material.clear();
}

//-----------------------------------------------------------------//
// �����f�[�^�̏��������s���܂��B                                  //
//-----------------------------------------------------------------//
void CMtl::clear(void)
{
  texturebind_flg = false;                       // �e�N�X�`���}�b�s���O�o�C���h�t���O������
  spherebind_flg = false;                        // �X�t�B�A�}�b�s���O�o�C���h�t���O������
  cubebind_flg = false;                          // �L���[�u�}�b�s���O�o�C���h�t���O������

  // mtl��`�ێ��̈�N���A
  v_mtl.clear();

  // �e�N�X�`����(ID)�ێ��̈�N���A
  v_tNo.clear();

  // �}�e���A�����N���A
  material.clear();
}

//-----------------------------------------------------------------//
// �����f�[�^�̏o�͂��s���܂��B                                    //
//-----------------------------------------------------------------//
void CMtl::show(const St_mtl_data &val, ostream &os)
{
  os << "MTL���F" << val.mtlnm.c_str() << endl;
  os << "����R�F" << val.ambient[0] << endl;
  os << "����G�F" << val.ambient[1] << endl;
  os << "����B�F" << val.ambient[2] << endl;

  os << "�g�U��R�F" << val.diffuse[0] << endl;
  os << "�g�U��G�F" << val.diffuse[1] << endl;
  os << "�g�U��B�F" << val.diffuse[2] << endl;

  os << "���ʌ�R�F" << val.specular[0] << endl;
  os << "���ʌ�G�F" << val.specular[1] << endl;
  os << "���ʌ�B�F" << val.specular[2] << endl;

  os << "�A���t�@�l�F" << val.transparency << endl;
  os << "���ʌW���F" << val.shininess << endl;
  os << "�C���~�l�[�V�����F" << val.illumination << endl;
  os << "�e�N�X�`��No�F" << val.tNo << endl;
  os << "�e�N�X�`���t�@�C�����F" << val.texturefnm.c_str() << endl;

  os << "�X�t�B�A�}�b�s���O:";
  if(val.isSphereTexture)
  {
    os << "����";
  }
  else
  {
    os << "�Ȃ�";
  }
  os << endl;

  os << "�L���[�u�}�b�s���O:";
  if(val.isCubeTexture)
  {
    os << "����";
  }
  else
  {
    os << "�Ȃ�";
  }
  os << endl;
}

//-----------------------------------------------------------------//
// �e�N�X�`���̃��[�h���s���܂��B                                  //
//-----------------------------------------------------------------//
bool CMtl::loadTexture(const St_mtl_data *pval)
{
  int ret;                                       // �߂�l
  int width;                                     // �C���[�W�̉���
  int height;                                    // �C���[�W�̍���
  int depth;                                     // �C���[�W�̐[�x
  int bits;                                      // �C���[�W�̃r�b�g�l(8/16)
  unsigned char *fimage;                         // �C���[�W�f�[�^

  // �e�N�X�`���t�@�C���̓Ǎ���
  ret = readPngImage(pval->texturefnm.c_str(), &width, &height, &depth, &bits, &fimage);
  if(ret == 1)
  {
    cout << "�e�N�X�`���t�@�C���̃I�[�v���G���[���������܂����B file = "
         << pval->texturefnm.c_str() << endl;
    return false;
  }
  else if(ret == 2)
  {
    cout << "�e�N�X�`���t�@�C���̓Ǎ��݃G���[���������܂����B file = "
         << pval->texturefnm.c_str() << endl;
    return false;
  }

  glEnable(GL_TEXTURE_2D);                       // �e�N�X�`���}�b�s���O�L����

  glBindTexture(GL_TEXTURE_2D, pval->tNo);       // �e�N�X�`���̃o�C���h

  // �e�N�X�`����
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, fimage);

  glDisable(GL_TEXTURE_2D);                      // �e�N�X�`���}�b�s���O������

  free(fimage);                                  // �C���[�W�̈�̊J��
  return true;
}

//-----------------------------------------------------------------//
// �X�t�B�A�}�b�s���O�p�e�N�X�`���̃��[�h���s���܂��B              //
//-----------------------------------------------------------------//
bool CMtl::loadSphereTexture(const St_mtl_data *pval)
{
  int ret;                                       // �߂�l
  int width;                                     // �C���[�W�̉���
  int height;                                    // �C���[�W�̍���
  int depth;                                     // �C���[�W�̐[�x
  int bits;                                      // �C���[�W�̃r�b�g�l(8/16)
  unsigned char *fimage;                         // �C���[�W�f�[�^

  // �e�N�X�`���t�@�C���̓Ǎ���
  ret = readPngImage(pval->texturefnm.c_str(), &width, &height, &depth, &bits, &fimage);
  if(ret == 1)
  {
    cout << "�e�N�X�`���t�@�C���̃I�[�v���G���[���������܂����B file = "
         << pval->texturefnm.c_str() << endl;
    return false;
  }
  else if(ret == 2)
  {
    cout << "�e�N�X�`���t�@�C���̓Ǎ��݃G���[���������܂����B file = "
         << pval->texturefnm.c_str() << endl;
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, pval->tNo);       // �e�N�X�`���̃o�C���h
#ifdef _WIN32
  glActiveTexture(GL_TEXTURE1);
#endif
  // �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă���
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // �e�N�X�`���̊��蓖��
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0
        ,GL_RGB, GL_UNSIGNED_BYTE, fimage);
  delete[] fimage;

#ifdef _WIN32
  glActiveTexture(GL_TEXTURE0);
#endif

  return true;
}

//-----------------------------------------------------------------//
// �L���[�u�}�b�s���O�p�e�N�X�`���̃��[�h���s���܂��B              //
//-----------------------------------------------------------------//
bool CMtl::loadCubeTexture(const St_mtl_data *pval)
{
  int ret;                                       // �߂�l
  int width;                                     // �C���[�W�̉���
  int height;                                    // �C���[�W�̍���
  int depth;                                     // �C���[�W�̐[�x
  int bits;                                      // �C���[�W�̃r�b�g�l(8/16)
  unsigned char *fimage;                         // �C���[�W�f�[�^

  // �e�N�X�`���̃^�[�Q�b�g��
  int target[] =
  {
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,  // ��
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,  // ��
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,  // �E
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,  // �O
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,  // ��
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y   // ��
  };

  glBindTexture(GL_TEXTURE_CUBE_MAP, pval->tNo);

#ifdef _WIN32
  glActiveTexture(GL_TEXTURE2);
#endif

  // �e�N�X�`������(6��)���[�v
  for(int i = 0; i < pval->textureCnt; i++)
  {
    // �e�N�X�`���t�@�C���̓Ǎ���
    ret = readPngImage(pval->v_texturefnm[pval->textureIndex[i]].c_str(), &width, &height, &depth, &bits, &fimage);
    if(ret == 1)
    {
      cout << "�e�N�X�`���t�@�C���̃I�[�v���G���[���������܂����B file = "
           << pval->v_texturefnm[pval->textureIndex[i]].c_str() << endl;
      return false;
    }
    else if(ret == 2)
    {
      cout << "�e�N�X�`���t�@�C���̓Ǎ��݃G���[���������܂����B file = "
           << pval->v_texturefnm[pval->textureIndex[i]].c_str() << endl;
      return false;
    }
    // �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă���
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // �e�N�X�`���̊��蓖��
    glTexImage2D(target[i], 0, GL_RGB, width, height, 0
          ,GL_RGB, GL_UNSIGNED_BYTE, fimage);

    delete[] fimage;
  }

#ifdef _WIN32
  glActiveTexture(GL_TEXTURE0);
#endif

  return true;
}
