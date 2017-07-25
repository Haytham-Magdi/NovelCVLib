#pragma once

//#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\OpenCVKillers.h>

namespace Ncpp
{
	
	//inline void KillObj(IplImage * a_ptr)
	void KillObj(IplImage * a_ptr)
	{
		cvReleaseImage(&a_ptr);
	}

	void KillObj(CvMat * a_ptr)
	{
		cvReleaseMat(&a_ptr);
	}

}