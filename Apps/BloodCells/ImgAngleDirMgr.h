#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>

#include <NovelCVLib\Ncv\ImageOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>

#include <NovelCVLib\OpenCV\OpenCV_Util.h>
#include <NovelCVLib\OpenCV\ImageArrayHolder.h>
#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>


#include <NovelCVLib\Ncv\ImgSizeRotation.h>
#include <NovelCVLib\Apps\BloodCells\ImgAngleDirMgr.h>
#include <NovelCVLib\Apps\BloodCells\AngleDirMgrColl_Context.h>


namespace Ncv
{
	namespace Ns_BloodCells
	{

		//class ImgAngleDirMgr;
		//class ImgAngleDirMgr::Context;
		//typedef Ncpp::ObjRef< ImgAngleDirMgr::Context > ImgAngleDirMgr_Context_Ref;

		class ImgAngleDirMgr : public Ncpp::Object
		{
		public:

			class Context : public Ncpp::Object
			{
			public:

				Context(int a_nIndex, ImgSizeRotationRef a_imgRot, F32ImageArrayHolder3C_Ref a_org_Img, F32ImageArrayHolder1C_Ref a_magSqr_Img, char a_hv);

				std::string & GetIdStr() {
					return m_idStr;
				}

				std::string MakeStrWithId(char * a_str) {
						return (GetIdStr() + std::string(a_str));
				}

				//protected:

				int m_nIndex;
				std::string m_idStr;

				F32ImageArrayHolder3C_Ref m_org_Img;
				F32ImageArrayHolder1C_Ref m_magSqr_Img;

				char m_hv;
				ImgSizeRotationRef m_imgRot;

				F32ImageArrayHolder1C_Ref m_standev1_X_Img;
				F32ImageArrayHolder1C_Ref m_standev2_X_Img;
				F32ImageArrayHolder1C_Ref m_normStandev1_X_Img;
				F32ImageArrayHolder1C_Ref m_normStandev2_X_Img;
				F32ImageArrayHolder1C_Ref m_normAvgStandev_X_Img;
				F32ImageArrayHolder1C_Ref m_normAvgStandev_X_T_Img;

				F32ImageArrayHolder1C_Ref m_normAvgStandev_X_ToNormRatio_Img;

				//S32ImageArrayHolder1C_Ref m_rotToOrgMap_Img;
				//S32ImageArrayHolder1C_Ref m_orgToRotMap_Img;

				ArrayHolder_2D_Ref<int> m_rotToOrgMap_Img;
				ArrayHolder_2D_Ref<int> m_orgToRotMap_Img;

				float m_angleByRad;
				ArrayHolder_2D_Ref<ConflictInfo2> m_conflict_Img;

				F32ImageArrayHolder3C_Ref m_diff1_1_Img;
				F32ImageArrayHolder3C_Ref m_diff_2_Img;
				F32ImageArrayHolder3C_Ref m_diff1_2_Img;

				ArrayHolder_2D_Ref<BidiffInfo> m_bidiffInfo_Img;

				//F32ImageArrayHolder1C_Ref m_standev_InrWide_Img;

				F32ImageArrayHolder1C_Ref m_wideConflictDiff_Img;
				F32VectorValImageArrayHolder_4C_Ref m_avgPStandev_InrWide_Img;
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

			void Proceed_1b_1();
			void PrepareNormAvgStandev_X();
			void PrepareStandev_X();
			void Proceed_1b_2();
			void Proceed_2_1();
			void Proceed_2_2();
			void Proceed_2b_1();
			void Proceed_2b_2();
			void Proceed_2c_1();
			void Proceed_3_1();
			void Proceed_3_2();
			void Proceed_4_1();
			void Proceed_4_2();

		protected:

			void AffectNormWithNormAvgStandev();
			//void AffectCommonAvgStandev_0();
			void AffectCommonNormAvgStandev();
			void AffectCommonNormAvgStandev2();
			void ConfirmConflict();
			void AffectCommonConflict();
			void AffectCommonBidiffInfo();
			void AffectCommonWideConflictDiff();
			void AffectCommonAvgPStandev_InrWide();

			void DisplayConflictImg();
			void DisplayNormAvgStandevRatioToNormImg();
			void DisplayStandevImg();
			void DisplayDiffImages();
			
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