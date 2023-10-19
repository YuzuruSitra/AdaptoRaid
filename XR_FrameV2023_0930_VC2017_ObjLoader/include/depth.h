#ifndef __DEPTH_H__
#define __DEPTH_H__

//--------------------------------------------------------------------------------------
//���_�Q��`�悷��i�񃆁[�U�֐��FezDepth�N���X�ł̂ݎg�p����֐��j
void drawPointCloud( unsigned short *depth, unsigned char *image, 
	int width, int height, float fovy, float clip_far, float clip_near, bool mirror );
//--------
//�������摜��Z�o�b�t�@�p��Z�l�摜�ɕϊ�����
void depthToZ( float *zimage, unsigned short *depth, int w, int h, float n, float f );
float _depthToZ( unsigned short depth, float n, float f );
//--------
//��Z�l�摜��Z�o�b�t�@�ɏ������ށi�񃆁[�U�֐��j
//zimage: Z�l�摜
//w, h: Z�l�摜�̃T�C�Y
//win_w, win_h: �`��E�B���h�E�̃T�C�Y
//reverse: ���E���]�t���O
void drawToZ( float *zimage, int w, int h, int win_w, int win_h, bool reverse );
//--------
//��
void drawDepthView( void );
//-------------------------------------------------------------------------------------
class ezDepth {
public:
	ezDepth(){}
	~ezDepth(){}
	//��KINECT�̃f�v�X�J�����̉摜�T�C�Y�E��p�E�N���b�v�����W��ݒ肷��
	void open( int w, int h, float fovy, float clip_near, float clip_far ){
		//_color = (unsigned char *)malloc( w * h * sizeof(unsigned char) * 4 );
		//_depth = (unsigned short*)malloc( w * h * sizeof(unsigned short ) );
		_zimage = (float *)malloc( w * h * sizeof(float) );
		_width = w;
		_height = h;
		_aspect = (float)w/h;
		_fovy = fovy;
		_clip_near = clip_near;
		_clip_far = clip_far;
	}
	//��KINECT����̃J���[�摜�ƃf�v�X�摜�̔z���R�Â���
	void attach( unsigned char *image, unsigned short *depth ){
		_color = image;
		_depth = depth;
	}
	//-----------------------
	void updateZ( void ){
		depthToZ( _zimage, _depth, _width, _height, _clip_near, _clip_far );
	}
	//-------------------------
	void drawZ( int win_w, int win_h, bool reverse = false ){
		drawToZ( _zimage, _width, _height, win_w, win_h, reverse );
	}
	//------------------------
	void drawPoints( bool background = false, bool mirror = false ){
		float clip;
		if( background ) clip = _clip_far * 0.6;
		else clip = 10000.0;
		drawPointCloud( _depth, _color, _width, _height, _fovy, _clip_near, clip, mirror );
	}
    //
	unsigned char *Color(){ return _color; }
	unsigned short *Depth(){ return _depth; }
	float *Zimage(){ return _zimage; }

private:
	unsigned short *_depth;
	unsigned char *_color;
	float *_zimage;

	int _width;
	int _height;
	float _aspect;
	float _fovy;
	float _clip_near;
	float _clip_far;
};

#endif //__DEPTH_H__