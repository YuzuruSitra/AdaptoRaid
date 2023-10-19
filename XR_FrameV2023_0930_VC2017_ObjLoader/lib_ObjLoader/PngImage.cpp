#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <png.h>
#include <zlib.h>
//-----------------------------------------------------------------//
// PNG�t�@�C����Ǎ��݂܂��B                                       //
//-----------------------------------------------------------------//
int readPngImage( const char *fname,
                  int *width,
                  int *height,
                  int *depth,
                  int *bits,
                  unsigned char **image
                )
{
    FILE            *fp;                         // �t�@�C���|�C���^
    png_structp     png_ptr;                     // png_structp�\����
    png_infop       info_ptr;                    // png_infop�\����
    unsigned long   pngWidth;                    // �摜�s�N�Z���̉���
    unsigned long   pngHeight;                   // �摜�s�N�Z���̍���
    unsigned long   row;                         // 1���C���̃T�C�Y
    int bit_depth;                               // �r�b�g�[�x
    int color_type;                              // �J���[/�A���t�@ �`�����l���̐ݒ�
    int interlace_type;                          // �C���^�[���[�X�̐ݒ�
    unsigned char   **pngImage;                  // �C���[�W�f�[�^�|�C���^
    unsigned long   i;                           // �ėp�J�E���^

    // PNG�t�@�C���`���łȂ��ꍇ
    if(!strstr(fname, ".png") && !strstr(fname, ".PNG"))
    {
      return 1;
    }

    // �t�@�C���Ǎ���
    if((fp = fopen(fname, "rb")) < 0)
    {
      return 1;
    }

    // png_structp�\���̂��m�ہE������
    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 
                                      NULL, NULL, NULL );
    // png_infop�\���̂��m�ہE������
    info_ptr = png_create_info_struct( png_ptr );

    // �t�@�C���|�C���^�̐ݒ�
    png_init_io( png_ptr, fp );

    // PNG�t�@�C���̃w�b�_�Ǎ���
    png_read_info( png_ptr, info_ptr );

    // IHDR�`�����N�����擾
    png_get_IHDR( png_ptr, info_ptr, (png_uint_32 *)&pngWidth, (png_uint_32 *)&pngHeight,
                  &bit_depth, &color_type, &interlace_type,
                  NULL, NULL );

    // 1���C���ɕK�v�ȃo�b�t�@�̃T�C�Y���擾
    row = png_get_rowbytes( png_ptr, info_ptr );

    // PNG�p�摜�f�[�^�̈�m��
    pngImage = (png_bytepp)malloc( pngHeight * sizeof(png_bytep) ); 

    // �摜�p�f�[�^�̈�m��
    *image = (unsigned char *)malloc( pngHeight * row );

    for( i=0; i<pngHeight; i++ ){
      pngImage[i] = (png_bytep)malloc( row );
    }
    // PNG�摜�f�[�^�Ǎ���
    png_read_image( png_ptr, pngImage );
    fclose(fp);

    for( i=0; i<pngHeight; i++ ){
      // opengl��ł́A�摜�̎n�_�����ォ��n�܂�ׁA�f�[�^�̏��Ԃ����ւ�
      memcpy( *image+(pngHeight-1-i)*row, pngImage[i], row );
      free( pngImage[i] );
    }
    free( pngImage );
    // �Q�̍\���̂̃����������
    png_destroy_read_struct( &png_ptr, &info_ptr, (png_infopp)NULL );

    *width  = pngWidth;
    *height = pngHeight;
    *depth  = row/pngWidth;
    *bits   = bit_depth;

    return 0;
}

//-----------------------------------------------------------------//
// PNG�C���[�W���t�@�C���ɏo�͂��܂��B                             //
//-----------------------------------------------------------------//
int writePngImage( int width
          , int height
          , int depth
          , unsigned char *image
          , const char *file_name
          , bool reverse
         ) 
{
    int             i, n;
    int             bits = 8;
    unsigned char   **pngImage;

    FILE            *fp;
    png_structp     png_ptr;
    png_infop       info_ptr;

    // �o�̓t�@�C���I�[�v��
    if((fp = fopen(file_name, "wb")) < 0)
    {
      return 1;
    }

    png_ptr = png_create_write_struct(           // png_structp�\���̂̊m�ہE������
                    PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if( png_ptr == NULL ){
      fclose( fp );
      return 2;
    }

    info_ptr = png_create_info_struct(png_ptr);  // png_infop�\���̂̊m�ہE������
    if( info_ptr == NULL ){
        png_destroy_write_struct( &png_ptr,  (png_infopp)NULL );
        fclose( fp );
        return 3;
    }

    png_init_io(png_ptr, fp);                    // �t�@�C���|�C���^�̐ݒ�
    png_set_filter(png_ptr, 0, PNG_ALL_FILTERS); // �t�B���^�̐ݒ�
    png_set_compression_level(png_ptr, Z_BEST_COMPRESSION); // ���k�̐ݒ�

    if( depth == 3 ){       // RGB
      png_set_IHDR( png_ptr, info_ptr, width, height, // RGB�p�`�����N���̐ݒ�
                    bits, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
    }
    else if( depth == 4 ){  // RGBA
      png_set_IHDR( png_ptr, info_ptr, width, height, // RGBA�p�`�����N���̐ݒ�
                    bits, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
    }
    else{                   // ��L�ȊO
      png_set_IHDR( png_ptr, info_ptr, width, height, // �O���C�X�P�[���p�`�����N���̐ݒ�
                    bits, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
    }

    png_set_gAMA( png_ptr, info_ptr, 1.0 );      // �t�@�C���E�K���}�̐ݒ�
    png_write_info( png_ptr, info_ptr );         // PNG�t�@�C���̃w�b�_���o��

    // PNG�p�摜�f�[�^�̈�m��
    pngImage = (png_bytepp)malloc( height * sizeof(png_bytep) ); 
    n = ((depth*width + 3) / 4) * 4;             // 4�o�C�g�̐����{�Ƃ���

    // ���������[�v
    for( i=0; i<height; i++ ){
    // �~���`��̏ꍇ
    if(reverse == true)
    {
      pngImage[i] = image + ((height-1) - i) * n;
    }
    // �����`��̏ꍇ
    else
    {
      pngImage[i] = image + i * n;
    }
  }

    png_write_image( png_ptr, pngImage );        // PNG�t�@�C���̉摜�f�[�^���o��
    free( pngImage );

    png_write_end( png_ptr, info_ptr );          // �c��̏����o��
    png_destroy_write_struct( &png_ptr, &info_ptr ); // �Q�̍\���̂̃����������

    fclose(fp);                                  // �o�̓t�@�C���N���[�Y
    return 0;
}
