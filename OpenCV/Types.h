#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Common\PtrRef.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>


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