#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		template<> void SetToZero(float * a_pArg);
		template<> bool IsUndefined(const float & a_arg);
		template<> void SetToUndefined(float * a_pArg);
	};
}