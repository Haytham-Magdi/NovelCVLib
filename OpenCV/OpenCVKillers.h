#pragma once

#include <NovelCVLib\Common\CommonKillers.h>

#include <NovelCVLib\OpenCV\CvIncludes.h>

namespace Ncpp
{

	template<> inline void KillObj<>(IplImage * a_ptr);
	template<> inline void KillObj(CvMat * a_ptr);

}