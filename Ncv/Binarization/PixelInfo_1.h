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
#include <NovelCVLib\Ncv\TempImageAccessor.h>
#include <NovelCVLib\Ncv\PixelStandevInfo.h>
#include <NovelCVLib\Ncv\ConflictInfo.h>

#include <NovelCVLib\Ncv\Binarization\ImgAngleDirMgr.h>
//#include <NovelCVLib\Ncv\Binarization\RotationMgrColl.h>
#include <NovelCVLib\Ncv\ConflictInfo.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		class PixelInfo_1 : public MultiListQueMember< PixelInfo_1 >
		{
		public:

			int X;
			int Y;

			ConflictInfo_Ex * pConflictInfo;

			float Val_WideOutStandev;

			bool IsPushed;

		};

		//typedef Ncpp::ObjRef< PixelInfo_1 > PixelInfo_1_Ref;
	};

}