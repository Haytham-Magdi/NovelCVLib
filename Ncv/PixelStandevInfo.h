#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>



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