#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Channel.h>
//#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Ncv\ImgSizeRotation.h>


namespace Ncv
{
	class ImgSizeRotationColl : public Ncpp::Object
	{
	public:

		ImgSizeRotationColl(Size_2D a_srcSiz, int a_nofRots);

		ImgSizeRotationRef GetRotAt(int a_nRotIdx)
		{
			return m_rotMgrArr[a_nRotIdx];
		}

		int GetNofRots()
		{
			return m_rotMgrArr.GetSize();
		}

		Size_2D GetSrcImgSiz()
		{
			return m_srcSiz;
		}

	protected:

		//void Prepare();

	protected:

		//F32ImageRef m_srcImg;
		Size_2D m_srcSiz;

		int m_nofRots;
		Ncpp::FixedVector< ImgSizeRotationRef > m_rotMgrArr;
	};

	typedef Ncpp::ObjRef< ImgSizeRotationColl > ImgSizeRotationCollRef;
}