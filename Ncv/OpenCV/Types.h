#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>


namespace Ncv
{
	typedef Ncpp::PtrRef<IplImage> IplImageRef;
	/*class IplImageRef : public Ncpp::PtrRef<IplImage>
	{
		IplImageRef() {}
		IplImageRef(IplImage * a_ptr) : Ncpp::PtrRef<IplImage>(a_ptr) {};
	};*/

	typedef Ncpp::PtrRef<CvMat> CvMatRef;
}