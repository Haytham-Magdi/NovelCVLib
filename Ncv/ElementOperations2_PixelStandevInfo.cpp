#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\Ncv\ElementOperations2_ConflictInfo2.h>
#include <NovelCVLib\Ncv\PixelStandevInfo.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void AssertValue(const PixelStandevInfo & a_arg)
		{
			AssertValue(a_arg.Dir);
		}
	};
}