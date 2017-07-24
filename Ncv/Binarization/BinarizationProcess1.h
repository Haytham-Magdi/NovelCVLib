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

//#include <NovelCVLib\Ncv\ImgRotationMgr.h>
#include <NovelCVLib\Ncv\Binarization\ImgAngleDirMgr.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		class BinarizationProcess1 : public Ncpp::Object
		{
		public:

			BinarizationProcess1(F32ImageRef a_srcImg);

			F32ImageRef GetSrcImg()
			{
				return m_srcImg;
			}

		protected:

			void Prepare();

		protected:

			F32ImageRef m_srcImg;
		};
	
		typedef Ncpp::ObjRef< BinarizationProcess1 > BinarizationProcess1Ref;
	};



}