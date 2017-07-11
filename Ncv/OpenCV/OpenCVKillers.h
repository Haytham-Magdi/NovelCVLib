#pragma once

#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>

namespace Ncpp
{
	
	inline void KillObj(IplImage * a_ptr)
	{
		cvReleaseImage(&a_ptr);
	}

	inline void KillObj(CvMat * a_ptr)
	{
		cvReleaseMat(&a_ptr);
	}


}