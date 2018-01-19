#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Ncv\VectorVal.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{

#define T_Elm float
#define N_Dims 2

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.h>

#undef T_Elm
#undef N_Dims


#define T_Elm float
#define N_Dims 3

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.h>

#undef T_Elm
#undef N_Dims


#define T_Elm float
#define N_Dims 4

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.h>

#undef T_Elm
#undef N_Dims



	};
}