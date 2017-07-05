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

#include <Novel-Lib\Ncv\ImgRotationMgr.h>
#include <Novel-Lib\Ncv\Binarization\ImgAngleDirMgr.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		class BinarizationProcess1 : FRM_Object
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