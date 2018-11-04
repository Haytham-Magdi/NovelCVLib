#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\VectorVal.h>

#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>

#include <NovelCVLib\Ncv\ImageOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>

#include <NovelCVLib\OpenCV\OpenCV_Util.h>
#include <NovelCVLib\OpenCV\ImageArrayHolder.h>
#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>



#include <NovelCVLib\Apps\BloodCells\AngleDirMgrColl.h>
#include <NovelCVLib\Apps\BloodCells\PixelInfo_1.h>


//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv;
	using namespace Ncv::ImageOperations2;

	using namespace Ncv::OpenCV_Util;

	//using namespace Ncv::ImageArrayHolderOperations;

	namespace Ns_BloodCells
	{
		AngleDirMgrColl::AngleDirMgrColl(F32ImageRef a_srcImg, ImgSizeRotationCollRef a_rotColl)
		{
			m_srcImg = a_srcImg;
			m_rotColl = a_rotColl;
			m_context_H = new AngleDirMgrColl_Context();
			m_context_V = new AngleDirMgrColl_Context();

			Prepare();
		}

		void AngleDirMgrColl::Prepare()
		{
			//Ncpp_ASSERT(m_srcImg)

			//m_rotColl
			F32ImageArrayHolder3C_Ref org_Img_H = new F32ImageArrayHolder3C(m_srcImg);
			//F32ImageArrayHolder3C_Ref org_Img_V = org_Img_H->CloneAccessorOnly(); org_Img_V->SwitchXY();

			ShowImage(org_Img_H->GetSrcImg(), "org_Img_H->GetSrcImg()");

			m_context_H->m_org_Img = org_Img_H;

			//m_context_H->m_standevInfoImg = ArrayHolderUtil::CreateFrom<PixelStandevInfo>(org_Img_H->GetVirtAccessor().GetSize());
			m_context_H->m_standevInfoImg = ArrayHolderUtil::CreateEmptyFrom<PixelStandevInfo>(org_Img_H->AsHolderRef());

			{
				PixelStandevInfo initPsi;
				//initPsi.Dir = -1;
				initPsi.Dir = 0;
				initPsi.Val = 10000000;
				//SetToUndefined(&initPsi.Val);
				initPsi.NormVal = 0;
				FillImage(m_context_H->m_standevInfoImg->GetVirtAccessor(), initPsi);
				//SetImageToBadValue(m_context_H->m_standevInfoImg->GetVirtAccessor());
			}

			m_context_H->m_conflictInfoImg = ArrayHolderUtil::CreateFrom<ConflictInfo2_Ex>(
				org_Img_H->GetActualSize());
			{
				ConflictInfo2_Ex ci_Init;
				//ci_Init.Dir = -1;
				ci_Init.Dir = 0;
				ci_Init.Offset_Side_1 = -567890;
				ci_Init.Offset_Side_2 = 567890;
				ci_Init.Exists = false;
				FillImage(m_context_H->m_conflictInfoImg->GetVirtAccessor(), ci_Init);
			}

			m_context_H->m_wideConflictDiff_Img = new F32ImageArrayHolder1C(
				org_Img_H->GetActualSize());
			{
				//float initVal = -10000000;
				float initVal = 0;
				FillImage(m_context_H->m_wideConflictDiff_Img->GetVirtAccessor(), initVal);
			}

			m_context_H->m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(
				org_Img_H->GetActualSize());
			{
				//float initVal = -10000000;
				VectorVal<Float, 4> initVal;
				SetToZero(&initVal);
				//initVal.Vals[0] = initVal.Vals[1] = initVal.Vals[2] = initVal.Vals[3] = 0;
				//auto tmpAcc1 = m_context_H->m_avgPStandev_InrWide_Img->GetVirtAccessor();
				const VirtArrayAccessor_2D< VectorVal<Float, 4>> & tmpAcc1 = m_context_H->m_avgPStandev_InrWide_Img->GetVirtAccessor();

				//FillImage(m_context_H->m_avgPStandev_InrWide_Img->GetVirtAccessor(), initVal);
				FillImage(tmpAcc1, initVal);
			}


			m_context_V->m_org_Img = m_context_H->m_org_Img->CreateTransposedProxy();
			m_context_V->m_standevInfoImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_standevInfoImg);
			m_context_V->m_conflictInfoImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_conflictInfoImg);
			m_context_V->m_wideConflictDiff_Img = m_context_H->m_wideConflictDiff_Img->CreateTransposedProxy();
			m_context_V->m_avgPStandev_InrWide_Img = m_context_H->m_avgPStandev_InrWide_Img->CreateTransposedProxy();


			m_angleDirMgrArr.SetSize(m_rotColl->GetNofRots() * 2);

			for (int i = 0; i < m_rotColl->GetNofRots(); i++)
			{
				ImgSizeRotationRef rotMgr = m_rotColl->GetRotAt(i);

				//F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(rotMgr->GetResImg());
				//F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(rotMgr->GetResImgSiz());
				F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(
					F32Image::Create(toCvSize(rotMgr->GetResImgSiz()), m_srcImg->GetNofChannels()));

				// AssertImageUndefinedOrValid(org_Img_H->GetVirtAccessor());

				rotMgr->RotateImage(rot_Img_H->GetActualAccessor(), org_Img_H->GetActualAccessor());

				//F32ImageArrayHolder1C_Ref magSqr_Img_H = new F32ImageArrayHolder1C(rot_Img_H->GetVirtAccessor().GetSize());
				F32ImageArrayHolder1C_Ref magSqr_Img_H = F32ImageArrayHolder1C::CreateEmptyFrom(rot_Img_H);
				CalcMagSqrImage(rot_Img_H->GetVirtAccessor(), magSqr_Img_H->GetVirtAccessor());

				ImgAngleDirMgr_Context_Ref dirContext_H = new ImgAngleDirMgr::Context(i, rotMgr,
					rot_Img_H, magSqr_Img_H, 'H');

				//dirContext_H->m_rotToOrgMap_Img = new S32ImageArrayHolder1C(rotMgr->Get_ResToNearestSrcIndexMapImage());
				//dirContext_H->m_orgToRotMap_Img = new S32ImageArrayHolder1C(rotMgr->Get_SrcToNearestResIndexMapImage());

				dirContext_H->m_rotToOrgMap_Img = rotMgr->Get_ResToNearestSrcIndexMapImage();
				dirContext_H->m_orgToRotMap_Img = rotMgr->Get_SrcToNearestResIndexMapImage();

				dirContext_H->m_angle = rotMgr->GetAngleByRad();

				//dirContext_H->m_conflict_Img = ArrayHolderUtil::CreateFrom<ConflictInfo2>(
				//	size_2D(rot_Img_H->GetSize()));

				F32ImageArrayHolder3C_Ref rot_Img_V = rot_Img_H->CreateTransposedProxy();
				F32ImageArrayHolder1C_Ref magSqr_Img_V = magSqr_Img_H->CreateTransposedProxy();

				ImgAngleDirMgr_Context_Ref dirContext_V = new ImgAngleDirMgr::Context(i + m_rotColl->GetNofRots(),
					rotMgr, rot_Img_V, magSqr_Img_V, 'V');

				//dirContext_V->m_rotToOrgMap_Img = dirContext_H->m_rotToOrgMap_Img->CreateTransposedProxy();
				//dirContext_V->m_orgToRotMap_Img = dirContext_H->m_orgToRotMap_Img->CreateTransposedProxy();

				dirContext_V->m_rotToOrgMap_Img = ArrayHolderUtil::CreateTransposedProxyFrom(dirContext_H->m_rotToOrgMap_Img);
				dirContext_V->m_orgToRotMap_Img = ArrayHolderUtil::CreateTransposedProxyFrom(dirContext_H->m_orgToRotMap_Img);

				dirContext_V->m_angle = rotMgr->GetAngleByRad() + M_PI / 2;
				//dirContext_V->m_conflict_Img = dirContext_H->m_conflict_Img->CloneAccessorOnly(); dirContext_V->m_conflict_Img->SwitchXY();

				ImgAngleDirMgrRef angleDirMgr_H = new ImgAngleDirMgr(dirContext_H, dirContext_V, m_context_H);
				m_angleDirMgrArr[i] = angleDirMgr_H;

				ImgAngleDirMgrRef angleDirMgr_V = new ImgAngleDirMgr(dirContext_V, dirContext_H, m_context_V);
				m_angleDirMgrArr[i + m_rotColl->GetNofRots()] = angleDirMgr_V;
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_1();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_2();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_3();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_4();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_5_1();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_5_2();
			}

			DivideImageByNum(m_context_H->m_avgPStandev_InrWide_Img->GetVirtAccessor(),
				this->m_angleDirMgrArr.GetSize());

			for (int i = 0; i < m_rotColl->GetNofRots(); i++) {
				
				ImgSizeRotationRef rot = m_rotColl->GetRotAt(i);

				ImgAngleDirMgrRef dirMgr_H = m_angleDirMgrArr[i];
				ImgAngleDirMgrRef dirMgr_V = m_angleDirMgrArr[i + m_rotColl->GetNofRots()];

				F32VectorValImageArrayHolder_4C_Ref avgPStandev_InrWide_Img_H = new F32VectorValImageArrayHolder_4C(
					dirMgr_H->GetContext()->m_org_Img->GetActualAccessor().GetSize());

				rot->RotateImage(avgPStandev_InrWide_Img_H->GetActualAccessor(), m_context_H->m_avgPStandev_InrWide_Img->GetActualAccessor());

				dirMgr_H->GetContext()->m_avgPStandev_InrWide_Img = avgPStandev_InrWide_Img_H;

				F32VectorValImageArrayHolder_4C_Ref avgPStandev_InrWide_Img_V = avgPStandev_InrWide_Img_H->CreateTransposedProxy();

				dirMgr_V->GetContext()->m_avgPStandev_InrWide_Img = avgPStandev_InrWide_Img_V;
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_5_3();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_6();
			}

			DisplayStandiv_Dir_Img();

			DisplayConflictImg();

			//ShowImage(standev_InrWide_Img->GetSrcImg(), "standev_InrWide_Img->GetSrcImg()");

			GlobalStuff::SetLinePathImg(GenTriChGrayImg(m_context_H->m_wideConflictDiff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			ShowImage(m_context_H->m_wideConflictDiff_Img->GetSrcImg(), "m_wideConflictDiff_Img->GetSrcImg()");

			SaveImage(m_context_H->m_wideConflictDiff_Img->GetSrcImg(), "m_wideConflictDiff_Img.jpg");



			ManageThresholding();

		}


		void AngleDirMgrColl::DisplayStandiv_Dir_Img()
		{
			const ActualArrayAccessor_2D<PixelStandevInfo> & psiAcc = m_context_H->m_standevInfoImg->GetActualAccessor();
			const VirtArrayAccessor_2D<PixelStandevInfo> & psiVirtAcc = m_context_H->m_standevInfoImg->GetVirtAccessor();
			//F32ImageRef dspImg_Values = F32Image::Create(cvSize(psiAcc.GetSize()), 1);
			
			F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(psiAcc.GetSize()), 3);

			const int nSize_1D = psiAcc.CalcSize_1D();

			PixelStandevInfo * srcPtr = (PixelStandevInfo *)psiAcc.GetData();
			//float * destPtr_Values = (float *)dspImg_Values->GetDataPtr();
			F32ColorVal * destPtr_Colored = (F32ColorVal *)dspImg_Colored->GetDataPtr();

			float angle_Old = -1;
			for (int i = 0; i < nSize_1D; i++)
			{
				PixelStandevInfo & rSrc = srcPtr[i];
				//float & rDest_Values = destPtr_Values[i];
				F32ColorVal & rDest_Colored = destPtr_Colored[i];

				Ncpp_ASSERT(-1 != rSrc.Dir);
				Ncpp_ASSERT(rSrc.Dir >= 0);

				float angle = m_angleDirMgrArr[rSrc.Dir]->GetContext()->m_angle;

				if (fabs(angle - angle_Old) > 0.01)
				{
					angle = angle;
				}
				angle_Old = angle;

				////rDest.val0 = 127 + rSrc.NormVal / 2;
				//rDest.val0 = 127;
				//rDest.val1 = (127 + 127 * cos(angle) * rSrc.NormVal * 2 / 3);
				//rDest.val2 = (127 + 127 * sin(angle) * rSrc.NormVal * 2 / 3);

				//rDest_Values = rSrc.NormVal;

				rDest_Colored.val0 = 0;
				//rDest.val1 = (fabs(cos(angle)) * rSrc.NormVal * 2 / 3);
				//rDest.val2 = (fabs(sin(angle)) * rSrc.NormVal * 2 / 3);
				rDest_Colored.val1 = (fabs(cos(angle)) * rSrc.NormVal * 5 / 3);
				rDest_Colored.val2 = (fabs(sin(angle)) * rSrc.NormVal * 5 / 3);
				//rDest.val1 = (fabs(cos(angle)) * rSrc.NormVal);
				//rDest.val2 = (fabs(sin(angle)) * rSrc.NormVal);

				////if (0 == rSrc.Dir)
				//if (5 == rSrc.Dir)
				////if (false)
				//{
				//	rDest.val0 = rSrc.NormVal;
				//	rDest.val1 = rSrc.NormVal;
				//	rDest.val2 = rSrc.NormVal;
				//}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}

				//rDest.val0 = 127 + rSrc.NormVal;
				//rDest.val1 = 127 + 127 * cos(angle);
				//rDest.val2 = 127 + 127 * sin(angle);
			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			//GlobalStuff::ShowLinePathImg();

			//ShowImage(dspImg_Values, "dspImg_Colored");
		}

		void AngleDirMgrColl::DisplayConflictImg()
		{
			const ActualArrayAccessor_2D<ConflictInfo2_Ex> & confAcc = m_context_H->m_conflictInfoImg->GetActualAccessor();
			F32ImageRef confDsp_Img = F32Image::Create(toCvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			const int nSize_1D = confAcc.CalcSize_1D();

			F32ColorVal * destPtr = (F32ColorVal *)confDsp_Img->GetDataPtr();
			ConflictInfo2_Ex * srcPtr = (ConflictInfo2_Ex *)confAcc.GetData();

			float angle_Old = -1;
			for (int i = 0; i < nSize_1D; i++)
			{
				ConflictInfo2_Ex & rSrc = srcPtr[i];
				AssertValue(rSrc);
				F32ColorVal & rDest = destPtr[i];

				//Ncpp_ASSERT(-1 != rSrc.Dir);

				if (rSrc.Exists)
				{
					F32ColorVal & rDest_Side_1 = destPtr[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = destPtr[rSrc.Offset_Side_2];

					rDest.val0 = 0;
					rDest.val1 = 0;
					rDest.val2 = 255;

					rDest_Side_1.val0 = 0;
					rDest_Side_1.val1 = 255;
					rDest_Side_1.val2 = 0;

					rDest_Side_2.val0 = 0;
					rDest_Side_2.val1 = 255;
					rDest_Side_2.val2 = 0;
				}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}
			}

			ShowImage(confDsp_Img, "confDsp_Img->GetSrcImg()");
		}


		void AngleDirMgrColl::ManageThresholding_0()
		{
			AngleDirMgrColl_Context & cx = *m_context_H;

			F32ColorVal * orgImg_Ptr = (F32ColorVal *)cx.m_org_Img->GetActualAccessor().GetData();
			ConflictInfo2_Ex * conf_Ptr = (ConflictInfo2_Ex *)cx.m_conflictInfoImg->GetActualAccessor().GetData();

			const int nSize_1D = cx.m_conflictInfoImg->GetActualAccessor().CalcSize_1D();

			//F32ImageArrayHolder3C_Ref threshold_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder3C_Ref threshold_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			F32ColorVal * threshold_Ptr = (F32ColorVal *)threshold_Img->GetActualAccessor().GetData();

			//F32ImageArrayHolder1C_Ref weight_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref weight_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			float * weight_Ptr = (float *)weight_Img->GetActualAccessor().GetData();
			{
				{
					float init_Val = 0.0f;
					FillImage(weight_Img->GetVirtAccessor(), init_Val);
				}

				for (int i = 0; i < nSize_1D; i++)
				{
					ConflictInfo2_Ex & rConf = conf_Ptr[i];
					float & rWeight = weight_Ptr[i];
					F32ColorVal & rThreshold = threshold_Ptr[i];

					if (!rConf.Exists)
					{
						rWeight = 0;
						rThreshold.AssignVal(0, 0, 0);
						continue;
					}

					rWeight = 1;

					F32ColorVal & rVal_Side_1 = orgImg_Ptr[rConf.Offset_Side_1];
					F32ColorVal & rVal_Side_2 = orgImg_Ptr[rConf.Offset_Side_2];

					rThreshold = F32ColorVal::Add(rVal_Side_1, rVal_Side_2).DividBy(2);

					//avg_Wide_Mag_Diff_Ptr[i] = fabs(mag_Ptr[i] - avg_Wide_Ptr[i]);
				}
			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(threshold_Mag_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//ShowImage(threshold_Img->GetSrcImg(), "threshold_Img->GetSrcImg()");

			F32ImageArrayHolder3C_Ref avg_Threshold_Img = threshold_Img;
			////F32ImageArrayHolder3C_Ref avg_Threshold_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32ImageArrayHolder3C_Ref avg_Threshold_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//{
			//	//const int nWinRadius = 5;
			//	//const int nWinRadius = 8;
			//	const int nWinRadius = 15;
			//	AvgImage_Weighted(threshold_Img->GetVirtAccessor(), weight_Img->GetVirtAccessor(), avg_Threshold_Img->GetVirtAccessor(),
			//		Window<int>::New(-nWinRadius, nWinRadius, -nWinRadius, nWinRadius));
			//}
			//ShowImage(avg_Threshold_Img->GetSrcImg(), "avg_Threshold_Img->GetSrcImg()");

			//F32ImageArrayHolder1C_Ref mag_Avg_Threshold_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref mag_Avg_Threshold_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(avg_Threshold_Img->GetVirtAccessor(), mag_Avg_Threshold_Img->GetVirtAccessor());
			float * mag_Avg_Threshold_Ptr = (float *)mag_Avg_Threshold_Img->GetActualAccessor().GetData();

			ShowImage(mag_Avg_Threshold_Img->GetSrcImg(), "mag_Avg_Threshold_Img->GetSrcImg()");

			//F32ImageArrayHolder1C_Ref magImg = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref magImg = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(cx.m_org_Img->GetVirtAccessor(), magImg->GetVirtAccessor());
			float * mag_Ptr = (float *)magImg->GetActualAccessor().GetData();

			//F32ImageArrayHolder1C_Ref bin_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref bin_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			{
				//{
				//	float init_Val = 0.0f;
				//	FillImage(bin_Img->GetVirtAccessor(), init_Val);
				//}
				float * bin_Ptr = (float *)bin_Img->GetActualAccessor().GetData();

				for (int i = 0; i < nSize_1D; i++)
				{
					float & rMag_Avg_Threshold = mag_Avg_Threshold_Ptr[i];
					float & rMag = mag_Ptr[i];
					float & rBin = bin_Ptr[i];

					if (rMag_Avg_Threshold < 5.0)
					{
						rBin = 128;
						continue;
					}

					if (rMag > rMag_Avg_Threshold)
					{
						rBin = 255;
					}
					else
					{
						rBin = 0;
					}
				}
			}
			ShowImage(bin_Img->GetSrcImg(), "bin_Img->GetSrcImg()");


			//SaveImage(GenTriChGrayImg(bin_Img->GetSrcImg()), "E:\\bin_Img.jpg");
			//SaveImage(GenTriChGrayImg(bin_Img->GetSrcImg()), "bin_Img.jpg");


			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(avg_Wide_Mag_Diff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//ShowImage(standev_Thin_Img->GetSrcImg(), "avg_Wide_Mag_Diff_Img->GetSrcImg()");






		}

		void AngleDirMgrColl::ManageThresholding()
		{
			AngleDirMgrColl_Context & cx = *m_context_H;

			F32ColorVal * orgImg_Ptr = (F32ColorVal *)cx.m_org_Img->GetActualAccessor().GetData();

			ArrayHolder_2D_Ref<PixelInfo_1> rgnGrow_Img = ArrayHolderUtil::CreateFrom<PixelInfo_1>(
				cx.m_org_Img->GetActualAccessor().GetSize());

			const int nQueScale = 10;

			const VirtArrayAccessor_2D<float> & sac_WideOutStandev = cx.m_wideConflictDiff_Img->GetVirtAccessor();
			const VirtArrayAccessor_2D<ConflictInfo2_Ex> & sac_Conflicts = cx.m_conflictInfoImg->GetVirtAccessor();

			MultiListQueMgr< PixelInfo_1 > rgnGrowQues;
			rgnGrowQues.InitSize(700 * nQueScale + 2);

			//MemSimpleAccessor_2D<PixelInfo_1> sac_RgnGrow = rgnGrow_Img->GetVirtAccessor()->GenSimpleAccessor();
			const VirtArrayAccessor_2D<PixelInfo_1> & sac_RgnGrow = rgnGrow_Img->GetVirtAccessor();

			for (int y = 0; y < sac_RgnGrow.GetSize_Y(); y++)
			{
				for (int x = 0; x < sac_RgnGrow.GetSize_X(); x++)
				{
					PixelInfo_1 & rPixInfo = sac_RgnGrow.GetAt(x, y);

					rPixInfo.X = x;
					rPixInfo.Y = y;

					ConflictInfo2_Ex * pConflictInfo = &sac_Conflicts.GetAt(x, y);
					AssertValue(*pConflictInfo);
					rPixInfo.pConflictInfo = pConflictInfo;

					rPixInfo.Val_WideOutStandev = sac_WideOutStandev.GetAt(x, y);
					Ncpp_ASSERT(rPixInfo.Val_WideOutStandev >= 0);
					if (rPixInfo.pConflictInfo->Exists)
					{
						//Ncpp_ASSERT(!IsUndefined(rPixInfo));
						
						Ncpp_ASSERT(!IsUndefined(*rPixInfo.pConflictInfo));
						//Ncpp_ASSERT(!IsUndefined(rPixInfo.pConflictInfo->Offset_Side_1));
						rgnGrowQues.PushPtr(rPixInfo.Val_WideOutStandev * nQueScale, &rPixInfo);
						rPixInfo.IsPushed = true;
					}
					else
					{
						rPixInfo.IsPushed = false;
					}
				}	//	end for x
			}	//	end for y

			////F32ImageArrayHolder3C_Ref disp1_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32ImageArrayHolder3C_Ref disp1_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);

			//MemSimpleAccessor_2D<F32ColorVal> sac_Disp1 = disp1_Img->GetVirtAccessor()->GenSimpleAccessor();

			PixelInfo_1 * pPI = nullptr;
			int nPushedCnt = 0;

			do
			{
				pPI = rgnGrowQues.PopPtrMin();
				if (nullptr == pPI)
				{
					continue;
				}

				nPushedCnt++;

				//Ncpp_ASSERT(!IsUndefined(*pPI->pConflictInfo));
				AssertValue(*pPI->pConflictInfo);
				Ncpp_ASSERT(pPI->pConflictInfo->Exists);

				Ncpp_ASSERT(pPI->IsPushed);

				//F32ColorVal * pVal_Disp1 = &sac_Disp1.GetAt(pPI->X, pPI->Y);
				//pVal_Disp1->val0 = 0;
				////pVal_Disp1->val1 = pPI->Val_WideOutStandev;
				//pVal_Disp1->val1 = nPushedCnt * 255.0f / 480000;
				//pVal_Disp1->val2 = 0;



				for (int yd = -1; yd <= 1; yd++)
				{
					int y = pPI->Y + yd;
					if (y < 0 || y >= sac_RgnGrow.GetSize_Y())
					{
						continue;
					}

					for (int xd = -1; xd <= 1; xd++)
					{
						int x = pPI->X + xd;
						if (x < 0 || x >= sac_RgnGrow.GetSize_X())
						{
							continue;
						}

						PixelInfo_1 * pPI_Dest = &sac_RgnGrow.GetAt(x, y);
						if (pPI_Dest->IsPushed)
						{
							continue;
						}

						Ncpp_ASSERT(!pPI_Dest->pConflictInfo->Exists);
						//Ncpp_ASSERT(!IsUndefined(pPI_Dest->Val_WideOutStandev));
						Ncpp_ASSERT(pPI_Dest->Val_WideOutStandev >= 0);
						
						pPI_Dest->pConflictInfo = pPI->pConflictInfo;

						rgnGrowQues.PushPtr(pPI_Dest->Val_WideOutStandev * nQueScale, pPI_Dest);
						pPI_Dest->IsPushed = true;
				
					}	//	end for xd
				}	//	end for yd


			} while (nullptr != pPI);

			//ShowImage(disp1_Img->GetSrcImg(), "disp1_Img");

			//return;


			//AngleDirMgrColl_Context & cx = *m_context_H;

			//F32ColorVal * orgImg_Ptr = (F32ColorVal *)cx.m_org_Img->GetDataPtr();
			//ConflictInfo2_Ex * conf_Ptr = cx.m_conflictInfoImg->GetDataPtr();


			const int nSize_1D = cx.m_conflictInfoImg->GetActualAccessor().CalcSize_1D();
			Ncpp_ASSERT(nSize_1D == nPushedCnt);

			//F32ImageArrayHolder3C_Ref threshold_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder3C_Ref threshold_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			F32ColorVal * threshold_Ptr = (F32ColorVal *)threshold_Img->GetActualAccessor().GetData();
			PixelInfo_1 * pixelInfo_Ptr = (PixelInfo_1 *)rgnGrow_Img->GetActualAccessor().GetData();

			{
				for (int i = 0; i < nSize_1D; i++)
				{
					PixelInfo_1 & rPI = pixelInfo_Ptr[i];
					F32ColorVal & rThreshold = threshold_Ptr[i];

					Ncpp_ASSERT(rPI.pConflictInfo->Exists);
					//if (!rPI.pConflictInfo->Exists)
					//{
					//	rThreshold.AssignVal(255, 255, 255);
					//	continue;
					//}

					F32ColorVal & rVal_Side_1 = orgImg_Ptr[rPI.pConflictInfo->Offset_Side_1];
					F32ColorVal & rVal_Side_2 = orgImg_Ptr[rPI.pConflictInfo->Offset_Side_2];

					rThreshold = F32ColorVal::Add(rVal_Side_1, rVal_Side_2).DividBy(2);
				
				}	//	end for i
			}	//	end block

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(threshold_Mag_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//ShowImage(threshold_Img->GetSrcImg(), "threshold_Img->GetSrcImg()");

			F32ImageArrayHolder3C_Ref avg_Threshold_Img = threshold_Img;
			////F32ImageArrayHolder3C_Ref avg_Threshold_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32ImageArrayHolder3C_Ref avg_Threshold_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//{
			//	//const int nWinRadius = 5;
			//	//const int nWinRadius = 8;
			//	const int nWinRadius = 15;
			//	AvgImage_Weighted(threshold_Img->GetVirtAccessor(), weight_Img->GetVirtAccessor(), avg_Threshold_Img->GetVirtAccessor(),
			//		Window<int>::New(-nWinRadius, nWinRadius, -nWinRadius, nWinRadius));
			//}
			ShowImage(avg_Threshold_Img->GetSrcImg(), "avg_Threshold_Img->GetSrcImg()");

			//F32ImageArrayHolder1C_Ref mag_Avg_Threshold_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref mag_Avg_Threshold_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(avg_Threshold_Img->GetVirtAccessor(), mag_Avg_Threshold_Img->GetVirtAccessor());
			float * mag_Avg_Threshold_Ptr = (float *)mag_Avg_Threshold_Img->GetActualAccessor().GetData();

			ShowImage(mag_Avg_Threshold_Img->GetSrcImg(), "mag_Avg_Threshold_Img->GetSrcImg()");

			//F32ImageArrayHolder1C_Ref magImg = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref magImg = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(cx.m_org_Img->GetVirtAccessor(), magImg->GetVirtAccessor());
			float * mag_Ptr = (float *)magImg->GetActualAccessor().GetData();


			//PixelInfo_1 & rPI = pixelInfo_Ptr[i];


			//F32ImageArrayHolder1C_Ref bin_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref bin_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			{
				//{
				//	float init_Val = 0.0f;
				//	FillImage(bin_Img->GetVirtAccessor(), init_Val);
				//}
				float * bin_Ptr = (float *)bin_Img->GetActualAccessor().GetData();

				for (int i = 0; i < nSize_1D; i++)
				{
					PixelInfo_1 & rPI = pixelInfo_Ptr[i];
					F32ColorVal & rThreshold = threshold_Ptr[i];

					Ncpp_ASSERT(rPI.pConflictInfo->Exists);

					const int offset_1 = rPI.pConflictInfo->Offset_Side_1;
					const int offset_2 = rPI.pConflictInfo->Offset_Side_2;

					//float & rMag_Avg_Threshold = mag_Avg_Threshold_Ptr[i];
					//float & rMag = mag_Ptr[i];
					float & rBin = bin_Ptr[i];

					F32ColorVal & rVal_Side_1 = orgImg_Ptr[offset_1];
					F32ColorVal & rVal_Side_2 = orgImg_Ptr[offset_2];

					F32ColorVal & rVal_Pix = orgImg_Ptr[i];

					float dif_1 = F32ColorVal::Sub(rVal_Pix, rVal_Side_1).CalcMag();
					float dif_2 = F32ColorVal::Sub(rVal_Pix, rVal_Side_2).CalcMag();

					float mag_1 = mag_Ptr[offset_1];
					float mag_2 = mag_Ptr[offset_2];

					if (dif_1 < dif_2)	//	closer to 1
					{
						if (mag_1 > mag_2)
						{
							rBin = 255;
						}
						else
						{
							rBin = 0;
						}
					}
					else	//	closer to 2
					{
						if (mag_1 > mag_2)
						{
							rBin = 0;
						}
						else
						{
							rBin = 255;
						}
					}


					//if (rMag_Avg_Threshold < 5.0)
					//{
					//	rBin = 128;
					//	continue;
					//}

					//if (rMag > rMag_Avg_Threshold)
					//{
					//	rBin = 255;
					//}
					//else
					//{
					//	rBin = 0;
					//}


					//float & rMag_Avg_Threshold = mag_Avg_Threshold_Ptr[i];
					//float & rMag = mag_Ptr[i];
					//float & rBin = bin_Ptr[i];

					//if (rMag_Avg_Threshold < 5.0)
					//{
					//	rBin = 128;
					//	continue;
					//}

					//if (rMag > rMag_Avg_Threshold)
					//{
					//	rBin = 255;
					//}
					//else
					//{
					//	rBin = 0;
					//}
				}
			}
			ShowImage(bin_Img->GetSrcImg(), "bin_Img->GetSrcImg()");


			//SaveImage(GenTriChGrayImg(bin_Img->GetSrcImg()), "E:\\bin_Img.jpg");
			SaveImage(GenTriChGrayImg(bin_Img->GetSrcImg()), "bin_Img.jpg");


			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(avg_Wide_Mag_Diff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//ShowImage(standev_Thin_Img->GetSrcImg(), "avg_Wide_Mag_Diff_Img->GetSrcImg()");






		}



	}
}

