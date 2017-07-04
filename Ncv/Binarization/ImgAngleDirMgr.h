#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>
#include <Lib\Novel\Ncv\ImageAccessor.h>

//#include <Lib\Novel\Ncv\ImageLineItrProvider.h>
//#include <Lib\Novel\Ncv\ImageItrMgr.h>

#include <Lib\Novel\Ncv\ImgSizeRotation.h>
#include <Lib\Novel\Ncv\Binarization\ImgAngleDirMgr.h>
#include <Lib\Novel\Ncv\Binarization\AngleDirMgrColl_Context.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		//class ImgAngleDirMgr;
		//class ImgAngleDirMgr::Context;
		//typedef Ncpp::ObjRef< ImgAngleDirMgr::Context > ImgAngleDirMgr_Context_Ref;

		class ImgAngleDirMgr : FRM_Object
		{
		public:

			class Context : FRM_Object
			{
			public:

				Context(int a_nIndex, ImgSizeRotationRef a_imgRot, F32ImageAccessor3C_Ref a_org_Img, F32ImageAccessor1C_Ref a_magSqr_Img, char a_hv);

				std::string & GetIdStr() {
					return m_idStr;
				}

				std::string MakeStrWithId(char * a_str) {
						return (GetIdStr() + std::string(a_str));
				}

				//protected:

				int m_nIndex;
				std::string m_idStr;

				F32ImageAccessor3C_Ref m_org_Img;
				F32ImageAccessor1C_Ref m_magSqr_Img;

				char m_hv;
				ImgSizeRotationRef m_imgRot;

				F32ImageAccessor1C_Ref m_avgStandev_H_Img;

				S32ImageAccessor1C_Ref m_rotToOrgMap_Img;
				S32ImageAccessor1C_Ref m_orgToRotMap_Img;
				float m_angle;
				TempImageAccessor_REF(ConflictInfo) m_conflict_Img;

				//F32ImageAccessor1C_Ref m_standev_InrWide_Img;

				F32ImageAccessor1C_Ref m_wideConflictDiff_Img;
				F32VectorValImageAcc_4C_Ref m_avgPStandev_InrWide_Img;
			};

		public:

			ImgAngleDirMgr(Ncpp::ObjRef< ImgAngleDirMgr::Context > a_context, Ncpp::ObjRef< ImgAngleDirMgr::Context > a_normalContext,
				AngleDirMgrColl_Context_Ref a_parentContext);

			Ncpp::ObjRef< ImgAngleDirMgr::Context > GetContext()
			{
				return m_context;
			}

			Ncpp::ObjRef< ImgAngleDirMgr::Context > GetNormalContext()
			{
				return m_normalContext;
			}

			void Proceed_1();
			void Proceed_2();
			void Proceed_3();
			void Proceed_4();
			void Proceed_5_1();
			void Proceed_5_2();
			void Proceed_5_3();
			void Proceed_6();

		protected:

			//void AffectCommonAvgStandev_0();
			void AffectCommonAvgStandev();
			void AffectCommonConflict();
			void AffectCommonWideConflictDiff();
			void AffectCommonAvgPStandev_InrWide();


			void DisplayConflictImg();

		protected:

			//ImgAngleDirMgr_Context_Ref m_context;
			//ImgAngleDirMgr_Context_Ref m_normalContext;

			Ncpp::ObjRef< ImgAngleDirMgr::Context > m_context;
			Ncpp::ObjRef< ImgAngleDirMgr::Context > m_normalContext;
			AngleDirMgrColl_Context_Ref m_parentContext;
		};

		typedef Ncpp::ObjRef< ImgAngleDirMgr > ImgAngleDirMgrRef;
		typedef Ncpp::ObjRef< ImgAngleDirMgr::Context > ImgAngleDirMgr_Context_Ref;

	};



}