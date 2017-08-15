#pragma once

//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\OpenCVKillers.h>

namespace Ncpp
{
	
	void KillObj(IplImage * a_ptr)
	{
		cvReleaseImage(&a_ptr);
	}

	void KillObj(CvMat * a_ptr)
	{
		cvReleaseMat(&a_ptr);
	}

}