#pragma once

#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>



namespace Ncv
{
	typedef struct _PixelTypeInfo
	{
		int IplDepthID;		
	}PixelTypeInfo;


	extern PixelTypeInfo g_Uint8PTI;
	extern PixelTypeInfo g_Int16PTI;
	extern PixelTypeInfo g_Int32PTI;
	extern PixelTypeInfo g_FloatPTI;

	template<class T>
		inline PixelTypeInfo * GetPixTInfo(T a_dmy)
	{
		Ncpp_ASSERT(false);
		return NULL;
	}

	inline PixelTypeInfo * GetPixTInfo(Ncpp::Int16 a_dmy)		
	{
		return &g_Int16PTI;
	}

	inline PixelTypeInfo * GetPixTInfo(Ncpp::Uint8 a_dmy)		
	{
		return &g_Uint8PTI;
	}

	inline PixelTypeInfo * GetPixTInfo(Ncpp::Int32 a_dmy)		
	{
		return &g_Int32PTI;
	}

	inline PixelTypeInfo * GetPixTInfo(Ncpp::Float a_dmy)		
	{
		return &g_FloatPTI;
	}

#define NCV_DEPTH_ID(T)		(GetPixTInfo((T)0))->IplDepthID
}