#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Channel.h>
//#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>

#include <NovelCVLib\Ncv\ImageOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>

#include <NovelCVLib\OpenCV\OpenCV_Util.h>
#include <NovelCVLib\OpenCV\ImageArrayHolder.h>
#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>

//#include <NovelCVLib\Ncv\PixelStandevInfoCmn.h>
//#include <NovelCVLib\Ncv\BidiffInfoCommon.h>
//#include <NovelCVLib\Ncv\ConflictInfo2.h>
//#include <NovelCVLib\Ncv\Bidiff.h>
//#include <NovelCVLib\Ncv\BidiffInfo.h>

//#include <NovelCVLib\Apps\BloodCells\ImgAngleDirMgr.h>
//#include <NovelCVLib\Apps\BloodCells\RotationMgrColl.h>


namespace Ncv
{

	template<class T_Inner>
	class CommonMultiListQueMember : public MultiListQueMember< CommonMultiListQueMember<T_Inner> >
	{
	public:

		T_Inner * pInner;
	};


}