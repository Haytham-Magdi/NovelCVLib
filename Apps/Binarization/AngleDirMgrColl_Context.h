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

#include <NovelCVLib\Apps\Binarization\ImgAngleDirMgr.h>
//#include <NovelCVLib\Apps\Binarization\RotationMgrColl.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		class AngleDirMgrColl_Context : public Ncpp::Object
		{
		public:

			TempImageAccessor_REF(PixelStandevInfo) m_standevInfoImg;
			TempImageAccessor_REF(ConflictInfo_Ex) m_conflictInfoImg;
			F32ImageAccessor1C_Ref m_wideConflictDiff_Img;
			F32VectorValImageAcc_4C_Ref m_avgPStandev_InrWide_Img;

			F32ImageAccessor3C_Ref m_org_Img;

			//TempImageAccessor_REF(int) m_standevInfoImg;
			//PixelStandevInfo psi;

		};

		typedef Ncpp::ObjRef< AngleDirMgrColl_Context > AngleDirMgrColl_Context_Ref;
	};

}