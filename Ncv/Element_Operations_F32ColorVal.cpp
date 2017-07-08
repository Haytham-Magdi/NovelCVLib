#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Image.h>

#include <NovelCVLib\Ncv\Element_Operations.h>
#include <NovelCVLib\Ncv\Element_Operations_F32ColorVal.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace Element_Operations
	{

		void Copy_ByPtr(F32ColorVal * a_pDest, F32ColorVal * a_pSrc)
		{
			memcpy(a_pDest, a_pSrc, sizeof(F32ColorVal));
		}

		float CalcMagSqr_ByPtr(F32ColorVal * a_pArg)
		{
			return a_pArg->CalcMagSqr();
		}

		void AssertValue_ByPtr(F32ColorVal * a_pArg)
		{
			Ncpp_ASSERT(a_pArg->val0 > -3000000.0f && a_pArg->val0 < 3000000.0f);
			Ncpp_ASSERT(a_pArg->val1 > -3000000.0f && a_pArg->val1 < 3000000.0f);
			Ncpp_ASSERT(a_pArg->val2 > -3000000.0f && a_pArg->val2 < 3000000.0f);
		}

		void Add_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut)
		{
			a_pOut->val0 = a_pInp1->val0 + a_pInp2->val0;
			a_pOut->val1 = a_pInp1->val1 + a_pInp2->val1;
			a_pOut->val2 = a_pInp1->val2 + a_pInp2->val2;
		}

		void Subtract_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut)
		{
			a_pOut->val0 = a_pInp1->val0 - a_pInp2->val0;
			a_pOut->val1 = a_pInp1->val1 - a_pInp2->val1;
			a_pOut->val2 = a_pInp1->val2 - a_pInp2->val2;
		}

		void DivideByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut)
		{
			a_pOut->val0 = a_pInp->val0 / a_num;
			a_pOut->val1 = a_pInp->val1 / a_num;
			a_pOut->val2 = a_pInp->val2 / a_num;
		}

		void MultiplyByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut)
		{
			a_pOut->val0 = a_pInp->val0 * a_num;
			a_pOut->val1 = a_pInp->val1 * a_num;
			a_pOut->val2 = a_pInp->val2 * a_num;
		}

		void SetToZero_ByPtr(F32ColorVal * a_pArg)
		{
			a_pArg->val0 = 0;
			a_pArg->val1 = 0;
			a_pArg->val2 = 0;
		}

	};
}