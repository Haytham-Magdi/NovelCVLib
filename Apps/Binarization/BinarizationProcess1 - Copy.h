#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>

#include <NovelCVLib\Ncv\ImgRotationMgr.h>
#include <NovelCVLib\Apps\Binarization\ImgAngleDirMgr.h>


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