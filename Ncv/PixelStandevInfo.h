#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>



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