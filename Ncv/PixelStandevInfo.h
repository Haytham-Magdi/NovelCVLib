#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>



namespace Ncv
{

	class PixelStandevInfo //: public Ncpp::Object
	{
	public:
		int Dir;
		float Val;
		float NormVal;
	};

	//typedef Ncpp::ObjRef< PixelStandevInfo > PixelStandevInfoRef;
}