#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal.h>


namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{

#define T_Elm float
#define N_Dims 2

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims

#define T_Elm float
#define N_Dims 3

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims


#define T_Elm float
#define N_Dims 4

#include <NovelCVLib\ElementOperations2\ElementOperations2_VectorVal_CoreFile.cpp>

#undef T_Elm
#undef N_Dims


	};
}