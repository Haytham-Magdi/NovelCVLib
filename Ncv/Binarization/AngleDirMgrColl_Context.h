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


namespace Ncv
{
	namespace Ns_Binarization
	{

		class AngleDirMgrColl_Context : FRM_Object
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