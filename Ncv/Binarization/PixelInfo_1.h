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
#include <Novel-Lib\Ncv\TempImageAccessor.h>
#include <Novel-Lib\Ncv\PixelStandevInfo.h>
#include <Novel-Lib\Ncv\ConflictInfo.h>

#include <Novel-Lib\Ncv\Binarization\ImgAngleDirMgr.h>
//#include <Novel-Lib\Ncv\Binarization\RotationMgrColl.h>
#include <Novel-Lib\Ncv\ConflictInfo.h>


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