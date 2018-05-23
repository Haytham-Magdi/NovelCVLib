#pragma once

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
	
		template<> void Assign(F32ColorVal * a_pDest, const F32ColorVal & a_src);
		
		template<> void AssertValue(const F32ColorVal & a_arg);

		template<> float CalcMagSqr(const F32ColorVal & a_arg);

		template<> void Add(const F32ColorVal & a_inp1, const F32ColorVal & a_inp2, F32ColorVal * a_pOut);

		template<> void Subtract(const F32ColorVal & a_inp1, const F32ColorVal & a_inp2, F32ColorVal * a_pOut);

		template<> void DivideByNum(const F32ColorVal & a_inp, const float a_num, F32ColorVal * a_pOut);

		template<> void MultiplyByNum(const F32ColorVal & a_inp, const float a_num, F32ColorVal * a_pOut);

		template<> void SetToZero(F32ColorVal * a_pArg);

		template<> bool IsUndefined(const F32ColorVal & a_arg);

		template<> void SetToUndefined(const F32ColorVal * a_pArg);





		//template<> void Copy_ByPtr<F32ColorVal>(F32ColorVal * a_pDest, F32ColorVal * a_pSrc);

		//template<> float CalcMagSqr_ByPtr(F32ColorVal * a_pArg);

		//template<> void AssertValue_ByPtr(F32ColorVal * a_pArg);

		//template<> void Add_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut);

		//template<> void Subtract_ByPtr(F32ColorVal * a_pInp1, F32ColorVal * a_pInp2, F32ColorVal * a_pOut);

		//template<> void DivideByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut);
		//
		//template<> void MultiplyByNum_ByPtr(F32ColorVal * a_pInp, float a_num, F32ColorVal * a_pOut);

		//template<> void SetToZero_ByPtr(F32ColorVal * a_pArg);
		//
		//template<> bool IsUndefined_ByPtr(F32ColorVal * a_pArg);
		//
		//template<> void SetToUndefined_ByPtr(F32ColorVal * a_pArg);
	}
}