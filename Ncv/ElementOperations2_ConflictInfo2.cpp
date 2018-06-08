#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\Ncv\ElementOperations2_ConflictInfo2.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{
		void AssertValue(const ConflictInfo2 & a_arg)
		{
			//throw "Not Implemented";
			//AssertValue(a_arg.Dir);
		
			Ncpp_ASSERT(a_arg.Offset_Side_1 > -100000);
		}

		void SetToBadValue(ConflictInfo2 * a_pArg)
		{
			a_pArg->Offset_Side_1 = -55555555;
		}



		void AssertValue(const ConflictInfo2_Ex & a_arg)
		{
			//AssertValue(a_arg.Dir);
			//Ncpp_ASSERT(a_arg.Dir >= 0);
		
			//Ncpp_ASSERT(a_arg.Dir > -10000);
			Ncpp_ASSERT(a_arg.Dir >= 0 && a_arg.Dir < 500);
		}

		void SetToBadValue(ConflictInfo2_Ex * a_pArg)
		{
			a_pArg->Dir = -55555555;
		}

	};
}