#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2_LongLong.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void SetToZero(long long * a_pArg)
		{
			*a_pArg = 0;
		}

		void AssertValue(const long long & a_arg)
		{
			Ncpp_ASSERT(a_arg > -9000000000000000000);
		}

		bool IsUndefined(const long long & a_arg)
		{
			return a_arg == -9200000000000000000;
		}

		void SetToUndefined(long long * a_pArg)
		{
			*a_pArg = -9200000000000000000;
		}
		

		void SetToBadValue(long long * a_pArg)
		{
			*a_pArg = -9000000000000000000;
		}

	};
}