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

#include <Lib\Novel\Ncv\ImgRotationMgr.h>
#include <Lib\Novel\Ncv\Binarization\ImgAngleDirMgr.h>


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