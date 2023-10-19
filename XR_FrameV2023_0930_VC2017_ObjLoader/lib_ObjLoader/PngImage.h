/** @file  PngImage.h
 *  @brief  PNG���o�͊֐�
 *  @author  Masakazu Yoshida(yoshida@iltj.jp)
 *  @version  1.0
 *  @date  2008/12/1 ... �V�K�쐬
 *  @attention  Copyright (C) 2008, ILTJ Inc.
 */

#ifndef __pngImage_h__
#define __pngImage_h__

//*******************************************************************
/*!
 *  @brief  PNG�t�@�C����Ǎ��݂܂��B
 *  @param  fname ... [In] PNG�t�@�C����
 *  @param  width ... [In/Out] �C���[�W�̕�
 *  @param  height ... [In/Out] �C���[�W�̍���
 *  @param  depth ... [In/Out] �C���[�W�̐[�x
 *  @param  bits ... [In/Out] �C���[�W�̃r�b�g[8/16]
 *  @param  image ... [In/Out] �Ǎ��񂾃C���[�W�f�[�^
 *  @return  int ... ���^�[���R�[�h@n
 *                  [0:����I�� / 1:�t�@�C���I�[�v���G���[ / 2:�t�@�C���Ǎ��݃G���[]
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
int readPngImage( const char *fname,
                  int *width,
                  int *height,
                  int *depth,
                  int *bits,
                  unsigned char **image
                 );

//*******************************************************************
/*!
 *  @brief  �C���[�W�f�[�^��PNG�t�@�C���ɏo�͂��܂��B
 *  @param  width ... [In] �C���[�W�̕�
 *  @param  height ... [In] �C���[�W�̍���
 *  @param  depth ... [In] �[�x[3:RGB / 4:RGBA]
 *  @param  image ... [In] �C���[�W�f�[�^
 *  @param  file_name ... [In] �o�̓t�@�C����
 *  @param  reverse ... [In] �o�͏���(true:�~�� / false:����)
 *  @return  int ... ���^�[���R�[�h@n
 *                   [1:�t�@�C���I�[�v���G���[ / 2:png_structp�\���̊m�ۃG���[ / 3:png_infop�\���̊m�ۃG���[]
 *  @date  2008/12/1 ... �V�K�쐬
 */
//********************************************************************
int writePngImage( int width, int height, int depth, 
                   unsigned char *image, const char *fname, bool reverse );

#endif

