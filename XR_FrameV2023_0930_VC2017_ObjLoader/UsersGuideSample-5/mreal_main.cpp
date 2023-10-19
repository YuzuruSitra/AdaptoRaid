// UsersGuideSample-5.cpp

#include "stdafx.h"
#include "UsersGuideSample.h"
#include <MrHarmonizer.h>

#include "sim.h"
#include "light.h"
extern SimDataT simdata;

#define METER_UNIT

// MREALiVR
void renderTarget(IMrhTarget *_pTarget, int id);
void copyTarget(IMrhTarget *_pTarget, int id, bool detected);
void copyMarker(IMrhMarker *_pMarker, int id, bool detected, int targetID);
void copyCamera(IMrhCamera *camera, TargetT *target, bool detected);

// �萔�E�ϐ���`
DWORD winX = 0;
DWORD winY = 0;
DWORD winW = 1280;								// �E�B���h�E�̕�
DWORD winH = 960;								// �E�B���h�E�̍���

struct {
	DWORD x;
	DWORD y;
}dispOrigin[2];									// �P��ʂ�\�����錴�_

struct {
	DWORD width;
	DWORD height;
}dispSize[2];									// �P��ʂ�\������T�C�Y

// MREAL Platform�֘A�ϐ�
IMrhEngine53			*pEngine;				// �G���W��
IMrhCamera				*pCamera[2];			// �J����
IMrhDisplayInfo			*pDispInfo;				// �\���ݒ�
IMrhRenderer53			*pRender[2];			// �`��API
IMrhDepth53* depth = 0;							// ���s���v�����ʃC���^�[�t�F�C�X
IMrhPolygon53* polygon[2] = {};					// ��̉��s���v�����ʂ̃|���S��

IMrhTarget				*pTarget[15];			// �^�[�Q�b�g

IMrhMarker              **vpMarkers;         // �}�[�J byTatewaki20170712

HANDLE					hEvent = NULL; // �G���W���X�V�C�x���g
static DWORD			dwNumOfCameras = 0;	// �J�����̐�
static DWORD			dwNumOfTarget = 0;	// �^�[�Q�b�g�̐�
static DWORD            dwNumOfMarker = 0;    // �}�[�J�̐� byTatewaki20170712

GLUquadricObj			*pFillObj = NULL; // ���z���̕`��Ɏg�p
static HDC				hDC = NULL;	// �f�o�C�X�R���e�L�X�g
static HGLRC			hRC = NULL;	// �����_�����O�R���e�L�X�g
static GLuint			bmpListID = 0;	// �f�B�X�v���C�E���X�gID

static tagMrhColorRegionMaskMethod maskMethod = MRH_COLOR_REGION_METHOD_NONE; // �}�X�N�摜�`����@

static DWORD regStatus;

