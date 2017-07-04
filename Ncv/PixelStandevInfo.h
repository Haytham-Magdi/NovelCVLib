#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>



namespace Ncv
{

	class PixelStandevInfo //: FRM_Object
	{
	public:
		int Dir;
		float Val;
		float NormVal;
	};

	//typedef Ncpp::ObjRef< PixelStandevInfo > PixelStandevInfoRef;
}