ezImage�N���X
�EJPEG�`���̉摜�t�@�C����ǂݍ���
�E�r�b�g�}�b�v�`���ŕ\������
�E�e�N�X�`���|���S���ŕ\������
�E�e�N�X�`���Ƃ��Ďg��
�E�J����������͂���
�EJPEG�ŕۑ�����

�C���X�g�[�����@
�E���̃t�H���_���ƁA�\�[�X�t�@�C���̃t�H���_�ɓ���Ă��������B
�����̃t�@�C�����\�[�X�t�@�C���̃t�H���_�ɃR�s�[���Ă�������
> libjpeg.lib
���ȉ��̃t�@�C�����\�����[�V�����ɒǉ����Ă�������
�i�t�@�C����ʂ̃t�H���_�ɃR�s�[����K�v�͂���܂���B�j
�\�[�X�t�@�C��
> ez\image.cpp
> ez\ezJpeg.cpp
> ez\ezWebCam.cpp
�w�b�_�t�@�C��
���g���͕K�{�ł͂���܂���
���v���g�^�C�v�̊m�F�Ɏg���ĉ������B
> ez\image.h

���d�v�F�t�H���_���̃t�@�C���͈ړ��E�폜���Ȃ��ł��������B
���d�v�F�s����C������Ȃǂ̂ق��́A
�@�@�@�@�ϋɓI�ȕύX�͔����Ă��������B
�@�@�@�@�ȍ~�̏C���łւ̍����ւ����ނ��������Ȃ�܂��B

�g�����̗�j

��STEP 1. �ϐ��̏���
SimDataT(sim.h)��ezImage�N���X�̃|�C���^�ϐ���o�^
ezImage *image;

��STEP 2. �C���X�^���X�̐���
InitScene(sim.cpp)

��p�@(1)�t�@�C���ǂݍ��݂ŃC���X�^���X�����ꍇ
���ʏ�p�r�Ƃ��Đ�����
�R���X�g���N�^�œǂݍ��ރt�@�C�����w�肵�܂�
simdata->image = new ezImage( "myimagefile.jpg" );

��p�@(2)���O�ɃC���X�^���X���쐬���Ă���A
�t�@�C������摜�f�[�^�����[�h����ꍇ
���d�l�㒍�ӎ������聚
//�R���X�g���N�^�ŋ�̃I�u�W�F�N�g�𐶐�
simdata->image = new ezImage();
//�摜��ǂݍ��񂾎��ɉ摜�̈悪�m�ۂ����
simdata->image->loadJpg( "myimagefile.jpg" );

loadJpg���\�b�h���g���Ɖ摜�f�[�^���t�@�C������
���[�h���ď㏑�����邱�Ƃ��ł��܂��B
�����Î~��ɕ��������t�@�C����ǂݍ��ނ��Ƃ�
�z�肵�Ă���A�������̈�̊m�ۂƉ�����J��Ԃ���邱�Ƃ�
������邽�߂ɁA�摜�̈���g���܂킵���Ă��܂��B
�ǂݍ��ݒ������Ƃ��ɂ́A�����𑜓x��
�C���[�W�ł��邱�Ƃ�z�肵�Ă��܂��̂ŁA
�قȂ�T�C�Y�̃f�[�^�͐��ݓI�ɃG���[�ƂȂ�܂��B
��O�����Ȃǂ͂��Ă��܂���B

��STEP 3. �`��
DrawScene(draw.cpp)

��p�@(1)�e�N�X�`���|���S���Ƃ��ĕ`�悷��

�c��1m�̃|���S���S�p�`�Ƃ��āA�C�ӂɕ`��ł��܂�
���̃I�u�W�F�N�g��`�悷�镔���ɑg�ݍ��߂΁A
�I�u�W�F�N�g��C�ӂ̏ꏊ�ɐݒ肷�镶���ŁA
���R�Ȉʒu�p���E�傫���ŕ`��ł��܂��B
���̊֐������ł́A�傫����1m�����AZ�̈ʒu�O
X,Y�̈ʒu�����w�肵�܂��B
�E�E�E
glPushMatrix();
//simdata.anyobject�͉��炩�̃I�u�W�F�N�g
//anyobject�̈ʒu�Ƀe�N�X�`���|���S�������������Ƃ���
applyObjTransform( &simdata.anyobject );
applyObjColor( &simdata.anyobject );
drawAnyobject();
//�e�N�X�`���|���S���𒲐�����C�ӂ̊􉽕ϊ�
glScalef( 0.1, 0.4, 1.0 ); //�Ⴆ��
simdata->image->draw( xpos, ypos );
//xpos, ypos�FXY���ʂł̈ʒu
glPopMatrix();

��p�@(2)�r�b�g�}�b�v�摜�Ƃ��ĕ`�悷��
�摜��glDrawPixels�Ńt���[���o�b�t�@�ɃR�s�[���܂��B

simdata->image->drawPixels( xpos, ypos );

��p�@(3)�e�N�X�`���Ƃ��Ďg��
//�e�N�X�`���Ƃ��ēK�p����
simdata->image->apply();
//���̂��ƂŔC�ӂ̕`��������Ȃ�
drawAnyobject
//�e�N�X�`�����O��
�������Y���ƈȍ~�̃I�u�W�F�N�g�ɂ��e�N�X�`�����\���܂�
simdata->image->unbind();

///////////////////////////////////////////////////////////
V2.0
�Emeshid�ǉ��A�e�N�X�`���|���S���`�惂�[�h�ǉ�
V3.0
�EUSB�J�����ɑΉ��i�g�����͕ʓr�񎦗\��j