//===========================================================================//
// WinMain�֐�
//===========================================================================//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	LPSTR lpszCmdLine, int nCmdShow) {
	// MREAL Platform�֘A�C���X�^���X�̏����ݒ�
	if (!initMrPlatform())
		return 0;

	// �E�B���h�E�N���X�̓o�^
	char className[] = "UsersGuideSample";
	if (!InitApp(hInstance, className)) {
		MessageBox(NULL, "Cannot Register WNDCLASSEX\n", "ERROR", MB_ICONERROR);
		return 0;
	}
	// �E�B���h�E�̍쐬
	HWND hWnd = NULL;
	if ((hWnd = InitInstance(hInstance, className, nCmdShow)) == NULL) {
		MessageBox(NULL, "Cannot Create Window\n", "ERROR", MB_ICONERROR);
		return 0;
	}

	MSG msg;
	BOOL bEndFlg = FALSE;
	while (!bEndFlg) {
		// �G���W���̏�ԕω��C�x���g���L�[�C�x���g���擾����܂őҋ@
		if (::MsgWaitForMultipleObjects(1, &hEvent, FALSE, INFINITE, QS_ALLINPUT) == 0) {
			HRESULT hr;

			// �G���W���̃p�����[�^�[���X�V
			hr = pEngine->Update();
			if (FAILED(hr)) {
				MessageBox(NULL, "IMrhEngine53::Update() FAILED.", "ERROR", MB_ICONERROR);
				DestroyWindow(hWnd);
			}

			pDispInfo->GetWindowRect(&winX, &winY, &winW, &winH);
			RECT rc = { winX, winY, winX + winW, winY + winH };
			::AdjustWindowRectEx(&rc, ::GetWindowLong(hWnd, GWL_STYLE), ::GetMenu(hWnd) != NULL, ::GetWindowLong(hWnd, GWL_EXSTYLE));
			::SetWindowPos(hWnd, NULL, winX, winY, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

			// �}�X�^�[�J���������邩�ǂ����m�F
			dwNumOfCameras = 0;
			BOOL isExist = FALSE;
			pEngine->QueryCamera(MRH_CAMERA_MASTER, &isExist);
			if (isExist) {

				pDispInfo->GetViewportRect(MRH_CAMERA_MASTER, &dispOrigin[0].x, &dispOrigin[0].y, &dispSize[0].width, &dispSize[0].height);
				dwNumOfCameras++;
			}
			// �X���[�u�J���������邩�ǂ����m�F
			// Configuration Tool�ŒP��ɐݒ肵���ۂɂ����삷��悤��
			// ���t���[���₢���킹��
			pEngine->QueryCamera(MRH_CAMERA_SLAVE, &isExist);
			if (isExist) {

				pDispInfo->GetViewportRect(MRH_CAMERA_SLAVE, &dispOrigin[1].x, &dispOrigin[1].y, &dispSize[1].width, &dispSize[1].height);
				dwNumOfCameras++;
			}

			// ���ʉ摜�y�щ��z���̂̕`��
			dispFunc();
			SwapBuffers(hDC);

		}
		else {
			// ���b�Z�[�W�L���[����L�[�C�x���g���擾
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					bEndFlg = TRUE;
					break;
				}
				// �L�[�C�x���g�𕶎����b�Z�[�W�֕ϊ�
				TranslateMessage(&msg);
				// �������b�Z�[�W��K�؂ȃE�B���h�E�v���V�[�W���ɓ]��
				DispatchMessage(&msg);
			}
		}
	}
	// MREAL Platform�֘A�C���X�^���X�̏I������
	releaseMrPlatform();
	return (int)msg.wParam;
}

