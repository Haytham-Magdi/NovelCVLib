#pragma once


//#include <NovelCVLib\Common\commonLib.h>

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		template<> void SetToZero(int * a_pArg);
		template<> void AssertValue(const int & a_pArg);
		template<> bool IsUndefined(const int & a_arg);
		template<> void SetToUndefined(int * a_pArg);
		template<> void SetToBadValue(int * a_pArg);
	};
}