#pragma once

#include <NovelCVLib\Common\CommonKillers.h>

#include <NovelCVLib\OpenCV\CvIncludes.h>

namespace Ncpp
{

	template<> inline void KillObj(cv::Mat * a_ptr);

}