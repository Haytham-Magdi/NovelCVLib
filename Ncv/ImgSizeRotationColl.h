#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>

#include <NovelCVLib\Ncv\ImgSizeRotation.h>


namespace Ncv
{
	class ImgSizeRotationColl : public Ncpp::Object
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