#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>


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