//===========================================================================//
// MREAL Platform�֘A�����ݒ�
//===========================================================================//
BOOL initMrPlatform() {
	// COM������
	// MREAL Platform API�̓}���`�X���b�h�A�p�[�g�����g�iMTA)�ɂ͔�Ή�
	// �Ȃ̂�CoInitializeEx()�͎g�p���Ȃ�����
	::CoInitialize(NULL);

	// �G���W���C���X�^���X���쐬
	HRESULT hr = S_OK;
	hr = CoCreateInstance(CLSID_CMrhEngine53, NULL, CLSCTX_INPROC, IID_IMrhEngine53, (LPVOID*)&pEngine);


	if (FAILED(hr)) {
		MessageBox(NULL, "Failed in creating a instance of the MREAL Engine.", "Failed in starting an MREAL Engine", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// �G���W��������
	hr = pEngine->Initialize();
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed in initializing a instance of the MREAL Engine.", "Failed in initializing an MREAL Engine", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	// �X�V�C�x���g�̐���
	hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	// �G���W���̏�Ԃ��ω������Ƃ��̃C�x���g���w��
	pEngine->SetEventNotification(hEvent);

	// �\���ݒ�̏���₢���킹��C���X�^���X���쐬
	if (FAILED(pEngine->QueryInterface(IID_IMrhDisplayInfo, (void **)&pDispInfo))) {
		MessageBox(NULL, "Failed in creating a instance of the DisplayInfo.", "Failed in getting a DisplayInfo", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// �}�X�^�[�J���������邩�ǂ����m�F
	dwNumOfCameras = 0;
	BOOL isExist = FALSE;
	pEngine->QueryCamera(MRH_CAMERA_MASTER, &isExist);
	if (isExist) {
		// �}�X�^�[�J�����C���X�^���X���쐬
		pEngine->GetCamera(MRH_CAMERA_MASTER, &pCamera[dwNumOfCameras]);
		pEngine->GetRenderer53(MRH_CAMERA_MASTER, &pRender[dwNumOfCameras]);
		dwNumOfCameras++;
	}
	// �X���[�u�J���������邩�ǂ����m�F
	pEngine->QueryCamera(MRH_CAMERA_SLAVE, &isExist);
	if (isExist) {
		// �X���[�u�J�����C���X�^���X���쐬
		pEngine->GetCamera(MRH_CAMERA_SLAVE, &pCamera[dwNumOfCameras]);
		pEngine->GetRenderer53(MRH_CAMERA_SLAVE, &pRender[dwNumOfCameras]);
		dwNumOfCameras++;
	}

	// �X���[�u�J�����̃C���^�[�t�F�C�X�����݂���ꍇ�ɃX�e���I�v�����s��
	//���o�����F�̈�̃|���S�����쐬����D���̂Ƃ��C���E�ŃX�e���I�v���Ώۂ�
	//�`�󂪈قȂ邽�߁C�E��C����p�̃C���^�[�t�F�C�X�����ꂼ��擾����D
	if (dwNumOfCameras == 2) {
		maskMethod = MRH_COLOR_REGION_METHOD_POLYGON;

		// �F�̈�̃X�e���I�v���Ɋւ���ݒ�
		BOOL exist = FALSE;
		HRESULT res;
		// �F�̈�̃X�e���I�v���̌��ʂ��擾����C���^�[�t�F�C�X���擾
		res = pEngine->QueryDepth(MRH_DEPTH_COLOR_REGION, &exist);
		assert(res == S_OK && exist);
		res = pEngine->GetDepth53(MRH_DEPTH_COLOR_REGION, &depth);
		assert(res == S_OK && depth);

		const DWORD camera[] = { MRH_CAMERA_MASTER, MRH_CAMERA_SLAVE };
		for (DWORD i = 0; i < dwNumOfCameras; ++i) {
			// �|���S���C���^�[�t�F�C�X���擾
			res = depth->QueryPolygon(camera[i], &exist);
			assert(res == S_OK && exist);
			res = depth->GetPolygon53(camera[i], &polygon[i]);
			assert(res == S_OK && polygon[i]);
		}
	}

	for (DWORD i = 0; i < dwNumOfCameras; ++i) {
		// �}�[�J�[�L�����Z���[�̏����ݒ�
		pRender[i]->SetMarkerCancelObject(MRH_MARKER_CANCEL_OBJECT_DETECTION);
		// �}�X�N�摜�`����@�̏����ݒ�
		pRender[i]->SetColorRegionMaskMethod(maskMethod);
	}

	// �^�[�Q�b�g�̐����擾
	pEngine->GetNumOfTarget(&dwNumOfTarget);
	assert(S_OK == pEngine->GetNumOfMarker(&dwNumOfMarker)); // byTatewaki20170712

	//////// MessageBox�e�X�g�p
	/*
	if( dwNumOfMarker == 13 ){
		MessageBox( NULL, "13 markers", "OK", MB_OK|MB_ICONINFORMATION );
	}
	else{
		MessageBox( NULL, "not 13 markers", "NG", MB_OK|MB_ICONERROR );
	}
	*/
	// �^�[�Q�b�g�C���X�^���X���쐬
	const DWORD targetObj[] = {
		MRH_TARGET_1, MRH_TARGET_2, MRH_TARGET_3,
		MRH_TARGET_4, MRH_TARGET_5, MRH_TARGET_6,
		MRH_TARGET_7, MRH_TARGET_8, MRH_TARGET_9,
		MRH_TARGET_10, MRH_TARGET_11, MRH_TARGET_12,
		MRH_TARGET_13, MRH_TARGET_14, MRH_TARGET_15
	};
	for (DWORD i = 0; i < dwNumOfTarget; ++i) {
		const HRESULT res = pEngine->GetTarget(targetObj[i], &pTarget[i]);
		assert(res == S_OK);
	}

	// �}�[�J�C���X�^���X���쐬
	/*
	const int markerObj[] = {
		//199,200,201,202,203,204,205,206,207,208,209,210,211
		0,1,2,3,4,5,6,7,8,9,10,11,12
	};
	*/
	vpMarkers = new IMrhMarker*[dwNumOfMarker];

	for (DWORD i = 0; i < dwNumOfMarker; ++i) {
		IMrhMarker *cpMarker;
		HRESULT res = pEngine->GetMarker(i, &cpMarker);
		vpMarkers[i] = cpMarker;
		assert(res == S_OK);
	}

	return TRUE;
}

//===========================================================================//
// �E�B���h�E�N���X�̓o�^
//===========================================================================//
BOOL InitApp(HINSTANCE hInstance, LPSTR className) {
	WNDCLASSEX wndclsex;

	wndclsex.cbSize = sizeof(WNDCLASSEX);

	wndclsex.style = CS_HREDRAW | CS_VREDRAW;					// �X�^�C��
	wndclsex.lpfnWndProc = WndProc;									// �E�B���h�E�v���V�[�W���̖��O
	wndclsex.cbClsExtra = 0;										// �������̈�̒ǉ��ݒ�
	wndclsex.cbWndExtra = 0;										// �������̈�̒ǉ��ݒ�
	wndclsex.hInstance = hInstance;								// �v���O�����n���h��
	wndclsex.hIcon = LoadIcon(hInstance, 						// �A�C�R��
		MAKEINTRESOURCE(IDI_GUIDESAMPLE1));
	wndclsex.hCursor = LoadCursor(NULL, IDC_ARROW);			// �J�[�\��
	wndclsex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �u���V
	wndclsex.lpszMenuName = NULL;										// ���j���[
	wndclsex.lpszClassName = className;
	wndclsex.hIconSm = LoadIcon(wndclsex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wndclsex);
}

//===========================================================================//
// �E�B���h�E�v���V�[�W��
//===========================================================================//
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		// �E�B���h�E�������b�Z�[�W -------------------------------------------
	case WM_CREATE:
		// OpenGL�̏����ݒ�
		initOpenGL(hWnd);
		break;
		// �E�B���h�E�j�����b�Z�[�W -------------------------------------------
	case WM_DESTROY:
		// OpenGL�֘A�̏I������
		finalizeOpenGL(hWnd);
		// ���b�Z�[�W�L���[�ɏI�����b�Z�[�W�𑗕t
		PostQuitMessage(0);
		break;
		// �`�惁�b�Z�[�W -----------------------------------------------------
	case WM_PAINT:
		dispFunc();
		return DefWindowProc(hWnd, msg, wParam, lParam);
		// �L�[�C�x���g -------------------------------------------------------
	case WM_CHAR:
		keyPress(hWnd, wParam);
		break;
		// ���b�Z�[�W�̃f�t�H���g���� -----------------------------------------
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

//===========================================================================//
// �L�[�C�x���g
//===========================================================================//
void keyPress(HWND hWnd, WPARAM wParam) {
	switch (wParam) {
	case 27:	// �v���O�����I��(Esc�L�[)
	case 'q':
		DestroyWindow(hWnd);
		break;
	}
}

//===========================================================================//
// �E�B���h�E�̍쐬
//===========================================================================//
HWND InitInstance(HINSTANCE hInstance, LPSTR className, int nCmdShow) {

	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(className,	// �N���X��
		"UsersGuideSample",						// �E�B���h�E�̖��O
		WS_POPUP,							// �g�Ȃ��̃E�C���h�E	
		0,				 					// X���W
		0,				 					// Y���W
		winW,								// ��
		winH,								// ����
		NULL,								// �e�E�B���h�E�n���h��
		NULL,								// ���j���[�n���h��
		hInstance,							// �C���X�^���X�n���h��
		NULL 								// �E�B���h�E�쐬�f�[�^
	);
	if (!hWnd) return NULL;
	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	// �ĕ`����w��
	UpdateWindow(hWnd);
	return hWnd;
}

//===========================================================================//
// OpenGL�֘A�����ݒ�
//===========================================================================//
void initOpenGL(HWND hWnd) {
	// �E�B���h�E�N���A���̐F�w��
	glClearColor(0, 0, 0, 1);

	// 2���ȖʃI�u�W�F�N�g�𐶐�
	pFillObj = gluNewQuadric();
	gluQuadricDrawStyle(pFillObj, GLU_FILL);

	// ������ݒ�
	setLight();

	// �f�o�C�X�R���e�L�X�g�̎擾
	hDC = GetDC(hWnd);
	// �s�N�Z���t�H�[�}�b�g�̐ݒ�
	if (!setPixelFormat(hDC)) {
		MessageBox(hWnd, "Cannot set PixelFormat", "ERROR", MB_ICONERROR);
		finalizeOpenGL(hWnd);
		DestroyWindow(hWnd);
	}
	// �����_�����O�R���e�L�X�g���쐬
	hRC = wglCreateContext(hDC);
	// �����_�����O�R���e�L�X�g���J�����g�ɐݒ�
	wglMakeCurrent(hDC, hRC);

	InitScene();
}

//===========================================================================//
// ���z���̕`��̂��߂̌����̐ݒ�
//===========================================================================//
void setLight(void) {
	// ���C�g�̐ݒ�
	// ���C�g�O�Ԃ̌����ݒ�
	static GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	static GLfloat lightPosition[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	// �������f���̐ݒ�
	static float lmodelAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	static float lmodelLocalviewer[] = { 0.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelAmbient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodelLocalviewer);
}

//===========================================================================//
//  �s�N�Z���t�H�[�}�b�g��ݒ�
//===========================================================================//
BOOL setPixelFormat(HDC hdc) {
	// �s�N�Z���t�H�[�}�b�g�̐ݒ�
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cStencilBits = 1;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;            // Layer type

	// �f�o�C�X�R���e�L�X�g�Ƀs�N�Z���t�H�[�}�b�g��ݒ�
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if (pixelFormat == 0) return FALSE;
	return SetPixelFormat(hdc, pixelFormat, &pfd);
}

//===========================================================================//
//  �`��֐�
//===========================================================================//
void dispFunc() {
	// ��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//�t���X�^���p�����[�^�[�擾�ϐ�
#ifdef METER_UNIT
	double l, r, b, t, n = 0.1, f = 10;
#else
	double l, r, b, t, n = 10, f = 10000;
#endif

	//�^�[�Q�b�g���̊l��
	//�J�����̈ʒu�p����������Ȃ��ꍇ�ł�
	//�^�[�Q�b�g�̃f�[�^��simdata�̃I�u�W�F�N�g�f�[�^�ɃR�s�[
	for (unsigned int j = 0; j < dwNumOfTarget; j++) {
		if (pTarget[j]->GetRegistrationStatus(&regStatus) == S_OK &&
			regStatus == MRH_REGISTRATION_RESULT_OK) {
			//renderTarget( pTarget[j], j );
			copyTarget(pTarget[j], j, true); //��
		}
		else {
			copyTarget(pTarget[j], j, false); //��
		}
	}
	//�}�[�J�[���̊l���^�[�Q�b�g��\������D
	//�J�����̈ʒu�p����������Ȃ��ꍇ�ł��C
	//�}�[�J�[�̃f�[�^��simdata�̃I�u�W�F�N�g�f�[�^�ɃR�s�[
	BYTE byteStatus;
	for (unsigned int j = 0; j < dwNumOfMarker; j++) {
		short targetID;
		vpMarkers[j]->GetTargetId(&targetID);
		if (vpMarkers[j]->GetStatus(&byteStatus, MRH_CAMERA_MASTER) == S_OK &&
			byteStatus == MRH_MREAL_MARKER_STATUS_DETECTED)
		{
			copyMarker(vpMarkers[j], j, true, targetID - 1); //��
		}
		else
		{
			copyMarker(vpMarkers[j], j, false, targetID - 1); //��
		}
	}

	/////////////
	UpdateScene();
	/////////////
	glEnable(GL_NORMALIZE); //�X�P�[�������Ƃ��̖@���x�N�g���̒P�ʃx�N�g����
	for (unsigned int i = 0; i < dwNumOfCameras; i++) {
		// �r���[�|�[�g�̐ݒ�
		glViewport(dispOrigin[i].x, dispOrigin[i].y, dispSize[i].width, dispSize[i].height);

		// ���ʉ摜�̕\��
		pRender[i]->SetDispPosition(dispOrigin[i].x, dispOrigin[i].y);
		pRender[i]->SetDispSize(dispSize[i].width, dispSize[i].height);
		pRender[i]->SetNearFar(n, f);
		pRender[i]->Render();

		// �������e�s��̐ݒ�
		glMatrixMode(GL_PROJECTION);
		// IMrhCamera����t���X�^���p�����[�^�[���擾
		pCamera[i]->GetFrustum(&l, &r, &b, &t, n);
		// �擾�����t���X�^���p�����[�^�[��glFrustum�֐ݒ肷�邱�Ƃ�, ���ݕ\�����Ă���
		// �L���v�`���[�摜�ɓK�������������e�ݒ�ŉ��z���̂�`�悷�邱�Ƃ�
		// �\�ɂȂ�D
		glLoadIdentity();
		glFrustum(l, r, b, t, n, f);

		// ���f���r���[�ϊ��s��̐ݒ�
		glMatrixMode(GL_MODELVIEW);

		// IMrhCamera����J�����̐��E���W�n��ł̈ʒu�p�����擾
		GLfloat position[3] = { 0.0, 0.0, 0.0 };
		GLfloat axis[3] = { 0.0, 0.0, 0.0 };
		GLfloat angle = 0.0;

		// �擾�����ʒu�p����ݒ肷�邱�Ƃ�, ���ݕ\�����Ă��錻����Ԃ�
		// �K�������ʒu��, ���z���̂�`�悷�邱�Ƃ��\�ɂȂ�D
		//�J�����̈ʒu�p���������ʒu�i���_�j�̂܂܂���CG�������f���𕢂��Ă��܂��C
		//�����f�����f���Ă��Ȃ��ƊԈႦ��\��������D���̂��߁C�J������
		//�ʒu�p�����擾�ł��Ă���CG��`�悷��D
		//�J�����ʒu�p���̎擾�t���O
		DWORD regResult;
		//�}�X�^�[�J�����̈ʒu�p�����擾�ł��Ă��邩�m�F
		pCamera[0]->GetRegistrationStatus(&regResult);

		pCamera[i]->GetPosition(&position[0], &position[1], &position[2]); 
		pCamera[i]->GetOrientation(&axis[0], &axis[1], &axis[2], &angle);

		if (regResult == MRH_REGISTRATION_RESULT_OK) {
			////2021.08.02 T.OHSHIMA
			//�}�X�^�[�J�����̈ʒu�p�����擾�ł��Ă���ꍇ�̏���
			/*
			simdata.mrealCamera[i].pos.x = position[0] * 0.001;
			simdata.mrealCamera[i].pos.y = position[1] * 0.001;
			simdata.mrealCamera[i].pos.z = position[2] * 0.001;
			simdata.mrealCamera[i].ori.angle * 180.0 / M_PI;
			simdata.mrealCamera[i].ori.x = axis[0];
			simdata.mrealCamera[i].ori.y = axis[1];
			simdata.mrealCamera[i].ori.z = axis[2];
			*/
			copyCamera( pCamera[i], &simdata.mrealCamera[i], true );
			////////////////////////////////////////////////////
		}
		else{
			copyCamera( pCamera[i], &simdata.mrealCamera[i], false );
		}

		glLoadIdentity();

		glRotatef((GLfloat)(-angle * 180. / M_PI),
				(GLfloat)axis[0], (GLfloat)axis[1], (GLfloat)axis[2]);
#ifdef METER_UNIT
		glTranslatef(-position[0] * 0.001, -position[1] * 0.001, -position[2] * 0.001);
#else
		glTranslatef(-position[0], -position[1], -position[2]);
#endif

		glPushMatrix();
#ifndef METER_UNIT
		glScalef(1000.0, 1000.0, 1000.0);
#endif
		//setLight();//�O���[�o�����C�g20170613 ohshima
		glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//glEnable(GL_LIGHT1);
		//glEnable(GL_LIGHT2);
		HeadLight(); //20210802 GL_LIGHT2
		Lighting();  //20210802 GL_LIGHT0, GL_LIGHT1

		DrawScene();

		glPopMatrix();

		glDisable(GL_LIGHTING);
		PostDraw();
	}
	glFlush();
}
void copyCamera(IMrhCamera *camera, TargetT *target, bool detected)
{
	GLfloat position[3] = { 0.0, 0.0, 0.0 };
	GLfloat axis[3] = { 0.0, 0.0, 0.0 };
	GLfloat angle = 0.0;

	if (!detected) {
		if (target->detected) target->state = -1;
		else target->state = 0;
		target->detected = false;
		return;
	}
	else {
		if (target->detected) target->state = 0;
		else target->state = 1;
		target->detected = true;
	}

	camera->GetPosition(&position[0], &position[1], &position[2]);
	camera->GetOrientation(&axis[0], &axis[1], &axis[2], &angle);

	target->pos.x = position[0] * 0.001;
	target->pos.y = position[1] * 0.001;
	target->pos.z = position[2] * 0.001;

	target->ori.x = axis[0];
	target->ori.y = axis[1];
	target->ori.z = axis[2];
	target->ori.angle = angle * 180.0 / M_PI;
	return;
}
void copyTarget(IMrhTarget *_pTarget, int id, bool detected)
{
	GLfloat position[3] = { 0.0, 0.0, 0.0 };
	GLfloat axis[3] = { 0.0, 0.0, 0.0 };
	GLfloat angle = 0.0;

	if (!detected) {
		if (simdata.TargetList[id].detected)
		{
			//�O�񌩂��Ă����������Ȃ��Ȃ���
			simdata.TargetList[id].state = -1;
		}
		else
		{
			//�����Ă��Ȃ��܂�
			simdata.TargetList[id].state = 0;
		}
		simdata.TargetList[id].detected = false;
		//�����Ă��Ȃ��ꍇ�ɂ͑O��̒l��ێ������܂ܖ߂�
		return;
	}
	else {
		if (simdata.TargetList[id].detected)
		{
			//�������܂�
			simdata.TargetList[id].state = 0;
		}
		else
		{
			//�O�񌩂��Ă��Ȃ���������������
			simdata.TargetList[id].state = 1;
		}
		simdata.TargetList[id].detected = true;
	}

	_pTarget->GetPosition(&position[0], &position[1], &position[2]);
	_pTarget->GetOrientation(&axis[0], &axis[1], &axis[2], &angle);

	simdata.TargetList[id].pos.x = position[0] * 0.001;
	simdata.TargetList[id].pos.y = position[1] * 0.001;
	simdata.TargetList[id].pos.z = position[2] * 0.001;

	simdata.TargetList[id].ori.x = axis[0];
	simdata.TargetList[id].ori.y = axis[1];
	simdata.TargetList[id].ori.z = axis[2];
	simdata.TargetList[id].ori.angle = angle * 180.0 / M_PI;
	return;
}

void copyMarker(IMrhMarker *_pMarker, int id, bool detected, int targetID)
{
	GLfloat position[3] = { 0.0, 0.0, 0.0 };
	GLfloat axis[3] = { 0.0, 0.0, 0.0 };
	GLfloat angle = 0.0;

	DWORD mid;

	simdata.MarkerList[id].targetID = targetID;
	if (!detected) {

		if (simdata.MarkerList[id].detected)
			simdata.MarkerList[id].state = -1;
		else
			simdata.MarkerList[id].state = 0;

		simdata.MarkerList[id].detected = false;
		return;
	}

	if (simdata.MarkerList[id].detected)
		simdata.MarkerList[id].state = 0;
	else
		simdata.MarkerList[id].state = 1;

	simdata.MarkerList[id].detected = true;

	_pMarker->GetPosition(&position[0], &position[1], &position[2]);
	_pMarker->GetOrientation(&axis[0], &axis[1], &axis[2], &angle);

	_pMarker->GetMarkerId(&mid);
	simdata.MarkerList[id].markerID = mid;

	simdata.MarkerList[id].pos.x = position[0] * 0.001;
	simdata.MarkerList[id].pos.y = position[1] * 0.001;
	simdata.MarkerList[id].pos.z = position[2] * 0.001;

	simdata.MarkerList[id].ori.x = axis[0];
	simdata.MarkerList[id].ori.y = axis[1];
	simdata.MarkerList[id].ori.z = axis[2];
	simdata.MarkerList[id].ori.angle = angle * 180.0 / M_PI;
	return;
}


//===========================================================================//
// �^�[�Q�b�g�I�u�W�F�N�g�̕`��
//===========================================================================//
void renderTarget(IMrhTarget *_pTarget, int id) {
	// �^�[�Q�b�g�ʒu�ɉ��z���̂�\��
	glPushMatrix();

	// �^�[�Q�b�g�̈ʒu�p�����擾
	GLfloat position[3] = { 0.0, 0.0, 0.0 };
	GLfloat axis[3] = { 0.0, 0.0, 0.0 };
	GLfloat angle = 0.0;

	_pTarget->GetPosition(&position[0], &position[1], &position[2]);
	_pTarget->GetOrientation(&axis[0], &axis[1], &axis[2], &angle);

	// �擾�����^�[�Q�b�g�̈ʒu�p����ݒ肷�邱�ƂŁC�^�[�Q�b�g�̈ʒu��
	// ���z���̂�`�悷�邱�Ƃ��o����.
	glTranslatef(position[0], position[1], position[2]);
	glRotatef((GLfloat)(angle * 180. / M_PI),
		(GLfloat)axis[0], (GLfloat)axis[1], (GLfloat)axis[2]);

	//////// �����Ƀ^�[�Q�b�g�̕`��R�[�h ////////

	glPopMatrix();
}

//===========================================================================//
// �~����\������֐�
//===========================================================================//
void dispCone(GLUquadric* Cylinder, GLdouble radius, GLdouble height,
	GLfloat r, GLfloat g, GLfloat b) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �}�e���A���̐ݒ�
	GLfloat matDiff[] = { r, g, b, 1.0f };
	GLfloat matSpec[] = { 0.6f, 0.6f, 1.0f, 1.0f };
	GLfloat matAmbient[] = { 0.6f, 0.6f, 0.7f, 1.0f };
	GLfloat matShininess = 128.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

	gluCylinder(Cylinder, radius, 0.0, height, 30, 30);
}

//===========================================================================//
// �~����\������֐�
//===========================================================================//
void dispCylinder(GLUquadric* Cylinder, GLdouble radius, GLdouble height,
	GLfloat r, GLfloat g, GLfloat b) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �}�e���A���̐ݒ�
	GLfloat matDiff[] = { r, g, b, 1.0f };
	GLfloat matSpec[] = { 0.6f, 0.6f, 1.0f, 1.0f };
	GLfloat matAmbient[] = { 0.6f, 0.6f, 0.7f, 1.0f };
	GLfloat matShininess = 128.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

	gluCylinder(Cylinder, radius, radius, height, 30, 30);

}
//===========================================================================//
// OpenGL�֘A�I������
//===========================================================================//
void finalizeOpenGL(HWND hWnd) {
	// �����_�����O�R���e�L�X�g������
	wglMakeCurrent(NULL, NULL);
	// �����_�����O�R���e�L�X�g���폜
	wglDeleteContext(hRC);
	// �f�o�C�X�R���e�L�X�g������
	ReleaseDC(hWnd, hDC);
	// 2���ȖʃI�u�W�F�N�g�̔j��
	gluDeleteQuadric(pFillObj);
}

//===========================================================================//
// MREAL Platform�֘A�C���X�^���X�I������
//===========================================================================//
void releaseMrPlatform() {
	for (unsigned int i = 0; i < dwNumOfTarget; i++)
		pTarget[i]->Release();
	for (unsigned int i = 0; i < dwNumOfCameras; i++) {
		pCamera[i]->Release();
		pRender[i]->Release();
	}

	// �F�̈�̃X�e���I�v���֘A�̃C���^�[�t�F�C�X�����
	if (polygon[0])
		polygon[0]->Release();
	if (polygon[1])
		polygon[1]->Release();
	if (depth)
		depth->Release();

	pDispInfo->Release();
	pEngine->Release();
	// COM���C�u�����[�����
	::CoUninitialize();
}
