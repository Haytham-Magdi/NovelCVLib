#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Element_Operations\Element_Operations.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace Element_Operations
	{

		template<> void Copy_ByPtr<F32ColorVal>(F32ColorVal * a_pDest, F32ColorVal * a_pSrc);

		template<> float CalcMagSqr_ByPtr(F32ColorVal * a_pArg);

		template<> void AssertValue_ByPtr(F32ColorVal * a_pArg);

		template<> void Add_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut);

		template<> void Subtract_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut);

		template<> void DivideByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut);
		
		template<> void MultiplyByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut);

		template<> void SetToZero_ByPtr(F32ColorVal * a_pArg);
		
		template<> bool IsUndefined_ByPtr(F32ColorVal * a_pArg);
		
		template<> void SetToUndefined_ByPtr(F32ColorVal * a_pArg);

	};
}