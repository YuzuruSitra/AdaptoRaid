

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Sep 16 14:15:41 2014
 */
/* Compiler settings for MrhAPI.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MrhAPI_x64_h__
#define __MrhAPI_x64_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMrhEngine_FWD_DEFINED__
#define __IMrhEngine_FWD_DEFINED__
typedef interface IMrhEngine IMrhEngine;
#endif 	/* __IMrhEngine_FWD_DEFINED__ */


#ifndef __IMrhEngine53_FWD_DEFINED__
#define __IMrhEngine53_FWD_DEFINED__
typedef interface IMrhEngine53 IMrhEngine53;
#endif 	/* __IMrhEngine53_FWD_DEFINED__ */


#ifndef __IMrhCamera_FWD_DEFINED__
#define __IMrhCamera_FWD_DEFINED__
typedef interface IMrhCamera IMrhCamera;
#endif 	/* __IMrhCamera_FWD_DEFINED__ */


#ifndef __IMrhCameraController_FWD_DEFINED__
#define __IMrhCameraController_FWD_DEFINED__
typedef interface IMrhCameraController IMrhCameraController;
#endif 	/* __IMrhCameraController_FWD_DEFINED__ */


#ifndef __IMrhImage_FWD_DEFINED__
#define __IMrhImage_FWD_DEFINED__
typedef interface IMrhImage IMrhImage;
#endif 	/* __IMrhImage_FWD_DEFINED__ */


#ifndef __IMrhDisplayInfo_FWD_DEFINED__
#define __IMrhDisplayInfo_FWD_DEFINED__
typedef interface IMrhDisplayInfo IMrhDisplayInfo;
#endif 	/* __IMrhDisplayInfo_FWD_DEFINED__ */


#ifndef __IMrhMaskController_FWD_DEFINED__
#define __IMrhMaskController_FWD_DEFINED__
typedef interface IMrhMaskController IMrhMaskController;
#endif 	/* __IMrhMaskController_FWD_DEFINED__ */


#ifndef __IMrhMaskController53_FWD_DEFINED__
#define __IMrhMaskController53_FWD_DEFINED__
typedef interface IMrhMaskController53 IMrhMaskController53;
#endif 	/* __IMrhMaskController53_FWD_DEFINED__ */


#ifndef __IMrhMaskImage_FWD_DEFINED__
#define __IMrhMaskImage_FWD_DEFINED__
typedef interface IMrhMaskImage IMrhMaskImage;
#endif 	/* __IMrhMaskImage_FWD_DEFINED__ */


#ifndef __IMrhRenderer_FWD_DEFINED__
#define __IMrhRenderer_FWD_DEFINED__
typedef interface IMrhRenderer IMrhRenderer;
#endif 	/* __IMrhRenderer_FWD_DEFINED__ */


#ifndef __IMrhRenderer53_FWD_DEFINED__
#define __IMrhRenderer53_FWD_DEFINED__
typedef interface IMrhRenderer53 IMrhRenderer53;
#endif 	/* __IMrhRenderer53_FWD_DEFINED__ */


#ifndef __IMrhSynchronizer_FWD_DEFINED__
#define __IMrhSynchronizer_FWD_DEFINED__
typedef interface IMrhSynchronizer IMrhSynchronizer;
#endif 	/* __IMrhSynchronizer_FWD_DEFINED__ */


#ifndef __IMrhSyncGaugeRenderer_FWD_DEFINED__
#define __IMrhSyncGaugeRenderer_FWD_DEFINED__
typedef interface IMrhSyncGaugeRenderer IMrhSyncGaugeRenderer;
#endif 	/* __IMrhSyncGaugeRenderer_FWD_DEFINED__ */


#ifndef __IMrhTarget_FWD_DEFINED__
#define __IMrhTarget_FWD_DEFINED__
typedef interface IMrhTarget IMrhTarget;
#endif 	/* __IMrhTarget_FWD_DEFINED__ */


#ifndef __IMrhMarker_FWD_DEFINED__
#define __IMrhMarker_FWD_DEFINED__
typedef interface IMrhMarker IMrhMarker;
#endif 	/* __IMrhMarker_FWD_DEFINED__ */


#ifndef __IMrhPolygon_FWD_DEFINED__
#define __IMrhPolygon_FWD_DEFINED__
typedef interface IMrhPolygon IMrhPolygon;
#endif 	/* __IMrhPolygon_FWD_DEFINED__ */


#ifndef __IMrhPolygon53_FWD_DEFINED__
#define __IMrhPolygon53_FWD_DEFINED__
typedef interface IMrhPolygon53 IMrhPolygon53;
#endif 	/* __IMrhPolygon53_FWD_DEFINED__ */


#ifndef __IMrhDepth_FWD_DEFINED__
#define __IMrhDepth_FWD_DEFINED__
typedef interface IMrhDepth IMrhDepth;
#endif 	/* __IMrhDepth_FWD_DEFINED__ */


#ifndef __IMrhDepth53_FWD_DEFINED__
#define __IMrhDepth53_FWD_DEFINED__
typedef interface IMrhDepth53 IMrhDepth53;
#endif 	/* __IMrhDepth53_FWD_DEFINED__ */


#ifndef __IMrhWarning_FWD_DEFINED__
#define __IMrhWarning_FWD_DEFINED__
typedef interface IMrhWarning IMrhWarning;
#endif 	/* __IMrhWarning_FWD_DEFINED__ */


#ifndef __IMrhConfiguration_FWD_DEFINED__
#define __IMrhConfiguration_FWD_DEFINED__
typedef interface IMrhConfiguration IMrhConfiguration;
#endif 	/* __IMrhConfiguration_FWD_DEFINED__ */


#ifndef __IMrhConfiguration53_FWD_DEFINED__
#define __IMrhConfiguration53_FWD_DEFINED__
typedef interface IMrhConfiguration53 IMrhConfiguration53;
#endif 	/* __IMrhConfiguration53_FWD_DEFINED__ */


#ifndef __CMrhEngine_FWD_DEFINED__
#define __CMrhEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhEngine CMrhEngine;
#else
typedef struct CMrhEngine CMrhEngine;
#endif /* __cplusplus */

#endif 	/* __CMrhEngine_FWD_DEFINED__ */


#ifndef __CMrhEngine53_FWD_DEFINED__
#define __CMrhEngine53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhEngine53 CMrhEngine53;
#else
typedef struct CMrhEngine53 CMrhEngine53;
#endif /* __cplusplus */

#endif 	/* __CMrhEngine53_FWD_DEFINED__ */


#ifndef __CMrhCamera_FWD_DEFINED__
#define __CMrhCamera_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhCamera CMrhCamera;
#else
typedef struct CMrhCamera CMrhCamera;
#endif /* __cplusplus */

#endif 	/* __CMrhCamera_FWD_DEFINED__ */


#ifndef __CMrhCameraController_FWD_DEFINED__
#define __CMrhCameraController_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhCameraController CMrhCameraController;
#else
typedef struct CMrhCameraController CMrhCameraController;
#endif /* __cplusplus */

#endif 	/* __CMrhCameraController_FWD_DEFINED__ */


#ifndef __CMrhImage_FWD_DEFINED__
#define __CMrhImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhImage CMrhImage;
#else
typedef struct CMrhImage CMrhImage;
#endif /* __cplusplus */

#endif 	/* __CMrhImage_FWD_DEFINED__ */


#ifndef __CMrhMaskController_FWD_DEFINED__
#define __CMrhMaskController_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhMaskController CMrhMaskController;
#else
typedef struct CMrhMaskController CMrhMaskController;
#endif /* __cplusplus */

#endif 	/* __CMrhMaskController_FWD_DEFINED__ */


#ifndef __CMrhMaskController53_FWD_DEFINED__
#define __CMrhMaskController53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhMaskController53 CMrhMaskController53;
#else
typedef struct CMrhMaskController53 CMrhMaskController53;
#endif /* __cplusplus */

#endif 	/* __CMrhMaskController53_FWD_DEFINED__ */


#ifndef __CMrhMaskImage_FWD_DEFINED__
#define __CMrhMaskImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhMaskImage CMrhMaskImage;
#else
typedef struct CMrhMaskImage CMrhMaskImage;
#endif /* __cplusplus */

#endif 	/* __CMrhMaskImage_FWD_DEFINED__ */


#ifndef __CMrhRenderer_FWD_DEFINED__
#define __CMrhRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhRenderer CMrhRenderer;
#else
typedef struct CMrhRenderer CMrhRenderer;
#endif /* __cplusplus */

#endif 	/* __CMrhRenderer_FWD_DEFINED__ */


#ifndef __CMrhRenderer53_FWD_DEFINED__
#define __CMrhRenderer53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhRenderer53 CMrhRenderer53;
#else
typedef struct CMrhRenderer53 CMrhRenderer53;
#endif /* __cplusplus */

#endif 	/* __CMrhRenderer53_FWD_DEFINED__ */


#ifndef __CMrhTarget_FWD_DEFINED__
#define __CMrhTarget_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhTarget CMrhTarget;
#else
typedef struct CMrhTarget CMrhTarget;
#endif /* __cplusplus */

#endif 	/* __CMrhTarget_FWD_DEFINED__ */


#ifndef __CMrhMarker_FWD_DEFINED__
#define __CMrhMarker_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhMarker CMrhMarker;
#else
typedef struct CMrhMarker CMrhMarker;
#endif /* __cplusplus */

#endif 	/* __CMrhMarker_FWD_DEFINED__ */


#ifndef __CMrhConfiguration_FWD_DEFINED__
#define __CMrhConfiguration_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhConfiguration CMrhConfiguration;
#else
typedef struct CMrhConfiguration CMrhConfiguration;
#endif /* __cplusplus */

#endif 	/* __CMrhConfiguration_FWD_DEFINED__ */


#ifndef __CMrhConfiguration53_FWD_DEFINED__
#define __CMrhConfiguration53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhConfiguration53 CMrhConfiguration53;
#else
typedef struct CMrhConfiguration53 CMrhConfiguration53;
#endif /* __cplusplus */

#endif 	/* __CMrhConfiguration53_FWD_DEFINED__ */


#ifndef __CMrhPolygon_FWD_DEFINED__
#define __CMrhPolygon_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhPolygon CMrhPolygon;
#else
typedef struct CMrhPolygon CMrhPolygon;
#endif /* __cplusplus */

#endif 	/* __CMrhPolygon_FWD_DEFINED__ */


#ifndef __CMrhPolygon53_FWD_DEFINED__
#define __CMrhPolygon53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhPolygon53 CMrhPolygon53;
#else
typedef struct CMrhPolygon53 CMrhPolygon53;
#endif /* __cplusplus */

#endif 	/* __CMrhPolygon53_FWD_DEFINED__ */


#ifndef __CMrhDepth_FWD_DEFINED__
#define __CMrhDepth_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhDepth CMrhDepth;
#else
typedef struct CMrhDepth CMrhDepth;
#endif /* __cplusplus */

#endif 	/* __CMrhDepth_FWD_DEFINED__ */


#ifndef __CMrhDepth53_FWD_DEFINED__
#define __CMrhDepth53_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhDepth53 CMrhDepth53;
#else
typedef struct CMrhDepth53 CMrhDepth53;
#endif /* __cplusplus */

#endif 	/* __CMrhDepth53_FWD_DEFINED__ */


#ifndef __CMrhWarning_FWD_DEFINED__
#define __CMrhWarning_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMrhWarning CMrhWarning;
#else
typedef struct CMrhWarning CMrhWarning;
#endif /* __cplusplus */

#endif 	/* __CMrhWarning_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MrhAPI_0000_0000 */
/* [local] */ 















