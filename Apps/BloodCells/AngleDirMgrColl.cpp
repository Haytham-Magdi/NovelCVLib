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

//#include <NovelCVLib\Ncv\PixelLink.h>
//#include <NovelCVLib\Ncv\PixelLinkType.h>
//#include <NovelCVLib\Ncv\PixelLinkTypes.h>
#include <NovelCVLib\Ncv\PixelLinkOwner.h>
#include <NovelCVLib\Ncv\PixelLinkUtil.h>
#include <NovelCVLib\Ncv\PixelLinkDefs.h>



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

			GlobalStuff::SetLinePathImg(org_Img_H->GetSrcImg());
			GlobalStuff::ShowLinePathImg();

			m_context_H->m_org_Img = org_Img_H;

			m_context_H->m_normAvgStandevInfoCmnImg = ArrayHolderUtil::CreateEmptyFrom<PixelStandevInfoCmn>(org_Img_H->AsHolderRef());

			{
				//PixelStandevInfoCmn initPsi;
				//////initPsi.Dir = -1;
				////initPsi.Dir = 0;
				//////initPsi.Val = 10000000;
				////initPsi.Val = 100000;
				////SetToUndefined(&initPsi.Val);
				////initPsi.NormLeastVal1 = 0;
				//// initPsi.NormLeastVal1 = 60;
				//
				////initPsi.NormLeastVal1 = 1000;
				////initPsi.NormSecondLeastVal = 1000;

				//initPsi.NormLeastVal1 = 0;
				//initPsi.NormSecondLeastVal = 0;

				//initPsi.LeastVal = 100000;
				//initPsi.LeastValDir = 0;

				//initPsi.SecondLeastVal = 100000;
				//initPsi.SecondLeastValDir = 1;

				//////initPsi.MaxVal = 1000;
				////initPsi.MaxVal = 0;
				////initPsi.MaxValDir = 2;

				//FillImage(m_context_H->m_normAvgStandevInfoCmnImg->GetVirtAccessor(), initPsi);
				SetImageToUndefined(m_context_H->m_normAvgStandevInfoCmnImg->GetVirtAccessor());

				ActualArrayAccessor_1D<PixelStandevInfoCmn> psiAcc_1D =
					m_context_H->m_normAvgStandevInfoCmnImg->GetActualAccessor().GenAcc_1D();

				for (int i = 0; i < psiAcc_1D.GetSize(); i++)
				{
					PixelStandevInfoCmn & rBdc = psiAcc_1D[i];
					rBdc.Index = i;
				}

			}


			m_context_H->m_standevInfo2CmnImg = ArrayHolderUtil::CreateEmptyFrom<PixelStandevInfoCmn>(org_Img_H->AsHolderRef());

			{

				SetImageToUndefined(m_context_H->m_standevInfo2CmnImg->GetVirtAccessor());
				
				ActualArrayAccessor_1D<PixelStandevInfoCmn> psiAcc_1D =
					m_context_H->m_standevInfo2CmnImg->GetActualAccessor().GenAcc_1D();

				for (int i = 0; i < psiAcc_1D.GetSize(); i++)
				{
					PixelStandevInfoCmn & rPsi = psiAcc_1D[i];
					rPsi.Index = i;
				}

			}


			m_context_H->m_bidiffInfoCommonImg = ArrayHolderUtil::CreateEmptyFrom<BidiffInfoCommon>(org_Img_H->AsHolderRef());

			{
				//BidiffInfoCommon initBdc;

				//initBdc.MinVal = 100000;
				//initBdc.MinValDir = 0;

				//initBdc.MaxVal = 100000;
				//initBdc.MaxValDir = 1;

				//FillImage(m_context_H->m_bidiffInfoCommonImg->GetVirtAccessor(), initBdc);
				SetImageToUndefined(m_context_H->m_bidiffInfoCommonImg->GetVirtAccessor());

				//const ActualArrayAccessor_2D<BidiffInfoCommon> & bdcAcc = m_context_H->m_bidiffInfoCommonImg->GetActualAccessor();
				ActualArrayAccessor_1D<BidiffInfoCommon> bdcAcc_1D = 
					m_context_H->m_bidiffInfoCommonImg->GetActualAccessor().GenAcc_1D();

				for (int i = 0; i < bdcAcc_1D.GetSize(); i++)
				{
					BidiffInfoCommon & rBdc = bdcAcc_1D[i];
					rBdc.Index = i;
				}

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
			m_context_V->m_normAvgStandevInfoCmnImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_normAvgStandevInfoCmnImg);
			m_context_V->m_standevInfo2CmnImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_standevInfo2CmnImg);
			m_context_V->m_bidiffInfoCommonImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_bidiffInfoCommonImg);
			m_context_V->m_conflictInfoImg = ArrayHolderUtil::CreateTransposedProxyFrom(m_context_H->m_conflictInfoImg);
			m_context_V->m_wideConflictDiff_Img = m_context_H->m_wideConflictDiff_Img->CreateTransposedProxy();
			m_context_V->m_avgPStandev_InrWide_Img = m_context_H->m_avgPStandev_InrWide_Img->CreateTransposedProxy();


			m_angleDirMgrArr.InitSize(m_rotColl->GetNofRots() * 2);

			for (int i = 0; i < m_rotColl->GetNofRots(); i++)
			{
				ImgSizeRotationRef rotMgr = m_rotColl->GetRotAt(i);

				//F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(rotMgr->GetResImg());
				//F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(rotMgr->GetResImgSiz());
				F32ImageArrayHolder3C_Ref rot_Img_H = new F32ImageArrayHolder3C(
					F32Image::Create(toCvSize(rotMgr->GetResImgSiz()), m_srcImg->GetNofChannels()));

				// AssertImageUndefinedOrValid(org_Img_H->GetVirtAccessor());

				rotMgr->RotateImageWithInterpolation(rot_Img_H->GetActualAccessor(), org_Img_H->GetActualAccessor());
				//rotMgr->RotateImageWithNearestValues(rot_Img_H->GetActualAccessor(), org_Img_H->GetActualAccessor());
				

				//F32ImageArrayHolder1C_Ref magSqr_Img_H = new F32ImageArrayHolder1C(rot_Img_H->GetVirtAccessor().GetSize());
				F32ImageArrayHolder1C_Ref magSqr_Img_H = F32ImageArrayHolder1C::CreateEmptyFrom(rot_Img_H);
				CalcMagSqrImage(rot_Img_H->GetVirtAccessor(), magSqr_Img_H->GetVirtAccessor());

				ImgAngleDirMgr_Context_Ref dirContext_H = new ImgAngleDirMgr::Context(i, rotMgr,
					rot_Img_H, magSqr_Img_H, 'H');

				//dirContext_H->m_rotToOrgMap_Img = new S32ImageArrayHolder1C(rotMgr->Get_ResToNearestSrcIndexMapImage());
				//dirContext_H->m_orgToRotMap_Img = new S32ImageArrayHolder1C(rotMgr->Get_SrcToNearestResIndexMapImage());

				dirContext_H->m_rotToOrgMap_Img = rotMgr->Get_ResToNearestSrcIndexMapImage();
				dirContext_H->m_orgToRotMap_Img = rotMgr->Get_SrcToNearestResIndexMapImage();

				dirContext_H->m_angleByRad = rotMgr->GetAngleByRad();

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

				dirContext_V->m_angleByRad = rotMgr->GetAngleByRad() + M_PI / 2;
				//dirContext_V->m_conflict_Img = dirContext_H->m_conflict_Img->CloneAccessorOnly(); dirContext_V->m_conflict_Img->SwitchXY();

				ImgAngleDirMgrRef angleDirMgr_H = new ImgAngleDirMgr(dirContext_H, dirContext_V, m_context_H);
				m_angleDirMgrArr[i] = angleDirMgr_H;

				ImgAngleDirMgrRef angleDirMgr_V = new ImgAngleDirMgr(dirContext_V, dirContext_H, m_context_V);
				m_angleDirMgrArr[i + m_rotColl->GetNofRots()] = angleDirMgr_V;
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_1b_1();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_1b_2();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_2_1();
			}

			for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
				m_angleDirMgrArr[i]->Proceed_2_2();
			}

			// for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			// 	m_angleDirMgrArr[i]->Proceed_2b_1();
			// }

			// for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			// 	m_angleDirMgrArr[i]->Proceed_2b_2();
			// }

			//for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			//	m_angleDirMgrArr[i]->Proceed_2c_1();
			//}

			//for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			//	m_angleDirMgrArr[i]->Proceed_3_1();
			//}

			//for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			//	m_angleDirMgrArr[i]->Proceed_3_2();
			//}

			//DivideImageByNum(m_context_H->m_avgPStandev_InrWide_Img->GetVirtAccessor(),
			//	this->m_angleDirMgrArr.GetSize());

			//for (int i = 0; i < m_rotColl->GetNofRots(); i++) {
			//	
			//	ImgSizeRotationRef rot = m_rotColl->GetRotAt(i);

			//	ImgAngleDirMgrRef dirMgr_H = m_angleDirMgrArr[i];
			//	ImgAngleDirMgrRef dirMgr_V = m_angleDirMgrArr[i + m_rotColl->GetNofRots()];

			//	F32VectorValImageArrayHolder_4C_Ref avgPStandev_InrWide_Img_H = new F32VectorValImageArrayHolder_4C(
			//		dirMgr_H->GetContext()->m_org_Img->GetActualAccessor().GetSize());

			//	rot->RotateImage(avgPStandev_InrWide_Img_H->GetActualAccessor(), m_context_H->m_avgPStandev_InrWide_Img->GetActualAccessor());

			//	dirMgr_H->GetContext()->m_avgPStandev_InrWide_Img = avgPStandev_InrWide_Img_H;

			//	F32VectorValImageArrayHolder_4C_Ref avgPStandev_InrWide_Img_V = avgPStandev_InrWide_Img_H->CreateTransposedProxy();

			//	dirMgr_V->GetContext()->m_avgPStandev_InrWide_Img = avgPStandev_InrWide_Img_V;
			//}

			//for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			//	m_angleDirMgrArr[i]->Proceed_4_1();
			//}

			//for (int i = 0; i < m_angleDirMgrArr.GetSize(); i++) {
			//	m_angleDirMgrArr[i]->Proceed_4_2();
			//}


			TryPixelLinkStuff();

			DisplayNormAvgStandiv_Dir_Img();
			
			//DisplayStandiv2_Dir_Img();

			//DisplayBidiffInfo_Dir_Img();

			//DisplayImgForEdges();

			DisplayConflictImg();

			////ShowImage(standev_InrWide_Img->GetSrcImg(), "standev_InrWide_Img->GetSrcImg()");

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(m_context_H->m_wideConflictDiff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//ShowImage(m_context_H->m_wideConflictDiff_Img->GetSrcImg(), "m_wideConflictDiff_Img->GetSrcImg()");

			//SaveImage(m_context_H->m_wideConflictDiff_Img->GetSrcImg(), "m_wideConflictDiff_Img.jpg");



			//ManageThresholding();

		}

		void AngleDirMgrColl::DisplayNormAvgStandiv_Dir_Img()
		{
			const ActualArrayAccessor_2D<PixelStandevInfoCmn> & psiAcc = m_context_H->m_normAvgStandevInfoCmnImg->GetActualAccessor();
			const VirtArrayAccessor_2D<PixelStandevInfoCmn> & psiVirtAcc = m_context_H->m_normAvgStandevInfoCmnImg->GetVirtAccessor();
			//F32ImageRef dspImg_Values = F32Image::Create(cvSize(psiAcc.GetSize()), 1);

			//const int checkMargin = 70;
			//Window<int> checkWin(checkMargin, psiAcc.GetSize_X() - checkMargin,
			//	checkMargin, psiAcc.GetSize_Y() - checkMargin);


			F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(psiAcc.GetSize()), 3);

			const int nSize_1D = psiAcc.CalcSize_1D();
			ActualArrayAccessor_1D<PixelStandevInfoCmn> psiAcc_1D = psiAcc.GenAcc_1D();

			ActualArrayAccessor_1D<F32ColorVal> coloredDispAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			for (int i = 0; i < nSize_1D; i++)
			{
				PixelStandevInfoCmn & rPsi = psiAcc_1D[i];

				S32Point pnt = psiAcc.CalcPointFromIndex_1D(i);
				//if (S32Point::AreEqual(pnt, S32Point(55, 270)))

				//if (S32Point::AreEqual(pnt, S32Point(580, 304)))
				if (S32Point::AreEqual(pnt, S32Point(132, 86)))
				{
					i = i;
				}

				//if (S32Point::AreEqual(pnt, S32Point(576, 312)))
				//if (S32Point::AreEqual(pnt, S32Point(356, 238)))
				if (S32Point::AreEqual(pnt, S32Point(359, 232)))
				{
					i = i;
				}


				//const bool isPntInCheckWindow = pnt.IsInWindow(checkWin);
				//Ncpp_ASSERT(!isPntInCheckWindow || (isPntInCheckWindow && 150 == rPsi.NormLeastVal1));

				F32ColorVal & rColoredDispElm = coloredDispAcc_1D[i];

				if (IsUndefined(rPsi))
				{
					//rColoredDispElm.val0 = 0;
					rColoredDispElm.val0 = 254;
					rColoredDispElm.val1 = 254;
					rColoredDispElm.val2 = 254;

					continue;
				}

				//Ncpp_ASSERT(-1 != rPsi.Dir);
				//Ncpp_ASSERT(rPsi.Dir >= 0);

				Ncpp_ASSERT(rPsi.LeastValDir >= 0);
				Ncpp_ASSERT(rPsi.SecondLeastValDir >= 0);

				//float angle = m_angleDirMgrArr[rPsi.Dir]->GetContext()->m_angleByRad;

				float angle, normVal;
				{
					//const float leastValAngle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(leastValAngle >= 0.0f && leastValAngle <= M_PI);

					//const float secondLeastValAngle = m_angleDirMgrArr[rPsi.SecondLeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(secondLeastValAngle >= 0.0f && secondLeastValAngle <= M_PI);
					//
					//float angle1, angle2, weight1, weight2, normVal1, normVal2;

					//if (leastValAngle <= secondLeastValAngle)
					//{
					//	angle1 = leastValAngle;
					//	angle2 = secondLeastValAngle;

					//	weight1 = rPsi.SecondLeastVal;
					//	weight2 = rPsi.LeastVal;

					//	normVal1 = rPsi.NormLeastVal1;
					//	normVal2 = rPsi.NormSecondLeastVal;
					//}
					//else
					//{
					//	angle1 = secondLeastValAngle;
					//	angle2 = leastValAngle;

					//	weight1 = rPsi.LeastVal;
					//	weight2 = rPsi.SecondLeastVal;

					//	normVal1 = rPsi.NormSecondLeastVal;
					//	normVal2 = rPsi.NormLeastVal1;
					//}

					//if ((angle2 - angle1) <= (M_PI / 2))
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * angle2) /
					//		(weight1 + weight2);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}
					//else
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * (angle2 - M_PI)) /
					//		(weight1 + weight2);

					//	//angle = (angle <= M_PI) ? angle : (angle + M_PI);
					//	angle = (angle >= 0.0f) ? angle : (angle + M_PI);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}

					//normVal = ((weight1 + weight2) < 0.01) ? normVal1 :
					//	(weight1 * normVal1 + weight2 * normVal2) / (weight1 + weight2);

					////float angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					//angle = ((rPsi.LeastVal + rPsi.SecondLeastVal) < 0.5) ? leastValAngle :
					//	(rPsi.SecondLeastVal * leastValAngle + rPsi.LeastVal * secondLeastValAngle) /
					//	(rPsi.LeastVal + rPsi.SecondLeastVal);

					//if (leastValAngle != secondLeastValAngle && rPsi.NormLeastVal1 > 50.0f)
					//{
					//	i = i;
					//}

					// to be removed
					angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);

					normVal = rPsi.NormLeastVal1;
				}


				////rDest.val0 = 127 + rPsi.NormLeastVal1 / 2;
				//rDest.val0 = 127;
				//rDest.val1 = (127 + 127 * cos(angle) * rPsi.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (127 + 127 * sin(angle) * rPsi.NormLeastVal1 * 2 / 3);

				//rDest_Values = rPsi.NormLeastVal1;

				//rColoredDispElm.val0 = 0;
				//rColoredDispElm.val0 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;
				//rColoredDispElm.val1 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;

				//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 2 / 3);

				//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 5 / 3);

				//if (rPsi.LeastVal > 0.5 * rPsi.NormLeastVal1)
				if (!rPsi.IsDirClear())
					//if (rPsi.LeastVal > 0.8 * rPsi.NormLeastVal1)
				{
					//	for debug.
					if (rPsi.NormLeastVal1 > 120)
					{
						i = i;
					}
					rColoredDispElm.val0 = rPsi.NormLeastVal1;
					rColoredDispElm.val1 = 0.75 * rPsi.NormLeastVal1;
					rColoredDispElm.val2 = 0;
				}
				//else if (0 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
				//}
				//else if (1 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val2 = 0;
				//}
				//else if (3 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = 0;
				//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
				//}
				else
				{
					rColoredDispElm.val0 = 0;
					rColoredDispElm.val1 = (fabs(cos(angle)) * normVal * 5 / 3);
					rColoredDispElm.val2 = (fabs(sin(angle)) * normVal * 5 / 3);
				}


				//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.MaxVal * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.MaxVal * 5 / 3);

				//rColoredDispElm.val1 = rPsi.MaxVal;
				//rColoredDispElm.val2 = rPsi.MaxVal;

				//rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//rColoredDispElm.val2 = rPsi.NormLeastVal1;

				//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1);
				//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1);

				////if (0 == rPsi.Dir)
				//if (5 == rPsi.Dir)
				////if (false)
				//{
				//	rDest.val0 = rPsi.NormLeastVal1;
				//	rDest.val1 = rPsi.NormLeastVal1;
				//	rDest.val2 = rPsi.NormLeastVal1;
				//}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}

				//rDest.val0 = 127 + rPsi.NormLeastVal1;
				//rDest.val1 = 127 + 127 * cos(angle);
				//rDest.val2 = 127 + 127 * sin(angle);
			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			//GlobalStuff::ShowLinePathImg();

			//ShowImage(dspImg_Values, "normAvgStandevDirImg_Colored");

			ShowImage(dspImg_Colored, "normAvgStandevDirImg_Colored");
		}

		
		void AngleDirMgrColl::TryPixelLinkStuff()
		{
			AngleDirMgrColl_Context & cx = *m_context_H;

			ArrayHolder_2D_Ref<F32PixelLinkOwner3C> pixelLinkOwner_Img = 
				ArrayHolderUtil::CreateEmptyFrom<F32PixelLinkOwner3C>(cx.m_org_Img->AsHolderRef());

			const ActualArrayAccessor_2D<F32PixelLinkOwner3C> ploAcc = pixelLinkOwner_Img->GetActualAccessor();


			for (int y = 0, x = 0; x < ploAcc.GetSize_X() && x < 1; x++)
			{
				F32PixelLinkOwner3C & rPlo = ploAcc.GetAt(x, y);

				//PixelLink 

			}



			//------

			//const ActualArrayAccessor_2D<PixelLinkOwner> plAcc = m_context_H->m_normAvgStandevInfoCmnImg->GetActualAccessor();

			//


			//	const ActualArrayAccessor_2D<PixelStandevInfoCmn> & psiAcc = m_context_H->m_normAvgStandevInfoCmnImg->GetActualAccessor();
			//	const VirtArrayAccessor_2D<PixelStandevInfoCmn> & psiVirtAcc = m_context_H->m_normAvgStandevInfoCmnImg->GetVirtAccessor();
			//	//F32ImageRef dspImg_Values = F32Image::Create(cvSize(psiAcc.GetSize()), 1);

			//	//const int checkMargin = 70;
			//	//Window<int> checkWin(checkMargin, psiAcc.GetSize_X() - checkMargin,
			//	//	checkMargin, psiAcc.GetSize_Y() - checkMargin);


			//	F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(psiAcc.GetSize()), 3);

			//	const int nSize_1D = psiAcc.CalcSize_1D();
			//	ActualArrayAccessor_1D<PixelStandevInfoCmn> psiAcc_1D = psiAcc.GenAcc_1D();

			//	ActualArrayAccessor_1D<F32ColorVal> coloredDispAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			//	for (int i = 0; i < nSize_1D; i++)
			//	{
			//		PixelStandevInfoCmn & rPsi = psiAcc_1D[i];

			//		S32Point pnt = psiAcc.CalcPointFromIndex_1D(i);
			//		//if (S32Point::AreEqual(pnt, S32Point(55, 270)))

			//		//if (S32Point::AreEqual(pnt, S32Point(580, 304)))
			//		if (S32Point::AreEqual(pnt, S32Point(132, 86)))
			//		{
			//			i = i;
			//		}

			//		//if (S32Point::AreEqual(pnt, S32Point(576, 312)))
			//		//if (S32Point::AreEqual(pnt, S32Point(356, 238)))
			//		if (S32Point::AreEqual(pnt, S32Point(359, 232)))
			//		{
			//			i = i;
			//		}


			//		//const bool isPntInCheckWindow = pnt.IsInWindow(checkWin);
			//		//Ncpp_ASSERT(!isPntInCheckWindow || (isPntInCheckWindow && 150 == rPsi.NormLeastVal1));

			//		F32ColorVal & rColoredDispElm = coloredDispAcc_1D[i];

			//		if (IsUndefined(rPsi))
			//		{
			//			//rColoredDispElm.val0 = 0;
			//			rColoredDispElm.val0 = 254;
			//			rColoredDispElm.val1 = 254;
			//			rColoredDispElm.val2 = 254;

			//			continue;
			//		}

			//		//Ncpp_ASSERT(-1 != rPsi.Dir);
			//		//Ncpp_ASSERT(rPsi.Dir >= 0);

			//		Ncpp_ASSERT(rPsi.LeastValDir >= 0);
			//		Ncpp_ASSERT(rPsi.SecondLeastValDir >= 0);

			//		//float angle = m_angleDirMgrArr[rPsi.Dir]->GetContext()->m_angleByRad;

			//		float angle, normVal;
			//		{
			//			//const float leastValAngle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
			//			//Ncpp_ASSERT(leastValAngle >= 0.0f && leastValAngle <= M_PI);

			//			//const float secondLeastValAngle = m_angleDirMgrArr[rPsi.SecondLeastValDir]->GetContext()->m_angleByRad;
			//			//Ncpp_ASSERT(secondLeastValAngle >= 0.0f && secondLeastValAngle <= M_PI);
			//			//
			//			//float angle1, angle2, weight1, weight2, normVal1, normVal2;

			//			//if (leastValAngle <= secondLeastValAngle)
			//			//{
			//			//	angle1 = leastValAngle;
			//			//	angle2 = secondLeastValAngle;

			//			//	weight1 = rPsi.SecondLeastVal;
			//			//	weight2 = rPsi.LeastVal;

			//			//	normVal1 = rPsi.NormLeastVal1;
			//			//	normVal2 = rPsi.NormSecondLeastVal;
			//			//}
			//			//else
			//			//{
			//			//	angle1 = secondLeastValAngle;
			//			//	angle2 = leastValAngle;

			//			//	weight1 = rPsi.LeastVal;
			//			//	weight2 = rPsi.SecondLeastVal;

			//			//	normVal1 = rPsi.NormSecondLeastVal;
			//			//	normVal2 = rPsi.NormLeastVal1;
			//			//}

			//			//if ((angle2 - angle1) <= (M_PI / 2))
			//			//{
			//			//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
			//			//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
			//			//		(weight1 * angle1 + weight2 * angle2) /
			//			//		(weight1 + weight2);

			//			//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
			//			//}
			//			//else
			//			//{
			//			//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
			//			//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
			//			//		(weight1 * angle1 + weight2 * (angle2 - M_PI)) /
			//			//		(weight1 + weight2);

			//			//	//angle = (angle <= M_PI) ? angle : (angle + M_PI);
			//			//	angle = (angle >= 0.0f) ? angle : (angle + M_PI);

			//			//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
			//			//}

			//			//normVal = ((weight1 + weight2) < 0.01) ? normVal1 :
			//			//	(weight1 * normVal1 + weight2 * normVal2) / (weight1 + weight2);

			//			////float angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
			//			//angle = ((rPsi.LeastVal + rPsi.SecondLeastVal) < 0.5) ? leastValAngle :
			//			//	(rPsi.SecondLeastVal * leastValAngle + rPsi.LeastVal * secondLeastValAngle) /
			//			//	(rPsi.LeastVal + rPsi.SecondLeastVal);

			//			//if (leastValAngle != secondLeastValAngle && rPsi.NormLeastVal1 > 50.0f)
			//			//{
			//			//	i = i;
			//			//}

			//			// to be removed
			//			angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
			//			Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);

			//			normVal = rPsi.NormLeastVal1;
			//		}


			//		////rDest.val0 = 127 + rPsi.NormLeastVal1 / 2;
			//		//rDest.val0 = 127;
			//		//rDest.val1 = (127 + 127 * cos(angle) * rPsi.NormLeastVal1 * 2 / 3);
			//		//rDest.val2 = (127 + 127 * sin(angle) * rPsi.NormLeastVal1 * 2 / 3);

			//		//rDest_Values = rPsi.NormLeastVal1;

			//		//rColoredDispElm.val0 = 0;
			//		//rColoredDispElm.val0 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;
			//		//rColoredDispElm.val1 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;

			//		//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 2 / 3);
			//		//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 2 / 3);

			//		//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 5 / 3);
			//		//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 5 / 3);

			//		//if (rPsi.LeastVal > 0.5 * rPsi.NormLeastVal1)
			//		if (!rPsi.IsDirClear())
			//			//if (rPsi.LeastVal > 0.8 * rPsi.NormLeastVal1)
			//		{
			//			//	for debug.
			//			if (rPsi.NormLeastVal1 > 120)
			//			{
			//				i = i;
			//			}
			//			rColoredDispElm.val0 = rPsi.NormLeastVal1;
			//			rColoredDispElm.val1 = 0.75 * rPsi.NormLeastVal1;
			//			rColoredDispElm.val2 = 0;
			//		}
			//		//else if (0 == rPsi.LeastValDir)
			//		//{
			//		//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
			//		//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
			//		//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
			//		//}
			//		//else if (1 == rPsi.LeastValDir)
			//		//{
			//		//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
			//		//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
			//		//	rColoredDispElm.val2 = 0;
			//		//}
			//		//else if (3 == rPsi.LeastValDir)
			//		//{
			//		//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
			//		//	rColoredDispElm.val1 = 0;
			//		//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
			//		//}
			//		else
			//		{
			//			rColoredDispElm.val0 = 0;
			//			rColoredDispElm.val1 = (fabs(cos(angle)) * normVal * 5 / 3);
			//			rColoredDispElm.val2 = (fabs(sin(angle)) * normVal * 5 / 3);
			//		}


			//		//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.MaxVal * 5 / 3);
			//		//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.MaxVal * 5 / 3);

			//		//rColoredDispElm.val1 = rPsi.MaxVal;
			//		//rColoredDispElm.val2 = rPsi.MaxVal;

			//		//rColoredDispElm.val1 = rPsi.NormLeastVal1;
			//		//rColoredDispElm.val2 = rPsi.NormLeastVal1;

			//		//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1);
			//		//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1);

			//		////if (0 == rPsi.Dir)
			//		//if (5 == rPsi.Dir)
			//		////if (false)
			//		//{
			//		//	rDest.val0 = rPsi.NormLeastVal1;
			//		//	rDest.val1 = rPsi.NormLeastVal1;
			//		//	rDest.val2 = rPsi.NormLeastVal1;
			//		//}
			//		//else
			//		//{
			//		//	rDest.val0 = 0;
			//		//	rDest.val1 = 0;
			//		//	rDest.val2 = 0;
			//		//}

			//		//rDest.val0 = 127 + rPsi.NormLeastVal1;
			//		//rDest.val1 = 127 + 127 * cos(angle);
			//		//rDest.val2 = 127 + 127 * sin(angle);
			//	}

			//	//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			//	//GlobalStuff::ShowLinePathImg();

			//	//ShowImage(dspImg_Values, "normAvgStandevDirImg_Colored");

			//	ShowImage(dspImg_Colored, "normAvgStandevDirImg_Colored");
			}


		void AngleDirMgrColl::DisplayStandiv2_Dir_Img()
		{
			const ActualArrayAccessor_2D<PixelStandevInfoCmn> & psiAcc = m_context_H->m_standevInfo2CmnImg->GetActualAccessor();
			//const VirtArrayAccessor_2D<PixelStandevInfoCmn> & psiVirtAcc = m_context_H->m_standevInfo2CmnImg->GetVirtAccessor();
			//F32ImageRef dspImg_Values = F32Image::Create(cvSize(psiAcc.GetSize()), 1);

			//const int checkMargin = 70;
			//Window<int> checkWin(checkMargin, psiAcc.GetSize_X() - checkMargin,
			//	checkMargin, psiAcc.GetSize_Y() - checkMargin);


			F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(psiAcc.GetSize()), 3);

			const int nSize_1D = psiAcc.CalcSize_1D();
			ActualArrayAccessor_1D<PixelStandevInfoCmn> psiAcc_1D = psiAcc.GenAcc_1D();
			
			ActualArrayAccessor_1D<F32ColorVal> coloredDispAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			for (int i = 0; i < nSize_1D; i++)
			{
				PixelStandevInfoCmn & rPsi = psiAcc_1D[i];
				
				//	for debug.
				S32Point pnt = psiAcc.CalcPointFromIndex_1D(i);
				//if (S32Point::AreEqual(pnt, S32Point(55, 270)))
				
				//if (S32Point::AreEqual(pnt, S32Point(580, 304)))
				if (S32Point::AreEqual(pnt, S32Point(132, 86)))
				{
					i = i;
				}

				//if (S32Point::AreEqual(pnt, S32Point(576, 312)))
				//if (S32Point::AreEqual(pnt, S32Point(356, 238)))
				if (S32Point::AreEqual(pnt, S32Point(359, 232)))
				{
					i = i;
				}


				//const bool isPntInCheckWindow = pnt.IsInWindow(checkWin);
				//Ncpp_ASSERT(!isPntInCheckWindow || (isPntInCheckWindow && 150 == rPsi.NormLeastVal1));
				
				F32ColorVal & rColoredDispElm = coloredDispAcc_1D[i];

				if (IsUndefined(rPsi))
				{
					//rColoredDispElm.val0 = 0;
					rColoredDispElm.val0 = 254;
					rColoredDispElm.val1 = 254;
					rColoredDispElm.val2 = 254;
					
					continue;
				}

				//Ncpp_ASSERT(-1 != rPsi.Dir);
				//Ncpp_ASSERT(rPsi.Dir >= 0);
				
				Ncpp_ASSERT(rPsi.LeastValDir >= 0);
				Ncpp_ASSERT(rPsi.SecondLeastValDir >= 0);

				//float angle = m_angleDirMgrArr[rPsi.Dir]->GetContext()->m_angleByRad;
		
				float angle, normVal;
				{
					//const float leastValAngle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(leastValAngle >= 0.0f && leastValAngle <= M_PI);

					//const float secondLeastValAngle = m_angleDirMgrArr[rPsi.SecondLeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(secondLeastValAngle >= 0.0f && secondLeastValAngle <= M_PI);
					//
					//float angle1, angle2, weight1, weight2, normVal1, normVal2;

					//if (leastValAngle <= secondLeastValAngle)
					//{
					//	angle1 = leastValAngle;
					//	angle2 = secondLeastValAngle;

					//	weight1 = rPsi.SecondLeastVal;
					//	weight2 = rPsi.LeastVal;

					//	normVal1 = rPsi.NormLeastVal1;
					//	normVal2 = rPsi.NormSecondLeastVal;
					//}
					//else
					//{
					//	angle1 = secondLeastValAngle;
					//	angle2 = leastValAngle;

					//	weight1 = rPsi.LeastVal;
					//	weight2 = rPsi.SecondLeastVal;

					//	normVal1 = rPsi.NormSecondLeastVal;
					//	normVal2 = rPsi.NormLeastVal1;
					//}

					//if ((angle2 - angle1) <= (M_PI / 2))
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * angle2) /
					//		(weight1 + weight2);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}
					//else
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * (angle2 - M_PI)) /
					//		(weight1 + weight2);

					//	//angle = (angle <= M_PI) ? angle : (angle + M_PI);
					//	angle = (angle >= 0.0f) ? angle : (angle + M_PI);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}

					//normVal = ((weight1 + weight2) < 0.01) ? normVal1 :
					//	(weight1 * normVal1 + weight2 * normVal2) / (weight1 + weight2);

					////float angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					//angle = ((rPsi.LeastVal + rPsi.SecondLeastVal) < 0.5) ? leastValAngle :
					//	(rPsi.SecondLeastVal * leastValAngle + rPsi.LeastVal * secondLeastValAngle) /
					//	(rPsi.LeastVal + rPsi.SecondLeastVal);

					//if (leastValAngle != secondLeastValAngle && rPsi.NormLeastVal1 > 50.0f)
					//{
					//	i = i;
					//}

					// to be removed
					angle = m_angleDirMgrArr[rPsi.LeastValDir]->GetContext()->m_angleByRad;
					Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);

					normVal = rPsi.NormLeastVal1;
				}


				////rDest.val0 = 127 + rPsi.NormLeastVal1 / 2;
				//rDest.val0 = 127;
				//rDest.val1 = (127 + 127 * cos(angle) * rPsi.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (127 + 127 * sin(angle) * rPsi.NormLeastVal1 * 2 / 3);

				//rDest_Values = rPsi.NormLeastVal1;

				//rColoredDispElm.val0 = 0;
				//rColoredDispElm.val0 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;
				//rColoredDispElm.val1 = (rPsi.NormLeastVal1 > 0.1) ? rPsi.LeastVal * 255 / rPsi.NormLeastVal1 : 0;

				//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 2 / 3);

				//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1 * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1 * 5 / 3);

				//if (rPsi.LeastVal > 0.5 * rPsi.NormLeastVal1)
				//if (!rPsi.IsDirClear())
				if (false && !rPsi.IsDirClear())
				//if (rPsi.LeastVal > 0.8 * rPsi.NormLeastVal1)
				{
					//	for debug.
					if (rPsi.NormLeastVal1 > 120)
					{
						i = i;
					}
					rColoredDispElm.val0 = rPsi.NormLeastVal1;
					rColoredDispElm.val1 = 0.75 * rPsi.NormLeastVal1;
					rColoredDispElm.val2 = 0;
				}
				//else if (0 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
				//}
				//else if (1 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val2 = 0;
				//}
				//else if (3 == rPsi.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rPsi.NormLeastVal1;
				//	rColoredDispElm.val1 = 0;
				//	rColoredDispElm.val2 = rPsi.NormLeastVal1;
				//}
				else
				{

					//rColoredDispElm.val0 = 0;
					rColoredDispElm.val0 = rPsi.LeastVal;

					rColoredDispElm.val1 = rPsi.NormLeastVal1;
					rColoredDispElm.val2 = rPsi.NormLeastVal2;

					//rColoredDispElm.val1 = (fabs(cos(angle)) * normVal * 5 / 3);
					//rColoredDispElm.val2 = (fabs(sin(angle)) * normVal * 5 / 3);
				}


				//rColoredDispElm.val1 = (fabs(cos(angle)) * rPsi.MaxVal * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rPsi.MaxVal * 5 / 3);

				//rColoredDispElm.val1 = rPsi.MaxVal;
				//rColoredDispElm.val2 = rPsi.MaxVal;

				//rColoredDispElm.val1 = rPsi.NormLeastVal1;
				//rColoredDispElm.val2 = rPsi.NormLeastVal1;

				//rDest.val1 = (fabs(cos(angle)) * rPsi.NormLeastVal1);
				//rDest.val2 = (fabs(sin(angle)) * rPsi.NormLeastVal1);

				////if (0 == rPsi.Dir)
				//if (5 == rPsi.Dir)
				////if (false)
				//{
				//	rDest.val0 = rPsi.NormLeastVal1;
				//	rDest.val1 = rPsi.NormLeastVal1;
				//	rDest.val2 = rPsi.NormLeastVal1;
				//}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}

				//rDest.val0 = 127 + rPsi.NormLeastVal1;
				//rDest.val1 = 127 + 127 * cos(angle);
				//rDest.val2 = 127 + 127 * sin(angle);
			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			GlobalStuff::SetLinePathImg(dspImg_Colored);
			GlobalStuff::ShowLinePathImg();

			//ShowImage(dspImg_Values, "standev2DirImg_Colored");
			
			ShowImage(dspImg_Colored, "standev2DirImg_Colored");
		}


		void AngleDirMgrColl::DisplayBidiffInfo_Dir_Img()
		{
			const ActualArrayAccessor_2D<BidiffInfoCommon> & bdcAcc = m_context_H->m_bidiffInfoCommonImg->GetActualAccessor();
			
			//F32ImageRef dspImg_Values = F32Image::Create(cvSize(bdcAcc.GetSize()), 1);

			//const int checkMargin = 70;
			//Window<int> checkWin(checkMargin, bdcAcc.GetSize_X() - checkMargin,
			//	checkMargin, bdcAcc.GetSize_Y() - checkMargin);


			F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(bdcAcc.GetSize()), 3);

			const int nSize_1D = bdcAcc.CalcSize_1D();
			ActualArrayAccessor_1D<BidiffInfoCommon> bdcAcc_1D = bdcAcc.GenAcc_1D();

			ActualArrayAccessor_1D<F32ColorVal> coloredDispAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			for (int i = 0; i < nSize_1D; i++)
			{
				BidiffInfoCommon & rBdc = bdcAcc_1D[i];

				S32Point pnt = bdcAcc.CalcPointFromIndex_1D(i);
				//if (S32Point::AreEqual(pnt, S32Point(55, 270)))

				//if (S32Point::AreEqual(pnt, S32Point(580, 304)))
				if (S32Point::AreEqual(pnt, S32Point(132, 86)))
				{
					i = i;
				}

				//if (S32Point::AreEqual(pnt, S32Point(576, 312)))
				//if (S32Point::AreEqual(pnt, S32Point(356, 238)))
				if (S32Point::AreEqual(pnt, S32Point(359, 232)))
				{
					i = i;
				}


				//const bool isPntInCheckWindow = pnt.IsInWindow(checkWin);
				//Ncpp_ASSERT(!isPntInCheckWindow || (isPntInCheckWindow && 150 == rBdc.NormLeastVal1));

				F32ColorVal & rColoredDispElm = coloredDispAcc_1D[i];

				if (IsUndefined(rBdc))
				{
					//rColoredDispElm.val0 = 0;
					rColoredDispElm.val0 = 254;
					rColoredDispElm.val1 = 254;
					rColoredDispElm.val2 = 254;

					continue;
				}

				//Ncpp_ASSERT(-1 != rBdc.Dir);
				//Ncpp_ASSERT(rBdc.Dir >= 0);

				Ncpp_ASSERT(rBdc.LeastValDir >= 0);
				Ncpp_ASSERT(rBdc.SecondLeastValDir >= 0);

				//float angle = m_angleDirMgrArr[rBdc.Dir]->GetContext()->m_angleByRad;

				float angle, normVal;
				{
					//const float leastValAngle = m_angleDirMgrArr[rBdc.LeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(leastValAngle >= 0.0f && leastValAngle <= M_PI);

					//const float secondLeastValAngle = m_angleDirMgrArr[rBdc.SecondLeastValDir]->GetContext()->m_angleByRad;
					//Ncpp_ASSERT(secondLeastValAngle >= 0.0f && secondLeastValAngle <= M_PI);
					//
					//float angle1, angle2, weight1, weight2, normVal1, normVal2;

					//if (leastValAngle <= secondLeastValAngle)
					//{
					//	angle1 = leastValAngle;
					//	angle2 = secondLeastValAngle;

					//	weight1 = rBdc.SecondLeastVal;
					//	weight2 = rBdc.LeastVal;

					//	normVal1 = rBdc.NormLeastVal1;
					//	normVal2 = rBdc.NormSecondLeastVal;
					//}
					//else
					//{
					//	angle1 = secondLeastValAngle;
					//	angle2 = leastValAngle;

					//	weight1 = rBdc.LeastVal;
					//	weight2 = rBdc.SecondLeastVal;

					//	normVal1 = rBdc.NormSecondLeastVal;
					//	normVal2 = rBdc.NormLeastVal1;
					//}

					//if ((angle2 - angle1) <= (M_PI / 2))
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * angle2) /
					//		(weight1 + weight2);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}
					//else
					//{
					//	//angle = ((weight1 + weight2) < 0.5) ? leastValAngle :
					//	angle = ((weight1 + weight2) < 0.01) ? leastValAngle :
					//		(weight1 * angle1 + weight2 * (angle2 - M_PI)) /
					//		(weight1 + weight2);

					//	//angle = (angle <= M_PI) ? angle : (angle + M_PI);
					//	angle = (angle >= 0.0f) ? angle : (angle + M_PI);

					//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);
					//}

					//normVal = ((weight1 + weight2) < 0.01) ? normVal1 :
					//	(weight1 * normVal1 + weight2 * normVal2) / (weight1 + weight2);

					////float angle = m_angleDirMgrArr[rBdc.LeastValDir]->GetContext()->m_angleByRad;
					//angle = ((rBdc.LeastVal + rBdc.SecondLeastVal) < 0.5) ? leastValAngle :
					//	(rBdc.SecondLeastVal * leastValAngle + rBdc.LeastVal * secondLeastValAngle) /
					//	(rBdc.LeastVal + rBdc.SecondLeastVal);

					//if (leastValAngle != secondLeastValAngle && rBdc.NormLeastVal1 > 50.0f)
					//{
					//	i = i;
					//}

					// to be removed
					angle = m_angleDirMgrArr[rBdc.LeastValDir]->GetContext()->m_angleByRad;
					Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);

					normVal = rBdc.NormLeastVal1;
				}


				////rDest.val0 = 127 + rBdc.NormLeastVal1 / 2;
				//rDest.val0 = 127;
				//rDest.val1 = (127 + 127 * cos(angle) * rBdc.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (127 + 127 * sin(angle) * rBdc.NormLeastVal1 * 2 / 3);

				//rDest_Values = rBdc.NormLeastVal1;

				//rColoredDispElm.val0 = 0;
				//rColoredDispElm.val0 = (rBdc.NormLeastVal1 > 0.1) ? rBdc.LeastVal * 255 / rBdc.NormLeastVal1 : 0;
				//rColoredDispElm.val1 = (rBdc.NormLeastVal1 > 0.1) ? rBdc.LeastVal * 255 / rBdc.NormLeastVal1 : 0;

				//rDest.val1 = (fabs(cos(angle)) * rBdc.NormLeastVal1 * 2 / 3);
				//rDest.val2 = (fabs(sin(angle)) * rBdc.NormLeastVal1 * 2 / 3);

				//rColoredDispElm.val1 = (fabs(cos(angle)) * rBdc.NormLeastVal1 * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rBdc.NormLeastVal1 * 5 / 3);

				if (
					//rBdc.LeastVal > 0.5 * rBdc.NormLeastVal1 ||
					//rBdc.NormDiff2LeastVal < 0.5 * rBdc.NormLeastVal1)
					//rBdc.NormDiff2LeastVal < 0.3 * rBdc.NormLeastVal1)
					
					!rBdc.IsEdge)
					//if (rBdc.LeastVal > 0.8 * rBdc.NormLeastVal1)
				{
					if (rBdc.NormLeastVal1 > 70)
					{
						i = i;
					}
					rColoredDispElm.val0 = rBdc.NormLeastVal1;
					rColoredDispElm.val1 = 0;
					rColoredDispElm.val2 = 0;
				}
				//else if (0 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val2 = rBdc.NormLeastVal1;
				//}
				//else if (1 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val2 = 0;
				//}
				//else if (3 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = 0;
				//	rColoredDispElm.val2 = rBdc.NormLeastVal1;
				//}
				else
				{
					rColoredDispElm.val0 = 0;
					rColoredDispElm.val1 = (fabs(cos(angle)) * normVal * 5 / 3);
					rColoredDispElm.val2 = (fabs(sin(angle)) * normVal * 5 / 3);
				}


				//rColoredDispElm.val1 = (fabs(cos(angle)) * rBdc.MaxVal * 5 / 3);
				//rColoredDispElm.val2 = (fabs(sin(angle)) * rBdc.MaxVal * 5 / 3);

				//rColoredDispElm.val1 = rBdc.MaxVal;
				//rColoredDispElm.val2 = rBdc.MaxVal;

				//rColoredDispElm.val1 = rBdc.NormLeastVal1;
				//rColoredDispElm.val2 = rBdc.NormLeastVal1;

				//rDest.val1 = (fabs(cos(angle)) * rBdc.NormLeastVal1);
				//rDest.val2 = (fabs(sin(angle)) * rBdc.NormLeastVal1);

				////if (0 == rBdc.Dir)
				//if (5 == rBdc.Dir)
				////if (false)
				//{
				//	rDest.val0 = rBdc.NormLeastVal1;
				//	rDest.val1 = rBdc.NormLeastVal1;
				//	rDest.val2 = rBdc.NormLeastVal1;
				//}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}

				//rDest.val0 = 127 + rBdc.NormLeastVal1;
				//rDest.val1 = 127 + 127 * cos(angle);
				//rDest.val2 = 127 + 127 * sin(angle);
			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			//GlobalStuff::ShowLinePathImg();

			//ShowImage(dspImg_Values, "bidiffCommonImg_Colored");

			ShowImage(dspImg_Colored, "bidiffCommonImg_Colored");
		}


		void AngleDirMgrColl::DisplayImgForEdges()
		{
			const ActualArrayAccessor_2D<BidiffInfoCommon> & bdcAcc = m_context_H->m_bidiffInfoCommonImg->GetActualAccessor();
			const ActualArrayAccessor_2D<F32ColorVal> & orgAcc = m_context_H->m_org_Img->GetActualAccessor();

			//F32ImageRef dspImg_Values = F32Image::Create(cvSize(bdcAcc.GetSize()), 1);

			//const int checkMargin = 70;
			//Window<int> checkWin(checkMargin, bdcAcc.GetSize_X() - checkMargin,
			//	checkMargin, bdcAcc.GetSize_Y() - checkMargin);


			F32ImageRef dspImg_Colored = F32Image::Create(toCvSize(bdcAcc.GetSize()), 3);

			const int nSize_1D = bdcAcc.CalcSize_1D();
			ActualArrayAccessor_1D<BidiffInfoCommon> bdcAcc_1D = bdcAcc.GenAcc_1D();
			ActualArrayAccessor_1D<F32ColorVal> orgAcc_1D = orgAcc.GenAcc_1D();

			ActualArrayAccessor_1D<F32ColorVal> coloredDispAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			for (int i = 0; i < nSize_1D; i++)
			{
				BidiffInfoCommon & rBdc = bdcAcc_1D[i];
				F32ColorVal & rOrg = orgAcc_1D[i];

				S32Point pnt = bdcAcc.CalcPointFromIndex_1D(i);
				//if (S32Point::AreEqual(pnt, S32Point(55, 270)))

				//if (S32Point::AreEqual(pnt, S32Point(580, 304)))
				//if (S32Point::AreEqual(pnt, S32Point(132, 86)))
				if (S32Point::AreEqual(pnt, S32Point(538, 282)))
				{
					i = i;
				}


				//if (S32Point::AreEqual(pnt, S32Point(576, 312)))
				if (S32Point::AreEqual(pnt, S32Point(539, 282)))
				{
					i = i;
				}


				//const bool isPntInCheckWindow = pnt.IsInWindow(checkWin);
				//Ncpp_ASSERT(!isPntInCheckWindow || (isPntInCheckWindow && 150 == rBdc.NormLeastVal1));

				F32ColorVal & rColoredDispElm = coloredDispAcc_1D[i];

				if (IsUndefined(rBdc))
				{
					//rColoredDispElm.val0 = 0;
					rColoredDispElm.val0 = 254;
					rColoredDispElm.val1 = 254;
					rColoredDispElm.val2 = 0;

					continue;
				}

				//if (S32Point::AreEqual(pnt, S32Point(539, 282)))
				//{
				//	rColoredDispElm.val0 = 0;
				//	rColoredDispElm.val1 = 135;
				//	rColoredDispElm.val2 = 255;

				//	continue;
				//}



				//Ncpp_ASSERT(-1 != rBdc.Dir);
				//Ncpp_ASSERT(rBdc.Dir >= 0);

				Ncpp_ASSERT(rBdc.LeastValDir >= 0);
				Ncpp_ASSERT(rBdc.SecondLeastValDir >= 0);

				////float angle = m_angleDirMgrArr[rBdc.Dir]->GetContext()->m_angleByRad;

				//float angle, normVal;
				//{

				//	// to be removed
				//	angle = m_angleDirMgrArr[rBdc.LeastValDir]->GetContext()->m_angleByRad;
				//	Ncpp_ASSERT(angle >= 0.0f && angle <= M_PI);

				//	normVal = rBdc.NormLeastVal1;
				//}



				if (rBdc.IsEdge)
					//if (rBdc.LeastVal > 0.8 * rBdc.NormLeastVal1)
				{
					rColoredDispElm = rOrg;

					//if (rBdc.NormLeastVal1 > 70)
					//{
					//	i = i;
					//}
					//rColoredDispElm.val0 = rBdc.NormLeastVal1;
					//rColoredDispElm.val1 = 0;
					//rColoredDispElm.val2 = 0;
				}
				//else if (0 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val2 = rBdc.NormLeastVal1;
				//}
				//else if (1 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val2 = 0;
				//}
				//else if (3 == rBdc.LeastValDir)
				//{
				//	rColoredDispElm.val0 = rBdc.NormLeastVal1;
				//	rColoredDispElm.val1 = 0;
				//	rColoredDispElm.val2 = rBdc.NormLeastVal1;
				//}
				else
				{
					rColoredDispElm.val0 = 128;
					rColoredDispElm.val1 = 58;
					rColoredDispElm.val2 = 128;
				}

			}

			//GlobalStuff::SetLinePathImg(GenTriChGrayImg(dspImg_Values));
			//GlobalStuff::ShowLinePathImg();

			//ShowImage(dspImg_Values, "bidiffCommonImg_Colored");

			ShowImage(dspImg_Colored, "imgForEdges");
		}


		void AngleDirMgrColl::DisplayConflictImg()
		{
			const ActualArrayAccessor_2D<ConflictInfo2_Ex> & confAcc = m_context_H->m_conflictInfoImg->GetActualAccessor();
			F32ImageRef confDsp_Img = F32Image::Create(toCvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			//ActualArrayAccessor_1D<ConflictInfo2_Ex> confAcc_1D = confAcc.GenAcc_1D();
			
			ActualArrayAccessor_2D<F32ColorVal> destAcc((F32ColorVal *)confDsp_Img->GetDataPtr(), size_2D(confDsp_Img->GetSize()));
			ActualArrayAccessor_1D<F32ColorVal> destAcc_1D = destAcc.GenAcc_1D();
			
			//ActualArrayAccessor_1D<F32ColorVal> destAcc_1D((F32ColorVal *)dspImg_Colored->GetDataPtr(), dspImg_Colored->GetSize1D());

			ActualArrayAccessor_1D<ConflictInfo2_Ex> srcAcc_1D = confAcc.GenAcc_1D();

			//	for debug.
			S32Point dbgCenter_Pnt(0, 0), dbgSide1_Pnt(0, 0), dbgSide2_Pnt(0, 0);

			for (int i = 0; i < srcAcc_1D.GetSize(); i++)
			{
				ConflictInfo2_Ex & rSrc = srcAcc_1D[i];
				AssertValue(rSrc);
				F32ColorVal & rDest = destAcc_1D[i];


				//Ncpp_ASSERT(-1 != rSrc.Dir);

				if (rSrc.Exists)
				{
					//	for debug.
					if (1 != rSrc.Dir)
					{
						i = i;
					}

					F32ColorVal & rDest_Side_1 = destAcc_1D[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = destAcc_1D[rSrc.Offset_Side_2];

					//	for debug.
					S32Point side1_Pnt = confAcc.CalcPointFromIndex_1D(rSrc.Offset_Side_1);
					S32Point side2_Pnt = confAcc.CalcPointFromIndex_1D(rSrc.Offset_Side_2);

					//	for debug.
					//S32Point testPnt(470, 182);
					//S32Point testPnt(415, 352);
					//S32Point testPnt(415, 352);
					//S32Point testPnt(225, 333);
					//S32Point testPnt(528, 225);
					//S32Point testPnt(353, 84);
					//S32Point testPnt(353, 63);
					S32Point testPnt(500, 444);
					if (S32Point::AreEqual(side1_Pnt, testPnt) ||
						S32Point::AreEqual(side2_Pnt, testPnt)
						)
					{
						dbgCenter_Pnt = confAcc.CalcPointFromIndex_1D(i);
						dbgSide1_Pnt = side1_Pnt;
						dbgSide2_Pnt = side2_Pnt;
					}

					rDest.val0 = 0;
					rDest.val1 = 70;
					rDest.val2 = 155;

					//rDest_Side_1.val0 = 0;
					//rDest_Side_1.val1 = 155;
					//rDest_Side_1.val2 = 0;

					//rDest_Side_2.val0 = 0;
					//rDest_Side_2.val1 = 155;
					//rDest_Side_2.val2 = 0;
				}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}

			}	//	end i for.



			{
				F32ColorVal & rDest = destAcc.GetAt(dbgCenter_Pnt.GetX(), dbgCenter_Pnt.GetY());
				F32ColorVal & rDest_Side_1 = destAcc.GetAt(dbgSide1_Pnt.GetX(), dbgSide1_Pnt.GetY());
				F32ColorVal & rDest_Side_2 = destAcc.GetAt(dbgSide2_Pnt.GetX(), dbgSide2_Pnt.GetY());

				rDest.val0 = 255;
				rDest.val1 = 255;
				rDest.val2 = 0;

				//rDest_Side_1.val0 = 0;
				//rDest_Side_1.val1 = 128;
				//rDest_Side_1.val2 = 255;

				//rDest_Side_2.val0 = 0;
				//rDest_Side_2.val1 = 128;
				//rDest_Side_2.val2 = 255;
			}


			//GlobalStuff::SetLinePathImg(confDsp_Img);
			//GlobalStuff::ShowLinePathImg();

			//ShowImage(confDsp_Img, "confDsp_Img->GetSrcImg()");
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

