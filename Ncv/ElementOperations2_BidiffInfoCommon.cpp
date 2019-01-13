#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Ncv\BidiffInfoCommon.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void AssertValue(const BidiffInfoCommon & a_arg)
		{
			////AssertValue(a_arg.Dir);
			//AssertValue(a_arg.Dir);

			//Ncpp_ASSERT(a_arg.Dir >= 0 && a_arg.Dir < 500);
			Ncpp_ASSERT(a_arg.LeastValDir >= 0 && a_arg.LeastValDir < 500);

			//AssertValue(a_arg.Val);
			AssertValue(a_arg.LeastValDirMaxVal);
		}

		bool IsUndefined(const BidiffInfoCommon & a_arg)
		{
			//return IsUndefined(a_arg.Val);
			return IsUndefined(a_arg.LeastValDirMaxVal);
		}

		void SetToUndefined(BidiffInfoCommon * a_pArg)
		{
			//SetToUndefined(&a_pArg->Val);
			SetToUndefined(&a_pArg->LeastValDirMaxVal);
		}

		void SetToBadValue(BidiffInfoCommon * a_pArg)
		{
			//SetToBadValue(&a_pArg->Val);
			SetToBadValue(&a_pArg->LeastValDirMaxVal);
		}
	};
}