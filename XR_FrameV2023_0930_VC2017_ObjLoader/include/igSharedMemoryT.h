/** @class	iglib::igSharedMemoryT
	@brief
	���L��������񋟂��܂��B

	@author Toshimitsu Mukai(toshimi@iltj.jp)

	@version 1.0

	@date    04-June-2007

	@attention
	Copyright (C) 2007, ILTJ Inc.

@verbatim
�Q�l:
	�{�N���X�̒񋟂��鋤�L�������̈�́A�P��reae/write�\�ȃv���Z�X�ƁA������read only�̃v���Z�X�Ԃ�
	���p����鎖��O��Ƃ��Ă���A������read/write�\�ȃv���Z�X�̑��݂������Ă��܂���B
	�܂��Aread/write�\�ȃv���Z�X����ԏ��߂Ƀ}�b�s���O�t�@�C���I�u�W�F�N�g���쐬����悤�ɂ��Ă��܂��B
	�{�N���X���p�҂�read/write���s���v���Z�X���P�ɂȂ�l�ɔz������΁A�ǂ̂悤�ȏ��ԂŃv���Z�X���N��
	���Ă��Aread/write�\�ȃv���Z�X���A��ԏ��߂Ƀ}�b�s���O�t�@�C���I�u�W�F�N�g���쐬����悤�ɂȂ��Ă��܂��B
	�t��read only�̃v���Z�X�݂̂����N�����Ȃ��ƁA���܂ł�wait��ԂƂȂ�܂��B
@endverbatim
*/
#ifndef __IG_SHARED_MEMORY_T_H__
#define __IG_SHARED_MEMORY_T_H__

#include <windows.h>
#include <string>
using namespace std;

