#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Ncv\BidiffMagCommon.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void AssertValue(const BidiffMagCommon & a_arg)
		{
			////AssertValue(a_arg.Dir);
			//AssertValue(a_arg.Dir);

			//Ncpp_ASSERT(a_arg.Dir >= 0 && a_arg.Dir < 500);
			Ncpp_ASSERT(a_arg.MinValDir >= 0 && a_arg.MinValDir < 500);

			//AssertValue(a_arg.Val);
			AssertValue(a_arg.MinVal);
		}

		bool IsUndefined(const BidiffMagCommon & a_arg)
		{
			//return IsUndefined(a_arg.Val);
			return IsUndefined(a_arg.MinVal);
		}

		void SetToUndefined(BidiffMagCommon * a_pArg)
		{
			//SetToUndefined(&a_pArg->Val);
			SetToUndefined(&a_pArg->MinVal);
		}

		void SetToBadValue(BidiffMagCommon * a_pArg)
		{
			//SetToBadValue(&a_pArg->Val);
			SetToBadValue(&a_pArg->MinVal);
		}
	};
}