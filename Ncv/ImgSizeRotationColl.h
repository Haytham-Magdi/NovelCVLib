#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>

//#include <Lib\Novel\Ncv\ImageLineItrProvider.h>
//#include <Lib\Novel\Ncv\ImageItrMgr.h>

#include <Lib\Novel\Ncv\ImgSizeRotation.h>


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