namespace iglib {	// iglib namespace start here...................................................

template <class T> class igSharedMemoryT {
	string m_mappedFilename;	///< �}�b�s���O�t�@�C���I�u�W�F�N�g��(�C�ӂɎw�肪�\�B�f�t�H���g�l����)
	string m_mutexName;			///< �~���[�e�b�N��(�Œ�l)
	HANDLE m_handle;			///< �}�b�s���O�t�@�C���I�u�W�F�N�g�̃n���h��
	bool m_writable;			///< �����݂������邩(�^�ŋ���)�B�ǂݍ��݂͏펞��
	T *m_data;					///< ���L�̈�ւ�read/write�p�f�[�^

public:
	igSharedMemoryT();

	/// @brief	�������̂���R���X�g���N�^
	///	@brief	��������ini�t�@�C���̃p�X���w�肵�܂��B
	///	@param	filename	[in]	���L���������ʗp�̃L�[���[�h
	igSharedMemoryT(const string filename);

	~igSharedMemoryT(){};

	///	@brief	���L�̈���쐬���܂��B�܂��͊��ɂ��鋤�L�̈�ւ̃A�N�Z�X���\�Ƃ��܂��B
	///	@param	writable	[in]	true��read/write�ŋ��L�̈���쐬���܂��Afalse��read only�ŋ��L�̈���J���܂��B
	///	@return	���L�̈�̍쐬�ɐ��������true�A���s�����false���߂�܂��B
	bool open(const bool writable = false);

	///	@brief	���L�̈�̃f�[�^��ǂ݂܂��B
	///	@param	data	[out]	���L�̈���̃f�[�^
	///	@return	read�ɐ��������true�A���s�����false���߂�܂��B
	/// @attention read���\�Ȃ̂͋��L�̈��open(true)�ō쐬�������݂̂ł��B
	bool read(T &data)const;

	///	@brief	���L�̈�փf�[�^�������܂��B
	///	@param	data	[in]	���L�̈�֏����f�[�^
	///	@return	write�ɐ��������true�A���s�����false���߂�܂��B
	bool write(const T &data);

	///	@brief	���L�̈���폜���܂��B�܂��͗��p���̋��L�̈�ւ̃A�N�Z�X����܂��B
	///	@return	���L�̈�̍폜�܂��͕��邱�Ƃɂɐ��������true�A���s�����false���߂�܂��B
	bool close(void)const;
};

//__________________________________________________________________________________________________
//__constractor_____________________________________________________________________________________
//
template <class T>
igSharedMemoryT<T>::igSharedMemoryT(){
	m_mappedFilename = "ICOM_SHARED_MEMORY_FILE_ID";	// default name
	m_mutexName = "ICOM_SHARED_MEMORY_MUTEX_NAME";
	m_handle = NULL;
	m_writable = false;
}

//__________________________________________________________________________________________________
//__constractor_____________________________________________________________________________________
//
template <class T>
igSharedMemoryT<T>::igSharedMemoryT(const string filename){
	m_mappedFilename = filename;
	m_mutexName = "ICOM_SHARED_MEMORY_MUTEX_NAME";
	m_handle = NULL;
	m_writable = false;
}

//__________________________________________________________________________________________________
//__open____________________________________________________________________________________________
//
template <class T>
bool igSharedMemoryT<T>::open(const bool writable){
	m_writable = writable;
	DWORD fdwProtect = m_writable ? PAGE_READWRITE : PAGE_READONLY;

	// �t�@�C���}�b�v�I�u�W�F�N�g�̍쐬
	for(;;){
		m_handle = CreateFileMappingA(
			HANDLE(-1),
			NULL,
			fdwProtect,
			0,
			sizeof(T),
			m_mappedFilename.c_str()
		);

		// ���Ƀt�@�C�������邩���m�F����
		DWORD fileExists = GetLastError();

		if(m_handle == NULL)return false;

		// ����read/write�\�ȃv���Z�X�����݂��A�Ă�read/write���\��
		// ���[�h�Ńt�@�C�����J�����Ƃ����ꍇ�ɂ̓G���[�ƂȂ�
		if(m_writable){
			if(fileExists == ERROR_ALREADY_EXISTS){			// ����read/write���\�ȃv���Z�X������
				this->close();
				return false;
			}else break;									// ���߂�read/write���\�ȃv���Z�X���쐬����
		}else{
			if(fileExists == ERROR_ALREADY_EXISTS)break;	// read only�̃t�@�C�����Q�Ԗڈȍ~�ɊJ����
			else{											// read only�̃t�@�C������ԏ��߂ɍ쐬���悤�Ƃ���
				this->close();
				Sleep(1000);								// 1�b��ɍēx�g���C����
				continue;
			}
		}
	}

	// �r���[�̍쐬
	DWORD dwDesiredAccess = m_writable ? FILE_MAP_WRITE : FILE_MAP_READ;
	m_data = (T *)MapViewOfFile(m_handle, dwDesiredAccess, 0, 0, sizeof(T));
	if(m_data == NULL)return false;

	return true;
}

//__________________________________________________________________________________________________
//__read____________________________________________________________________________________________
//
template <class T>
bool igSharedMemoryT<T>::read(T &data)const{
	// �r�������̊J�n
#ifdef UNICODE
  wchar_t l_mutexName[1024];
  mbstowcs(l_mutexName, m_mutexName.c_str(), 1023);
  HANDLE hMutex = CreateMutex(NULL, FALSE, l_mutexName);
#else
	HANDLE hMutex = CreateMutex(NULL, FALSE, m_mutexName.c_str());
#endif

	WaitForSingleObject(hMutex, INFINITE);

	data = *m_data;

	// �r�������̉��� 
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return true;
}

//__________________________________________________________________________________________________
//__write___________________________________________________________________________________________
//
template <class T>
bool igSharedMemoryT<T>::write(const T &data){
	// �r�������̊J�n
#ifdef UNICODE
  wchar_t l_mutexName[1024];
  mbstowcs(l_mutexName, m_mutexName.c_str(), 1023);
  HANDLE hMutex = CreateMutex(NULL, FALSE, l_mutexName);
#else
	HANDLE hMutex = CreateMutex(NULL, FALSE, m_mutexName.c_str());
#endif

	WaitForSingleObject(hMutex, INFINITE);

	*m_data = data;

	// �r�������̉���
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return true;
}

//__________________________________________________________________________________________________
//__close___________________________________________________________________________________________
//
template <class T>
bool igSharedMemoryT<T>::close(void)const{
	if(m_data != NULL)UnmapViewOfFile(m_data);
	if(m_handle != NULL)CloseHandle(m_handle);

	return true;
}

}	// end of iglib namespace.......................................................................

#endif
