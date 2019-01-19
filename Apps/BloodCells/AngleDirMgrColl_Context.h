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

#include <NovelCVLib\Ncv\ImageOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>

#include <NovelCVLib\OpenCV\OpenCV_Util.h>
#include <NovelCVLib\OpenCV\ImageArrayHolder.h>
#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>

#include <NovelCVLib\Ncv\PixelStandevInfo.h>
#include <NovelCVLib\Ncv\BidiffInfoCommon.h>
#include <NovelCVLib\Ncv\ConflictInfo2.h>
#include <NovelCVLib\Ncv\Bidiff.h>
#include <NovelCVLib\Ncv\BidiffInfo.h>


#include <NovelCVLib\Apps\BloodCells\ImgAngleDirMgr.h>
//#include <NovelCVLib\Apps\BloodCells\RotationMgrColl.h>


namespace Ncv
{
	namespace Ns_BloodCells
	{

		class AngleDirMgrColl_Context : public Ncpp::Object
		{
		public:

			int GetDiffPosDist() { return 1; }

			ArrayHolder_2D_Ref<PixelStandevInfo> m_standevInfoImg;
			ArrayHolder_2D_Ref<BidiffInfoCommon> m_bidiffInfoCommonImg;
			ArrayHolder_2D_Ref<ConflictInfo2_Ex> m_conflictInfoImg;
			F32ImageArrayHolder1C_Ref m_wideConflictDiff_Img;
			F32VectorValImageArrayHolder_4C_Ref m_avgPStandev_InrWide_Img;

			F32ImageArrayHolder3C_Ref m_org_Img;
		};

		typedef Ncpp::ObjRef< AngleDirMgrColl_Context > AngleDirMgrColl_Context_Ref;
	}

}