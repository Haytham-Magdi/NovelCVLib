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
#include <NovelCVLib\Ncv\ConflictInfo2.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		template<> void AssertValue(const ConflictInfo2 & a_arg);
		template<> void SetToBadValue(ConflictInfo2 * a_pArg);

		template<> void AssertValue(const ConflictInfo2_Ex & a_arg);
		template<> void SetToBadValue(ConflictInfo2_Ex * a_pArg);
	};
}