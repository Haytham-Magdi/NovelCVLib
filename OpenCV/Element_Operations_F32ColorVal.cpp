#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Element_Operations\Element_Operations.h>
#include <NovelCVLib\Element_Operations\Element_Operations_Float.h>
#include <NovelCVLib\OpenCV\Element_Operations_F32ColorVal.h>
#include <NovelCVLib\Element_Operations\Element_Operations_Float.h>


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

		bool IsUndefined_ByPtr(F32ColorVal * a_pArg)
		{
			//return a_pArg->val0 < -88888888.0f;
			return IsUndefined_ByPtr<float>(&a_pArg->val0);
		}

		void SetToUndefined_ByPtr(F32ColorVal * a_pArg)
		{
			SetToUndefined_ByPtr<float>(&a_pArg->val0);
			//SetToUndefined_ByPtr(&a_pArg->val1);
			//SetToUndefined_ByPtr(&a_pArg->val2);
		}

	};
}