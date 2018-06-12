#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2_Int.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void SetToZero(int * a_pArg)
		{
			*a_pArg = 0;
		}

		void AssertValue(const int & a_arg)
		{
			Ncpp_ASSERT(a_arg > -2000000000);
		}

		bool IsUndefined(const int & a_arg)
		{
			return a_arg == -2100000000;
		}

		void SetToUndefined(int * a_pArg)
		{
			*a_pArg = -2100000000;
		}

		void SetToBadValue(int * a_pArg)
		{
			*a_pArg = -2000000000;
		}

	};
}