#pragma once

//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\OpenCVKillers.h>

namespace Ncpp
{
	
	void KillObj(cv::Mat * a_ptr)
	{
		////cvReleaseMat(&a_ptr);
		//a_ptr->deallocate();
	}

}