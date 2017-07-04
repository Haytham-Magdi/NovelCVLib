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
#include <Lib\Novel\Ncv\TempImageAccessor.h>
#include <Lib\Novel\Ncv\PixelStandevInfo.h>
#include <Lib\Novel\Ncv\ConflictInfo.h>

#include <Lib\Novel\Ncv\Binarization\ImgAngleDirMgr.h>
//#include <Lib\Novel\Ncv\Binarization\RotationMgrColl.h>
#include <Lib\Novel\Ncv\ConflictInfo.h>


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