#pragma once
//ezJpeg.h

//JPG�摜���t�@�C������ǂݍ���
//w, h: �摜�T�C�Y
//image: �摜�o�b�t�@���w�肵�Ȃ��ꍇ�ɂ́A�V�����̈���m�ۂ��Ԃ�
unsigned char* readImageJPEG( const char *file, int *w, int *h, 
	unsigned char *image = nullptr, bool reverse = true );
void writeImageJPEG( const char *file, unsigned char *image, int w, int h );

void nameRAW( char *rawfile, const char *infile, int w, int h, int d );
void saveRAW( char *rawfile, unsigned char *img, int x, int y );