typedef 
enum MrhImageType
    {	MRH_FORMAT_RGB565	= 0,
	MRH_FORMAT_RGB888	= ( MRH_FORMAT_RGB565 + 1 ) ,
	MRH_FORMAT_YUV422_CR	= ( MRH_FORMAT_RGB888 + 1 ) ,
	MRH_FORMAT_BW	= ( MRH_FORMAT_YUV422_CR + 1 ) ,
	MRH_FORMAT_ARGB8888	= ( MRH_FORMAT_BW + 1 ) ,
	MRH_FORMAT_RGBA8888	= ( MRH_FORMAT_ARGB8888 + 1 ) ,
	MRH_FORMAT_ABGR8888	= ( MRH_FORMAT_RGBA8888 + 1 ) ,
	MRH_FORMAT_BGRA8888	= ( MRH_FORMAT_ABGR8888 + 1 ) ,
	MRH_FORMAT_YUV422_FR	= ( MRH_FORMAT_BGRA8888 + 1 ) 
    } 	MrhImageType;

typedef 
enum MrhLabelingMethod
    {	MRH_METHOD_LABEL4	= 0,
	MRH_METHOD_LABEL8	= ( MRH_METHOD_LABEL4 + 1 ) 
    } 	MrhLabelingMethod;

typedef 
enum MrhDepthMethod
    {	MRH_DEPTH_COLOR_REGION	= 0,
	MRH_DEPTH_OBJECT_MODEL	= ( MRH_DEPTH_COLOR_REGION + 1 ) 
    } 	MrhDepthMethod;

typedef 
enum tagMrhColorRegionMaskMethod
    {	MRH_COLOR_REGION_METHOD_POLYGON	= 0,
	MRH_COLOR_REGION_METHOD_MASK_IMAGE	= ( MRH_COLOR_REGION_METHOD_POLYGON + 1 ) ,
	MRH_COLOR_REGION_METHOD_NONE	= ( MRH_COLOR_REGION_METHOD_MASK_IMAGE + 1 ) 
    } 	tagMrhColorRegionMaskMethod;

typedef 
enum tagMrhMarkerCancelObject
    {	MRH_MARKER_CANCEL_OBJECT_PROJECTION	= 0,
	MRH_MARKER_CANCEL_OBJECT_DETECTION	= ( MRH_MARKER_CANCEL_OBJECT_PROJECTION + 1 ) ,
	MRH_MARKER_CANCEL_OBJECT_BOTH	= ( MRH_MARKER_CANCEL_OBJECT_DETECTION + 1 ) ,
	MRH_MARKER_CANCEL_OBJECT_NONE	= ( MRH_MARKER_CANCEL_OBJECT_BOTH + 1 ) 
    } 	tagMrhMarkerCancelObject;

typedef 
enum tagMrhWarningKind
    {	MRH_WARNING_HUMAN	= 0,
	MRH_WARNING_OBJECT	= ( MRH_WARNING_HUMAN + 1 ) 
    } 	tagMrhWarningKIND;

typedef 
enum tagMrhWarningObjectKind
    {	MRH_WARNING_TYPE_NONE	= 0,
	MRH_WARNING_TYPE_MASK	= ( MRH_WARNING_TYPE_NONE + 1 ) ,
	MRH_WARNING_TYPE_WARNING	= ( MRH_WARNING_TYPE_MASK + 1 ) ,
	MRH_WARNING_TYPE_MASK_AND_WARNING	= ( MRH_WARNING_TYPE_WARNING + 1 ) 
    } 	tagMrhWarningObjectKind;

typedef 
enum MrhProfileConversion
    {	MRH_PROFILE_CONVERSION_NONE	= 0,
	MRH_PROFILE_CONVERSION_FORCE	= ( MRH_PROFILE_CONVERSION_NONE + 1 ) ,
	MRH_PROFILE_CONVERSION_FORCE_AND_BACKUP	= ( MRH_PROFILE_CONVERSION_FORCE + 1 ) 
    } 	MrhProfileConversion;



extern RPC_IF_HANDLE __MIDL_itf_MrhAPI_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MrhAPI_0000_0000_v0_0_s_ifspec;

#ifndef __IMrhEngine_INTERFACE_DEFINED__
#define __IMrhEngine_INTERFACE_DEFINED__

