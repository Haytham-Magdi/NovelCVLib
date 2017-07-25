#pragma once

#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>

namespace Ncpp
{

	//inline void KillObj(IplImage * a_ptr)
	//{
	//	cvReleaseImage(&a_ptr);
	//}

	template<> void KillObj<IplImage>(IplImage * a_ptr);

	//inline void KillObj(_IplImage * a_ptr)
	//{
	//	cvReleaseImage(&a_ptr);
	//}

	//inline void KillObj(CvMat * a_ptr)
	template<> void KillObj(CvMat * a_ptr);

}