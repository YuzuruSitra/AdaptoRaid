#pragma once
#define USE_LIBJPEG

typedef struct{
	int width;
	int height;
	unsigned int pixformat; //GLenum
	unsigned int pixtype;   //GLenum
	int pixsize; //data size of each pixel
	int texid; //GLuint texture id
	void *pixdata; //
} image_t;

void initImage( image_t *image, int width = 0, int height = 0, 
	unsigned int pixformat = GL_RGB,
	unsigned int pixtype = GL_UNSIGNED_BYTE );

image_t *newImage( int width = 0, int height = 0, 
	unsigned int pixformat = GL_RGB,
	unsigned int pixtype = GL_UNSIGNED_BYTE );

void deleteImage( image_t *image );

void loadImage( image_t *image, const char *file );
int loadImageJpg( image_t *image, const char *file );
void drawImage( image_t *image, int x, int y );
image_t *newImageJpg( const char *file );
void propertyImage( image_t *image, const char *text );

void saveImageJpg( image_t *image, const char *file );

void allocTexture(image_t *image);
void updateTexture(image_t *image);

int makeMesh( int texid = 0 );
void drawMesh( int texid, int meshid );
void drawMesh( image_t *image, int meshid );

class ezImage {
private:
	int meshid;
public:
	image_t *image;
	ezImage( int width = 0, int height = 0, 
	unsigned int pixformat = GL_RGB,
	unsigned int pixtype = GL_UNSIGNED_BYTE ){ 
		/*
		image = newImage();
		initImage( image, width, height, pixformat, pixtype ); 
		*/
		image = newImage( width, height, pixformat, pixtype ); 
		meshid = makeMesh();
	}
	ezImage( const char *file ){
		image = newImageJpg( file );
		meshid = makeMesh();
		allocTexture(image);
	}
	~ezImage(){
		if( image->pixdata != nullptr ) delete image->pixdata;
	}
	void loadJpg( const char *file ){
		loadImageJpg( image, file );
		allocTexture(image);
	}
	void saveJpg( const char *file ){
		saveImageJpg( image, file );
	}
	void drawPixels( int x, int y ){
		drawImage( image, x, y );
	}
	void draw( void ) {
		drawMesh( image, meshid );
	}
	void preperty( const char *text ){
		propertyImage( image, text );
	}
};

