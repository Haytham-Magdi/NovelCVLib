#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>

//#include <Novel-Lib\Ncv\ImageLineItrProvider.h>
//#include <Novel-Lib\Ncv\ImageItrMgr.h>

#include <Novel-Lib\Ncv\ImgSizeRotation.h>


namespace Ncv
{
	class ImgSizeRotationColl : FRM_Object
	{
	public:

		ImgSizeRotationColl(CvSize a_srcSiz, int a_nofRots);

		ImgSizeRotationRef GetRotAt(int a_nRotIdx)
		{
			return m_rotMgrArr[a_nRotIdx];
		}

		int GetNofRots()
		{
			return m_rotMgrArr.GetSize();
		}

		CvSize GetSrcImgSiz()
		{
			return m_srcSiz;
		}

	protected:

		//void Prepare();

	protected:

		//F32ImageRef m_srcImg;
		CvSize m_srcSiz;

		int m_nofRots;
		Ncpp::FixedVector< ImgSizeRotationRef > m_rotMgrArr;
	};

	typedef Ncpp::ObjRef< ImgSizeRotationColl > ImgSizeRotationCollRef;
}