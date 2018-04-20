#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>

namespace Ncv
{
	namespace OpenCV_Util
	{
		using namespace Ncpp;

		Size_2D size_2D(const CvSize & src);
		CvSize cvSize(const Size_2D & src);

	}
}