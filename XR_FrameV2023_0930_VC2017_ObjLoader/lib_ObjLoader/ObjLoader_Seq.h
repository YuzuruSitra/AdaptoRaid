#pragma once
#include "ObjLoader.h";

#include <vector>
#include <sstream>
#include <chrono>

using namespace std::chrono;

namespace objloader
{
	class CObjLoader_Seq
	{
	/*--------------*/
	/* ���J�����o   */
	/*--------------*/
	public:
		//*******************************************************************
		/*!
		*  @brief  �f�t�H���g�R���X�g���N�^
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		CObjLoader_Seq();

		//*******************************************************************
		/*!
		*  @brief  �f�X�g���N�^
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		~CObjLoader_Seq();

		//*******************************************************************
		/*!
		*  @brief  �����ł���OBJ�t�@�C�����ƃt���[�������g�p���āAOBJ�̘A�ԃt�@�C����Ǎ��݂܂��B
		*  @param  objfnm ... [In] OBJ�t�@�C�����A�A�ԕ����͏����w�蕶��(%i)�����
		*  @param  framenum ... [In] �t���[����
		*  @param  framerate ... [In] �t���[�����[�g
		*  @retval  true  ... ����I��
		*  @retval  false ... �ُ�I��
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		bool read_sequence(string objfnm, int framenum, double framerate);

		//*******************************************************************
		/*!
		*  @brief  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C����`�悵�܂��B
		*  @attention  ���O��read_sequence()���Ăяo���Ă���K�v������܂��B
		*  @param  enlarge ... [In] �g��䗦
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		
		void draw_sequence(double enlarge);

		//*******************************************************************
		/*!
		*  @brief  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C�������C���`�悵�܂��B
		*  @attention  ���O��read_sequence()���Ăяo���Ă���K�v������܂��B
		*  @param  enlarge ... [In] �g��䗦
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		void drawLine_sequence(double enlarge);

		//*******************************************************************
		/*!
		*  @brief  read_sequence()�œǍ��ݍς݂�OBJ�A�ԃt�@�C���̖@����`�悵�܂��B
		*  @attention  ���O��read_sequence()���Ăяo���Ă���K�v������܂��B
		*  @param  enlarge ... [In] �g��䗦
		*  @date  2020/03/10 ... �V�K�쐬
		*/
		//********************************************************************
		void drawNormal_sequence(double enlarge);

	/*--------------*/
	/* ����J�����o */
	/*--------------*/
	private:
		int frameCounter;
		vector <CObjLoader> v_objSeq;

		system_clock::time_point prevTime;
		double frameDuration;
		double frameTolerance;
	};
}
