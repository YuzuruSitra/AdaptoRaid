#pragma once

#define	MRH_MAKE_OBJECT_ID_CODE( wTypeCode, wSerial )	(DWORD)( (WORD)(wTypeCode) << 16 | (WORD)(wSerial) )

#define	MRH_CAMERA_OBJECTS_TYPE	(0x0001)
#define	MRH_TARGET_OBJECTS_TYPE	(0x0002)

// Object ID code
#define	MRH_NULL_OBJECT		((DWORD)0xFFFFFFFF)
#define	MRH_CAMERA_MASTER	MRH_MAKE_OBJECT_ID_CODE( MRH_CAMERA_OBJECTS_TYPE, 0 )	// 0x00010000
#define	MRH_CAMERA_SLAVE	MRH_MAKE_OBJECT_ID_CODE( MRH_CAMERA_OBJECTS_TYPE, 1 )	// 0x00010001
#define MRH_CAMERA_ANY		MRH_MAKE_OBJECT_ID_CODE( MRH_CAMERA_OBJECTS_TYPE, 2 )	// 0x00010002

#define	MRH_TARGET_1		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 0 )	// 0x00020000
#define	MRH_TARGET_2		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 1 )	// 0x00020001
#define	MRH_TARGET_3		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 2 )	// 0x00020002
#define	MRH_TARGET_4		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 3 )	// 0x00020003
#define	MRH_TARGET_5		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 4 )	// 0x00020004
#define	MRH_TARGET_6		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 5 )	// 0x00020005
#define	MRH_TARGET_7		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 6 )	// 0x00020006
#define	MRH_TARGET_8		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 7 )	// 0x00020007
#define	MRH_TARGET_9		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 8 )	// 0x00020008
#define	MRH_TARGET_10		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 9 )	// 0x00020009
#define	MRH_TARGET_11		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 10 )	// 0x00020010
#define	MRH_TARGET_12		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 11 )	// 0x00020011
#define	MRH_TARGET_13		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 12 )	// 0x00020012
#define	MRH_TARGET_14		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 13 )	// 0x00020013
#define	MRH_TARGET_15		MRH_MAKE_OBJECT_ID_CODE( MRH_TARGET_OBJECTS_TYPE, 14 )	// 0x00020014

// Registration Status
#define MRH_REGISTRATION_RESULT_OK				((DWORD)0x00000000)	// Success(default)
#define MRH_REGISTRATION_RESULT_POSITION_NG		((DWORD)(0x1 << 0))	// Lost position
#define MRH_REGISTRATION_RESULT_ORIENTATION_NG	((DWORD)(0x1 << 1))	// Lost orietation
#define MRH_REGISTRATION_RESULT_NG \
	(MRH_REGISTRATION_RESULT_POSITION_NG \
	| MRH_REGISTRATION_RESULT_ORIENTATION_NG)						// Lost position and orientation

// MREAL Marker detection status
#define MRH_MREAL_MARKER_STATUS_UNDEFINED		((BYTE)0x00)		// Undefined
#define MRH_MREAL_MARKER_STATUS_NOT_DETECTED	((BYTE)(0x01 << 0))	// Not Detected
#define MRH_MREAL_MARKER_STATUS_DETECTED		((BYTE)(0x01 << 1))	// MREAL Marker detected successfly
#define MRH_F_CODE_STATUS_UNDEFINED				MRH_MREAL_MARKER_STATUS_UNDEFINED		// for backward compatibility
#define MRH_F_CODE_STATUS_NOT_DETECTED			MRH_MREAL_MARKER_STATUS_NOT_DETECTED	// for backward compatibility
#define MRH_F_CODE_STATUS_DETECTED				MRH_MREAL_MARKER_STATUS_DETECTED		// for backward compatibility



inline WORD MrhGetObjectCode(DWORD dwCode)
{
	return (WORD)(dwCode >> 16);
}

