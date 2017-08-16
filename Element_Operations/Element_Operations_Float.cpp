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


namespace Ncv
{
	using namespace Ncpp;

	namespace Element_Operations
	{

		void Copy_ByPtr(float * a_pDest, float * a_pSrc)
		{
			*a_pDest = *a_pSrc;
		}

		//float CalcMagSqr_ByPtr(float * a_pArg)
		//{
		//	return Sqr(*a_pArg);
		//}

		//void AssertValue_ByPtr(float * a_pArg)
		//{
		//	Ncpp_ASSERT(a_pArg->val0 > -3000000.0f && a_pArg->val0 < 3000000.0f);
		//	Ncpp_ASSERT(a_pArg->val1 > -3000000.0f && a_pArg->val1 < 3000000.0f);
		//	Ncpp_ASSERT(a_pArg->val2 > -3000000.0f && a_pArg->val2 < 3000000.0f);
		//}

		//void Add_ByPtr(float * a_pInp1, float * a_pInp2, float * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp1->val0 + a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 + a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 + a_pInp2->val2;
		//}

		//void Subtract_ByPtr(float * a_pInp1, float * a_pInp2, float * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp1->val0 - a_pInp2->val0;
		//	a_pOut->val1 = a_pInp1->val1 - a_pInp2->val1;
		//	a_pOut->val2 = a_pInp1->val2 - a_pInp2->val2;
		//}

		//void DivideByNum_ByPtr(float * a_pInp, float a_num, float * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 / a_num;
		//	a_pOut->val1 = a_pInp->val1 / a_num;
		//	a_pOut->val2 = a_pInp->val2 / a_num;
		//}

		//void MultiplyByNum_ByPtr(float * a_pInp, float a_num, float * a_pOut)
		//{
		//	a_pOut->val0 = a_pInp->val0 * a_num;
		//	a_pOut->val1 = a_pInp->val1 * a_num;
		//	a_pOut->val2 = a_pInp->val2 * a_num;
		//}

		void SetToZero_ByPtr(float * a_pArg)
		{
			*a_pArg = 0.0f;
		}

		bool IsUndefined_ByPtr(float * a_pArg)
		{
			return *a_pArg < -88888888.0f;
		}

		void SetToUndefined_ByPtr(float * a_pArg)
		{
			*a_pArg = -99999999.0f;
		}

	};
}