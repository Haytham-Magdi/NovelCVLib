#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2_Float.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void SetToZero(float * a_pArg)
		{
			*a_pArg = 0.0f;
		}

		void AssertValue(const float & a_arg)
		{
			//Hcpl_ASSERT(a_arg > -30000000.0f && arg < 30000000.0f);
			Ncpp_ASSERT(a_arg > -50000000.0f);
		}

		bool IsUndefined(const float & a_arg)
		{
			return a_arg < -88888888.0f;
		}

		void SetToUndefined(float * a_pArg)
		{
			*a_pArg = -99999999.0f;
		}

		void SetToBadValue(float * a_pArg)
		{
			*a_pArg = -77777777.0f;
		}

	};
}