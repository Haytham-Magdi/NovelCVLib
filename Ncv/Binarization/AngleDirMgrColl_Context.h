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