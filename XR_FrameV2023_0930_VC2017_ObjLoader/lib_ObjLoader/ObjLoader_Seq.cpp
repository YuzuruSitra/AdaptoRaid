#include "ObjLoader_Seq.h"

using namespace objloader;

//-----------------------------------------------------------------//
// �f�t�H���g�R���X�g���N�^                                        //
//-----------------------------------------------------------------//
CObjLoader_Seq::CObjLoader_Seq()
{
	frameCounter = 0;
	frameTolerance = 3;
	prevTime = std::chrono::system_clock::now();
}

//-----------------------------------------------------------------//
// �f�X�g���N�^                                                    //
//-----------------------------------------------------------------//
CObjLoader_Seq::~CObjLoader_Seq()
{
}

//-----------------------------------------------------------------//
// OBJ�̘A�ԃt�@�C����ǂݍ��݂܂�                                 //
//-----------------------------------------------------------------//
bool CObjLoader_Seq::read_sequence(string objfnm, int framenum, double framerate)
{
	CObjLoader cobj;                               // �C���X�^���X����
	char buf[128];

	for (int i = 0; i < framenum; i++)
	{		
		sprintf(buf, objfnm.c_str(), i);
		
		if (!cobj.read(string(buf)))
		{
			cout << "OBJ�̓Ǎ��݂Ɏ��s���܂����B" << endl;
			return false;
		}
		cout << buf << endl;
		v_objSeq.push_back(cobj);
	}

	frameDuration = 1000.0 / framerate;

	return true;
}

//-----------------------------------------------------------------//
//  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C����`�悵�܂��B     //
//-----------------------------------------------------------------//
void CObjLoader_Seq::draw_sequence(double enlarge)
{
	auto current = std::chrono::system_clock::now();
	auto dur = current - prevTime;
	auto msec = duration_cast<milliseconds>(dur).count();
	
	bool result = msec >= frameDuration ||
					abs(msec - frameDuration) <= frameTolerance;

	v_objSeq[frameCounter].draw(enlarge);

	if (result)
	{
		frameCounter++;
		if (v_objSeq.size() <= frameCounter)
			frameCounter = 0;

		prevTime = current;
	}
}

//-----------------------------------------------------------------//
//  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C�������C���`�悵�܂� //
//-----------------------------------------------------------------//
void CObjLoader_Seq::drawLine_sequence(double enlarge)
{
	v_objSeq[frameCounter].drawLine(enlarge);

	frameCounter++;
	if (v_objSeq.size() <= frameCounter)
		frameCounter = 0;
}

//-----------------------------------------------------------------//
//  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C���̖@����`�悵�܂� //
//-----------------------------------------------------------------//
void CObjLoader_Seq::drawNormal_sequence(double enlarge)
{
	v_objSeq[frameCounter].drawNormal(enlarge);

	frameCounter++;
	if (v_objSeq.size() <= frameCounter)
		frameCounter = 0;
}