/* interface IMrhEngine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DAB390A6-6A2F-46a2-8477-41E3907A7894")
    IMrhEngine : public IUnknown
    {
    public:
        virtual /* [nonbrowsable][hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCamera( 
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhCamera **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTarget( 
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhTarget **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRenderer( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhRenderer **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhImage **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMaskController( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhMaskController **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraController( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhCameraController **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [local][helpstring] */ HRESULT STDMETHODCALLTYPE SetEventNotification( 
            /* [in] */ HANDLE hEvent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryCamera( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ BOOL *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfTarget( 
            /* [out][in] */ DWORD *pdwNumOfTargets) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryTargetButton( 
            /* [in] */ DWORD dwTargetId,
            /* [out][in] */ BOOL *pbButtonExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageYUV( 
            /* [in] */ DWORD dwCamera,
            /* [out] */ IMrhImage **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CheckUserProcessBeginPoint( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CheckUserProcessEndPoint( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfMarker( 
            /* [out][in] */ DWORD *pdwNumOfMarker) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMarker( 
            /* [in] */ int mk_index,
            /* [out][in] */ IMrhMarker **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryDepth( 
            /* [in] */ DWORD dwMethod,
            /* [out] */ BOOL *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDepth( 
            /* [in] */ DWORD dwMethod,
            /* [out] */ IMrhDepth **ppMrhDepth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMaskImage( 
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhEngine * This);
        
        /* [nonbrowsable][hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhEngine * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCamera )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhCamera **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTarget )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhTarget **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRenderer )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhRenderer **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhImage **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaskController )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhMaskController **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraController )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhCameraController **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IMrhEngine * This);
        
        /* [local][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEventNotification )( 
            IMrhEngine * This,
            /* [in] */ HANDLE hEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryCamera )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfTarget )( 
            IMrhEngine * This,
            /* [out][in] */ DWORD *pdwNumOfTargets);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryTargetButton )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwTargetId,
            /* [out][in] */ BOOL *pbButtonExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImageYUV )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCamera,
            /* [out] */ IMrhImage **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckUserProcessBeginPoint )( 
            IMrhEngine * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckUserProcessEndPoint )( 
            IMrhEngine * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfMarker )( 
            IMrhEngine * This,
            /* [out][in] */ DWORD *pdwNumOfMarker);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMarker )( 
            IMrhEngine * This,
            /* [in] */ int mk_index,
            /* [out][in] */ IMrhMarker **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryDepth )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwMethod,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDepth )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwMethod,
            /* [out] */ IMrhDepth **ppMrhDepth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaskImage )( 
            IMrhEngine * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppObj);
        
        END_INTERFACE
    } IMrhEngineVtbl;

    interface IMrhEngine
    {
        CONST_VTBL struct IMrhEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhEngine_Initialize(This)	\
    ( (This)->lpVtbl -> Initialize(This) ) 

#define IMrhEngine_GetCamera(This,dwObjectType,ppObj)	\
    ( (This)->lpVtbl -> GetCamera(This,dwObjectType,ppObj) ) 

#define IMrhEngine_GetTarget(This,dwObjectType,ppObj)	\
    ( (This)->lpVtbl -> GetTarget(This,dwObjectType,ppObj) ) 

#define IMrhEngine_GetRenderer(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetRenderer(This,dwCamera,ppObj) ) 

#define IMrhEngine_GetImage(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetImage(This,dwCamera,ppObj) ) 

#define IMrhEngine_GetMaskController(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetMaskController(This,dwCamera,ppObj) ) 

#define IMrhEngine_GetCameraController(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetCameraController(This,dwCamera,ppObj) ) 

#define IMrhEngine_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IMrhEngine_SetEventNotification(This,hEvent)	\
    ( (This)->lpVtbl -> SetEventNotification(This,hEvent) ) 

#define IMrhEngine_QueryCamera(This,dwCamera,pbExist)	\
    ( (This)->lpVtbl -> QueryCamera(This,dwCamera,pbExist) ) 

#define IMrhEngine_GetNumOfTarget(This,pdwNumOfTargets)	\
    ( (This)->lpVtbl -> GetNumOfTarget(This,pdwNumOfTargets) ) 

#define IMrhEngine_QueryTargetButton(This,dwTargetId,pbButtonExist)	\
    ( (This)->lpVtbl -> QueryTargetButton(This,dwTargetId,pbButtonExist) ) 

#define IMrhEngine_GetImageYUV(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetImageYUV(This,dwCamera,ppObj) ) 

#define IMrhEngine_CheckUserProcessBeginPoint(This)	\
    ( (This)->lpVtbl -> CheckUserProcessBeginPoint(This) ) 

#define IMrhEngine_CheckUserProcessEndPoint(This)	\
    ( (This)->lpVtbl -> CheckUserProcessEndPoint(This) ) 

#define IMrhEngine_GetNumOfMarker(This,pdwNumOfMarker)	\
    ( (This)->lpVtbl -> GetNumOfMarker(This,pdwNumOfMarker) ) 

#define IMrhEngine_GetMarker(This,mk_index,ppObj)	\
    ( (This)->lpVtbl -> GetMarker(This,mk_index,ppObj) ) 

#define IMrhEngine_QueryDepth(This,dwMethod,pbExist)	\
    ( (This)->lpVtbl -> QueryDepth(This,dwMethod,pbExist) ) 

#define IMrhEngine_GetDepth(This,dwMethod,ppMrhDepth)	\
    ( (This)->lpVtbl -> GetDepth(This,dwMethod,ppMrhDepth) ) 

#define IMrhEngine_GetMaskImage(This,dwCameraID,ppObj)	\
    ( (This)->lpVtbl -> GetMaskImage(This,dwCameraID,ppObj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhEngine_INTERFACE_DEFINED__ */


#ifndef __IMrhEngine53_INTERFACE_DEFINED__
#define __IMrhEngine53_INTERFACE_DEFINED__

/* interface IMrhEngine53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhEngine53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("635312DF-7988-495D-9524-B4597836BD4A")
    IMrhEngine53 : public IMrhEngine
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWarning( 
            /* [out][in] */ IMrhWarning **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LaunchHandMaskingTool( void) = 0;
        
        virtual /* [local][helpstring] */ HRESULT STDMETHODCALLTYPE GetHandMaskingEventNotification( 
            /* [out][in] */ HANDLE *eventHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetEngineLUT( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRenderer53( 
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhRenderer53 **ppObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDepth53( 
            /* [in] */ DWORD dwMethod,
            /* [out] */ IMrhDepth53 **ppMrhDepth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhEngine53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhEngine53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhEngine53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhEngine53 * This);
        
        /* [nonbrowsable][hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhEngine53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCamera )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhCamera **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTarget )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwObjectType,
            /* [out][in] */ IMrhTarget **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRenderer )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhRenderer **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhImage **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaskController )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhMaskController **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraController )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhCameraController **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IMrhEngine53 * This);
        
        /* [local][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEventNotification )( 
            IMrhEngine53 * This,
            /* [in] */ HANDLE hEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryCamera )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfTarget )( 
            IMrhEngine53 * This,
            /* [out][in] */ DWORD *pdwNumOfTargets);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryTargetButton )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwTargetId,
            /* [out][in] */ BOOL *pbButtonExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImageYUV )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out] */ IMrhImage **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckUserProcessBeginPoint )( 
            IMrhEngine53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckUserProcessEndPoint )( 
            IMrhEngine53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfMarker )( 
            IMrhEngine53 * This,
            /* [out][in] */ DWORD *pdwNumOfMarker);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMarker )( 
            IMrhEngine53 * This,
            /* [in] */ int mk_index,
            /* [out][in] */ IMrhMarker **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryDepth )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwMethod,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDepth )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwMethod,
            /* [out] */ IMrhDepth **ppMrhDepth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaskImage )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWarning )( 
            IMrhEngine53 * This,
            /* [out][in] */ IMrhWarning **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LaunchHandMaskingTool )( 
            IMrhEngine53 * This);
        
        /* [local][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHandMaskingEventNotification )( 
            IMrhEngine53 * This,
            /* [out][in] */ HANDLE *eventHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetEngineLUT )( 
            IMrhEngine53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRenderer53 )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwCamera,
            /* [out][in] */ IMrhRenderer53 **ppObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDepth53 )( 
            IMrhEngine53 * This,
            /* [in] */ DWORD dwMethod,
            /* [out] */ IMrhDepth53 **ppMrhDepth);
        
        END_INTERFACE
    } IMrhEngine53Vtbl;

    interface IMrhEngine53
    {
        CONST_VTBL struct IMrhEngine53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhEngine53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhEngine53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhEngine53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhEngine53_Initialize(This)	\
    ( (This)->lpVtbl -> Initialize(This) ) 

#define IMrhEngine53_GetCamera(This,dwObjectType,ppObj)	\
    ( (This)->lpVtbl -> GetCamera(This,dwObjectType,ppObj) ) 

#define IMrhEngine53_GetTarget(This,dwObjectType,ppObj)	\
    ( (This)->lpVtbl -> GetTarget(This,dwObjectType,ppObj) ) 

#define IMrhEngine53_GetRenderer(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetRenderer(This,dwCamera,ppObj) ) 

#define IMrhEngine53_GetImage(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetImage(This,dwCamera,ppObj) ) 

#define IMrhEngine53_GetMaskController(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetMaskController(This,dwCamera,ppObj) ) 

#define IMrhEngine53_GetCameraController(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetCameraController(This,dwCamera,ppObj) ) 

#define IMrhEngine53_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IMrhEngine53_SetEventNotification(This,hEvent)	\
    ( (This)->lpVtbl -> SetEventNotification(This,hEvent) ) 

#define IMrhEngine53_QueryCamera(This,dwCamera,pbExist)	\
    ( (This)->lpVtbl -> QueryCamera(This,dwCamera,pbExist) ) 

#define IMrhEngine53_GetNumOfTarget(This,pdwNumOfTargets)	\
    ( (This)->lpVtbl -> GetNumOfTarget(This,pdwNumOfTargets) ) 

#define IMrhEngine53_QueryTargetButton(This,dwTargetId,pbButtonExist)	\
    ( (This)->lpVtbl -> QueryTargetButton(This,dwTargetId,pbButtonExist) ) 

#define IMrhEngine53_GetImageYUV(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetImageYUV(This,dwCamera,ppObj) ) 

#define IMrhEngine53_CheckUserProcessBeginPoint(This)	\
    ( (This)->lpVtbl -> CheckUserProcessBeginPoint(This) ) 

#define IMrhEngine53_CheckUserProcessEndPoint(This)	\
    ( (This)->lpVtbl -> CheckUserProcessEndPoint(This) ) 

#define IMrhEngine53_GetNumOfMarker(This,pdwNumOfMarker)	\
    ( (This)->lpVtbl -> GetNumOfMarker(This,pdwNumOfMarker) ) 

#define IMrhEngine53_GetMarker(This,mk_index,ppObj)	\
    ( (This)->lpVtbl -> GetMarker(This,mk_index,ppObj) ) 

#define IMrhEngine53_QueryDepth(This,dwMethod,pbExist)	\
    ( (This)->lpVtbl -> QueryDepth(This,dwMethod,pbExist) ) 

#define IMrhEngine53_GetDepth(This,dwMethod,ppMrhDepth)	\
    ( (This)->lpVtbl -> GetDepth(This,dwMethod,ppMrhDepth) ) 

#define IMrhEngine53_GetMaskImage(This,dwCameraID,ppObj)	\
    ( (This)->lpVtbl -> GetMaskImage(This,dwCameraID,ppObj) ) 


#define IMrhEngine53_GetWarning(This,ppObj)	\
    ( (This)->lpVtbl -> GetWarning(This,ppObj) ) 

#define IMrhEngine53_LaunchHandMaskingTool(This)	\
    ( (This)->lpVtbl -> LaunchHandMaskingTool(This) ) 

#define IMrhEngine53_GetHandMaskingEventNotification(This,eventHandle)	\
    ( (This)->lpVtbl -> GetHandMaskingEventNotification(This,eventHandle) ) 

#define IMrhEngine53_ResetEngineLUT(This)	\
    ( (This)->lpVtbl -> ResetEngineLUT(This) ) 

#define IMrhEngine53_GetRenderer53(This,dwCamera,ppObj)	\
    ( (This)->lpVtbl -> GetRenderer53(This,dwCamera,ppObj) ) 

#define IMrhEngine53_GetDepth53(This,dwMethod,ppMrhDepth)	\
    ( (This)->lpVtbl -> GetDepth53(This,dwMethod,ppMrhDepth) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhEngine53_INTERFACE_DEFINED__ */


#ifndef __IMrhCamera_INTERFACE_DEFINED__
#define __IMrhCamera_INTERFACE_DEFINED__

/* interface IMrhCamera */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhCamera;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E3172E7F-0B11-4e71-A45C-DC35715672D8")
    IMrhCamera : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrustum( 
            /* [out][in] */ double *pdfLeft,
            /* [out][in] */ double *pdfRight,
            /* [out][in] */ double *pdfBottom,
            /* [out][in] */ double *pdfTop,
            /* [in] */ double dfNear) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOrientation( 
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRegistrationStatus( 
            /* [out][in] */ DWORD *pdwStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraVector( 
            /* [out][in] */ float *pfLookatX,
            /* [out][in] */ float *pfLookatY,
            /* [out][in] */ float *pfLookatZ,
            /* [out][in] */ float *pfUpX,
            /* [out][in] */ float *pfUpY,
            /* [out][in] */ float *pfUpZ) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhCameraVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhCamera * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhCamera * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhCamera * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhCamera * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFrustum )( 
            IMrhCamera * This,
            /* [out][in] */ double *pdfLeft,
            /* [out][in] */ double *pdfRight,
            /* [out][in] */ double *pdfBottom,
            /* [out][in] */ double *pdfTop,
            /* [in] */ double dfNear);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IMrhCamera * This,
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetOrientation )( 
            IMrhCamera * This,
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRegistrationStatus )( 
            IMrhCamera * This,
            /* [out][in] */ DWORD *pdwStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraVector )( 
            IMrhCamera * This,
            /* [out][in] */ float *pfLookatX,
            /* [out][in] */ float *pfLookatY,
            /* [out][in] */ float *pfLookatZ,
            /* [out][in] */ float *pfUpX,
            /* [out][in] */ float *pfUpY,
            /* [out][in] */ float *pfUpZ);
        
        END_INTERFACE
    } IMrhCameraVtbl;

    interface IMrhCamera
    {
        CONST_VTBL struct IMrhCameraVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhCamera_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhCamera_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhCamera_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhCamera_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhCamera_GetFrustum(This,pdfLeft,pdfRight,pdfBottom,pdfTop,dfNear)	\
    ( (This)->lpVtbl -> GetFrustum(This,pdfLeft,pdfRight,pdfBottom,pdfTop,dfNear) ) 

#define IMrhCamera_GetPosition(This,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetPosition(This,pfX,pfY,pfZ) ) 

#define IMrhCamera_GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle)	\
    ( (This)->lpVtbl -> GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle) ) 

#define IMrhCamera_GetRegistrationStatus(This,pdwStatus)	\
    ( (This)->lpVtbl -> GetRegistrationStatus(This,pdwStatus) ) 

#define IMrhCamera_GetCameraVector(This,pfLookatX,pfLookatY,pfLookatZ,pfUpX,pfUpY,pfUpZ)	\
    ( (This)->lpVtbl -> GetCameraVector(This,pfLookatX,pfLookatY,pfLookatZ,pfUpX,pfUpY,pfUpZ) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhCamera_INTERFACE_DEFINED__ */


#ifndef __IMrhCameraController_INTERFACE_DEFINED__
#define __IMrhCameraController_INTERFACE_DEFINED__

/* interface IMrhCameraController */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhCameraController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2AB254F1-7EBE-45b1-A0D3-C699DC56A3AA")
    IMrhCameraController : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShift( 
            /* [in] */ double dX,
            /* [in] */ double dY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShift( 
            /* [out] */ double *pdX,
            /* [out] */ double *pdY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetScale( 
            /* [in] */ float fX,
            /* [in] */ float fY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScale( 
            /* [out] */ float *pfX,
            /* [out] */ float *pfY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRotationAngle( 
            /* [in] */ float fAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRotationAngle( 
            /* [out] */ float *pfAngle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhCameraControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhCameraController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhCameraController * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhCameraController * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhCameraController * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetShift )( 
            IMrhCameraController * This,
            /* [in] */ double dX,
            /* [in] */ double dY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetShift )( 
            IMrhCameraController * This,
            /* [out] */ double *pdX,
            /* [out] */ double *pdY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetScale )( 
            IMrhCameraController * This,
            /* [in] */ float fX,
            /* [in] */ float fY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetScale )( 
            IMrhCameraController * This,
            /* [out] */ float *pfX,
            /* [out] */ float *pfY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRotationAngle )( 
            IMrhCameraController * This,
            /* [in] */ float fAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRotationAngle )( 
            IMrhCameraController * This,
            /* [out] */ float *pfAngle);
        
        END_INTERFACE
    } IMrhCameraControllerVtbl;

    interface IMrhCameraController
    {
        CONST_VTBL struct IMrhCameraControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhCameraController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhCameraController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhCameraController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhCameraController_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhCameraController_SetShift(This,dX,dY)	\
    ( (This)->lpVtbl -> SetShift(This,dX,dY) ) 

#define IMrhCameraController_GetShift(This,pdX,pdY)	\
    ( (This)->lpVtbl -> GetShift(This,pdX,pdY) ) 

#define IMrhCameraController_SetScale(This,fX,fY)	\
    ( (This)->lpVtbl -> SetScale(This,fX,fY) ) 

#define IMrhCameraController_GetScale(This,pfX,pfY)	\
    ( (This)->lpVtbl -> GetScale(This,pfX,pfY) ) 

#define IMrhCameraController_SetRotationAngle(This,fAngle)	\
    ( (This)->lpVtbl -> SetRotationAngle(This,fAngle) ) 

#define IMrhCameraController_GetRotationAngle(This,pfAngle)	\
    ( (This)->lpVtbl -> GetRotationAngle(This,pfAngle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhCameraController_INTERFACE_DEFINED__ */


#ifndef __IMrhImage_INTERFACE_DEFINED__
#define __IMrhImage_INTERFACE_DEFINED__

/* interface IMrhImage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("323DEB4E-45BB-4ead-B600-88BE5AE8A40B")
    IMrhImage : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera,
            /* [in] */ MrhImageType type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out][in] */ DWORD *dwWidth,
            /* [out][in] */ DWORD *dwHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [out][in] */ MrhImageType *pFormat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageData( 
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwDataSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFormattedImageData( 
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwWrittenSize,
            /* [in] */ MrhImageType Format) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhImage * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhImage * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera,
            /* [in] */ MrhImageType type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IMrhImage * This,
            /* [out][in] */ DWORD *dwWidth,
            /* [out][in] */ DWORD *dwHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IMrhImage * This,
            /* [out][in] */ MrhImageType *pFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImageData )( 
            IMrhImage * This,
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwDataSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFormattedImageData )( 
            IMrhImage * This,
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwWrittenSize,
            /* [in] */ MrhImageType Format);
        
        END_INTERFACE
    } IMrhImageVtbl;

    interface IMrhImage
    {
        CONST_VTBL struct IMrhImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhImage_Initialize(This,guid,dwCamera,type)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera,type) ) 

#define IMrhImage_GetSize(This,dwWidth,dwHeight)	\
    ( (This)->lpVtbl -> GetSize(This,dwWidth,dwHeight) ) 

#define IMrhImage_GetFormat(This,pFormat)	\
    ( (This)->lpVtbl -> GetFormat(This,pFormat) ) 

#define IMrhImage_GetImageData(This,pbyData,dwBufferSize,pdwDataSize)	\
    ( (This)->lpVtbl -> GetImageData(This,pbyData,dwBufferSize,pdwDataSize) ) 

#define IMrhImage_GetFormattedImageData(This,pbyData,dwBufferSize,pdwWrittenSize,Format)	\
    ( (This)->lpVtbl -> GetFormattedImageData(This,pbyData,dwBufferSize,pdwWrittenSize,Format) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhImage_INTERFACE_DEFINED__ */


#ifndef __IMrhDisplayInfo_INTERFACE_DEFINED__
#define __IMrhDisplayInfo_INTERFACE_DEFINED__

/* interface IMrhDisplayInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhDisplayInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B56554DB-A277-469f-B3CD-3BE8A5498698")
    IMrhDisplayInfo : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWindowRect( 
            /* [out][in] */ LPDWORD pdwX,
            /* [out][in] */ LPDWORD pdwY,
            /* [out][in] */ LPDWORD pdwWidth,
            /* [out][in] */ LPDWORD pdwHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetViewportRect( 
            /* [in] */ DWORD dwCameraID,
            /* [out][in] */ LPDWORD pdwX,
            /* [out][in] */ LPDWORD pdwY,
            /* [out][in] */ LPDWORD pdwWidth,
            /* [out][in] */ LPDWORD pdwHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhDisplayInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhDisplayInfo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhDisplayInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhDisplayInfo * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWindowRect )( 
            IMrhDisplayInfo * This,
            /* [out][in] */ LPDWORD pdwX,
            /* [out][in] */ LPDWORD pdwY,
            /* [out][in] */ LPDWORD pdwWidth,
            /* [out][in] */ LPDWORD pdwHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetViewportRect )( 
            IMrhDisplayInfo * This,
            /* [in] */ DWORD dwCameraID,
            /* [out][in] */ LPDWORD pdwX,
            /* [out][in] */ LPDWORD pdwY,
            /* [out][in] */ LPDWORD pdwWidth,
            /* [out][in] */ LPDWORD pdwHeight);
        
        END_INTERFACE
    } IMrhDisplayInfoVtbl;

    interface IMrhDisplayInfo
    {
        CONST_VTBL struct IMrhDisplayInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhDisplayInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhDisplayInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhDisplayInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhDisplayInfo_GetWindowRect(This,pdwX,pdwY,pdwWidth,pdwHeight)	\
    ( (This)->lpVtbl -> GetWindowRect(This,pdwX,pdwY,pdwWidth,pdwHeight) ) 

#define IMrhDisplayInfo_GetViewportRect(This,dwCameraID,pdwX,pdwY,pdwWidth,pdwHeight)	\
    ( (This)->lpVtbl -> GetViewportRect(This,dwCameraID,pdwX,pdwY,pdwWidth,pdwHeight) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhDisplayInfo_INTERFACE_DEFINED__ */


#ifndef __IMrhMaskController_INTERFACE_DEFINED__
#define __IMrhMaskController_INTERFACE_DEFINED__

/* interface IMrhMaskController */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhMaskController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4537302A-E195-40b6-9325-BAFEAF5CE897")
    IMrhMaskController : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisableNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsNoiseReductionEnabled( 
            /* [out] */ BOOL *pbEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableInternalNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisableInternalNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsInternalNoiseReductionEnabled( 
            /* [out] */ BOOL *pbEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableExternalNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisableExternalNoiseReduction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsExternalNoiseReductionEnabled( 
            /* [out] */ BOOL *pbEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetInternalNoiseThreshold( 
            /* [in] */ float fThreshold) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInternalNoiseThreshold( 
            /* [out] */ float *pfThreshold) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetExternalNoiseThreshold( 
            float fThreshold) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExternalNoiseThreshold( 
            /* [out] */ float *pfThreshold) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLabelingMethod( 
            /* [in] */ MrhLabelingMethod method) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLabelingMethod( 
            /* [out] */ MrhLabelingMethod *pMethod) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetYRange( 
            /* [in] */ float fYMin,
            /* [in] */ float fYMax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetYRange( 
            /* [out] */ float *pfYMin,
            /* [out] */ float *pfYMax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ int nCenterX,
            /* [in] */ int nCenterY,
            /* [in] */ float fRadialLength,
            /* [in] */ float fTangentialLength) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ int *pnCenterX,
            /* [out] */ int *pnCenterY,
            /* [out] */ float *pfRadialLength,
            /* [out] */ float *pfTangentialLength) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLUT( 
            /* [in] */ BYTE *pbyData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLUT( 
            /* [out] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out] */ DWORD *pdwDataSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhMaskControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhMaskController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhMaskController * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhMaskController * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhMaskController * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsNoiseReductionEnabled )( 
            IMrhMaskController * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableInternalNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableInternalNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsInternalNoiseReductionEnabled )( 
            IMrhMaskController * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableExternalNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableExternalNoiseReduction )( 
            IMrhMaskController * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsExternalNoiseReductionEnabled )( 
            IMrhMaskController * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetInternalNoiseThreshold )( 
            IMrhMaskController * This,
            /* [in] */ float fThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInternalNoiseThreshold )( 
            IMrhMaskController * This,
            /* [out] */ float *pfThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetExternalNoiseThreshold )( 
            IMrhMaskController * This,
            float fThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExternalNoiseThreshold )( 
            IMrhMaskController * This,
            /* [out] */ float *pfThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLabelingMethod )( 
            IMrhMaskController * This,
            /* [in] */ MrhLabelingMethod method);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLabelingMethod )( 
            IMrhMaskController * This,
            /* [out] */ MrhLabelingMethod *pMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetYRange )( 
            IMrhMaskController * This,
            /* [in] */ float fYMin,
            /* [in] */ float fYMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetYRange )( 
            IMrhMaskController * This,
            /* [out] */ float *pfYMin,
            /* [out] */ float *pfYMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetColor )( 
            IMrhMaskController * This,
            /* [in] */ int nCenterX,
            /* [in] */ int nCenterY,
            /* [in] */ float fRadialLength,
            /* [in] */ float fTangentialLength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetColor )( 
            IMrhMaskController * This,
            /* [out] */ int *pnCenterX,
            /* [out] */ int *pnCenterY,
            /* [out] */ float *pfRadialLength,
            /* [out] */ float *pfTangentialLength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLUT )( 
            IMrhMaskController * This,
            /* [in] */ BYTE *pbyData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLUT )( 
            IMrhMaskController * This,
            /* [out] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out] */ DWORD *pdwDataSize);
        
        END_INTERFACE
    } IMrhMaskControllerVtbl;

    interface IMrhMaskController
    {
        CONST_VTBL struct IMrhMaskControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhMaskController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhMaskController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhMaskController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhMaskController_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhMaskController_EnableNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableNoiseReduction(This) ) 

#define IMrhMaskController_DisableNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableNoiseReduction(This) ) 

#define IMrhMaskController_IsNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController_EnableInternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableInternalNoiseReduction(This) ) 

#define IMrhMaskController_DisableInternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableInternalNoiseReduction(This) ) 

#define IMrhMaskController_IsInternalNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsInternalNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController_EnableExternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableExternalNoiseReduction(This) ) 

#define IMrhMaskController_DisableExternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableExternalNoiseReduction(This) ) 

#define IMrhMaskController_IsExternalNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsExternalNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController_SetInternalNoiseThreshold(This,fThreshold)	\
    ( (This)->lpVtbl -> SetInternalNoiseThreshold(This,fThreshold) ) 

#define IMrhMaskController_GetInternalNoiseThreshold(This,pfThreshold)	\
    ( (This)->lpVtbl -> GetInternalNoiseThreshold(This,pfThreshold) ) 

#define IMrhMaskController_SetExternalNoiseThreshold(This,fThreshold)	\
    ( (This)->lpVtbl -> SetExternalNoiseThreshold(This,fThreshold) ) 

#define IMrhMaskController_GetExternalNoiseThreshold(This,pfThreshold)	\
    ( (This)->lpVtbl -> GetExternalNoiseThreshold(This,pfThreshold) ) 

#define IMrhMaskController_SetLabelingMethod(This,method)	\
    ( (This)->lpVtbl -> SetLabelingMethod(This,method) ) 

#define IMrhMaskController_GetLabelingMethod(This,pMethod)	\
    ( (This)->lpVtbl -> GetLabelingMethod(This,pMethod) ) 

#define IMrhMaskController_SetYRange(This,fYMin,fYMax)	\
    ( (This)->lpVtbl -> SetYRange(This,fYMin,fYMax) ) 

#define IMrhMaskController_GetYRange(This,pfYMin,pfYMax)	\
    ( (This)->lpVtbl -> GetYRange(This,pfYMin,pfYMax) ) 

#define IMrhMaskController_SetColor(This,nCenterX,nCenterY,fRadialLength,fTangentialLength)	\
    ( (This)->lpVtbl -> SetColor(This,nCenterX,nCenterY,fRadialLength,fTangentialLength) ) 

#define IMrhMaskController_GetColor(This,pnCenterX,pnCenterY,pfRadialLength,pfTangentialLength)	\
    ( (This)->lpVtbl -> GetColor(This,pnCenterX,pnCenterY,pfRadialLength,pfTangentialLength) ) 

#define IMrhMaskController_SetLUT(This,pbyData)	\
    ( (This)->lpVtbl -> SetLUT(This,pbyData) ) 

#define IMrhMaskController_GetLUT(This,pbyData,dwBufferSize,pdwDataSize)	\
    ( (This)->lpVtbl -> GetLUT(This,pbyData,dwBufferSize,pdwDataSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhMaskController_INTERFACE_DEFINED__ */


#ifndef __IMrhMaskController53_INTERFACE_DEFINED__
#define __IMrhMaskController53_INTERFACE_DEFINED__

/* interface IMrhMaskController53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhMaskController53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1093A0FC-27DE-4A9C-A69D-DE0E0BA4063E")
    IMrhMaskController53 : public IMrhMaskController
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLUTEx( 
            /* [in] */ BYTE *pbyData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhMaskController53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhMaskController53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhMaskController53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhMaskController53 * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhMaskController53 * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsNoiseReductionEnabled )( 
            IMrhMaskController53 * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableInternalNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableInternalNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsInternalNoiseReductionEnabled )( 
            IMrhMaskController53 * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableExternalNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableExternalNoiseReduction )( 
            IMrhMaskController53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsExternalNoiseReductionEnabled )( 
            IMrhMaskController53 * This,
            /* [out] */ BOOL *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetInternalNoiseThreshold )( 
            IMrhMaskController53 * This,
            /* [in] */ float fThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInternalNoiseThreshold )( 
            IMrhMaskController53 * This,
            /* [out] */ float *pfThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetExternalNoiseThreshold )( 
            IMrhMaskController53 * This,
            float fThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExternalNoiseThreshold )( 
            IMrhMaskController53 * This,
            /* [out] */ float *pfThreshold);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLabelingMethod )( 
            IMrhMaskController53 * This,
            /* [in] */ MrhLabelingMethod method);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLabelingMethod )( 
            IMrhMaskController53 * This,
            /* [out] */ MrhLabelingMethod *pMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetYRange )( 
            IMrhMaskController53 * This,
            /* [in] */ float fYMin,
            /* [in] */ float fYMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetYRange )( 
            IMrhMaskController53 * This,
            /* [out] */ float *pfYMin,
            /* [out] */ float *pfYMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetColor )( 
            IMrhMaskController53 * This,
            /* [in] */ int nCenterX,
            /* [in] */ int nCenterY,
            /* [in] */ float fRadialLength,
            /* [in] */ float fTangentialLength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetColor )( 
            IMrhMaskController53 * This,
            /* [out] */ int *pnCenterX,
            /* [out] */ int *pnCenterY,
            /* [out] */ float *pfRadialLength,
            /* [out] */ float *pfTangentialLength);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLUT )( 
            IMrhMaskController53 * This,
            /* [in] */ BYTE *pbyData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLUT )( 
            IMrhMaskController53 * This,
            /* [out] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out] */ DWORD *pdwDataSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLUTEx )( 
            IMrhMaskController53 * This,
            /* [in] */ BYTE *pbyData);
        
        END_INTERFACE
    } IMrhMaskController53Vtbl;

    interface IMrhMaskController53
    {
        CONST_VTBL struct IMrhMaskController53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhMaskController53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhMaskController53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhMaskController53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhMaskController53_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhMaskController53_EnableNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableNoiseReduction(This) ) 

#define IMrhMaskController53_DisableNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableNoiseReduction(This) ) 

#define IMrhMaskController53_IsNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController53_EnableInternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableInternalNoiseReduction(This) ) 

#define IMrhMaskController53_DisableInternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableInternalNoiseReduction(This) ) 

#define IMrhMaskController53_IsInternalNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsInternalNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController53_EnableExternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> EnableExternalNoiseReduction(This) ) 

#define IMrhMaskController53_DisableExternalNoiseReduction(This)	\
    ( (This)->lpVtbl -> DisableExternalNoiseReduction(This) ) 

#define IMrhMaskController53_IsExternalNoiseReductionEnabled(This,pbEnable)	\
    ( (This)->lpVtbl -> IsExternalNoiseReductionEnabled(This,pbEnable) ) 

#define IMrhMaskController53_SetInternalNoiseThreshold(This,fThreshold)	\
    ( (This)->lpVtbl -> SetInternalNoiseThreshold(This,fThreshold) ) 

#define IMrhMaskController53_GetInternalNoiseThreshold(This,pfThreshold)	\
    ( (This)->lpVtbl -> GetInternalNoiseThreshold(This,pfThreshold) ) 

#define IMrhMaskController53_SetExternalNoiseThreshold(This,fThreshold)	\
    ( (This)->lpVtbl -> SetExternalNoiseThreshold(This,fThreshold) ) 

#define IMrhMaskController53_GetExternalNoiseThreshold(This,pfThreshold)	\
    ( (This)->lpVtbl -> GetExternalNoiseThreshold(This,pfThreshold) ) 

#define IMrhMaskController53_SetLabelingMethod(This,method)	\
    ( (This)->lpVtbl -> SetLabelingMethod(This,method) ) 

#define IMrhMaskController53_GetLabelingMethod(This,pMethod)	\
    ( (This)->lpVtbl -> GetLabelingMethod(This,pMethod) ) 

#define IMrhMaskController53_SetYRange(This,fYMin,fYMax)	\
    ( (This)->lpVtbl -> SetYRange(This,fYMin,fYMax) ) 

#define IMrhMaskController53_GetYRange(This,pfYMin,pfYMax)	\
    ( (This)->lpVtbl -> GetYRange(This,pfYMin,pfYMax) ) 

#define IMrhMaskController53_SetColor(This,nCenterX,nCenterY,fRadialLength,fTangentialLength)	\
    ( (This)->lpVtbl -> SetColor(This,nCenterX,nCenterY,fRadialLength,fTangentialLength) ) 

#define IMrhMaskController53_GetColor(This,pnCenterX,pnCenterY,pfRadialLength,pfTangentialLength)	\
    ( (This)->lpVtbl -> GetColor(This,pnCenterX,pnCenterY,pfRadialLength,pfTangentialLength) ) 

#define IMrhMaskController53_SetLUT(This,pbyData)	\
    ( (This)->lpVtbl -> SetLUT(This,pbyData) ) 

#define IMrhMaskController53_GetLUT(This,pbyData,dwBufferSize,pdwDataSize)	\
    ( (This)->lpVtbl -> GetLUT(This,pbyData,dwBufferSize,pdwDataSize) ) 


#define IMrhMaskController53_SetLUTEx(This,pbyData)	\
    ( (This)->lpVtbl -> SetLUTEx(This,pbyData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhMaskController53_INTERFACE_DEFINED__ */


#ifndef __IMrhMaskImage_INTERFACE_DEFINED__
#define __IMrhMaskImage_INTERFACE_DEFINED__

/* interface IMrhMaskImage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhMaskImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79E37834-8B2B-417f-BAFD-75E310C71808")
    IMrhMaskImage : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera,
            MrhImageType type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out][in] */ DWORD *dwWidth,
            /* [out][in] */ DWORD *dwHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [out][in] */ MrhImageType *pFormat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageData( 
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwDataSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFormattedImageData( 
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwWrittenSize,
            /* [in] */ MrhImageType Format) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhMaskImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhMaskImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhMaskImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhMaskImage * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhMaskImage * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera,
            MrhImageType type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IMrhMaskImage * This,
            /* [out][in] */ DWORD *dwWidth,
            /* [out][in] */ DWORD *dwHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IMrhMaskImage * This,
            /* [out][in] */ MrhImageType *pFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImageData )( 
            IMrhMaskImage * This,
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwDataSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFormattedImageData )( 
            IMrhMaskImage * This,
            /* [size_is][out][in] */ BYTE *pbyData,
            /* [in] */ DWORD dwBufferSize,
            /* [out][in] */ DWORD *pdwWrittenSize,
            /* [in] */ MrhImageType Format);
        
        END_INTERFACE
    } IMrhMaskImageVtbl;

    interface IMrhMaskImage
    {
        CONST_VTBL struct IMrhMaskImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhMaskImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhMaskImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhMaskImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhMaskImage_Initialize(This,guid,dwCamera,type)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera,type) ) 

#define IMrhMaskImage_GetSize(This,dwWidth,dwHeight)	\
    ( (This)->lpVtbl -> GetSize(This,dwWidth,dwHeight) ) 

#define IMrhMaskImage_GetFormat(This,pFormat)	\
    ( (This)->lpVtbl -> GetFormat(This,pFormat) ) 

#define IMrhMaskImage_GetImageData(This,pbyData,dwBufferSize,pdwDataSize)	\
    ( (This)->lpVtbl -> GetImageData(This,pbyData,dwBufferSize,pdwDataSize) ) 

#define IMrhMaskImage_GetFormattedImageData(This,pbyData,dwBufferSize,pdwWrittenSize,Format)	\
    ( (This)->lpVtbl -> GetFormattedImageData(This,pbyData,dwBufferSize,pdwWrittenSize,Format) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhMaskImage_INTERFACE_DEFINED__ */


#ifndef __IMrhRenderer_INTERFACE_DEFINED__
#define __IMrhRenderer_INTERFACE_DEFINED__

/* interface IMrhRenderer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("91F9B16F-55E6-41d5-8607-77D613063BCA")
    IMrhRenderer : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDispSize( 
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDispPosition( 
            /* [in] */ DWORD dwX,
            /* [in] */ DWORD dwY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNearFar( 
            /* [in] */ double n,
            /* [in] */ double f) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColorRegionMaskMethod( 
            /* [in] */ tagMrhColorRegionMaskMethod ColorRegionMaskMethod) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMarkerCancelObject( 
            /* [in] */ tagMrhMarkerCancelObject MarkerCancelObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColorRegionMaskMethod( 
            /* [out][in] */ tagMrhColorRegionMaskMethod *pMethod) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMarkerCancelObject( 
            /* [out][in] */ tagMrhMarkerCancelObject *pTarget) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhRenderer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhRenderer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhRenderer * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhRenderer * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Render )( 
            IMrhRenderer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDispSize )( 
            IMrhRenderer * This,
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDispPosition )( 
            IMrhRenderer * This,
            /* [in] */ DWORD dwX,
            /* [in] */ DWORD dwY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetNearFar )( 
            IMrhRenderer * This,
            /* [in] */ double n,
            /* [in] */ double f);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetColorRegionMaskMethod )( 
            IMrhRenderer * This,
            /* [in] */ tagMrhColorRegionMaskMethod ColorRegionMaskMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetMarkerCancelObject )( 
            IMrhRenderer * This,
            /* [in] */ tagMrhMarkerCancelObject MarkerCancelObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetColorRegionMaskMethod )( 
            IMrhRenderer * This,
            /* [out][in] */ tagMrhColorRegionMaskMethod *pMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMarkerCancelObject )( 
            IMrhRenderer * This,
            /* [out][in] */ tagMrhMarkerCancelObject *pTarget);
        
        END_INTERFACE
    } IMrhRendererVtbl;

    interface IMrhRenderer
    {
        CONST_VTBL struct IMrhRendererVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhRenderer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhRenderer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhRenderer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhRenderer_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhRenderer_Render(This)	\
    ( (This)->lpVtbl -> Render(This) ) 

#define IMrhRenderer_SetDispSize(This,dwWidth,dwHeight)	\
    ( (This)->lpVtbl -> SetDispSize(This,dwWidth,dwHeight) ) 

#define IMrhRenderer_SetDispPosition(This,dwX,dwY)	\
    ( (This)->lpVtbl -> SetDispPosition(This,dwX,dwY) ) 

#define IMrhRenderer_SetNearFar(This,n,f)	\
    ( (This)->lpVtbl -> SetNearFar(This,n,f) ) 

#define IMrhRenderer_SetColorRegionMaskMethod(This,ColorRegionMaskMethod)	\
    ( (This)->lpVtbl -> SetColorRegionMaskMethod(This,ColorRegionMaskMethod) ) 

#define IMrhRenderer_SetMarkerCancelObject(This,MarkerCancelObject)	\
    ( (This)->lpVtbl -> SetMarkerCancelObject(This,MarkerCancelObject) ) 

#define IMrhRenderer_GetColorRegionMaskMethod(This,pMethod)	\
    ( (This)->lpVtbl -> GetColorRegionMaskMethod(This,pMethod) ) 

#define IMrhRenderer_GetMarkerCancelObject(This,pTarget)	\
    ( (This)->lpVtbl -> GetMarkerCancelObject(This,pTarget) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhRenderer_INTERFACE_DEFINED__ */


#ifndef __IMrhRenderer53_INTERFACE_DEFINED__
#define __IMrhRenderer53_INTERFACE_DEFINED__

/* interface IMrhRenderer53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhRenderer53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3C3FE18-7465-4E8B-A83E-82E326848AF6")
    IMrhRenderer53 : public IMrhRenderer
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenderOverlay( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhRenderer53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhRenderer53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhRenderer53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhRenderer53 * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhRenderer53 * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Render )( 
            IMrhRenderer53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDispSize )( 
            IMrhRenderer53 * This,
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDispPosition )( 
            IMrhRenderer53 * This,
            /* [in] */ DWORD dwX,
            /* [in] */ DWORD dwY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetNearFar )( 
            IMrhRenderer53 * This,
            /* [in] */ double n,
            /* [in] */ double f);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetColorRegionMaskMethod )( 
            IMrhRenderer53 * This,
            /* [in] */ tagMrhColorRegionMaskMethod ColorRegionMaskMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetMarkerCancelObject )( 
            IMrhRenderer53 * This,
            /* [in] */ tagMrhMarkerCancelObject MarkerCancelObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetColorRegionMaskMethod )( 
            IMrhRenderer53 * This,
            /* [out][in] */ tagMrhColorRegionMaskMethod *pMethod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMarkerCancelObject )( 
            IMrhRenderer53 * This,
            /* [out][in] */ tagMrhMarkerCancelObject *pTarget);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RenderOverlay )( 
            IMrhRenderer53 * This);
        
        END_INTERFACE
    } IMrhRenderer53Vtbl;

    interface IMrhRenderer53
    {
        CONST_VTBL struct IMrhRenderer53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhRenderer53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhRenderer53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhRenderer53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhRenderer53_Initialize(This,guid,dwCamera)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwCamera) ) 

#define IMrhRenderer53_Render(This)	\
    ( (This)->lpVtbl -> Render(This) ) 

#define IMrhRenderer53_SetDispSize(This,dwWidth,dwHeight)	\
    ( (This)->lpVtbl -> SetDispSize(This,dwWidth,dwHeight) ) 

#define IMrhRenderer53_SetDispPosition(This,dwX,dwY)	\
    ( (This)->lpVtbl -> SetDispPosition(This,dwX,dwY) ) 

#define IMrhRenderer53_SetNearFar(This,n,f)	\
    ( (This)->lpVtbl -> SetNearFar(This,n,f) ) 

#define IMrhRenderer53_SetColorRegionMaskMethod(This,ColorRegionMaskMethod)	\
    ( (This)->lpVtbl -> SetColorRegionMaskMethod(This,ColorRegionMaskMethod) ) 

#define IMrhRenderer53_SetMarkerCancelObject(This,MarkerCancelObject)	\
    ( (This)->lpVtbl -> SetMarkerCancelObject(This,MarkerCancelObject) ) 

#define IMrhRenderer53_GetColorRegionMaskMethod(This,pMethod)	\
    ( (This)->lpVtbl -> GetColorRegionMaskMethod(This,pMethod) ) 

#define IMrhRenderer53_GetMarkerCancelObject(This,pTarget)	\
    ( (This)->lpVtbl -> GetMarkerCancelObject(This,pTarget) ) 


#define IMrhRenderer53_RenderOverlay(This)	\
    ( (This)->lpVtbl -> RenderOverlay(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhRenderer53_INTERFACE_DEFINED__ */


#ifndef __IMrhSynchronizer_INTERFACE_DEFINED__
#define __IMrhSynchronizer_INTERFACE_DEFINED__

/* interface IMrhSynchronizer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhSynchronizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2CDE7412-02D7-4bda-AA55-4E9E6DBBD63A")
    IMrhSynchronizer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SyncReady( void) = 0;
        
        virtual /* [local][helpstring] */ HRESULT STDMETHODCALLTYPE SetSyncEventNotification( 
            /* [in] */ HANDLE hEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhSynchronizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhSynchronizer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhSynchronizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhSynchronizer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SyncReady )( 
            IMrhSynchronizer * This);
        
        /* [local][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSyncEventNotification )( 
            IMrhSynchronizer * This,
            /* [in] */ HANDLE hEvent);
        
        END_INTERFACE
    } IMrhSynchronizerVtbl;

    interface IMrhSynchronizer
    {
        CONST_VTBL struct IMrhSynchronizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhSynchronizer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhSynchronizer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhSynchronizer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhSynchronizer_SyncReady(This)	\
    ( (This)->lpVtbl -> SyncReady(This) ) 

#define IMrhSynchronizer_SetSyncEventNotification(This,hEvent)	\
    ( (This)->lpVtbl -> SetSyncEventNotification(This,hEvent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhSynchronizer_INTERFACE_DEFINED__ */


#ifndef __IMrhSyncGaugeRenderer_INTERFACE_DEFINED__
#define __IMrhSyncGaugeRenderer_INTERFACE_DEFINED__

/* interface IMrhSyncGaugeRenderer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhSyncGaugeRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C93C9383-40CE-433d-93A2-655244E25A55")
    IMrhSyncGaugeRenderer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenderSyncGauge( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhSyncGaugeRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhSyncGaugeRenderer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhSyncGaugeRenderer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhSyncGaugeRenderer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RenderSyncGauge )( 
            IMrhSyncGaugeRenderer * This);
        
        END_INTERFACE
    } IMrhSyncGaugeRendererVtbl;

    interface IMrhSyncGaugeRenderer
    {
        CONST_VTBL struct IMrhSyncGaugeRendererVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhSyncGaugeRenderer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhSyncGaugeRenderer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhSyncGaugeRenderer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhSyncGaugeRenderer_RenderSyncGauge(This)	\
    ( (This)->lpVtbl -> RenderSyncGauge(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhSyncGaugeRenderer_INTERFACE_DEFINED__ */


#ifndef __IMrhTarget_INTERFACE_DEFINED__
#define __IMrhTarget_INTERFACE_DEFINED__

/* interface IMrhTarget */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhTarget;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31D191CA-BD2F-41c4-85E7-5144815E105F")
    IMrhTarget : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwObjectID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOrientation( 
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetButtonStatus( 
            /* [out][in] */ DWORD *pdwStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRegistrationStatus( 
            /* [out][in] */ DWORD *pdwStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPoseMatrix( 
            /* [out][in] */ float *pfM00,
            /* [out][in] */ float *pfM01,
            /* [out][in] */ float *pfM02,
            /* [out][in] */ float *pfM03,
            /* [out][in] */ float *pfM10,
            /* [out][in] */ float *pfM11,
            /* [out][in] */ float *pfM12,
            /* [out][in] */ float *pfM13,
            /* [out][in] */ float *pfM20,
            /* [out][in] */ float *pfM21,
            /* [out][in] */ float *pfM22,
            /* [out][in] */ float *pfM23,
            /* [out][in] */ float *pfM30,
            /* [out][in] */ float *pfM31,
            /* [out][in] */ float *pfM32,
            /* [out][in] */ float *pfM33) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTargetTransform( 
            /* [out][in] */ FLOAT *pfX,
            /* [out][in] */ FLOAT *pfY,
            /* [out][in] */ FLOAT *pfZ,
            /* [out][in] */ FLOAT *pfAxisX,
            /* [out][in] */ FLOAT *pfAxisY,
            /* [out][in] */ FLOAT *pfAxisZ,
            /* [out][in] */ FLOAT *pfAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTargetTransform( 
            /* [in] */ FLOAT fX,
            /* [in] */ FLOAT fY,
            /* [in] */ FLOAT fZ,
            /* [in] */ FLOAT fAxisX,
            /* [in] */ FLOAT fAxisY,
            /* [in] */ FLOAT fAxisZ,
            /* [in] */ FLOAT fAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FreezePositionAndOrientation( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnfreezePositionAndOrientation( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOriginalPosition( 
            /* [out][in] */ FLOAT *pfX,
            /* [out][in] */ FLOAT *pfY,
            /* [out][in] */ FLOAT *pfZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOriginalOrientation( 
            /* [out][in] */ FLOAT *pfAxisX,
            /* [out][in] */ FLOAT *pfAxisY,
            /* [out][in] */ FLOAT *pfAxisZ,
            /* [out][in] */ FLOAT *pfAngle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhTargetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhTarget * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhTarget * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhTarget * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhTarget * This,
            /* [in] */ REFGUID guid,
            /* [in] */ DWORD dwObjectID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IMrhTarget * This,
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetOrientation )( 
            IMrhTarget * This,
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetButtonStatus )( 
            IMrhTarget * This,
            /* [out][in] */ DWORD *pdwStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRegistrationStatus )( 
            IMrhTarget * This,
            /* [out][in] */ DWORD *pdwStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoseMatrix )( 
            IMrhTarget * This,
            /* [out][in] */ float *pfM00,
            /* [out][in] */ float *pfM01,
            /* [out][in] */ float *pfM02,
            /* [out][in] */ float *pfM03,
            /* [out][in] */ float *pfM10,
            /* [out][in] */ float *pfM11,
            /* [out][in] */ float *pfM12,
            /* [out][in] */ float *pfM13,
            /* [out][in] */ float *pfM20,
            /* [out][in] */ float *pfM21,
            /* [out][in] */ float *pfM22,
            /* [out][in] */ float *pfM23,
            /* [out][in] */ float *pfM30,
            /* [out][in] */ float *pfM31,
            /* [out][in] */ float *pfM32,
            /* [out][in] */ float *pfM33);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTargetTransform )( 
            IMrhTarget * This,
            /* [out][in] */ FLOAT *pfX,
            /* [out][in] */ FLOAT *pfY,
            /* [out][in] */ FLOAT *pfZ,
            /* [out][in] */ FLOAT *pfAxisX,
            /* [out][in] */ FLOAT *pfAxisY,
            /* [out][in] */ FLOAT *pfAxisZ,
            /* [out][in] */ FLOAT *pfAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetTargetTransform )( 
            IMrhTarget * This,
            /* [in] */ FLOAT fX,
            /* [in] */ FLOAT fY,
            /* [in] */ FLOAT fZ,
            /* [in] */ FLOAT fAxisX,
            /* [in] */ FLOAT fAxisY,
            /* [in] */ FLOAT fAxisZ,
            /* [in] */ FLOAT fAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FreezePositionAndOrientation )( 
            IMrhTarget * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnfreezePositionAndOrientation )( 
            IMrhTarget * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetOriginalPosition )( 
            IMrhTarget * This,
            /* [out][in] */ FLOAT *pfX,
            /* [out][in] */ FLOAT *pfY,
            /* [out][in] */ FLOAT *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetOriginalOrientation )( 
            IMrhTarget * This,
            /* [out][in] */ FLOAT *pfAxisX,
            /* [out][in] */ FLOAT *pfAxisY,
            /* [out][in] */ FLOAT *pfAxisZ,
            /* [out][in] */ FLOAT *pfAngle);
        
        END_INTERFACE
    } IMrhTargetVtbl;

    interface IMrhTarget
    {
        CONST_VTBL struct IMrhTargetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhTarget_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhTarget_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhTarget_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhTarget_Initialize(This,guid,dwObjectID)	\
    ( (This)->lpVtbl -> Initialize(This,guid,dwObjectID) ) 

#define IMrhTarget_GetPosition(This,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetPosition(This,pfX,pfY,pfZ) ) 

#define IMrhTarget_GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle)	\
    ( (This)->lpVtbl -> GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle) ) 

#define IMrhTarget_GetButtonStatus(This,pdwStatus)	\
    ( (This)->lpVtbl -> GetButtonStatus(This,pdwStatus) ) 

#define IMrhTarget_GetRegistrationStatus(This,pdwStatus)	\
    ( (This)->lpVtbl -> GetRegistrationStatus(This,pdwStatus) ) 

#define IMrhTarget_GetPoseMatrix(This,pfM00,pfM01,pfM02,pfM03,pfM10,pfM11,pfM12,pfM13,pfM20,pfM21,pfM22,pfM23,pfM30,pfM31,pfM32,pfM33)	\
    ( (This)->lpVtbl -> GetPoseMatrix(This,pfM00,pfM01,pfM02,pfM03,pfM10,pfM11,pfM12,pfM13,pfM20,pfM21,pfM22,pfM23,pfM30,pfM31,pfM32,pfM33) ) 

#define IMrhTarget_GetTargetTransform(This,pfX,pfY,pfZ,pfAxisX,pfAxisY,pfAxisZ,pfAngle)	\
    ( (This)->lpVtbl -> GetTargetTransform(This,pfX,pfY,pfZ,pfAxisX,pfAxisY,pfAxisZ,pfAngle) ) 

#define IMrhTarget_SetTargetTransform(This,fX,fY,fZ,fAxisX,fAxisY,fAxisZ,fAngle)	\
    ( (This)->lpVtbl -> SetTargetTransform(This,fX,fY,fZ,fAxisX,fAxisY,fAxisZ,fAngle) ) 

#define IMrhTarget_FreezePositionAndOrientation(This)	\
    ( (This)->lpVtbl -> FreezePositionAndOrientation(This) ) 

#define IMrhTarget_UnfreezePositionAndOrientation(This)	\
    ( (This)->lpVtbl -> UnfreezePositionAndOrientation(This) ) 

#define IMrhTarget_GetOriginalPosition(This,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetOriginalPosition(This,pfX,pfY,pfZ) ) 

#define IMrhTarget_GetOriginalOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle)	\
    ( (This)->lpVtbl -> GetOriginalOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhTarget_INTERFACE_DEFINED__ */


#ifndef __IMrhMarker_INTERFACE_DEFINED__
#define __IMrhMarker_INTERFACE_DEFINED__

/* interface IMrhMarker */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhMarker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2ED51F79-1282-4628-826A-A4C8AE5BD294")
    IMrhMarker : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid,
            /* [in] */ short index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOrientation( 
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out][in] */ float *pfSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMarkerId( 
            /* [out][in] */ DWORD *dwMarkerId) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTargetId( 
            /* [out][in] */ short *TargetId) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out][in] */ BYTE *pbyStatus,
            /* [in] */ DWORD dwCamera) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhMarkerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhMarker * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhMarker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhMarker * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhMarker * This,
            /* [in] */ REFGUID guid,
            /* [in] */ short index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IMrhMarker * This,
            /* [out][in] */ float *pfX,
            /* [out][in] */ float *pfY,
            /* [out][in] */ float *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetOrientation )( 
            IMrhMarker * This,
            /* [out][in] */ float *pfAxisX,
            /* [out][in] */ float *pfAxisY,
            /* [out][in] */ float *pfAxisZ,
            /* [out][in] */ float *pfAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IMrhMarker * This,
            /* [out][in] */ float *pfSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMarkerId )( 
            IMrhMarker * This,
            /* [out][in] */ DWORD *dwMarkerId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTargetId )( 
            IMrhMarker * This,
            /* [out][in] */ short *TargetId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            IMrhMarker * This,
            /* [out][in] */ BYTE *pbyStatus,
            /* [in] */ DWORD dwCamera);
        
        END_INTERFACE
    } IMrhMarkerVtbl;

    interface IMrhMarker
    {
        CONST_VTBL struct IMrhMarkerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhMarker_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhMarker_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhMarker_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhMarker_Initialize(This,guid,index)	\
    ( (This)->lpVtbl -> Initialize(This,guid,index) ) 

#define IMrhMarker_GetPosition(This,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetPosition(This,pfX,pfY,pfZ) ) 

#define IMrhMarker_GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle)	\
    ( (This)->lpVtbl -> GetOrientation(This,pfAxisX,pfAxisY,pfAxisZ,pfAngle) ) 

#define IMrhMarker_GetSize(This,pfSize)	\
    ( (This)->lpVtbl -> GetSize(This,pfSize) ) 

#define IMrhMarker_GetMarkerId(This,dwMarkerId)	\
    ( (This)->lpVtbl -> GetMarkerId(This,dwMarkerId) ) 

#define IMrhMarker_GetTargetId(This,TargetId)	\
    ( (This)->lpVtbl -> GetTargetId(This,TargetId) ) 

#define IMrhMarker_GetStatus(This,pbyStatus,dwCamera)	\
    ( (This)->lpVtbl -> GetStatus(This,pbyStatus,dwCamera) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhMarker_INTERFACE_DEFINED__ */


#ifndef __IMrhPolygon_INTERFACE_DEFINED__
#define __IMrhPolygon_INTERFACE_DEFINED__

/* interface IMrhPolygon */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhPolygon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9D4E231-9F72-45b6-B5C2-E1DA4DF78633")
    IMrhPolygon : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfTriangles( 
            /* [out] */ DWORD *pdwNumberOfTriangles) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTriangle( 
            /* [in] */ DWORD dwTriangle,
            /* [out] */ DWORD *pdwVertex0,
            /* [out] */ DWORD *pdwVertex1,
            /* [out] */ DWORD *pdwVertex2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfVertices( 
            /* [out] */ DWORD *pdwNumberOfVertices) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfRegions( 
            /* [out] */ DWORD *pdwNumberOfRegions) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVertex( 
            /* [in] */ DWORD dwVertex,
            /* [out] */ float *pfX,
            /* [out] */ float *pfY,
            /* [out] */ float *pfZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVertexColor( 
            /* [in] */ DWORD dwVertex,
            /* [out] */ BYTE *pbyRed,
            /* [out] */ BYTE *pbyGreen,
            /* [out] */ BYTE *pdyBlue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRegionId( 
            /* [in] */ DWORD dwVertex,
            /* [out] */ DWORD *pdwRegionId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhPolygonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhPolygon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhPolygon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhPolygon * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfTriangles )( 
            IMrhPolygon * This,
            /* [out] */ DWORD *pdwNumberOfTriangles);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTriangle )( 
            IMrhPolygon * This,
            /* [in] */ DWORD dwTriangle,
            /* [out] */ DWORD *pdwVertex0,
            /* [out] */ DWORD *pdwVertex1,
            /* [out] */ DWORD *pdwVertex2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfVertices )( 
            IMrhPolygon * This,
            /* [out] */ DWORD *pdwNumberOfVertices);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfRegions )( 
            IMrhPolygon * This,
            /* [out] */ DWORD *pdwNumberOfRegions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVertex )( 
            IMrhPolygon * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ float *pfX,
            /* [out] */ float *pfY,
            /* [out] */ float *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVertexColor )( 
            IMrhPolygon * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ BYTE *pbyRed,
            /* [out] */ BYTE *pbyGreen,
            /* [out] */ BYTE *pdyBlue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRegionId )( 
            IMrhPolygon * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ DWORD *pdwRegionId);
        
        END_INTERFACE
    } IMrhPolygonVtbl;

    interface IMrhPolygon
    {
        CONST_VTBL struct IMrhPolygonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhPolygon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhPolygon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhPolygon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhPolygon_GetNumOfTriangles(This,pdwNumberOfTriangles)	\
    ( (This)->lpVtbl -> GetNumOfTriangles(This,pdwNumberOfTriangles) ) 

#define IMrhPolygon_GetTriangle(This,dwTriangle,pdwVertex0,pdwVertex1,pdwVertex2)	\
    ( (This)->lpVtbl -> GetTriangle(This,dwTriangle,pdwVertex0,pdwVertex1,pdwVertex2) ) 

#define IMrhPolygon_GetNumOfVertices(This,pdwNumberOfVertices)	\
    ( (This)->lpVtbl -> GetNumOfVertices(This,pdwNumberOfVertices) ) 

#define IMrhPolygon_GetNumOfRegions(This,pdwNumberOfRegions)	\
    ( (This)->lpVtbl -> GetNumOfRegions(This,pdwNumberOfRegions) ) 

#define IMrhPolygon_GetVertex(This,dwVertex,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetVertex(This,dwVertex,pfX,pfY,pfZ) ) 

#define IMrhPolygon_GetVertexColor(This,dwVertex,pbyRed,pbyGreen,pdyBlue)	\
    ( (This)->lpVtbl -> GetVertexColor(This,dwVertex,pbyRed,pbyGreen,pdyBlue) ) 

#define IMrhPolygon_GetRegionId(This,dwVertex,pdwRegionId)	\
    ( (This)->lpVtbl -> GetRegionId(This,dwVertex,pdwRegionId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhPolygon_INTERFACE_DEFINED__ */


#ifndef __IMrhPolygon53_INTERFACE_DEFINED__
#define __IMrhPolygon53_INTERFACE_DEFINED__

/* interface IMrhPolygon53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhPolygon53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A17EF5AF-808A-4EBE-8808-EF30820F322C")
    IMrhPolygon53 : public IMrhPolygon
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetKind( 
            /* [in] */ DWORD dwRegionID,
            /* [out] */ tagMrhWarningObjectKind *pdwKind) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhPolygon53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhPolygon53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhPolygon53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhPolygon53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfTriangles )( 
            IMrhPolygon53 * This,
            /* [out] */ DWORD *pdwNumberOfTriangles);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTriangle )( 
            IMrhPolygon53 * This,
            /* [in] */ DWORD dwTriangle,
            /* [out] */ DWORD *pdwVertex0,
            /* [out] */ DWORD *pdwVertex1,
            /* [out] */ DWORD *pdwVertex2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfVertices )( 
            IMrhPolygon53 * This,
            /* [out] */ DWORD *pdwNumberOfVertices);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfRegions )( 
            IMrhPolygon53 * This,
            /* [out] */ DWORD *pdwNumberOfRegions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVertex )( 
            IMrhPolygon53 * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ float *pfX,
            /* [out] */ float *pfY,
            /* [out] */ float *pfZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVertexColor )( 
            IMrhPolygon53 * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ BYTE *pbyRed,
            /* [out] */ BYTE *pbyGreen,
            /* [out] */ BYTE *pdyBlue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRegionId )( 
            IMrhPolygon53 * This,
            /* [in] */ DWORD dwVertex,
            /* [out] */ DWORD *pdwRegionId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetKind )( 
            IMrhPolygon53 * This,
            /* [in] */ DWORD dwRegionID,
            /* [out] */ tagMrhWarningObjectKind *pdwKind);
        
        END_INTERFACE
    } IMrhPolygon53Vtbl;

    interface IMrhPolygon53
    {
        CONST_VTBL struct IMrhPolygon53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhPolygon53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhPolygon53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhPolygon53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhPolygon53_GetNumOfTriangles(This,pdwNumberOfTriangles)	\
    ( (This)->lpVtbl -> GetNumOfTriangles(This,pdwNumberOfTriangles) ) 

#define IMrhPolygon53_GetTriangle(This,dwTriangle,pdwVertex0,pdwVertex1,pdwVertex2)	\
    ( (This)->lpVtbl -> GetTriangle(This,dwTriangle,pdwVertex0,pdwVertex1,pdwVertex2) ) 

#define IMrhPolygon53_GetNumOfVertices(This,pdwNumberOfVertices)	\
    ( (This)->lpVtbl -> GetNumOfVertices(This,pdwNumberOfVertices) ) 

#define IMrhPolygon53_GetNumOfRegions(This,pdwNumberOfRegions)	\
    ( (This)->lpVtbl -> GetNumOfRegions(This,pdwNumberOfRegions) ) 

#define IMrhPolygon53_GetVertex(This,dwVertex,pfX,pfY,pfZ)	\
    ( (This)->lpVtbl -> GetVertex(This,dwVertex,pfX,pfY,pfZ) ) 

#define IMrhPolygon53_GetVertexColor(This,dwVertex,pbyRed,pbyGreen,pdyBlue)	\
    ( (This)->lpVtbl -> GetVertexColor(This,dwVertex,pbyRed,pbyGreen,pdyBlue) ) 

#define IMrhPolygon53_GetRegionId(This,dwVertex,pdwRegionId)	\
    ( (This)->lpVtbl -> GetRegionId(This,dwVertex,pdwRegionId) ) 


#define IMrhPolygon53_GetKind(This,dwRegionID,pdwKind)	\
    ( (This)->lpVtbl -> GetKind(This,dwRegionID,pdwKind) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhPolygon53_INTERFACE_DEFINED__ */


#ifndef __IMrhDepth_INTERFACE_DEFINED__
#define __IMrhDepth_INTERFACE_DEFINED__

/* interface IMrhDepth */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhDepth;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8235105-6A62-4548-BC18-9D57BD9367BB")
    IMrhDepth : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryImage( 
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppMrhImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryPolygon( 
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPolygon( 
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhPolygon **ppMrhPolygon) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhDepthVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhDepth * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhDepth * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhDepth * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryImage )( 
            IMrhDepth * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IMrhDepth * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppMrhImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryPolygon )( 
            IMrhDepth * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPolygon )( 
            IMrhDepth * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhPolygon **ppMrhPolygon);
        
        END_INTERFACE
    } IMrhDepthVtbl;

    interface IMrhDepth
    {
        CONST_VTBL struct IMrhDepthVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhDepth_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhDepth_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhDepth_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhDepth_QueryImage(This,dwCameraID,pbExist)	\
    ( (This)->lpVtbl -> QueryImage(This,dwCameraID,pbExist) ) 

#define IMrhDepth_GetImage(This,dwCameraID,ppMrhImage)	\
    ( (This)->lpVtbl -> GetImage(This,dwCameraID,ppMrhImage) ) 

#define IMrhDepth_QueryPolygon(This,dwCameraID,pbExist)	\
    ( (This)->lpVtbl -> QueryPolygon(This,dwCameraID,pbExist) ) 

#define IMrhDepth_GetPolygon(This,dwCameraID,ppMrhPolygon)	\
    ( (This)->lpVtbl -> GetPolygon(This,dwCameraID,ppMrhPolygon) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhDepth_INTERFACE_DEFINED__ */


#ifndef __IMrhDepth53_INTERFACE_DEFINED__
#define __IMrhDepth53_INTERFACE_DEFINED__

/* interface IMrhDepth53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhDepth53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4AEBCBE6-DBA9-4CD9-8826-AAA6D44E8E5B")
    IMrhDepth53 : public IMrhDepth
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPolygon53( 
            /* [in] */ DWORD dwRegionID,
            /* [out] */ IMrhPolygon53 **ppMrhPolygon) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhDepth53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhDepth53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhDepth53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhDepth53 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryImage )( 
            IMrhDepth53 * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IMrhDepth53 * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhImage **ppMrhImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryPolygon )( 
            IMrhDepth53 * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ BOOL *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPolygon )( 
            IMrhDepth53 * This,
            /* [in] */ DWORD dwCameraID,
            /* [out] */ IMrhPolygon **ppMrhPolygon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPolygon53 )( 
            IMrhDepth53 * This,
            /* [in] */ DWORD dwRegionID,
            /* [out] */ IMrhPolygon53 **ppMrhPolygon);
        
        END_INTERFACE
    } IMrhDepth53Vtbl;

    interface IMrhDepth53
    {
        CONST_VTBL struct IMrhDepth53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhDepth53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhDepth53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhDepth53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhDepth53_QueryImage(This,dwCameraID,pbExist)	\
    ( (This)->lpVtbl -> QueryImage(This,dwCameraID,pbExist) ) 

#define IMrhDepth53_GetImage(This,dwCameraID,ppMrhImage)	\
    ( (This)->lpVtbl -> GetImage(This,dwCameraID,ppMrhImage) ) 

#define IMrhDepth53_QueryPolygon(This,dwCameraID,pbExist)	\
    ( (This)->lpVtbl -> QueryPolygon(This,dwCameraID,pbExist) ) 

#define IMrhDepth53_GetPolygon(This,dwCameraID,ppMrhPolygon)	\
    ( (This)->lpVtbl -> GetPolygon(This,dwCameraID,ppMrhPolygon) ) 


#define IMrhDepth53_GetPolygon53(This,dwRegionID,ppMrhPolygon)	\
    ( (This)->lpVtbl -> GetPolygon53(This,dwRegionID,ppMrhPolygon) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhDepth53_INTERFACE_DEFINED__ */


#ifndef __IMrhWarning_INTERFACE_DEFINED__
#define __IMrhWarning_INTERFACE_DEFINED__

/* interface IMrhWarning */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhWarning;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC82677F-73C3-4829-ADA7-C3376F61019B")
    IMrhWarning : public IUnknown
    {
    public:
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ REFGUID guid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumOfWarningInfo( 
            /* [out] */ int *pNumOfWarningInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWarningInfo( 
            /* [in] */ DWORD dwWarningID,
            /* [out] */ DWORD *pKIND,
            float *pVecX,
            float *pVecY,
            float *pVecZ,
            float *pWarningDistance,
            float *pActualDistance,
            DWORD *pRegionID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhWarningVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhWarning * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhWarning * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhWarning * This);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMrhWarning * This,
            /* [in] */ REFGUID guid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumOfWarningInfo )( 
            IMrhWarning * This,
            /* [out] */ int *pNumOfWarningInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWarningInfo )( 
            IMrhWarning * This,
            /* [in] */ DWORD dwWarningID,
            /* [out] */ DWORD *pKIND,
            float *pVecX,
            float *pVecY,
            float *pVecZ,
            float *pWarningDistance,
            float *pActualDistance,
            DWORD *pRegionID);
        
        END_INTERFACE
    } IMrhWarningVtbl;

    interface IMrhWarning
    {
        CONST_VTBL struct IMrhWarningVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhWarning_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhWarning_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhWarning_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhWarning_Initialize(This,guid)	\
    ( (This)->lpVtbl -> Initialize(This,guid) ) 

#define IMrhWarning_GetNumOfWarningInfo(This,pNumOfWarningInfo)	\
    ( (This)->lpVtbl -> GetNumOfWarningInfo(This,pNumOfWarningInfo) ) 

#define IMrhWarning_GetWarningInfo(This,dwWarningID,pKIND,pVecX,pVecY,pVecZ,pWarningDistance,pActualDistance,pRegionID)	\
    ( (This)->lpVtbl -> GetWarningInfo(This,dwWarningID,pKIND,pVecX,pVecY,pVecZ,pWarningDistance,pActualDistance,pRegionID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhWarning_INTERFACE_DEFINED__ */


#ifndef __IMrhConfiguration_INTERFACE_DEFINED__
#define __IMrhConfiguration_INTERFACE_DEFINED__

/* interface IMrhConfiguration */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhConfiguration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6DA3EA9-5D1B-4cc9-A511-421850479552")
    IMrhConfiguration : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProfilesList( 
            /* [out] */ VARIANT *profiles) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetProfile( 
            /* [in] */ BSTR profileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentProfile( 
            /* [out] */ BSTR *profileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhConfigurationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhConfiguration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhConfiguration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhConfiguration * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMrhConfiguration * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMrhConfiguration * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMrhConfiguration * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMrhConfiguration * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetProfilesList )( 
            IMrhConfiguration * This,
            /* [out] */ VARIANT *profiles);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetProfile )( 
            IMrhConfiguration * This,
            /* [in] */ BSTR profileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentProfile )( 
            IMrhConfiguration * This,
            /* [out] */ BSTR *profileName);
        
        END_INTERFACE
    } IMrhConfigurationVtbl;

    interface IMrhConfiguration
    {
        CONST_VTBL struct IMrhConfigurationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhConfiguration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhConfiguration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhConfiguration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhConfiguration_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMrhConfiguration_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMrhConfiguration_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMrhConfiguration_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMrhConfiguration_GetProfilesList(This,profiles)	\
    ( (This)->lpVtbl -> GetProfilesList(This,profiles) ) 

#define IMrhConfiguration_SetProfile(This,profileName)	\
    ( (This)->lpVtbl -> SetProfile(This,profileName) ) 

#define IMrhConfiguration_GetCurrentProfile(This,profileName)	\
    ( (This)->lpVtbl -> GetCurrentProfile(This,profileName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhConfiguration_INTERFACE_DEFINED__ */


#ifndef __IMrhConfiguration53_INTERFACE_DEFINED__
#define __IMrhConfiguration53_INTERFACE_DEFINED__

/* interface IMrhConfiguration53 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMrhConfiguration53;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CF08D17-6311-4DE0-AA1A-C5A87644D2AD")
    IMrhConfiguration53 : public IMrhConfiguration
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetProfile53( 
            /* [in] */ BSTR profileName,
            /* [in] */ DWORD dwMethod) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMrhConfiguration53Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMrhConfiguration53 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMrhConfiguration53 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMrhConfiguration53 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMrhConfiguration53 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMrhConfiguration53 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMrhConfiguration53 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMrhConfiguration53 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetProfilesList )( 
            IMrhConfiguration53 * This,
            /* [out] */ VARIANT *profiles);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetProfile )( 
            IMrhConfiguration53 * This,
            /* [in] */ BSTR profileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentProfile )( 
            IMrhConfiguration53 * This,
            /* [out] */ BSTR *profileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetProfile53 )( 
            IMrhConfiguration53 * This,
            /* [in] */ BSTR profileName,
            /* [in] */ DWORD dwMethod);
        
        END_INTERFACE
    } IMrhConfiguration53Vtbl;

    interface IMrhConfiguration53
    {
        CONST_VTBL struct IMrhConfiguration53Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMrhConfiguration53_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMrhConfiguration53_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMrhConfiguration53_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMrhConfiguration53_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMrhConfiguration53_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMrhConfiguration53_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMrhConfiguration53_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMrhConfiguration53_GetProfilesList(This,profiles)	\
    ( (This)->lpVtbl -> GetProfilesList(This,profiles) ) 

#define IMrhConfiguration53_SetProfile(This,profileName)	\
    ( (This)->lpVtbl -> SetProfile(This,profileName) ) 

#define IMrhConfiguration53_GetCurrentProfile(This,profileName)	\
    ( (This)->lpVtbl -> GetCurrentProfile(This,profileName) ) 


#define IMrhConfiguration53_SetProfile53(This,profileName,dwMethod)	\
    ( (This)->lpVtbl -> SetProfile53(This,profileName,dwMethod) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMrhConfiguration53_INTERFACE_DEFINED__ */



#ifndef __MrhAPI_LIBRARY_DEFINED__
#define __MrhAPI_LIBRARY_DEFINED__

/* library MrhAPI */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MrhAPI;

EXTERN_C const CLSID CLSID_CMrhEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("EA4BFA5F-862C-4c73-8381-E24F949B7E53")
CMrhEngine;
#endif

EXTERN_C const CLSID CLSID_CMrhEngine53;

#ifdef __cplusplus

class DECLSPEC_UUID("0ED56CBB-DA9B-49EA-991D-AB955445DB49")
CMrhEngine53;
#endif

EXTERN_C const CLSID CLSID_CMrhCamera;

#ifdef __cplusplus

class DECLSPEC_UUID("7EC378B6-641F-4b71-BAAC-4617DC8BBE94")
CMrhCamera;
#endif

EXTERN_C const CLSID CLSID_CMrhCameraController;

#ifdef __cplusplus

class DECLSPEC_UUID("64E19419-9E1E-45bd-B916-4B9BDB03762D")
CMrhCameraController;
#endif

EXTERN_C const CLSID CLSID_CMrhImage;

#ifdef __cplusplus

class DECLSPEC_UUID("E17B47F6-9C00-4baf-93F3-CDD53FC6F7D7")
CMrhImage;
#endif

EXTERN_C const CLSID CLSID_CMrhMaskController;

#ifdef __cplusplus

class DECLSPEC_UUID("09CCACE1-5F24-4714-8F31-6807E6D744A0")
CMrhMaskController;
#endif

EXTERN_C const CLSID CLSID_CMrhMaskController53;

#ifdef __cplusplus

class DECLSPEC_UUID("51CADA3E-4FA0-474B-BA26-5723C0139D72")
CMrhMaskController53;
#endif

EXTERN_C const CLSID CLSID_CMrhMaskImage;

#ifdef __cplusplus

class DECLSPEC_UUID("8A7B825C-4D9C-496d-9965-E34EBD271E56")
CMrhMaskImage;
#endif

EXTERN_C const CLSID CLSID_CMrhRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("40860AF4-BD8A-4ac2-8F37-042C05CC1E8A")
CMrhRenderer;
#endif

EXTERN_C const CLSID CLSID_CMrhRenderer53;

#ifdef __cplusplus

class DECLSPEC_UUID("7F1665A8-226C-4A69-960D-FEF8462BFE92")
CMrhRenderer53;
#endif

EXTERN_C const CLSID CLSID_CMrhTarget;

#ifdef __cplusplus

class DECLSPEC_UUID("F25BB659-1D04-4460-9DB8-FE73A8D5C1B4")
CMrhTarget;
#endif

EXTERN_C const CLSID CLSID_CMrhMarker;

#ifdef __cplusplus

class DECLSPEC_UUID("16661F86-2277-4218-A9FF-A080F8E1388F")
CMrhMarker;
#endif

EXTERN_C const CLSID CLSID_CMrhConfiguration;

#ifdef __cplusplus

class DECLSPEC_UUID("9B753D5B-7A8C-42dd-B967-5C90C5AD0A59")
CMrhConfiguration;
#endif

EXTERN_C const CLSID CLSID_CMrhConfiguration53;

#ifdef __cplusplus

class DECLSPEC_UUID("9A0D956A-6E76-45EF-A96F-2D87D6892F3A")
CMrhConfiguration53;
#endif

EXTERN_C const CLSID CLSID_CMrhPolygon;

#ifdef __cplusplus

class DECLSPEC_UUID("3E5B1CC8-6573-4a88-850D-4B0E7319C395")
CMrhPolygon;
#endif

EXTERN_C const CLSID CLSID_CMrhPolygon53;

#ifdef __cplusplus

class DECLSPEC_UUID("50EC53A4-A8D7-41AC-9009-BFBB26F7E701")
CMrhPolygon53;
#endif

EXTERN_C const CLSID CLSID_CMrhDepth;

#ifdef __cplusplus

class DECLSPEC_UUID("5A915420-785E-4b1c-B1A7-028DEF1BAF46")
CMrhDepth;
#endif

EXTERN_C const CLSID CLSID_CMrhDepth53;

#ifdef __cplusplus

class DECLSPEC_UUID("1FC08DB5-E122-4F9F-9A34-620B890C25EB")
CMrhDepth53;
#endif

EXTERN_C const CLSID CLSID_CMrhWarning;

#ifdef __cplusplus

class DECLSPEC_UUID("D16D42B9-5E06-4CF2-8872-BD711E9F6D6E")
CMrhWarning;
#endif
#endif /* __MrhAPI_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