inline WORD MrhGetObjectIndex(DWORD dwCode)
{
	switch( dwCode ) {
		case MRH_CAMERA_MASTER:
			dwCode = MRH_CAMERA_MASTER;
			break;
		case MRH_CAMERA_SLAVE:
			dwCode = MRH_CAMERA_SLAVE;
			break;
		default:
			break;
	}
	return (WORD)(dwCode & 0xFFFF);
}

inline bool MrhIsCameraObjectCode(DWORD dwCode)
{
	return MrhGetObjectCode( dwCode ) == MRH_CAMERA_OBJECTS_TYPE;
}

inline bool MrhIsTargetObjectCode(DWORD dwCode)
{
	return MrhGetObjectCode( dwCode ) == MRH_TARGET_OBJECTS_TYPE;
}


////////////////////////////////////////////////////////////
// MrhAPI
////////////////////////////////////////////////////////////

// HRESULT code generator macro
#define	MRH_MAKE_SUCCESS_CODE( error_code )	MAKE_HRESULT( SEVERITY_SUCCESS, FACILITY_ITF, (WORD)( error_code ) )
#define	MRH_MAKE_ERROR_CODE( error_code )	MAKE_HRESULT( SEVERITY_ERROR, FACILITY_ITF, (WORD)( error_code ) )

#define	MRH_HRESULT_FIRST	(0x200)

/// Success
/// Value : 0x00000000
#define	MRH_OK				S_OK


// Error code

/// Timeout error for waiting the MREAL Engine 
/// Value : 0x80040200
#define	MRH_ERROR_WAIT_FOR_ENGINE_STARTUP_TIMEOUT			MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 0 )

/// Failure of starting up the MREAL Engine process
/// Value : 0x80040201
#define	MRH_ERROR_ENGINE_STARTUP_FAILED						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 1 )

/// Failure of waiting for MREAL Engine start up
/// Value : 0x80040202
#define	MRH_ERROR_WAIT_FOR_ENGINE_STARTUP_FAILED			MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 2 )


/// Unexpected termination
/// Value : 0x80040203
#define	MRH_ERROR_WAIT_FOR_ENGINE_FAILED_BY_EXIT			MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 3 )


/// Failure of retrieving information from the MREAL Engine
/// Value : 0x80040204
#define	MRH_ERROR_GET_ENGINE_INFORMAITON_FAILED				MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 4 )


/// Failure of initializing the shared memory 
/// Value : 0x80040205
#define	MRH_ERROR_SHARED_MEMORY_INITIALIZE_FAILED			MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 5 )


/// Failure of loading the registory value
/// Value : 0x80040206
#define	MRH_ERROR_REGISTORY_LOAD_FAILED						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 6 )


/// Some MREAL Platform process already exist
/// Value : 0x80040207
#define	MRH_ERROR_NOT_ENGINE_PROCESS						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 7 )


/// MREAL Engine instance is lost
/// Value : 0x80040208
#define	MRH_ERROR_INSTANCE_LOST								MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 8 )


/// Failure of initializing the MREAL Engine
/// Value : 0x80040209
#define	MRH_ERROR_MRP_INITIALIZE_FAILED						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 9 )



/// Unknown status
/// Value : 0x8004020A
#define	MRH_ERROR_STATUS_UNKNOWN							MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 10 )


/// Failure of accesing to the MREAL Engine process
/// Value : 0x8004020B
#define	MRH_ERROR_ENGINE_ACCESS_DENIED						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 11 )


/// Profile is not found
/// Value : 0x8004020C
#define	MRH_ERROR_PROFILE_NOT_FOUND							MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 12 )


/// Failure of loading the profile
/// Value : 0x8004020D
#define	MRH_ERROR_INVALID_PROFILE							MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 13 )


/// Failure of set of the profile
/// Value : 0x8004020E
#define	MRH_ERROR_SET_PROFILE								MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 14 )


/// Failure of set of the profile which includes unavailable value
/// Value : 0x8004020F
#define	MRH_ERROR_UNAVAILABLE_SETTING						MRH_MAKE_ERROR_CODE( MRH_HRESULT_FIRST + 15 )
