#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>
#include "libjpeg/jpeglib.h"
#include <string.h>

#include "ezJpeg.h"

unsigned char* readImageJPEG( const char *file, int *w, int *h, unsigned char *image )
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	unsigned char *rawimage, *p;
	JSAMPARRAY img;
	int i, j;
	int width;
	int height;

	FILE *infile;

	// JPEG�I�u�W�F�N�g�̏�����
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_decompress( &cinfo );

	// �t�@�C�����J��
	infile = fopen( file, "rb" );
	jpeg_stdio_src( &cinfo, infile );

	// �w�b�_�̓ǂݍ���
	jpeg_read_header( &cinfo, TRUE );

	// �W�J�̊J�n
	jpeg_start_decompress( &cinfo );

	// ���ƍ����̎擾
	width = cinfo.output_width;
	height = cinfo.output_height;

	// �C���[�W��ێ����郁�����̈�̊m�ۂƏ�����
	img = (JSAMPARRAY)malloc( sizeof( JSAMPROW ) * height );
	for ( i = 0; i < height; i++ ) {
		img[i] = (JSAMPROW)calloc( sizeof( JSAMPLE ), 3 * width );
	}

	// �S�C���[�W�f�[�^���擾	
	while( cinfo.output_scanline < cinfo.output_height ) {
		jpeg_read_scanlines( &cinfo,
			img + cinfo.output_scanline,
			cinfo.output_height - cinfo.output_scanline
		);
	}

	// �W�J�̏I��
	jpeg_finish_decompress( &cinfo );

	// JPEG�I�u�W�F�N�g�̔j��
	jpeg_destroy_decompress( &cinfo );

	// �t�@�C�������
	fclose( infile );
	
	//�C���[�W�f�[�^���R�s�[���ێ����郁�����̈���J��
	if( image == NULL ){
		p = rawimage = (unsigned char*)malloc( width * height * 3 );
	}
	else{
		p = rawimage = image;
	}
	for ( i = height-1; i >= 0; i-- ){
	//for (i = 0; i < height; i++ ) {
		for( j= 0; j < width; j++ ){
			*p = img[i][j * 3 + 0 ]; p++;
			*p = img[i][j * 3 + 1 ]; p++;
			*p = img[i][j * 3 + 2 ]; p++;
		}
		free( img[i] );
	}
	free( img );
	
	*w = width;
	*h = height;
	return rawimage;
}

void writeImageJPEG( const char *file, unsigned char *image, int w, int h )
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE *outfile;

	// JPEG�I�u�W�F�N�g�̏�����
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress( &cinfo );

	// �t�@�C�����J��
	outfile = fopen( file, "wb" ); //��
	jpeg_stdio_dest( &cinfo, outfile );

	// �p�����[�^�̐ݒ�
	cinfo.image_width = w; //��
	cinfo.image_height = h; //��
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	// �f�t�H���g�l�̐ݒ�
	jpeg_set_defaults( &cinfo );

	// ���k�̊J�n
	jpeg_start_compress( &cinfo, TRUE );

	// �C���[�W��ێ����郁�����̈�̊m�ۂƏ�����
	JSAMPARRAY img;
	unsigned char *p = image;
	img = (JSAMPARRAY)malloc( sizeof( JSAMPROW ) * h );
	for ( int i = 0; i < h; i++ ) {
		img[i] = (JSAMPROW)calloc( sizeof( JSAMPLE ), 3 * w );
		for( int j = 0; j < w; j++ ){
			img[i][j * 3 + 2 ] = *p; p++;
			img[i][j * 3 + 1 ] = *p; p++;
			img[i][j * 3 + 0 ] = *p; p++;
			p++;
		}
	}
	// �S�C���[�W�f�[�^���o��
	//jpeg_write_scanlines( &cinfo, (JSAMPARRAY)image, cinfo.image_height ); //��
	jpeg_write_scanlines( &cinfo, img, cinfo.image_height ); //��

	// ���k�̏I��
	jpeg_finish_compress( &cinfo );

	// JPEG�I�u�W�F�N�g�̔j��
	jpeg_destroy_compress( &cinfo );

	// �t�@�C�������
	fclose( outfile );	
}

void saveRAW( char *rawfile, unsigned char *img, int x, int y )
{
	FILE *fp;

	fp = fopen( rawfile, "wb" );
	fwrite( img, x * 3, y, fp );
	fclose( fp );
}

void nameRAW( char *rawfile, const char *infile, int w, int h, int d )
{
	char width[6], height[6];

	strcpy( rawfile, infile );
	*strchr( rawfile, '.' ) = '\0';
	sprintf( width, "%d", w );
	sprintf( height, "%d", h );

	strcat( rawfile, "_" );
	strcat( rawfile, width );
	strcat( rawfile, "x" );
	strcat( rawfile, height );
	switch( d ){
	case 1: //intensity
	strcat( rawfile, "xI.raw" );
		break;
	case 2: //intensity and alpha
		strcat( rawfile, "xIA.raw" );
		break;
	case 3: //rgb
		strcat( rawfile, "xRGB.raw" );
		break;
	case 4: //rgba
		strcat( rawfile, "xRGBA.raw" );
		break;
	}
}
