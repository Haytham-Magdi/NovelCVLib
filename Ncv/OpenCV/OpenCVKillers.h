#pragma once

#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>

namespace Ncpp
{

	template<> inline void KillObj<>(IplImage * a_ptr);
	template<> inline void KillObj(CvMat * a_ptr);

}