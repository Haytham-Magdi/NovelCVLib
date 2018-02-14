#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>
#include <NovelCVLib\Ncv\TempImageAccessor.h>
#include <NovelCVLib\Ncv\PixelStandevInfo.h>
#include <NovelCVLib\Ncv\ConflictInfo.h>

#include <NovelCVLib\Apps\Binarization2\ImgAngleDirMgr.h>
//#include <NovelCVLib\Apps\Binarization2\RotationMgrColl.h>
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