#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\PixelTypes.h>



namespace Ncv
{
	PixelTypeInfo g_Uint8PTI = 
	{
		IPL_DEPTH_8U
	};

	PixelTypeInfo g_Int16PTI = 
	{
		IPL_DEPTH_16S
	};

	PixelTypeInfo g_Int32PTI = 
	{
		IPL_DEPTH_32S
	};

	PixelTypeInfo g_FloatPTI = 
	{
		IPL_DEPTH_32F
	};

}